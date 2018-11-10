/*===[[ START ]]==============================================================*/
#include  "yLOG.h"

#include  <stdio.h>
#include  <stdlib.h>                  /* getenv()                            */
#include  <string.h>
#include  <ctype.h>
#include  <time.h>              /* clock, time                                */
#include  <sys/time.h>          /* gettimeofday                               */
#include  <sys/unistd.h>        /* gethostname, getpid, getppid               */
#include  <stdarg.h>                   /* va_arg                              */
#include  <ySTR.h>

/*-> to support the 'uname' call to get machine and system names  */
#include  <sys/utsname.h>

#define     LEN_PREFIX       100

#define           LOGDIR     "/var/log/yLOG/"
#define           HISDIR     "/var/log/yLOG.historical/"
#define           ROOTDIR    "/"

typedef struct tm   tTIME;

static char      its_prog [30];       /* program name                         */
static FILE     *its_log;             /* file to receive logging messages     */
static char      its_core;            /* log core heatherly libraries or skip */
llong            its_wall_start;      /* start wall msec time                 */
static int       its_count;           /* message count                        */
static int       its_indent;          /* level of indent (0 - 9)              */
static char      its_prefix [LEN_PREFIX];    /* actual indent text (of spaces)       */

#define   MSG_LEN      200
static char      _text      [MSG_LEN];
static char      its_msg    [MSG_LEN];
static char      its_single [MSG_LEN];
static char      its_quiet;

static int       its_header = 11;      /* count of lines in header            */
static int       its_nsyncs = 0;       /* count of sync calls                 */

static char      filename   [500] = "stdout";

static char      yLOG_ver [200] = "";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yLOG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strlcpy (t, "[hephaestus ]", 18);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (yLOG_ver, 100, "%s   %s : %s", t, YLOG_VER_NUM, YLOG_VER_TXT);
   return yLOG_ver;
}


/*====================------------------------------------====================*/
/*===----                             driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;}

llong
yLOG__timestamp(void)             /* PURPOSE : timestamp in milliseconds      */
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   llong            tint = 0;
   struct timespec  tv;
   clock_gettime (CLOCK_MONOTONIC, &tv);
   tint += (llong) tv.tv_sec  * 1000;
   tint += (llong) tv.tv_nsec / 1000000;
   return tint;
}

static char
ylog__prefix            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(standard prefix)----------------*/
   strlcpy (its_prefix, "", LEN_PREFIX);
   for (i = 0; i <  its_indent; ++i   )  strlcat (its_prefix, "Ï··", LEN_PREFIX);
   /*---(add marks every third)----------*/
   for (i = 2; i <  its_indent; i += 3)  its_prefix [i * 3] = '+';
   /*---(clear just before entry)--------*/
   its_prefix [its_indent * 3 - 1] = ' ';
   its_prefix [its_indent * 3 - 2] = ' ';
   /*---(complete)-----------------------*/
   return 0;
}

static void             /* PURPOSE : write a message to the log file          */
yLOG__main(
      char     a_change,     /* type of change to indentation                 */
      char     a_level,      /* type of message                               */
      char    *a_message)    /* actual message text                           */
{
   /*===[[ design notes ]]====================================================#
    *   - writes a log message to the log file, no matter what
    *   - always flush buffer so message exists even in catastrophic failure
    *   - data will be fixed as a partial message is better than none
    *   - calls to log are done through specializers (this function is private)
    *   - the pCHG and pLVL standards are defined in the file header
    *=========================================================================*/
   /*---(locals)-----------+-----+-----+-*/
   llong       _wall;                            /* timestamp                 */
   /*---(first, defense)-----------------*/
   if (a_change != '<' && a_change != '>' && a_change != '-')
      a_change = '?';
   /*> if (strchr ("sixt>", a_level) == NULL)  a_level  = '?';                        <*/
   /*---(exdent, if needed)--------------*/
   if (a_change == '<' && its_indent > 0) {
      its_indent--;
      ylog__prefix ();
   }
   /*---(get wall time)----------------*/
   _wall  = yLOG__timestamp() - its_wall_start;
   /*---(update count)-------------------*/
   its_count++;
   /*---(log)----------------------------*/
   /*> fprintf(its_log, "%8lld %4d [%c] %s%s\n", _wall % 100000000,                   <* 
    *>       its_count % 10000, a_level, its_prefix, a_message);                      <*/
   fprintf(its_log, "%7lld.%03lld %6d [%c] %s%s\n",
         (_wall / 1000) % 10000000, _wall % 1000,
         its_count % 1000000, a_level, its_prefix, a_message);
   fflush(its_log);
   /*---(indent, if needed)--------------*/
   if (a_change == '>') {
      its_indent++;
      ylog__prefix ();
   }
   /*---(complete)-----------------------*/
   return;
}



/*====================------------------------------------====================*/
/*===----                        begin and end                         ----===*/
/*====================------------------------------------====================*/
static void      o___BOOKENDS________________o (void) {;}

int        /*----: initialize logger and log header info ---------------------*/
yLOG_begin         (cchar *a_program, cchar a_location, cchar a_quiet)
{
   /*---(locals)-------------------------*/
   time_t    time_date;
   tTIME    *curr_time = NULL;
   char      _prog[50] = "________________________________________________";
   int       i    = 0;                       /* loop iterator                 */
   char      _prefix[20];
   char      _suffix[20];
   /*---(defense)------------------------*/
   if (a_quiet == 0) its_quiet = a_quiet;
   else              its_quiet = 1;
   if (its_quiet) return 1;
   /*---(initialize class variables)-----*/
   its_count  = 0;
   its_indent = 0;
   strcpy(its_prefix, "");
   /*---(get the date)-------------------*/
   time_date = time(NULL);
   curr_time = localtime(&time_date);
   /*---(open the log file)--------------*/
   if (a_location == yLOG_STDOUT) {
      its_log = stdout;
   } else {
      for (i = 0; i < 30; ++i) {
         if (a_program[i] == '\0') break;
         if ((  a_program[i] >= 'A' && a_program[i] <= 'Z') ||
               (a_program[i] >= 'a' && a_program[i] <= 'z') ||
               (a_program[i] >= '0' && a_program[i] <= '9')) {
            _prog[i] = a_program[i];
            continue;
         }
         _prog[i] = '_';
      }
      strftime(_prefix, 20, "%y.%m.%d.%H.%M.%S", curr_time);
      strftime(_suffix, 20, "%U",                curr_time);
      if (a_location == yLOG_SYSTEM) {
         snprintf(filename, 500, "%s%s.%-25.25s.%s.ulog", LOGDIR, _prefix, _prog, _suffix);
      } else if (a_location == yLOG_HISTORICAL) {
         snprintf(filename, 500, "%s%s.%-25.25s.%s.ulog", HISDIR, _prefix, _prog, _suffix);
      } else if (a_location == yLOG_ROOT      ) {
         snprintf(filename, 500, "%s%s.%-25.25s.%s.ulog", ROOTDIR, _prefix, _prog, _suffix);
      } else {  /* default is personal log file */
         snprintf(filename, 500, "%s/l_hlisda/%s.%-25.25s.%s.ulog", getenv("HOME"), _prefix, _prog, _suffix);
      }
      its_log = fopen (filename, "w");
      if (its_log == NULL) {
         printf ("FATAL, can not open logger\n");
         return -1;
      }
   }
   strlcpy (its_prog, a_program, 29);
   /*---(get wall time)------------------*/
   its_wall_start = yLOG__timestamp();
   /*---(display)------------------------*/
   fprintf(its_log, "heatherly program logger================================================begin===\n");
   gethostname(_text, 50);
   fprintf(its_log, "   host       : %s\n",    _text);
   getlogin_r(_text, 50);
   fprintf(its_log, "   user       : %s\n",    _text);
   fprintf(its_log, "   program    : %s\n",    a_program);
   fprintf(its_log, "   pid        : %06i\n",  getpid());
   fprintf(its_log, "   start date : %s",      asctime(curr_time));
   fprintf(its_log, "   start (ms) : %lld\n",  its_wall_start);
   fprintf(its_log, "   log file   : %s\n",    filename);
   fprintf(its_log, "   log core   : %s\n",    "false");
   fprintf(its_log, "================================================================================\n");
   fprintf(its_log, "secs---.-ms -step- lvl ---comment-----------------------------------------------\n");
   yLOG_note("logger loaded");
   /*---(complete)-----------------------*/
   return fileno (its_log);
}

int yLOG_lognum          (void) { return fileno (its_log); }

void                    /* PURPOSE : log footer and close logger              */
yLOG_end      (void)
{
   if (its_quiet) return;
   /*---(get the date)---------------------------*/
   time_t      time_date = time(NULL);
   struct tm*  curr_time = localtime(&time_date);
   /*---(get wall time)----------------*/
   llong _wall = yLOG__timestamp();
   long  _elap = _wall - its_wall_start;
   long  _sec  = _elap / 1000;
   long  _hrs  = _sec / 3600;
   _sec -= _hrs * 3600;
   long  _min  = _sec / 60;
   _sec -= _min * 60;
   /*---(display end)------------------*/
   yLOG_note("logger stopped");
   fprintf(its_log, "secs---.-ms -step- lvl ---comment-----------------------------------------------\n");
   fprintf(its_log, "================================================================================\n");
   fprintf(its_log, "   end date   : %s",      asctime(curr_time));
   fprintf(its_log, "   end (ms)   : %lld\n",  _wall);
   fprintf(its_log, "   dur (ms)   : %lld\n",  _wall - its_wall_start);
   fprintf(its_log, "   duration   : %2ldh, %2ldm, %2lds\n", _hrs, _min, _sec);
   fprintf(its_log, "==========================================================================end===\n");
   fclose (its_log);
   its_quiet = 1;
   return;
}


/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

void
yLOG_enter    (const char *a_func)
{
   if (its_quiet) return;
   snprintf (its_msg, MSG_LEN, "ENTERING (%.30s)", a_func);
   yLOG__main ('>', 's', its_msg);
   return;
}

void
yLOG_exit     (const char *a_func)
{
   if (its_quiet) return;
   snprintf (its_msg, MSG_LEN, "EXITING  (%.30s)", a_func);
   yLOG__main ('<', 's', its_msg);
   return;
}

void
yLOG_exitr    (const char *a_func, const int a_rce)
{
   if (its_quiet) return;
   snprintf (its_msg, MSG_LEN, "WARNING, rce (%d)", a_rce);
   yLOG__main ('-', 'w', its_msg);
   snprintf (its_msg, MSG_LEN, "EXITING  (%.30s)", a_func);
   yLOG__main ('<', 's', its_msg);
   return;
}


/*====================------------------------------------====================*/
/*===----                        separators                            ----===*/
/*====================------------------------------------====================*/
static void      o___SEPARATORS______________o (void) {;}

void
yLOG_sync     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        cmd         [1000] = "";
   /*---(defense: quiet mode)------------*/
   if (its_quiet) return;
   /*---(output line)--------------------*/
   fprintf (its_log, "SYNC======= ====== === %s%s\n", its_prefix,
         "============================================================");
   /*---(update)-------------------------*/
   ++its_nsyncs;
   if (its_nsyncs == 1)  return;
   /*---(close log)----------------------*/
   fclose (its_log);
   /*---(trim)---------------------------*/
   snprintf (cmd, 950, "cat %s | head -n $(grep -n \"^SYNC=====\" %s | head -n 1 | cut -d: -f 1) > temp.ulog", filename, filename);
   system (cmd);
   snprintf (cmd, 950, "rm -f %s", filename);
   system (cmd);
   snprintf (cmd, 950, "mv -f temp.ulog %s", filename);
   system (cmd);
   /*---(reopen)-------------------------*/
   its_log = fopen(filename, "a");
   if (its_log == NULL) {
      printf ("FATAL, can not open logger\n");
      return -1;
   }
   /*---(complete)-----------------------*/
   return;
}

llong
yLOG_time     (void)
{
   return yLOG__timestamp();
}

void
yLOG_break    (void)
{
   if (its_quiet) return;
   fprintf (its_log, "------- --- ------ --- %s%s\n", its_prefix,
         "---------------------------------------------------------");
   return;
}

void
yLOG_unitcond (int a_scrp, int a_cond, int a_line, char *a_desc)
{
   if (its_quiet) return;
   fprintf (its_log, "unit=== === ====== [t] %s%s\n", its_prefix,
         "=========================================================");
   snprintf   (its_msg, 190, "COND %2.2d.%3.3d.-- at %5d, %s", a_scrp, a_cond, a_line, a_desc);
   yLOG__main ('-', 't', its_msg);
   return;
}

void
yLOG_unitstep (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (its_quiet) return;
   fprintf (its_log, "unit--- --- ------ [t] %s%s\n", its_prefix,
         "---------------------------------------------------------");
   snprintf   (its_msg, 190, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   yLOG__main ('-', 't', its_msg);
   return;
}

void
yLOG_unitdone (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (its_quiet) return;
   fprintf (its_log, "unit--- --- ------ [t] %s%s\n", its_prefix,
         "---------------------------------------------------------");
   snprintf   (its_msg, 190, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   yLOG__main ('-', 't', its_msg);
   return;
}


/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES________________o (void) {;}

void
yLOG_note          (const char *a_info)
{
   if (its_quiet) return;
   snprintf(its_msg, 190, "%.150s...", a_info);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_info          (const char *a_subject, const char *a_info)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %.150s", a_subject, a_info);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_delim         (const char *a_subject, const char *a_info)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: <<%.50s>>", a_subject, a_info);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_char          (const char *a_subject, const char a_char)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %c", a_subject, (unsigned char) chrvisible (a_char));
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_value         (const char *a_subject, const int a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %d", a_subject, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_hex           (const char *a_subject, const int a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: 0x%08x", a_subject, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_llong         (const char *a_subject, const long long a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %lld", a_subject, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_double        (const char *a_subject, const double a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %20.6lf", a_subject, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_bullet        (const int   a_num,     const char *a_info)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10d: %.50s", a_num, a_info);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_pair          (const int   a_num,     const int  a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10d: %d", a_num, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_point         (const char *a_subject, const void *a_value)
{
   if (its_quiet) return;
   sprintf(its_msg, "%-10.10s: %p", a_subject, a_value);
   yLOG__main('-', 'i', its_msg);
   return;
}

void
yLOG_complex       (const char *a_subject, cchar *a_format, ...)
{
   if (its_quiet) return;
   /*---(locals)---------+-------------+-*/
   char        x_format  [200] = "";
   va_list     args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   sprintf   (its_msg, "%-10.10s: %.150s", a_subject, x_format);
   yLOG__main('-', 'i', its_msg);
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}



/*====================------------------------------------====================*/
/*===----                             errors                           ----===*/
/*====================------------------------------------====================*/
static void      o___ERRORS__________________o (void) {;}

void
yLOG_hintx         (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [200] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   fprintf   (stderr, "%-20.20s : %4d : HINT,  %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its_quiet) {
      vsnprintf (x_format, 190, a_format, args);
      sprintf   (its_msg, "HINT      : %s", x_format);
      yLOG__main('-', 'w', its_msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_warn          (const char *a_item,    const char *a_issue)
{
   if (its_quiet) return;
   sprintf(its_msg, "WARNING   : (%.15s) %.45s", a_item, a_issue);
   yLOG__main('-', 'w', its_msg);
   return;
}

void
yLOG_warnx         (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [200] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   x_format [190] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : WARN,  %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   /*> if (!its_quiet) {                                                              <* 
    *>    vsnprintf (x_format, 190, a_format, args);                                  <* 
    *>    sprintf   (its_msg, "WARNING   : %s", x_format);                            <* 
    *>    yLOG__main('-', 'w', its_msg);                                              <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_error    (const char *a_item,    const char *a_issue)
{
   if (its_quiet) return;
   sprintf(its_msg, "ERROR     : (%.15s) %.45s", a_item, a_issue);
   yLOG__main('-', 'e', its_msg);
   return;
}

void
yLOG_errorx        (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [200] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   x_format [190] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : ERROR, %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its_quiet) {
      vsnprintf (x_format, 190, a_format, args);
      sprintf   (its_msg, "ERROR     : %s", x_format);
      yLOG__main('-', 'w', its_msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_fatal    (const char *a_item,    const char *a_issue)
{
   if (its_quiet) return;
   sprintf(its_msg, "FATAL     : (%.15s) %.45s", a_item, a_issue);
   yLOG__main('-', 'g', its_msg);
   return;
}

void
yLOG_fatalx        (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [200] = "FATAL, ";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   x_format [190] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : FATAL, %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its_quiet) {
      vsnprintf (x_format, 190, a_format, args);
      x_format [190] = '\0';
      sprintf   (its_msg, "FATAL     : %s", x_format);
      yLOG__main('-', 'w', its_msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}



/*====================------------------------------------====================*/
/*===----                          incremental                         ----===*/
/*====================------------------------------------====================*/
static void      o___INCEMENTALS_____________o (void) {;}

void
yLOG_senter   (const char *a_func)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, "%.30s>>", a_func);
   strlcpy (its_single, msg, 200);
   return;
}

void
yLOG_sexit    (const char *a_func)
{
   if (its_quiet) return;
   strlcat (its_single, ";;", 200);
   yLOG__main('-', 's', its_single);
   return;
}

void
yLOG_sexitr   (const char *a_func, const int a_rce)
{
   char  msg[200];
   if (its_quiet) return;
   snprintf(msg, 200, ", WARN %d;;", a_rce);
   strlcat (its_single, msg, 200);
   yLOG__main('-', 'w', its_single);
   return;
}

void
yLOG_snote    (const char *a_info)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s", a_info);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_sint     (const int  a_value)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %d", a_value);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_sdouble  (const double  a_value)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %.6lf", a_value);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_shex     (const unsigned int  a_value)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", 0x%08x", a_value);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_spoint   (const void *a_pointer)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %p", a_pointer);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_schar    (const char a_info)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %c", a_info);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_sinfo    (const char *a_subject, const char *a_info)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s=%s", a_subject, a_info);
   strlcat (its_single, msg, 200);
   return;
}

void
yLOG_svalue   (const char *a_subject, const int  a_value)
{
   if (its_quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s=%d", a_subject, a_value);
   strlcat (its_single, msg, 200);
   return;
}


/*===[[ END ]]================================================================*/

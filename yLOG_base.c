/*============================[[ beg-of-code ]]===============================*/
#include    "yLOG.h"
#include    "yLOG_priv.h"

tITS        its;








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
   snprintf (its.version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return its.version;
}


/*====================------------------------------------====================*/
/*===----                             driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;}

llong             /* PURPOSE : timestamp in milliseconds      */
ylog__timestamp         (void)
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

char
ylog__prefix            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(rational limits)----------------*/
   if (its.indent <  0)  its.indent = 0;
   if (its.indent > 30)  its.indent = 30;
   /*---(standard prefix)----------------*/
   strlcpy (its.prefix, "", LEN_HUND);
   for (i = 0; i <  its.indent; ++i   )  strlcat (its.prefix, "Ï··", LEN_HUND);
   /*---(add marks every third)----------*/
   for (i = 2; i <  its.indent; i += 3)  its.prefix [i * 3] = '+';
   /*---(clear just before entry)--------*/
   if (its.indent > 0) {
      its.prefix [its.indent * 3 - 1] = ' ';
      its.prefix [its.indent * 3 - 2] = ' ';
   }
   /*---(complete)-----------------------*/
   return 0;
}

void             /* PURPOSE : write a message to the log file          */
ylog__main(
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
   llong       x_wall;                            /* timestamp                 */
   /*---(first, defense)-----------------*/
   if (a_change == 0 || strchr (LVL_VALID , a_change) == NULL)   a_change = LVL_UNKNOWN;
   if (a_level  == 0 || strchr (TYPE_VALID, a_level ) == NULL)   a_level  = TYPE_UNKNOWN;
   /*---(exdent, if needed)--------------*/
   if (a_change == '<' && its.indent > 0) {
      its.indent--;
      ylog__prefix ();
   }
   /*---(get wall time)----------------*/
   x_wall  = ylog__timestamp() - its.wall_start;
   /*---(update count)-------------------*/
   its.count++;
   /*---(message)------------------------*/
   sprintf (its.full, "%7lld.%03lld %6d [%c] %s%s",
         (x_wall / 1000) % 10000000, x_wall % 1000,
         its.count % 1000000, a_level, its.prefix, a_message);
   /*---(log)----------------------------*/
   if (its.logger != NULL) {
      fprintf (its.logger, "%s\n", its.full);
      fflush  (its.logger);
   }
   /*---(indent, if needed)--------------*/
   if (a_change == '>') {
      its.indent++;
      ylog__prefix ();
   }
   /*---(complete)-----------------------*/
   return;
}



/*====================------------------------------------====================*/
/*===----                        data accessors                        ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSORS_______________o (void) {;}

int   yLOG_lognum   (void) { return fileno (its.logger); }

llong yLOG_time     (void) { return ylog__timestamp(); }



/*====================------------------------------------====================*/
/*===----                        begin and end                         ----===*/
/*====================------------------------------------====================*/
static void      o___BOOKENDS________________o (void) {;}

int        /*----: initialize logger and log header info ---------------------*/
yLOG_begin         (cchar *a_program, cchar a_location, cchar a_quiet)
{
   /*---(locals)-----------+-----+-----+-*/
   time_t      time_date;
   tTIME      *curr_time   = NULL;
   char        x_prog      [50] = "________________________________________________";
   int         i           =    0;
   char        x_prefix    [20];
   int         x_fd        =    0;
   char        t           [LEN_DESC];
   /*---(initialize class variables)-----*/
   strcpy (its.filename, "stdout");
   its.logger = NULL;
   its.nsyncs = 0;
   its.count  = 0;
   its.indent = 0;
   strcpy (its.prefix, "");
   /*---(defense)------------------------*/
   if (a_quiet == yLOG_NOISE) its.loud  = 'y';
   else                       its.loud  = '-';
   if (RUN_QUIET)  return 1;
   /*---(get the date)-------------------*/
   time_date = time(NULL);
   curr_time = localtime(&time_date);
   /*---(open the log file)--------------*/
   if (a_location == yLOG_STDOUT) {
      its.logger = stdout;
   } else {
      for (i = 0; i < 30; ++i) {
         if (a_program[i] == '\0') break;
         if ((  a_program[i] >= 'A' && a_program[i] <= 'Z') ||
               (a_program[i] >= 'a' && a_program[i] <= 'z') ||
               (a_program[i] >= '0' && a_program[i] <= '9')) {
            x_prog[i] = a_program[i];
            continue;
         }
         x_prog[i] = '_';
      }
      strftime (x_prefix, 20, "%y.%m.%d.%H.%M.%S", curr_time);
      if (a_location == yLOG_SYSTEM) {
         snprintf(its.filename, 500, "%s%s.%-25.25s.ulog", LOGDIR , x_prefix, x_prog);
      } else if (a_location == yLOG_HISTORICAL) {
         snprintf(its.filename, 500, "%s%s.%-25.25s.ulog", HISDIR , x_prefix, x_prog);
      } else if (a_location == yLOG_ROOT      ) {
         snprintf(its.filename, 500, "%s%s.%-25.25s.ulog", ROOTDIR, x_prefix, x_prog);
      } else if (a_location == yLOG_USB) {
         snprintf(its.filename, 500, "%s%s.%-25.25s.ulog", USBDIR , x_prefix, x_prog);
      } else if (a_location == yLOG_NULL) {
         snprintf(its.filename, 500, "/dev/null");
      } else {  /* default is personal log file */
         snprintf(its.filename, 500, "%s/l_hlisda/%s.%-25.25s.ulog", getenv("HOME"), x_prefix, x_prog);
      }
      x_fd    = open  (its.filename, O_WRONLY | O_CREAT | O_TRUNC);
      if (x_fd < 0) {
         its.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -1;
      }
      dup2 (x_fd, LOG_FD);
      close (x_fd);
      its.logger = fdopen (LOG_FD, "w");
      if (its.logger == NULL) {
         its.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -1;
      }
   }
   strlcpy (its.prog, a_program, 29);
   /*---(get wall time)------------------*/
   its.wall_start = ylog__timestamp();
   /*---(display)------------------------*/
   fprintf(its.logger, "heatherly program logger================================================begin===\n");
   gethostname(t, LEN_DESC);
   fprintf(its.logger, "   host       : %s\n",    t);
   getlogin_r(t, LEN_DESC);
   fprintf(its.logger, "   user       : %s\n",    t);
   fprintf(its.logger, "   program    : %s\n",    a_program);
   fprintf(its.logger, "   pid        : %06i\n",  getpid());
   fprintf(its.logger, "   start date : %s",      asctime(curr_time));
   fprintf(its.logger, "   start (ms) : %lld\n",  its.wall_start);
   fprintf(its.logger, "   log file   : %s\n",    its.filename);
   fprintf(its.logger, "   log core   : %s\n",    "false");
   fprintf(its.logger, "================================================================================\n");
   fprintf(its.logger, "secs---.-ms -step- lvl ---comment-----------------------------------------------\n");
   yLOG_note("logger loaded");
   /*---(complete)-----------------------*/
   return fileno (its.logger);
}

void                    /* PURPOSE : log footer and close logger              */
yLOG_end      (void)
{
   if (its.logger == NULL) return;
   /*---(get the date)---------------------------*/
   time_t      time_date = time(NULL);
   struct tm*  curr_time = localtime(&time_date);
   /*---(get wall time)----------------*/
   llong _wall = ylog__timestamp();
   long  _elap = _wall - its.wall_start;
   long  _sec  = _elap / 1000;
   long  _hrs  = _sec / 3600;
   _sec -= _hrs * 3600;
   long  _min  = _sec / 60;
   _sec -= _min * 60;
   /*---(display end)------------------*/
   yLOG_note("logger stopped");
   fprintf(its.logger, "secs---.-ms -step- lvl ---comment-----------------------------------------------\n");
   fprintf(its.logger, "================================================================================\n");
   fprintf(its.logger, "   end date   : %s",      asctime(curr_time));
   fprintf(its.logger, "   end (ms)   : %lld\n",  _wall);
   fprintf(its.logger, "   dur (ms)   : %lld\n",  _wall - its.wall_start);
   fprintf(its.logger, "   duration   : %2ldh, %2ldm, %2lds\n", _hrs, _min, _sec);
   fprintf(its.logger, "==========================================================================end===\n");
   fclose (its.logger);
   its.loud  = '-';
   return;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char          unit_answer [LEN_RECD];

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_quiet       (void)
{
   yLOG_begin ("yLOG", yLOG_SYSTEM, yLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_loud        (void)
{
   yLOG_begin   ("yLOG_unit", yLOG_SYSTEM, yLOG_NOISE);
   /*> DEBUG_YLOGS  yLOG_info     ("yLOG"      , yLOG_version   ());                  <*/
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ylog__unit_end         (void)
{
   yLOG_end     ();
   return 0;
}

char*            /*--> unit test accessor ------------------------------*/
ylog_base__unit         (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "[]";
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "BASE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "prefix"     ) == 0) {
      sprintf (t, "[%s]", its.prefix);
      snprintf (unit_answer, LEN_RECD, "BASE prefix      : %2d  %2d%s", its.indent, strlen (its.prefix), t);
   }
   else if (strcmp (a_question, "full"       ) == 0) {
      sprintf (t, "[%s]", its.full);
      snprintf (unit_answer, LEN_RECD, "BASE full        : %2d%s", strlen (its.full), t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===[[ END ]]================================================================*/

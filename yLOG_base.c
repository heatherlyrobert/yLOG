/*============================[[ beg-of-code ]]===============================*/
#include    "yLOG.h"
#include    "yLOG_priv.h"

tITS        myLOG;
static int  s_lines  = 0;








/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yLOGS_version           (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (myLOG.version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return myLOG.version;
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
   int         x_indent    =    0;
   /*---(rational limits)----------------*/
   x_indent = myLOG.indent;
   if (x_indent <  0)  { myLOG.indent = x_indent = 0; }
   if (x_indent > 30)  x_indent = 30;
   /*---(standard prefix)----------------*/
   strncpy (myLOG.prefix, "", LEN_HUND);
   for (i = 0; i <  x_indent; ++i   )  strncat (myLOG.prefix, "´··", LEN_HUND);
   /*---(add marks every third)----------*/
   for (i = 2; i <  x_indent; i += 3)  myLOG.prefix [i * 3] = '+';
   /*---(clear just before entry)--------*/
   if (x_indent > 0) {
      myLOG.prefix [x_indent * 3 - 1] = ' ';
      myLOG.prefix [x_indent * 3 - 2] = ' ';
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
   /*---(filter)-------------------------*/
   if (myLOG.loud != 'y')  return;
   /*---(first, defense)-----------------*/
   if (a_change == 0 || strchr (LVL_VALID , a_change) == NULL)   a_change = LVL_UNKNOWN;
   if (a_level  == 0 || strchr (TYPE_VALID, a_level ) == NULL)   a_level  = TYPE_UNKNOWN;
   /*---(exdent, if needed)--------------*/
   if (a_change == '<' && myLOG.indent > 0) {
      myLOG.indent--;
      ylog__prefix ();
   }
   /*---(get wall time)----------------*/
   x_wall  = ylog__timestamp() - myLOG.wall_start;
   /*---(update count)-------------------*/
   myLOG.count++;
   /*---(message)------------------------*/
   sprintf (myLOG.full, "%7lld.%03lld %6d %c%c%c %s%s",
         (x_wall / 1000) % 10000000, x_wall % 1000,
         myLOG.count % 1000000, myLOG.stage, myLOG.urg, a_level, myLOG.prefix, a_message);
   /*---(log)----------------------------*/
   IF_LOGGER {
      fprintf (myLOG.logger, "%s\n", myLOG.full);
      fflush  (myLOG.logger);
   }
   /*---(indent, if needed)--------------*/
   if (a_change == '>') {
      myLOG.indent++;
      ylog__prefix ();
   }
   /*---(complete)-----------------------*/
   return;
}



/*====================------------------------------------====================*/
/*===----                        data accessors                        ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSORS_______________o (void) {;}

int   yLOGS_lognum   (void) { if (myLOG.logger == NULL) return -1; else return fileno (myLOG.logger); }

llong yLOGS_time     (void) { return ylog__timestamp(); }

char *yLOGS_path     (void) { return myLOG.path; };

char *yLOGS_filename (void) { return myLOG.filename; };



/*====================------------------------------------====================*/
/*===----                        begin and end                         ----===*/
/*====================------------------------------------====================*/
static void      o___BOOKENDS________________o (void) {;}

char
ylogs__progname      (cchar *a_prog)
{
   int         i           =    0;
   char       *x_valid     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   strcpy (myLOG.prog, "");
   if (a_prog == NULL)  return -1;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (a_prog [i] == '\0') break;
      if (strchr (x_valid, a_prog [i]) != NULL)   myLOG.prog [i] = a_prog [i];
      else                                        myLOG.prog [i] = '_';
   }
   myLOG.prog [i] = '\0';
   return 0;
}

char*
ylogs__logname       (cchar *a_prog, cchar a_loc)
{
   /*---(locals)-----------+-----+-----+-*/
   time_t      time_date;
   tTIME      *curr_time   = NULL;
   char        t           [LEN_HUND];
   /*---(initialize)---------------------*/
   strcpy (myLOG.filename, "/dev/null");
   strcpy (myLOG.path    , "");
   if (a_prog == NULL)  return -1;
   /*---(get the date)-------------------*/
   time_date = time (NULL);
   curr_time = localtime (&time_date);
   strftime (myLOG.timestamp, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", curr_time);
   /*---(program name)-------------------*/
   sprintf (t, "%s_____________________________________________________", a_prog);
   /*---(create the file name)-----------*/
   switch (a_loc) {
   case YLOG_STDOUT:
      strcpy   (myLOG.filename, "stdout");
      break;
   case YLOG_SYS   :
      snprintf (myLOG.filename, LEN_PATH, "%s%s.%-25.25s.ulog", LOGDIR , myLOG.timestamp, t);
      strcpy   (myLOG.path, LOGDIR);
      break;
   case YLOG_HIST  :
      snprintf (myLOG.filename, LEN_PATH, "%s%s.%-25.25s.ulog", HISDIR , myLOG.timestamp, t);
      strcpy   (myLOG.path, HISDIR);
      break;
   case YLOG_ROOT  :
      snprintf (myLOG.filename, LEN_PATH, "%s%s.%-25.25s.ulog", ROOTDIR, myLOG.timestamp, t);
      strcpy   (myLOG.path, ROOTDIR);
      break;
   case YLOG_USB   :
      snprintf (myLOG.filename, LEN_PATH, "%s%s.%-25.25s.ulog", USBDIR , myLOG.timestamp, t);
      strcpy   (myLOG.path, USBDIR);
      break;
   case YLOG_TMP   :
      snprintf (myLOG.filename, LEN_PATH, "%s%s.%-25.25s.ulog", TMPDIR , myLOG.timestamp, t);
      strcpy   (myLOG.path, TMPDIR);
      break;
   case YLOG_NULL  :
      strcpy   (myLOG.filename, "/dev/null");
      break;
   default         :
      strcpy   (myLOG.filename, "/dev/null");
      return -2;
      break;
   }
   /*> printf ("%-20.20s  %c  %s\n", a_prog, a_loc, myLOG.filename);                  <*/
   return 0;
}

char       /*----: initialize logger and log header info ---------------------*/
yLOGS_begin         (cchar *a_program, cchar a_loc, cchar a_quiet)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         x_fd        =    0;
   char        t           [LEN_DESC];
   int         x_len       = 0;
   char       *p           = NULL;
   char        x_progname  [LEN_FULL] = "";
   /*---(get the date)---------------------------*/
   time_t      time_date = time(NULL);
   struct tm*  curr_time = localtime(&time_date);
   /*---(initialize class variables)-----*/
   strcpy (myLOG.filename, "stdout");
   myLOG.logger = NULL;
   myLOG.nsyncs = 0;
   myLOG.count  = 0;
   myLOG.indent = 0;
   ylog_vol_init ();
   strcpy (myLOG.prefix, "");
   myLOG.stage  = '·';
   myLOG.urg    = '·';
   /*---(defense)------------------------*/
   if (a_quiet == YLOG_NOISE) myLOG.loud  = 'y';
   else                       myLOG.loud  = '-';
   /*> IF_QUIET  return 0;                                                            <*/
   /*---(test for normal version)--------*/
   p = strrchr (a_program, '/');
   if (p == NULL)  strncpy (x_progname, a_program, LEN_FULL);
   else            strncpy (x_progname, p + 1    , LEN_FULL);
   x_len  = strlen (x_progname);
   myLOG.use    = '-';
   if (x_len >= 6) {
      if (strstr (x_progname, "_debug") != 0)  myLOG.use  = 'd';
      if (strstr (x_progname, "_unit" ) != 0)  myLOG.use  = 'u';
   }
   /*> printf ("myLOG.loud = %c\n", myLOG.loud);                                      <*/
   /*> printf ("myLOG.use  = %c\n", myLOG.use);                                       <*/
   /*---(open the log file)--------------*/
   if (a_loc == YLOG_STDOUT) {
      myLOG.logger = stdout;
   } else {
      /*---(clean prog name)-------------*/
      rc = ylogs__progname (a_program);
      /*---(create file name)------------*/
      rc = ylogs__logname  (myLOG.prog, a_loc);
      if (rc < 0) {
         myLOG.loud  = '-';
         printf ("FATAL, can not name log file\n");
         return -1;
      }
      /*---(open log)--------------------*/
      x_fd    = open  (myLOG.filename, O_WRONLY | O_CREAT | O_TRUNC);
      if (x_fd < 0) {
         myLOG.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -2;
      }
      /*---(move to std fd)--------------*/
      dup2 (x_fd, LOG_FD);
      close (x_fd);
      myLOG.logger = fdopen (LOG_FD, "w");
      if (myLOG.logger == NULL) {
         myLOG.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -3;
      }
      /*---(done)------------------------*/
   }
   /*> printf ("myLOG.logger = %p\n", myLOG.logger);                                  <*/
   strncpy (myLOG.prog, a_program, 29);
   /*---(get wall time)------------------*/
   myLOG.wall_start = ylog__timestamp();
   /*---(display)------------------------*/
   IF_LOGGER  fprintf (myLOG.logger, "heatherly program logger=================================================begin===\n");
   gethostname (t, LEN_DESC);
   IF_LOGGER  fprintf (myLOG.logger, "   host       : %s\n",    t);
   getlogin_r (t, LEN_DESC);
   IF_LOGGER  fprintf (myLOG.logger, "   user       : %s\n",    t);
   IF_LOGGER  fprintf (myLOG.logger, "   program    : %s\n",    a_program);
   IF_LOGGER  fprintf (myLOG.logger, "   pid        : %06i\n",  getpid());
   IF_LOGGER  fprintf (myLOG.logger, "   start date : %s",      asctime(curr_time));
   IF_LOGGER  fprintf (myLOG.logger, "   start (ms) : %lld\n",  myLOG.wall_start);
   IF_LOGGER  fprintf (myLOG.logger, "   log file   : %s\n",    myLOG.filename);
   IF_LOGGER  fprintf (myLOG.logger, "=================================================================================\n");
   IF_LOGGER  fprintf (myLOG.logger, "secs---.-ms -step- cat ---comment------------------------------------------------\n");
   /*> printf ("myLOG.logger = %p\n", myLOG.logger);                                  <*/
   IF_LOGGER  yLOG_note ("logger loaded");
   /*> printf ("myLOG.logger = %p\n", myLOG.logger);                                  <*/
   /*---(complete)-----------------------*/
   return 0;
}

void                    /* PURPOSE : log footer and close logger              */
yLOGS_end      (void)
{
   if (myLOG.logger == NULL) return;
   /*---(get the date)---------------------------*/
   time_t      time_date = time(NULL);
   struct tm*  curr_time = localtime(&time_date);
   /*---(get wall time)----------------*/
   llong _wall = ylog__timestamp();
   long  _elap = _wall - myLOG.wall_start;
   long  _sec  = _elap / 1000;
   long  _hrs  = _sec / 3600;
   _sec -= _hrs * 3600;
   long  _min  = _sec / 60;
   _sec -= _min * 60;
   /*---(display end)------------------*/
   IF_LOGGER  yLOG_note("logger stopped");
   IF_LOGGER  fprintf(myLOG.logger, "secs---.-ms -step- cat ---comment------------------------------------------------\n");
   IF_LOGGER  fprintf(myLOG.logger, "=================================================================================\n");
   IF_LOGGER  fprintf(myLOG.logger, "   end date   : %s",      asctime(curr_time));
   IF_LOGGER  fprintf(myLOG.logger, "   end (ms)   : %lld\n",  _wall);
   IF_LOGGER  fprintf(myLOG.logger, "   dur (ms)   : %lld\n",  _wall - myLOG.wall_start);
   IF_LOGGER  fprintf(myLOG.logger, "   duration   : %2ldh, %2ldm, %2lds\n", _hrs, _min, _sec);
   IF_LOGGER  fprintf(myLOG.logger, "===========================================================================end===\n");
   IF_LOGGER  fclose (myLOG.logger);
   myLOG.loud  = '-';
   return;
}



/*====================------------------------------------====================*/
/*===----                   specialty testing support                  ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;};

void
yLOG_curr               (uchar a_stage, uchar a_urg)
{
   myLOG.stage  = a_stage;
   myLOG.urg    = a_urg;
   if (a_stage <= 32 || (a_stage >= 127 && a_stage <= 159))  myLOG.stage = '·';
   if (a_urg   <= 32 || (a_urg   >= 127 && a_urg   <= 159))  myLOG.urg    = '·';
   return 0;
}

char
yLOGS_verify            (cchar *a_name, cchar a_log, cchar a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_path      [LEN_PATH];
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_name      [LEN_PATH];
   int         x_len       =    0;
   char       *p           = NULL;
   tSTAT       s;
   char        c           =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD] = "";
   /*---(header)-------------------------*/
   DEBUG_YLOGS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YLOGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YLOGS  yLOG_info    ("a_name"    , a_name);
   /*---(location)-----------------------*/
   DEBUG_YLOGS  yLOG_char    ("a_log"     , a_log);
   --rce;  switch (a_log) {
   case YLOG_SYS  : strcpy (x_path, LOGDIR); break;
   case YLOG_HIST : strcpy (x_path, HISDIR); break;
   case YLOG_ROOT : strcpy (x_path, ROOTDIR); break;
   case YLOG_USB  : strcpy (x_path, USBDIR); break;
   case YLOG_TMP  : strcpy (x_path, TMPDIR); break;
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_YLOGS  yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_YLOGS  yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_YLOGS  yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_YLOGS  yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_YLOGS  yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_YLOGS  yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_YLOGS  yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_YLOGS  yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_YLOGS  yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YLOGS  yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check good result)--------------*/
   DEBUG_YLOGS  yLOG_value   ("c"         , c);
   --rce;  if (c != 1) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return c;
   }
   /*---(check on crontab file)----------*/
   rc = stat (x_name, &s);
   DEBUG_YLOGS  yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISREG (s.st_mode))  {
      DEBUG_YLOGS  yLOG_note    ("can only use regular files");
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get a line)------------------*/
   s_lines = 0;
   --rce;  if (a_line >= 0) {
      strncpy (myLOG.full, "-", LEN_PATH);
      f = fopen (x_name, "rt");
      if (rc < 0) {
         DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      while (1) {
         fgets (x_recd, LEN_RECD, f);
         if (feof (f))   break;
         x_len = strlen (x_recd);
         if (x_recd [x_len - 1] == '\n') x_recd [--x_len] = '\0';
         if (s_lines == a_line) strncpy (myLOG.full, x_recd, LEN_PATH);
         ++s_lines;
      }
      if (myLOG.full [0] == '-') {
         DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YLOGS  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yLOGS_remove            (cchar *a_name, cchar a_log)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_path      [LEN_PATH];
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_name      [LEN_PATH];
   int         x_len       =    0;
   char       *p           = NULL;
   tSTAT       s;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YLOGS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YLOGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YLOGS  yLOG_info    ("a_name"    , a_name);
   /*---(location)-----------------------*/
   DEBUG_YLOGS  yLOG_char    ("a_log"     , a_log);
   --rce;  switch (a_log) {
   case YLOG_SYS  : strcpy (x_path, LOGDIR); break;
   case YLOG_HIST : strcpy (x_path, HISDIR); break;
   case YLOG_ROOT : strcpy (x_path, ROOTDIR); break;
   case YLOG_USB  : strcpy (x_path, USBDIR); break;
   case YLOG_TMP  : strcpy (x_path, TMPDIR); break;
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_YLOGS  yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_YLOGS  yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_YLOGS  yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_YLOGS  yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_YLOGS  yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_YLOGS  yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_YLOGS  yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_YLOGS  yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_YLOGS  yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      unlink  (x_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YLOGS  yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YLOGS  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char          unit_answer [LEN_RECD];

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_quiet       (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_QUIET);
   myLOG.use   = 'u';
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_loud        (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_NOISE);
   myLOG.use   = 'u';
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ylog__unit_end         (void)
{
   yLOGS_end     ();
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
      sprintf (t, "[%s]", myLOG.prefix);
      snprintf (unit_answer, LEN_RECD, "BASE prefix      : %2d  %2d%s", myLOG.indent, strlen (myLOG.prefix), t);
   }
   else if (strcmp (a_question, "full"       ) == 0) {
      c = strlen (myLOG.full);
      if (c > 99)  c = 99;
      sprintf (t, "[%s]", myLOG.full);
      snprintf (unit_answer, LEN_RECD, "BASE full        : %2d%s", c, t);
   }
   else if (strcmp (a_question, "prog"       ) == 0) {
      sprintf (t, "[%s]", myLOG.prog);
      snprintf (unit_answer, LEN_RECD, "BASE prog        : %2d%s", strlen (myLOG.prog), t);
   }
   else if (strcmp (a_question, "loud"       ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE loud        : %c  %2d", myLOG.loud, myLOG.count);
   }
   else if (strcmp (a_question, "lines"      ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE lines       : %2d", s_lines);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===[[ END ]]================================================================*/

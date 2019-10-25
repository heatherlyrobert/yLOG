/*============================[[ beg-of-code ]]===============================*/
#include    "yLOG.h"
#include    "yLOG_priv.h"

tITS        its;








/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yLOGS_version           (void)
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
   for (i = 0; i <  its.indent; ++i   )  strlcat (its.prefix, "Ϸ�", LEN_HUND);
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

int   yLOGS_lognum   (void) { return fileno (its.logger); }

llong yLOGS_time     (void) { return ylog__timestamp(); }

char *yLOGS_path     (void) { return its.path; };

char *yLOGS_filename (void) { return its.filename; };



/*====================------------------------------------====================*/
/*===----                        begin and end                         ----===*/
/*====================------------------------------------====================*/
static void      o___BOOKENDS________________o (void) {;}

char
ylogs__progname      (cchar *a_prog)
{
   int         i           =    0;
   char       *x_valid     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   strcpy (its.prog, "");
   if (a_prog == NULL)  return -1;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (a_prog [i] == '\0') break;
      if (strchr (x_valid, a_prog [i]) != NULL)   its.prog [i] = a_prog [i];
      else                                        its.prog [i] = '_';
   }
   its.prog [i] = '\0';
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
   strcpy (its.filename, "/dev/null");
   strcpy (its.path    , "");
   if (a_prog == NULL)  return -1;
   /*---(get the date)-------------------*/
   time_date = time (NULL);
   curr_time = localtime (&time_date);
   strftime (its.timestamp, LEN_LABEL, "%y.%m.%d.%H.%M.%S", curr_time);
   /*---(program name)-------------------*/
   sprintf (t, "%s_____________________________________________________", a_prog);
   /*---(create the file name)-----------*/
   switch (a_loc) {
   case YLOG_STDOUT:
      strcpy   (its.filename, "stdout");
      break;
   case YLOG_SYS   :
      snprintf (its.filename, LEN_PATH, "%s%s.%-25.25s.ulog", LOGDIR , its.timestamp, t);
      strcpy   (its.path, LOGDIR);
      break;
   case YLOG_HIST  :
      snprintf (its.filename, LEN_PATH, "%s%s.%-25.25s.ulog", HISDIR , its.timestamp, t);
      strcpy   (its.path, HISDIR);
      break;
   case YLOG_ROOT  :
      snprintf (its.filename, LEN_PATH, "%s%s.%-25.25s.ulog", ROOTDIR, its.timestamp, t);
      strcpy   (its.path, ROOTDIR);
      break;
   case YLOG_USB   :
      snprintf (its.filename, LEN_PATH, "%s%s.%-25.25s.ulog", USBDIR , its.timestamp, t);
      strcpy   (its.path, USBDIR);
      break;
   case YLOG_NULL  :
   default         :
      strcpy   (its.filename, "/dev/null");
      return -2;
      break;
   }
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
   /*---(get the date)---------------------------*/
   time_t      time_date = time(NULL);
   struct tm*  curr_time = localtime(&time_date);
   /*---(initialize class variables)-----*/
   strcpy (its.filename, "stdout");
   its.logger = NULL;
   its.nsyncs = 0;
   its.count  = 0;
   its.indent = 0;
   ylog_vol_init ();
   strcpy (its.prefix, "");
   /*---(defense)------------------------*/
   if (a_quiet == YLOG_NOISE) its.loud  = 'y';
   else                       its.loud  = '-';
   if (RUN_QUIET)  return 0;
   /*---(open the log file)--------------*/
   if (a_loc == YLOG_STDOUT) {
      its.logger = stdout;
   } else {
      /*---(clean prog name)-------------*/
      rc = ylogs__progname (a_program);
      /*---(create file name)------------*/
      rc = ylogs__logname  (its.prog, a_loc);
      if (rc < 0) {
         its.loud  = '-';
         printf ("FATAL, can not name log file\n");
         return -1;
      }
      /*---(open log)--------------------*/
      x_fd    = open  (its.filename, O_WRONLY | O_CREAT | O_TRUNC);
      if (x_fd < 0) {
         its.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -2;
      }
      /*---(move to std fd)--------------*/
      dup2 (x_fd, LOG_FD);
      close (x_fd);
      its.logger = fdopen (LOG_FD, "w");
      if (its.logger == NULL) {
         its.loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -3;
      }
      /*---(done)------------------------*/
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
   fprintf(its.logger, "================================================================================\n");
   fprintf(its.logger, "secs---.-ms -step- lvl ---comment-----------------------------------------------\n");
   yLOG_note("logger loaded");
   /*---(complete)-----------------------*/
   return 0;
}

void                    /* PURPOSE : log footer and close logger              */
yLOGS_end      (void)
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
/*===----                   specialty testing support                  ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;};

char
yLOGS_verify            (cchar *a_name, cchar a_log)
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
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_INPT   yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_INPT   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_INPT   yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_INPT   yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_INPT   yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_INPT   yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_INPT   yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check good result)--------------*/
   DEBUG_INPT   yLOG_value   ("c"         , c);
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
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_INPT   yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_INPT   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_INPT   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_INPT   yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_INPT   yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_INPT   yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_INPT   yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_INPT   yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_INPT   yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      remove (x_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_INPT   yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
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
   yLOGS_begin ("yLOG", YLOG_SYS, YLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_loud        (void)
{
   yLOGS_begin   ("yLOG_unit", YLOG_SYS, YLOG_NOISE);
   /*> DEBUG_YLOGS  yLOG_info     ("yLOG"      , yLOG_version   ());                  <*/
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
      sprintf (t, "[%s]", its.prefix);
      snprintf (unit_answer, LEN_RECD, "BASE prefix      : %2d  %2d%s", its.indent, strlen (its.prefix), t);
   }
   else if (strcmp (a_question, "full"       ) == 0) {
      sprintf (t, "[%s]", its.full);
      snprintf (unit_answer, LEN_RECD, "BASE full        : %2d%s", strlen (its.full), t);
   }
   else if (strcmp (a_question, "prog"       ) == 0) {
      sprintf (t, "[%s]", its.prog);
      snprintf (unit_answer, LEN_RECD, "BASE prog        : %2d%s", strlen (its.prog), t);
   }
   else if (strcmp (a_question, "loud"       ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE loud        : %c  %2d", its.loud, its.count);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===[[ END ]]================================================================*/

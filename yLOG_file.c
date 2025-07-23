/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        begin and end                         ----===*/
/*====================------------------------------------====================*/
static void      o___BOOKENDS________________o (void) {;}

char
ylogs__progname      (char *a_prog)
{
   int         i           =    0;
   char       *x_valid     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   strcpy (myLOG.m_prog, "");
   if (a_prog == NULL)  return -1;
   for (i = 0; i < LEN_LABEL; ++i) {
      if (a_prog [i] == '\0') break;
      if (strchr (x_valid, a_prog [i]) != NULL)   myLOG.m_prog [i] = a_prog [i];
      else                                        myLOG.m_prog [i] = '_';
   }
   myLOG.m_prog [i] = '\0';
   return 0;
}

char*
ylogs__logname       (char *a_prog, char a_loc)
{
   /*---(locals)-----------+-----+-----+-*/
   time_t      x_now;
   tTIME      *x_local     = NULL;
   tTIMEVAL    x_better;
   int         x_micro     =    0;
   char        t           [LEN_HUND]  = "";
   char        x_file      [LEN_HUND]  = "";
   /*---(initialize)---------------------*/
   strcpy (myLOG.m_filename, "/dev/null");
   strcpy (myLOG.m_path    , "");
   if (a_prog == NULL)  return -1;
   /*---(get the date)-------------------*/
   /*> x_now = time (NULL);                                                           <*/
   gettimeofday (&x_better, NULL);
   x_now   = x_better.tv_sec;
   x_local = localtime (&x_now);
   strftime (myLOG.m_timestamp, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", x_local);
   x_micro = x_better.tv_usec;
   /*---(program name)-------------------*/
   sprintf (t, "%s_____________________________________________________", a_prog);
   sprintf (x_file, "%s.%06d.%-25.25s.ulog", myLOG.m_timestamp, x_micro, t);
   /*---(create the file name)-----------*/
   switch (a_loc) {
   case YLOG_STDOUT:
      strcpy   (myLOG.m_filename, "stdout");
      break;
   case YLOG_SYS   :
      snprintf (myLOG.m_filename, LEN_PATH, "%s%s", LOGDIR , x_file);
      strcpy   (myLOG.m_path, LOGDIR);
      break;
   case YLOG_HIST  :
      snprintf (myLOG.m_filename, LEN_PATH, "%s%s", HISDIR , x_file);
      strcpy   (myLOG.m_path, HISDIR);
      break;
   case YLOG_ROOT  :
      snprintf (myLOG.m_filename, LEN_PATH, "%s%s", ROOTDIR, x_file);
      strcpy   (myLOG.m_path, ROOTDIR);
      break;
   case YLOG_USB   :
      snprintf (myLOG.m_filename, LEN_PATH, "%s%s", USBDIR , x_file);
      strcpy   (myLOG.m_path, USBDIR);
      break;
   case YLOG_TMP   :
      snprintf (myLOG.m_filename, LEN_PATH, "%s%s", TMPDIR , x_file);
      strcpy   (myLOG.m_path, TMPDIR);
      break;
   case YLOG_NULL  :
      strcpy   (myLOG.m_filename, "/dev/null");
      break;
   default         :
      strcpy   (myLOG.m_filename, "/dev/null");
      return -2;
      break;
   }
   return 0;
}

char
ylogs_init          (void)
{
   strcpy (myLOG.m_prog, "");
   strcpy (myLOG.m_filename, "stdout");
   myLOG.m_logger = NULL;
   myLOG.m_nsyncs = 0;
   myLOG.m_count  = 0;
   myLOG.m_indent = 0;
   strcpy (myLOG.m_prefix, "");
   myLOG.m_stage  = '·';
   myLOG.m_urg    = '·';
   myLOG.m_loud   = '-';
   myLOG.m_use    = '-';
   strcpy (myLOG.m_msg , "");
   strcpy (myLOG.m_full, "");
   ylog_vol_init ();
   return 0;
}

char       /*----: initialize logger and log header info ---------------------*/
yLOGS_begin         (char *a_program, char a_loc, char a_quiet)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   int         x_fd        =    0;
   char        t           [LEN_DESC];
   int         x_len       = 0;
   char       *p           = NULL;
   char        x_progname  [LEN_FULL] = "";
   time_t      x_now       = 0;
   struct tm*  x_local     = NULL;
   /*---(get the date)---------------------------*/
   x_now   = time (NULL);
   x_local = localtime (&x_now);
   /*---(clear all)--------------------*/
   ylogs_init ();
   /*---(defense)------------------------*/
   if (a_quiet == YLOG_NOISE) myLOG.m_loud  = 'y';
   else                       myLOG.m_loud  = '-';
   /*---(test for normal version)--------*/
   p = strrchr (a_program, '/');
   if (p == NULL)  strncpy (x_progname, a_program, LEN_FULL);
   else            strncpy (x_progname, p + 1    , LEN_FULL);
   x_len  = strlen (x_progname);
   myLOG.m_use    = '-';
   if (x_len >= 6) {
      if (strstr (x_progname, "_debug") != 0)  myLOG.m_use  = 'd';
      if (strstr (x_progname, "_unit" ) != 0)  myLOG.m_use  = 'u';
   }
   /*---(open the log file)--------------*/
   if (a_loc == YLOG_STDOUT) {
      myLOG.m_logger = stdout;
   } else {
      /*---(clean prog name)-------------*/
      rc = ylogs__progname (a_program);
      /*---(create file name)------------*/
      rc = ylogs__logname  (myLOG.m_prog, a_loc);
      if (rc < 0) {
         myLOG.m_loud  = '-';
         printf ("FATAL, can not name log file\n");
         return -11;
      }
      /*---(open log)--------------------*/
      x_fd    = open  (myLOG.m_filename, O_WRONLY | O_CREAT | O_TRUNC);
      if (x_fd < 0) {
         myLOG.m_loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -12;
      }
      /*---(move to std fd)--------------*/
      dup2 (x_fd, LOG_FD);
      close (x_fd);
      myLOG.m_logger = fdopen (LOG_FD, "w");
      if (myLOG.m_logger == NULL) {
         myLOG.m_loud  = '-';
         printf ("FATAL, can not open logger\n");
         return -13;
      }
      /*---(done)------------------------*/
   }
   strncpy (myLOG.m_prog, a_program, 29);
   /*---(get wall time)------------------*/
   myLOG.m_start = ylog__timestamp();
   /*---(display)------------------------*/
   IF_LOGGER  fprintf (myLOG.m_logger, "heatherly program logger=================================================begin===\n");
   gethostname (t, LEN_DESC);
   IF_LOGGER  fprintf (myLOG.m_logger, "   host       : %s\n",      t);
   getlogin_r (t, LEN_DESC);
   IF_LOGGER  fprintf (myLOG.m_logger, "   user       : %s\n",      t);
   IF_LOGGER  fprintf (myLOG.m_logger, "   program    : %s\n",      a_program);
   IF_LOGGER  fprintf (myLOG.m_logger, "   pid        : %06i\n",    getpid());
   IF_LOGGER  fprintf (myLOG.m_logger, "   start date : %s",        asctime(x_local));
   IF_LOGGER  fprintf (myLOG.m_logger, "   start (ms) : %lld\n",    myLOG.m_start);
   IF_LOGGER  fprintf (myLOG.m_logger, "   log file   : %s\n",      myLOG.m_filename);
   IF_LOGGER  fprintf (myLOG.m_logger, "   init state : %c   %s\n", myLOG.m_loud, (myLOG.m_loud == 'y') ? "ACTIVE" : "MUTED");
   IF_LOGGER  fprintf (myLOG.m_logger, "=================================================================================\n");
   IF_LOGGER  fprintf (myLOG.m_logger, "secs---.-ms -step- cat ---comment------------------------------------------------\n");
   IF_LOGGER  yLOG_note ("logger loaded");
   IF_LOGGER  fflush (myLOG.m_logger);
   /*---(complete)-----------------------*/
   return 1;
}

char                    /* PURPOSE : log footer and close logger              */
yLOGS_end      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   time_t      x_now       = 0;
   struct tm*  x_local     = NULL;
   llong       x_wall;
   long        x_elap, x_hrs, x_min, x_sec;
   /*---(quick out)----------------------*/
   if (myLOG.m_logger == NULL) return 0;
   /*---(get the date)-------------------*/
   x_now   = time (NULL);
   x_local = localtime (&x_now);
   /*---(get wall time)----------------*/
   x_wall  = ylog__timestamp();
   x_elap  = x_wall - myLOG.m_start;
   x_sec   = x_elap / 1000;
   x_hrs   = x_sec / 3600;
   x_sec  -= x_hrs * 3600;
   x_min   = x_sec / 60;
   x_sec  -= x_min * 60;
   /*---(display end)--------------------*/
   IF_LOGGER  yLOG_note("logger stopped");
   IF_LOGGER  fprintf(myLOG.m_logger, "secs---.-ms -step- cat ---comment------------------------------------------------\n");
   IF_LOGGER  fprintf(myLOG.m_logger, "=================================================================================\n");
   IF_LOGGER  fprintf(myLOG.m_logger, "   end date   : %s",         asctime(x_local));
   IF_LOGGER  fprintf(myLOG.m_logger, "   end (ms)   : %lld\n",     x_wall);
   IF_LOGGER  fprintf(myLOG.m_logger, "   dur (ms)   : %lld\n",     x_wall - myLOG.m_start);
   IF_LOGGER  fprintf(myLOG.m_logger, "   duration   : %2ldh, %2ldm, %2lds\n", x_hrs, x_min, x_sec);
   IF_LOGGER  fprintf(myLOG.m_logger, "===========================================================================end===\n");
   IF_LOGGER  fflush (myLOG.m_logger);
   IF_LOGGER  fclose (myLOG.m_logger);
   /*---(clear all)----------------------*/
   ylogs_init ();
   /*---(complete)-----------------------*/
   return 1;
}




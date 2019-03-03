/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"






/*====================------------------------------------====================*/
/*===----                          simple versions                     ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE__________________o (void) {;}

void
yLOG_warn          (const char *a_issue)
{
   if (RUN_QUIET)  return;
   snprintf (its.msg, LEN_FULL, "%-10.10s: %.150s", "WARNING", ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_WARNING , its.msg);
   return;
}

void
yLOG_error         (const char *a_issue)
{
   if (RUN_QUIET)  return;
   snprintf (its.msg, LEN_FULL, "%-10.10s: %.150s", "ERROR"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_ERROR   , its.msg);
   return;
}

void
yLOG_fatal         (const char *a_issue)
{
   if (RUN_QUIET)  return;
   snprintf (its.msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_GRACEFUL, its.msg);
   return;
}

void
yLOG_boom          (const char *a_issue)
{
   if (RUN_QUIET)  return;
   snprintf (its.msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_CLUMSY  , its.msg);
   return;
}

void
yLOG_signal        (const int   a_signal)
{
   switch (a_signal) {
   case SIGHUP  :   strcpy (its.title, "SIGHUP" );    strcpy (its.temp, "daemon/program should reassess and look around");  break;
   case SIGALRM :   strcpy (its.title, "SIGALRM");    strcpy (its.temp, "daemon/program received a preset alarm");          break;
   case SIGUSR1 :   strcpy (its.title, "SIGUSR1");    strcpy (its.temp, "unknown");                                         break;
   case SIGUSR2 :   strcpy (its.title, "SIGUSR2");    strcpy (its.temp, "unknown");                                         break;
   case SIGABRT :   strcpy (its.title, "SIGABRT");    strcpy (its.temp, "unknown");                                         break;
   case SIGSEGV :   strcpy (its.title, "SIGSEGV");    strcpy (its.temp, "unknown");                                         break;
   case SIGCHLD :   strcpy (its.title, "SIGCHLD");    strcpy (its.temp, "unknown");                                         break;
   case SIGQUIT :   strcpy (its.title, "SIGQUIT");    strcpy (its.temp, "unknown");                                         break;
   default      :   strcpy (its.title, "¢unknown?");  strcpy (its.temp, "unknown");                                         break;
   }
   if (RUN_QUIET)  return;
   snprintf (its.msg, LEN_FULL, "%-10.10s: %.150s", its.title, its.temp);
   ylog__main (LVL_SAME, TYPE_CALLBACK, its.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                        complex errors                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMPLEX_________________o (void) {;}

void
yLOG_errors        (cchar *a_desc, cchar a_type, cchar *a_file, cint a_line, cchar *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_format    [LEN_FULL]  = "";
   va_list     x_args;
   /*---(defense)------------------------*/
   if (RUN_QUIET)  return;
   /*---(va_args)------------------------*/
   va_start   (x_args, a_format);
   vsnprintf  (x_format, LEN_FULL - 1, a_format, x_args);
   va_end     (x_args);
   /*---(stderr)-------------------------*/
   fprintf    (stderr, "%-20.20s : %4d : %-10.10s,  %-80.80s\n", a_file, a_line, a_desc, x_format);
   /*---(log)----------------------------*/
   sprintf    (its.msg, "-10.10s : %s", a_desc, x_format);
   ylog__main (LVL_SAME, a_type, its.msg);
   /*---(complete)-----------------------*/
   return;
}



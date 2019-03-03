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

#define       SIGLOST       30
#define       SIGSTK        16

void
yLOG_signal        (const int   a_signal)
{
   switch (a_signal) {  /* 09 kill and 19 stop can not be caught, 26 is weird */
      /*---(user defined)--------*/
   case SIGHUP   :   strcpy (its.title, "SIGHUP"   );    strcpy (its.temp, "01 daemon/program should reassess and look around");  break;
   case SIGUSR1  :   strcpy (its.title, "SIGUSR1"  );    strcpy (its.temp, "10 user defined signal"                           );  break;
   case SIGUSR2  :   strcpy (its.title, "SIGUSR2"  );    strcpy (its.temp, "12 user defined signal"                           );  break;
   case SIGSTK   :   strcpy (its.title, "SIGSTK"   );    strcpy (its.temp, "16 stack fault, can make user defined"            );  break;
   case SIGLOST  :   strcpy (its.title, "SIGLOST"  );    strcpy (its.temp, "30 power failure, can make used defined"          );  break;
   case SIGSYS   :   strcpy (its.title, "SIGSYS"   );    strcpy (its.temp, "31 unused signal, can make used defined"          );  break;
                     /*---(normal activities)---*/
   case SIGALRM  :   strcpy (its.title, "SIGALRM"  );    strcpy (its.temp, "14 preset alarm requested with alarm()"           );  break;
   case SIGTERM  :   strcpy (its.title, "SIGTERM"  );    strcpy (its.temp, "15 termination"                                   );  break;
   case SIGCHLD  :   strcpy (its.title, "SIGCHLD"  );    strcpy (its.temp, "17 child process has stopped, exited, or changed" );  break;
   case SIGURG   :   strcpy (its.title, "SIGURG"   );    strcpy (its.temp, "23 urgent condition on socket"                    );  break;
   case SIGWINCH :   strcpy (its.title, "SIGWINCH" );    strcpy (its.temp, "28 window size changed"                           );  break;
   case SIGIO    :   strcpy (its.title, "SIGIO"    );    strcpy (its.temp, "29 input/output now possible (O_ASYNC on pipe)"   );  break;
                     /*---(terminal/console)----*/
   case SIGINT   :   strcpy (its.title, "SIGINT"   );    strcpy (its.temp, "02 console/tty/pty interrupt (control-c)"         );  break;
   case SIGQUIT  :   strcpy (its.title, "SIGQUIT"  );    strcpy (its.temp, "03 console/tty/pty quit (control-d)"              );  break;
   case SIGCONT  :   strcpy (its.title, "SIGCONT"  );    strcpy (its.temp, "18 console/tty/pty continue"                      );  break;
   case SIGTSTP  :   strcpy (its.title, "SIGTSTP"  );    strcpy (its.temp, "20 console/tty/pty stop (control-z)"              );  break;
   case SIGTTIN  :   strcpy (its.title, "SIGTTIN"  );    strcpy (its.temp, "21 background process trying to read tty/pty"     );  break;
   case SIGTTOU  :   strcpy (its.title, "SIGTTOU"  );    strcpy (its.temp, "22 background process trying to write tty/pty"    );  break;
                     /*---(limits and traps)----*/
   case SIGTRAP  :   strcpy (its.title, "SIGTRAP"  );    strcpy (its.temp, "05 trace trap"                                    );  break;
   case SIGXCPU  :   strcpy (its.title, "SIGXCPU"  );    strcpy (its.temp, "24 cpu time limit exceeded"                       );  break;
   case SIGXFSZ  :   strcpy (its.title, "SIGXFSZ"  );    strcpy (its.temp, "25 file size limit exceeded"                      );  break;
   case SIGPROF  :   strcpy (its.title, "SIGPROF"  );    strcpy (its.temp, "27 profiling alarm clock"                         );  break;
                     /*---(bad stuff)-----------*/
   case SIGILL   :   strcpy (its.title, "SIGILL"   );    strcpy (its.temp, "04 illegal instruction"                           );  break;
   case SIGABRT  :   strcpy (its.title, "SIGABRT"  );    strcpy (its.temp, "06 program or library called abort() function"    );  break;
   case SIGBUS   :   strcpy (its.title, "SIGBUS"   );    strcpy (its.temp, "07 bus error"                                     );  break;
   case SIGFPE   :   strcpy (its.title, "SIGFPE"   );    strcpy (its.temp, "08 floating point exception"                      );  break;
   case SIGSEGV  :   strcpy (its.title, "SIGSEGV"  );    strcpy (its.temp, "11 invalid memory segment access"                 );  break;
   case SIGPIPE  :   strcpy (its.title, "SIGPIPE"  );    strcpy (its.temp, "13 write on a pipe with no reader"                );  break;
                     /*---(crazy stuff)---------*/
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



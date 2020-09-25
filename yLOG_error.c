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
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", "WARNING", ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_WARNING , myLOG.msg);
   return;
}

void
yLOG_error         (const char *a_issue)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", "ERROR"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_ERROR   , myLOG.msg);
   return;
}

void
yLOG_fatal         (const char *a_issue)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_GRACEFUL, myLOG.msg);
   return;
}

void
yLOG_boom          (const char *a_issue)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   ylog__main (LVL_SAME, TYPE_CLUMSY  , myLOG.msg);
   return;
}

#define       SIGLOST       30
#define       SIGSTK        16

void
yLOG_signal        (const int   a_signal)
{
   switch (a_signal) {  /* 09 kill and 19 stop can not be caught, 26 is weird */
      /*---(user defined)--------*/
   case SIGHUP   :   strcpy (myLOG.title, "SIGHUP"   );    strcpy (myLOG.temp, "01 daemon/program should reassess and look around");  break;
   case SIGUSR1  :   strcpy (myLOG.title, "SIGUSR1"  );    strcpy (myLOG.temp, "10 user defined signal"                           );  break;
   case SIGUSR2  :   strcpy (myLOG.title, "SIGUSR2"  );    strcpy (myLOG.temp, "12 user defined signal"                           );  break;
   case SIGSTK   :   strcpy (myLOG.title, "SIGSTK"   );    strcpy (myLOG.temp, "16 stack fault, can make user defined"            );  break;
   case SIGLOST  :   strcpy (myLOG.title, "SIGLOST"  );    strcpy (myLOG.temp, "30 power failure, can make used defined"          );  break;
   case SIGSYS   :   strcpy (myLOG.title, "SIGSYS"   );    strcpy (myLOG.temp, "31 unused signal, can make used defined"          );  break;
                     /*---(normal activities)---*/
   case SIGALRM  :   strcpy (myLOG.title, "SIGALRM"  );    strcpy (myLOG.temp, "14 preset alarm requested with alarm()"           );  break;
   case SIGTERM  :   strcpy (myLOG.title, "SIGTERM"  );    strcpy (myLOG.temp, "15 termination"                                   );  break;
   case SIGCHLD  :   strcpy (myLOG.title, "SIGCHLD"  );    strcpy (myLOG.temp, "17 child process has stopped, exited, or changed" );  break;
   case SIGURG   :   strcpy (myLOG.title, "SIGURG"   );    strcpy (myLOG.temp, "23 urgent condition on socket"                    );  break;
   case SIGWINCH :   strcpy (myLOG.title, "SIGWINCH" );    strcpy (myLOG.temp, "28 window size changed"                           );  break;
   case SIGIO    :   strcpy (myLOG.title, "SIGIO"    );    strcpy (myLOG.temp, "29 input/output now possible (O_ASYNC on pipe)"   );  break;
                     /*---(terminal/console)----*/
   case SIGINT   :   strcpy (myLOG.title, "SIGINT"   );    strcpy (myLOG.temp, "02 console/tty/pty interrupt (control-c)"         );  break;
   case SIGQUIT  :   strcpy (myLOG.title, "SIGQUIT"  );    strcpy (myLOG.temp, "03 console/tty/pty quit (control-d)"              );  break;
   case SIGCONT  :   strcpy (myLOG.title, "SIGCONT"  );    strcpy (myLOG.temp, "18 console/tty/pty continue"                      );  break;
   case SIGTSTP  :   strcpy (myLOG.title, "SIGTSTP"  );    strcpy (myLOG.temp, "20 console/tty/pty stop (control-z)"              );  break;
   case SIGTTIN  :   strcpy (myLOG.title, "SIGTTIN"  );    strcpy (myLOG.temp, "21 background process trying to read tty/pty"     );  break;
   case SIGTTOU  :   strcpy (myLOG.title, "SIGTTOU"  );    strcpy (myLOG.temp, "22 background process trying to write tty/pty"    );  break;
                     /*---(limits and traps)----*/
   case SIGTRAP  :   strcpy (myLOG.title, "SIGTRAP"  );    strcpy (myLOG.temp, "05 trace trap"                                    );  break;
   case SIGXCPU  :   strcpy (myLOG.title, "SIGXCPU"  );    strcpy (myLOG.temp, "24 cpu time limit exceeded"                       );  break;
   case SIGXFSZ  :   strcpy (myLOG.title, "SIGXFSZ"  );    strcpy (myLOG.temp, "25 file size limit exceeded"                      );  break;
   case SIGPROF  :   strcpy (myLOG.title, "SIGPROF"  );    strcpy (myLOG.temp, "27 profiling alarm clock"                         );  break;
                     /*---(bad stuff)-----------*/
   case SIGILL   :   strcpy (myLOG.title, "SIGILL"   );    strcpy (myLOG.temp, "04 illegal instruction"                           );  break;
   case SIGABRT  :   strcpy (myLOG.title, "SIGABRT"  );    strcpy (myLOG.temp, "06 program or library called abort() function"    );  break;
   case SIGBUS   :   strcpy (myLOG.title, "SIGBUS"   );    strcpy (myLOG.temp, "07 bus error"                                     );  break;
   case SIGFPE   :   strcpy (myLOG.title, "SIGFPE"   );    strcpy (myLOG.temp, "08 floating point exception"                      );  break;
   case SIGSEGV  :   strcpy (myLOG.title, "SIGSEGV"  );    strcpy (myLOG.temp, "11 invalid memory segment access"                 );  break;
   case SIGPIPE  :   strcpy (myLOG.title, "SIGPIPE"  );    strcpy (myLOG.temp, "13 write on a pipe with no reader"                );  break;
                     /*---(crazy stuff)---------*/
   default      :   strcpy (myLOG.title, "¢unknown?");  strcpy (myLOG.temp, "unknown");                                         break;
   }
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", myLOG.title, myLOG.temp);
   ylog__main (LVL_SAME, TYPE_CALLBACK, myLOG.msg);
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
   IF_QUIET  return;
   /*---(va_args)------------------------*/
   va_start   (x_args, a_format);
   vsnprintf  (x_format, LEN_FULL - 1, a_format, x_args);
   va_end     (x_args);
   /*---(stderr)-------------------------*/
   IF_LOGGER  fprintf    (stderr, "%-20.20s : %4d : %-10.10s,  %-80.80s\n", a_file, a_line, a_desc, x_format);
   /*---(log)----------------------------*/
   sprintf    (myLOG.msg, "-10.10s : %s", a_desc, x_format);
   ylog__main (LVL_SAME, a_type, myLOG.msg);
   /*---(complete)-----------------------*/
   return;
}



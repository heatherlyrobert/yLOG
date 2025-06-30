#include  "yLOG.h"
#include  "yLOG_priv.h"




/*====================------------------------------------====================*/
/*===----                          simple versions                     ----===*/
/*====================------------------------------------====================*/
static void      o___SIMPLE__________________o (void) {;}

char
yLOG_warn          (char *a_issue)
{
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", "WARNING", ylog_data (a_issue));
   return ylog__main (LVL_SAME, TYPE_WARNING , myLOG.m_msg);
}

char
yLOG_error         (char *a_issue)
{
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", "ERROR"  , ylog_data (a_issue));
   return ylog__main (LVL_SAME, TYPE_ERROR   , myLOG.m_msg);
}

char
yLOG_fatal         (char *a_issue)
{
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   return ylog__main (LVL_SAME, TYPE_GRACEFUL, myLOG.m_msg);
}

char
yLOG_boom          (char *a_issue)
{
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", "FATAL"  , ylog_data (a_issue));
   return ylog__main (LVL_SAME, TYPE_CLUMSY  , myLOG.m_msg);
}

#define       SIGLOST       30
#define       SIGSTK        16

char
yLOG_signal        (int   a_signal)
{
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   switch (a_signal) {  /* 09 kill and 19 stop can not be caught, 26 is weird */
      /*---(user defined)--------*/
   case SIGHUP   :   strcpy (myLOG.m_title, "SIGHUP"   );    strcpy (myLOG.m_temp, "01 daemon/program should reassess and look around");  break;
   case SIGUSR1  :   strcpy (myLOG.m_title, "SIGUSR1"  );    strcpy (myLOG.m_temp, "10 user defined signal"                           );  break;
   case SIGUSR2  :   strcpy (myLOG.m_title, "SIGUSR2"  );    strcpy (myLOG.m_temp, "12 user defined signal"                           );  break;
   case SIGSTK   :   strcpy (myLOG.m_title, "SIGSTK"   );    strcpy (myLOG.m_temp, "16 stack fault, can make user defined"            );  break;
   case SIGLOST  :   strcpy (myLOG.m_title, "SIGLOST"  );    strcpy (myLOG.m_temp, "30 power failure, can make used defined"          );  break;
   case SIGSYS   :   strcpy (myLOG.m_title, "SIGSYS"   );    strcpy (myLOG.m_temp, "31 unused signal, can make used defined"          );  break;
                     /*---(normal activities)---*/
   case SIGALRM  :   strcpy (myLOG.m_title, "SIGALRM"  );    strcpy (myLOG.m_temp, "14 preset alarm requested with alarm()"           );  break;
   case SIGTERM  :   strcpy (myLOG.m_title, "SIGTERM"  );    strcpy (myLOG.m_temp, "15 termination"                                   );  break;
   case SIGCHLD  :   strcpy (myLOG.m_title, "SIGCHLD"  );    strcpy (myLOG.m_temp, "17 child process has stopped, exited, or changed" );  break;
   case SIGURG   :   strcpy (myLOG.m_title, "SIGURG"   );    strcpy (myLOG.m_temp, "23 urgent condition on socket"                    );  break;
   case SIGWINCH :   strcpy (myLOG.m_title, "SIGWINCH" );    strcpy (myLOG.m_temp, "28 window size changed"                           );  break;
   case SIGIO    :   strcpy (myLOG.m_title, "SIGIO"    );    strcpy (myLOG.m_temp, "29 input/output now possible (O_ASYNC on pipe)"   );  break;
                     /*---(terminal/console)----*/
   case SIGINT   :   strcpy (myLOG.m_title, "SIGINT"   );    strcpy (myLOG.m_temp, "02 console/tty/pty interrupt (control-c)"         );  break;
   case SIGQUIT  :   strcpy (myLOG.m_title, "SIGQUIT"  );    strcpy (myLOG.m_temp, "03 console/tty/pty quit (control-d)"              );  break;
   case SIGCONT  :   strcpy (myLOG.m_title, "SIGCONT"  );    strcpy (myLOG.m_temp, "18 console/tty/pty continue"                      );  break;
   case SIGTSTP  :   strcpy (myLOG.m_title, "SIGTSTP"  );    strcpy (myLOG.m_temp, "20 console/tty/pty stop (control-z)"              );  break;
   case SIGTTIN  :   strcpy (myLOG.m_title, "SIGTTIN"  );    strcpy (myLOG.m_temp, "21 background process trying to read tty/pty"     );  break;
   case SIGTTOU  :   strcpy (myLOG.m_title, "SIGTTOU"  );    strcpy (myLOG.m_temp, "22 background process trying to write tty/pty"    );  break;
                     /*---(limits and traps)----*/
   case SIGTRAP  :   strcpy (myLOG.m_title, "SIGTRAP"  );    strcpy (myLOG.m_temp, "05 trace trap"                                    );  break;
   case SIGXCPU  :   strcpy (myLOG.m_title, "SIGXCPU"  );    strcpy (myLOG.m_temp, "24 cpu time limit exceeded"                       );  break;
   case SIGXFSZ  :   strcpy (myLOG.m_title, "SIGXFSZ"  );    strcpy (myLOG.m_temp, "25 file size limit exceeded"                      );  break;
   case SIGPROF  :   strcpy (myLOG.m_title, "SIGPROF"  );    strcpy (myLOG.m_temp, "27 profiling alarm clock"                         );  break;
                     /*---(bad stuff)-----------*/
   case SIGILL   :   strcpy (myLOG.m_title, "SIGILL"   );    strcpy (myLOG.m_temp, "04 illegal instruction"                           );  break;
   case SIGABRT  :   strcpy (myLOG.m_title, "SIGABRT"  );    strcpy (myLOG.m_temp, "06 program or library called abort() function"    );  break;
   case SIGBUS   :   strcpy (myLOG.m_title, "SIGBUS"   );    strcpy (myLOG.m_temp, "07 bus error"                                     );  break;
   case SIGFPE   :   strcpy (myLOG.m_title, "SIGFPE"   );    strcpy (myLOG.m_temp, "08 floating point exception"                      );  break;
   case SIGSEGV  :   strcpy (myLOG.m_title, "SIGSEGV"  );    strcpy (myLOG.m_temp, "11 invalid memory segment access"                 );  break;
   case SIGPIPE  :   strcpy (myLOG.m_title, "SIGPIPE"  );    strcpy (myLOG.m_temp, "13 write on a pipe with no reader"                );  break;
                     /*---(crazy stuff)---------*/
   default      :   strcpy (myLOG.m_title, "¢unknown?");  strcpy (myLOG.m_temp, "unknown");                                         break;
   }
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", myLOG.m_title, myLOG.m_temp);
   return ylog__main (LVL_SAME, TYPE_CALLBACK, myLOG.m_msg);
}



/*====================------------------------------------====================*/
/*===----                        complex errors                        ----===*/
/*====================------------------------------------====================*/
static void      o___COMPLEX_________________o (void) {;}

char
yLOG_errors        (char *a_desc, char a_type, char *a_file, int a_line, char *a_format, ...)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_format    [LEN_FULL]  = "";
   va_list     x_args;
   /*---(defense)------------------------*/
   IF_QUIET   return 0;
   IF_NOSHOW  return 0;
   /*---(va_args)------------------------*/
   va_start   (x_args, a_format);
   vsnprintf  (x_format, LEN_FULL - 1, a_format, x_args);
   va_end     (x_args);
   /*---(stderr)-------------------------*/
   IF_LOGGER  fprintf    (stderr, "%-20.20s : %4d : %-10.10s,  %-80.80s\n", a_file, a_line, a_desc, x_format);
   /*---(log)----------------------------*/
   sprintf    (myLOG.m_msg, "-10.10s : %s", a_desc, x_format);
   /*---(complete)-----------------------*/
   return ylog__main (LVL_SAME, a_type, myLOG.m_msg);
}



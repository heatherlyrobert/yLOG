/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"




/*====================------------------------------------====================*/
/*===----                             errors                           ----===*/
/*====================------------------------------------====================*/
static void      o___ERRORS__________________o (void) {;}

void
yLOG_hintx         (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [LEN_FULL] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL - 1, a_format, args);
   x_format [LEN_FULL - 1] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : HINT,  %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its.quiet) {
      vsnprintf (x_format, LEN_FULL - 1, a_format, args);
      sprintf   (its.msg, "HINT      : %s", x_format);
      ylog__main (LVL_SAME, TYPE_WARNING, its.msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_warn          (const char *a_item,    const char *a_issue)
{
   if (its.quiet) return;
   sprintf(its.msg, "WARNING   : (%.15s) %.45s", a_item, a_issue);
   ylog__main (LVL_SAME, TYPE_WARNING, its.msg);
   return;
}

void
yLOG_warnx         (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [LEN_FULL] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL - 1, a_format, args);
   x_format [LEN_FULL - 1] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : WARN,  %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   /*> if (!its.quiet) {                                                              <* 
    *>    vsnprintf (x_format, LEN_FULL - 1, a_format, args);                                  <* 
    *>    sprintf   (its.msg, "WARNING   : %s", x_format);                            <* 
    *>    ylog__main (LVL_SAME, TYPE_WARNING, its.msg);                                              <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_error    (const char *a_item,    const char *a_issue)
{
   if (its.quiet) return;
   sprintf(its.msg, "ERROR     : (%.15s) %.45s", a_item, a_issue);
   ylog__main (LVL_SAME, TYPE_ERROR, its.msg);
   return;
}

void
yLOG_errorx        (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [LEN_FULL] = "";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL - 1, a_format, args);
   x_format [LEN_FULL - 1] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : ERROR, %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its.quiet) {
      vsnprintf (x_format, LEN_FULL - 1, a_format, args);
      sprintf   (its.msg, "ERROR     : %s", x_format);
      ylog__main (LVL_SAME, TYPE_ERROR, its.msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

void
yLOG_fatal    (const char *a_item,    const char *a_issue)
{
   if (its.quiet) return;
   sprintf(its.msg, "FATAL     : (%.15s) %.45s", a_item, a_issue);
   ylog__main (LVL_SAME, TYPE_GRACEFUL, its.msg);
   return;
}

void
yLOG_fatalx        (cchar *a_file, cint a_line, char *a_reason, cchar *a_format, ...)
{
   /*---(locals)-------*-----------------*/
   char      x_format [LEN_FULL] = "FATAL, ";
   va_list   args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL - 1, a_format, args);
   x_format [LEN_FULL - 1] = '\0';
   fprintf   (stderr, "%-20.20s : %4d : FATAL, %-80.80s  [ %-12.12s ]\n", a_file, a_line, x_format, a_reason);
   /*---(to log)-------------------------*/
   if (!its.quiet) {
      vsnprintf (x_format, LEN_FULL - 1, a_format, args);
      x_format [LEN_FULL - 1] = '\0';
      sprintf   (its.msg, "FATAL     : %s", x_format);
      ylog__main (LVL_SAME, TYPE_GRACEFUL, its.msg);
   }
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

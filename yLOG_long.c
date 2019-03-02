/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"




/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

void
yLOG_enter    (const char *a_func)
{
   if (its.quiet) return;
   snprintf (its.msg, LEN_PATH, "ENTERING (%.30s)", a_func);
   ylog__main (LVL_BEG , TYPE_STRUCT, its.msg);
   return;
}

void
yLOG_exit     (const char *a_func)
{
   if (its.quiet) return;
   snprintf (its.msg, LEN_PATH, "EXITING  (%.30s)", a_func);
   ylog__main (LVL_END , TYPE_STRUCT, its.msg);
   return;
}

void
yLOG_exitr    (const char *a_func, const int a_rce)
{
   if (its.quiet) return;
   snprintf (its.msg, LEN_PATH, "WARNING, rce (%d)", a_rce);
   ylog__main (LVL_SAME, TYPE_WARNING, its.msg);
   snprintf (its.msg, LEN_PATH, "EXITING  (%.30s)", a_func);
   ylog__main (LVL_END , TYPE_STRUCT, its.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES________________o (void) {;}

void
yLOG_note          (const char *a_info)
{
   if (its.quiet) return;
   snprintf(its.msg, 190, "%.150s...", a_info);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_info          (const char *a_subject, const char *a_info)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %.150s", a_subject, a_info);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_delim         (const char *a_subject, const char *a_info)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: <<%.50s>>", a_subject, a_info);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_char          (const char *a_subject, const char a_char)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %c", a_subject, (unsigned char) chrvisible (a_char));
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_value         (const char *a_subject, const int a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %d", a_subject, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_hex           (const char *a_subject, const int a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: 0x%08x", a_subject, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_llong         (const char *a_subject, const long long a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %lld", a_subject, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_double        (const char *a_subject, const double a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %20.6lf", a_subject, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_point         (const char *a_subject, const void *a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10.10s: %p", a_subject, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                          special                             ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

void
yLOG_bullet        (const int   a_num,     const char *a_info)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10d: %.50s", a_num, a_info);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}

void
yLOG_pair          (const int   a_num,     const int  a_value)
{
   if (its.quiet) return;
   sprintf(its.msg, "%-10d: %d", a_num, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG__________________o (void) {;}

void
yLOG_complex       (const char *a_subject, cchar *a_format, ...)
{
   if (its.quiet) return;
   /*---(locals)---------+-------------+-*/
   char        x_format  [200] = "";
   va_list     args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, 190, a_format, args);
   sprintf   (its.msg, "%-10.10s: %.150s", a_subject, x_format);
   ylog__main (LVL_SAME, TYPE_INFO, its.msg);
   /*---(complete)-----------------------*/
   va_end    (args);
   return;
}

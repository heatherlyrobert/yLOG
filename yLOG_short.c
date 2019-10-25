/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        start and stop                        ----===*/
/*====================------------------------------------====================*/
static void      o___ENDS____________________o (void) {;}

void
yLOG_senter   (const char *a_func)
{
   ylog_check_enter (a_func);
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, "%.30s>>", ylog_title (a_func));
   strlcpy  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_sexit    (const char *a_func)
{
   if (RUN_QUIET)  return;
   strlcat  (its.single, ";;", LEN_FULL);
   ylog__main (LVL_SAME, TYPE_STRUCT, its.single);
   ylog_check_exit  (a_func);
   return;
}

void
yLOG_sexitr   (const char *a_func, const int a_rce)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", WARN %d;;", a_rce);
   strlcat  (its.single, its.temp, LEN_FULL);
   ylog__main (LVL_SAME, TYPE_WARNING, its.single);
   ylog_check_exit  (a_func);
   return;
}



/*====================------------------------------------====================*/
/*===----                         data content                         ----===*/
/*====================------------------------------------====================*/
static void      o___CONTENT_________________o (void) {;}

void
yLOG_snote    (const char *a_info)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %s", ylog_title (a_info));
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_sint     (const int  a_value)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %d", a_value);
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_sdouble  (const double  a_value)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %.6lf", a_value);
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_shex     (const long  a_value)
{
   if (RUN_QUIET)  return;
   if (a_value < 0)                 sprintf (its.temp, ", ¢negative?");
   else if (a_value > 0xFFFFFFFF)   sprintf (its.temp, ", ¢overflow?");
   else                             sprintf (its.temp, ", 0x%08X", a_value);
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_spoint   (const void *a_pointer)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %p", a_pointer);
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_schar    (const char a_char)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %c", (unsigned char) chrvisible (a_char));
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}



/*====================------------------------------------====================*/
/*===----                  labeled data content                        ----===*/
/*====================------------------------------------====================*/
static void      o___LABELED_________________o (void) {;}

void
yLOG_sinfo    (const char *a_subject, const char *a_info)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %s=%s", ylog_title (a_subject), ylog_terse (a_info));
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}

void
yLOG_svalue   (const char *a_subject, const int  a_value)
{
   if (RUN_QUIET)  return;
   snprintf (its.temp, LEN_FULL, ", %s=%d", ylog_title (a_subject), a_value);
   strlcat  (its.single, its.temp, LEN_FULL);
   return;
}




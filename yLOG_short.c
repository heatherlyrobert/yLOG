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
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, "%.30s>>", a_func);
   strlcpy (its.single, msg, 200);
   return;
}

void
yLOG_sexit    (const char *a_func)
{
   if (its.quiet) return;
   strlcat (its.single, ";;", 200);
   yLOG__main('-', 's', its.single);
   return;
}

void
yLOG_sexitr   (const char *a_func, const int a_rce)
{
   char  msg[200];
   if (its.quiet) return;
   snprintf(msg, 200, ", WARN %d;;", a_rce);
   strlcat (its.single, msg, 200);
   yLOG__main('-', 'w', its.single);
   return;
}



/*====================------------------------------------====================*/
/*===----                         data content                         ----===*/
/*====================------------------------------------====================*/
static void      o___CONTENT_________________o (void) {;}

void
yLOG_snote    (const char *a_info)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s", a_info);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_sint     (const int  a_value)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %d", a_value);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_sdouble  (const double  a_value)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %.6lf", a_value);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_shex     (const unsigned int  a_value)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", 0x%08x", a_value);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_spoint   (const void *a_pointer)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %p", a_pointer);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_schar    (const char a_info)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %c", a_info);
   strlcat (its.single, msg, 200);
   return;
}



/*====================------------------------------------====================*/
/*===----                  labeled data content                        ----===*/
/*====================------------------------------------====================*/
static void      o___LABELED_________________o (void) {;}

void
yLOG_sinfo    (const char *a_subject, const char *a_info)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s=%s", a_subject, a_info);
   strlcat (its.single, msg, 200);
   return;
}

void
yLOG_svalue   (const char *a_subject, const int  a_value)
{
   if (its.quiet) return;
   char  msg[200];
   snprintf(msg, 200, ", %s=%d", a_subject, a_value);
   strlcat (its.single, msg, 200);
   return;
}




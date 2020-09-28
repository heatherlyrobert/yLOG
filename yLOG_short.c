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
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, "%.30s>>", ylog_title (a_func));
   strncpy  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_sexit    (const char *a_func)
{
   IF_QUIET  return;
   strncat  (myLOG.single, ";;", LEN_FULL);
   ylog__main (LVL_SAME, TYPE_STRUCT, myLOG.single);
   ylog_check_exit  (a_func);
   return;
}

void
yLOG_sexitr   (const char *a_func, const int a_rce)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", WARN %d;;", a_rce);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   ylog__main (LVL_SAME, TYPE_WARNING, myLOG.single);
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
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %s", ylog_title (a_info));
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_sint     (const int  a_value)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %d", a_value);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_sdouble  (const double  a_value)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %.6lf", a_value);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_shex     (const long  a_value)
{
   IF_QUIET  return;
   if (a_value < 0)                 sprintf (myLOG.temp, ", ¢negative?");
   else if (a_value > 0xFFFFFFFF)   sprintf (myLOG.temp, ", ¢overflow?");
   else                             sprintf (myLOG.temp, ", 0x%08X", a_value);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_spoint   (const void *a_pointer)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %p", a_pointer);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_schar    (const unsigned char a_char)
{
   unsigned char c  = 'Ï';
   IF_QUIET  return;
   if (a_char >   32 && a_char <  127)  c = a_char;
   if (a_char >  160)                   c = a_char;
   switch (a_char) {
   case   0 : c = '£';  break;   /* null   */
   case  10 : c = '¦';  break;   /* return */
   case  13 : c = '¦';  break;   /* enter  */
   case  27 : c = '¥';  break;   /* escape */
   case  29 : c = '¨';  break;   /* group  */
   case  31 : c = '§';  break;   /* escape */
   case  32 : c = '·';  break;   /* space  */
   }
   snprintf (myLOG.temp, LEN_FULL, ", %c", c);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}



/*====================------------------------------------====================*/
/*===----                  labeled data content                        ----===*/
/*====================------------------------------------====================*/
static void      o___LABELED_________________o (void) {;}

void
yLOG_sinfo    (const char *a_subject, const char *a_info)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %s=%s", ylog_title (a_subject), ylog_terse (a_info));
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}

void
yLOG_svalue   (const char *a_subject, const int  a_value)
{
   IF_QUIET  return;
   snprintf (myLOG.temp, LEN_FULL, ", %s=%d", ylog_title (a_subject), a_value);
   strncat  (myLOG.single, myLOG.temp, LEN_FULL);
   return;
}




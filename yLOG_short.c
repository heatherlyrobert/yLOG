/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        start and stop                        ----===*/
/*====================------------------------------------====================*/
static void      o___ENDS____________________o (void) {;}

char
yLOG_senter   (char a_func [LEN_TITLE])
{
   ylog_check_enter (a_func);
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, "%.30s>>", ylog_title (a_func));
   strncpy  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 0;
}

char
yLOG_sexit    (char a_func [LEN_TITLE])
{
   char        rc          =    0;
   IF_NOSHOW  return 0;
   strncat  (myLOG.m_single, ";;", LEN_FULL);
   rc = ylog__main (LVL_SAME, TYPE_STRUCT, myLOG.m_single);
   ylog_check_exit  (a_func);
   return rc;
}

char
yLOG_sexitr   (char a_func [LEN_TITLE], int a_rce)
{
   char        rc          =    0;
   char        x_type      =  '-';
   char        x_note      [LEN_TERSE] = "";
   IF_NOSHOW  return 0;
   if (a_rce >= 0) { x_type = TYPE_STRUCT;  strcpy (x_note, "NOTE"); }
   else            { x_type = TYPE_WARNING; strcpy (x_note, "WARN"); }
   snprintf (myLOG.m_temp, LEN_FULL, ", %s %d;;", x_note, a_rce);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   rc = ylog__main (LVL_SAME, x_type, myLOG.m_single);
   ylog_check_exit  (a_func);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         data content                         ----===*/
/*====================------------------------------------====================*/
static void      o___CONTENT_________________o (void) {;}

char
yLOG_snote    (char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %s", ylog_title (a_info));
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char
yLOG_sint     (cint  a_value)
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %d", a_value);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char
yLOG_sdouble  (double  a_value)
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %.6lf", a_value);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char yLOG_sreal (double  a_value)  { return yLOG_sdouble (a_value); }

char
yLOG_shex     (long  a_value)
{
   IF_NOSHOW  return 0;
   if (a_value < 0)                 sprintf (myLOG.m_temp, ", ¢negative?");
   else if (a_value > 0xFFFFFFFF)   sprintf (myLOG.m_temp, ", ¢overflow?");
   else                             sprintf (myLOG.m_temp, ", 0x%08X", a_value);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char
yLOG_spoint   (void *a_pointer)
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %p", a_pointer);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char
yLOG_schar    (uchar a_char)
{
   unsigned char c  = 'Ï';
   IF_NOSHOW  return 0;
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
   snprintf (myLOG.m_temp, LEN_FULL, ", %c", c);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                  labeled data content                        ----===*/
/*====================------------------------------------====================*/
static void      o___LABELED_________________o (void) {;}

char
yLOG_sinfo    (char a_subject [LEN_LABEL], char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %s=%s", ylog_title (a_subject), ylog_terse (a_info));
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}

char
yLOG_svalue   (char a_subject [LEN_LABEL], cint  a_value)
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_temp, LEN_FULL, ", %s=%d", ylog_title (a_subject), a_value);
   strncat  (myLOG.m_single, myLOG.m_temp, LEN_FULL);
   return 1;
}




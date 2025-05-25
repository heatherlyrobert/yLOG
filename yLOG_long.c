/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                       helper functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char*        /*--> defense for bad titles in longs ---------------------------*/
ylog_title         (char *a_title)
{
   if (a_title == NULL)              strncpy (myLOG.m_title, "¢null?"  , LEN_FULL);
   else if (strlen (a_title) <= 0)   strncpy (myLOG.m_title, "¢empty?" , LEN_FULL);
   else                              strncpy (myLOG.m_title, a_title   , LEN_FULL);
   return myLOG.m_title;
}

char*        /*--> defense for bad data in longs -----------------------------*/
ylog_data          (char *a_data)
{
   if (a_data == NULL)               strncpy (myLOG.m_data , "¢ data was null ?" , LEN_FULL);
   else if (strlen (a_data) <= 0)    strncpy (myLOG.m_data , "¢ data was empty ?", LEN_FULL);
   else                              strncpy (myLOG.m_data , a_data              , LEN_FULL);
   return myLOG.m_data;
}

char*        /*--> defense for bad data in shorts ----------------------------*/
ylog_terse         (char *a_data)
{
   if (a_data == NULL)               strncpy (myLOG.m_data , "¢null?"  , LEN_FULL);
   else if (strlen (a_data) <= 0)    strncpy (myLOG.m_data , "¢empty?" , LEN_FULL);
   else                              strncpy (myLOG.m_data , a_data    , LEN_FULL);
   return myLOG.m_data;
}



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

char
yLOG_enter    (char a_func [LEN_TITLE])
{
   ylog_check_enter (a_func);
   snprintf (myLOG.m_msg, LEN_FULL, "ENTERING (%.30s)", ylog_title (a_func));
   return ylog__main (LVL_BEG , TYPE_STRUCT, myLOG.m_msg);
}

char
yLOG_exit     (char a_func [LEN_TITLE])
{
   char        rc          =    0;
   snprintf (myLOG.m_msg, LEN_FULL, "EXITING  (%.30s)", ylog_title (a_func));
   rc = ylog__main (LVL_END , TYPE_STRUCT, myLOG.m_msg);
   ylog_check_exit (a_func);
   return rc;
}

char
yLOG_exitr    (char a_func [LEN_TITLE], int a_rce)
{
   if (a_rce < 0) {
      snprintf (myLOG.m_msg, LEN_FULL, "WARNING, rce (%d)", a_rce);
      ylog__main (LVL_SAME, TYPE_WARNING, myLOG.m_msg);
   } else if (a_rce > 0) {
      snprintf (myLOG.m_msg, LEN_FULL, "NOTE, rc (%d)", a_rce);
      ylog__main (LVL_SAME, TYPE_WARNING, myLOG.m_msg);
   }
   return yLOG_exit (a_func);
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES________________o (void) {;}

char
yLOG_note          (char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%.150s...", ylog_data (a_info));
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_info          (char a_subject [LEN_LABEL], char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: %.150s", ylog_title (a_subject), ylog_data (a_info));
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_delim         (char a_subject [LEN_LABEL], char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   snprintf (myLOG.m_msg, LEN_FULL, "%-10.10s: [%.50s]", ylog_title (a_subject), ylog_data (a_info));
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_char          (char a_subject [LEN_LABEL], unsigned char a_char)
{
   unsigned char c  = 'Ï';
   IF_NOSHOW  return 0;
   if (a_char >   32 && a_char != 127)  c = a_char;
   switch (a_char) {
   case   0 : c = '£';  break;   /* null   */
   case  10 : c = '¦';  break;   /* return */
   case  13 : c = '¦';  break;   /* enter  */
   case  27 : c = '¥';  break;   /* escape */
   case  29 : c = '¨';  break;   /* group  */
   case  31 : c = '§';  break;   /* escape */
   case  32 : c = '·';  break;   /* space  */
   }
   sprintf (myLOG.m_msg, "%-10.10s: %c", ylog_title (a_subject), c);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_value         (char a_subject [LEN_LABEL], cint a_value)
{
   IF_NOSHOW  return 0;
   sprintf(myLOG.m_msg, "%-10.10s: %d", ylog_title (a_subject), a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_hex           (char a_subject [LEN_LABEL], long a_value)
{
   /* used 08 format so the hex lines up top-to-bottom in lines  */
   IF_NOSHOW  return 0;
   if (a_value < 0)                 sprintf(myLOG.m_msg, "%-10.10s: ¢negative?", ylog_title (a_subject));
   else if (a_value > 0xFFFFFFFF)   sprintf(myLOG.m_msg, "%-10.10s: ¢overflow?", ylog_title (a_subject));
   else                             sprintf(myLOG.m_msg, "%-10.10s: 0x%08X", ylog_title (a_subject), a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}


char
yLOG_llong         (char a_subject [LEN_LABEL], llong a_value)
{
   IF_NOSHOW  return 0;
   sprintf(myLOG.m_msg, "%-10.10s: %lld", ylog_title (a_subject), a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_double        (char a_subject [LEN_LABEL], double a_value)
{
   /* used 20.6 format so the decimals line up top-to-bottom in lines  */
   IF_NOSHOW  return 0;
   sprintf(myLOG.m_msg, "%-10.10s: %20.6lf", ylog_title (a_subject), a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char yLOG_real  (char a_subject [LEN_LABEL], double a_value) { return yLOG_double (a_subject, a_value); }

char
yLOG_point         (char a_subject [LEN_LABEL], void *a_value)
{
   IF_NOSHOW  return 0;
   sprintf (myLOG.m_msg, "%-10.10s: %p", ylog_title (a_subject), a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}



/*====================------------------------------------====================*/
/*===----                          special                             ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

char
yLOG_bullet        (cint   a_num,     char a_info [LEN_FULL])
{
   IF_NOSHOW  return 0;
   sprintf(myLOG.m_msg, "#%-9d: %.150s", a_num, ylog_data (a_info));
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}

char
yLOG_pair          (cint   a_num,     cint  a_value)
{
   IF_NOSHOW  return 0;
   sprintf(myLOG.m_msg, "#%-9d: %d", a_num, a_value);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG__________________o (void) {;}

char
yLOG_complex       (char a_subject [LEN_LABEL], char *a_format, ...)
{
   IF_NOSHOW  return 0;
   /*---(locals)---------+-------------+-*/
   char        x_format  [LEN_FULL] = "";
   va_list     args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL, a_format, args);
   if (a_subject != NULL && strcmp (a_subject, "ERROR") == 0) {
      sprintf   (myLOG.m_msg, "%s", x_format);
   } else {
      sprintf   (myLOG.m_msg, "%-10.10s: %.150s", ylog_title (a_subject), x_format);
   }
   va_end    (args);
   return ylog__main (LVL_SAME, TYPE_INFO, myLOG.m_msg);
}


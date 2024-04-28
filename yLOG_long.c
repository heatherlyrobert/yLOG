/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                       helper functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char*        /*--> defense for bad titles in longs ---------------------------*/
ylog_title         (cchar *a_title)
{
   if (a_title == NULL)              strncpy (myLOG.title, "¢null?"  , LEN_FULL);
   else if (strlen (a_title) <= 0)   strncpy (myLOG.title, "¢empty?" , LEN_FULL);
   else                              strncpy (myLOG.title, a_title   , LEN_FULL);
   return myLOG.title;
}

char*        /*--> defense for bad data in longs -----------------------------*/
ylog_data          (cchar *a_data)
{
   if (a_data == NULL)               strncpy (myLOG.data , "¢ data was null ?" , LEN_FULL);
   else if (strlen (a_data) <= 0)    strncpy (myLOG.data , "¢ data was empty ?", LEN_FULL);
   else                              strncpy (myLOG.data , a_data              , LEN_FULL);
   return myLOG.data;
}

char*        /*--> defense for bad data in shorts ----------------------------*/
ylog_terse         (cchar *a_data)
{
   if (a_data == NULL)               strncpy (myLOG.data , "¢null?"  , LEN_FULL);
   else if (strlen (a_data) <= 0)    strncpy (myLOG.data , "¢empty?" , LEN_FULL);
   else                              strncpy (myLOG.data , a_data   , LEN_FULL);
   return myLOG.data;
}



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

void
yLOG_enter    (cchar a_func [LEN_TITLE])
{
   ylog_check_enter (a_func);
   /*> IF_QUIET  return;                                                              <*/
   snprintf (myLOG.msg, LEN_PATH, "ENTERING (%.30s)", ylog_title (a_func));
   ylog__main (LVL_BEG , TYPE_STRUCT, myLOG.msg);
   return;
}

void
yLOG_exit     (cchar a_func [LEN_TITLE])
{
   /*> IF_QUIET  return;                                                              <*/
   snprintf (myLOG.msg, LEN_PATH, "EXITING  (%.30s)", ylog_title (a_func));
   ylog__main (LVL_END , TYPE_STRUCT, myLOG.msg);
   ylog_check_exit (a_func);
   return;
}

void
yLOG_exitr    (cchar a_func [LEN_TITLE], cint a_rce)
{
   /*> IF_QUIET  return;                                                              <*/
   if (a_rce < 0) {
      snprintf (myLOG.msg, LEN_PATH, "WARNING, rce (%d)", a_rce);
      ylog__main (LVL_SAME, TYPE_WARNING, myLOG.msg);
   } else if (a_rce > 0) {
      snprintf (myLOG.msg, LEN_PATH, "NOTE, rc (%d)", a_rce);
      ylog__main (LVL_SAME, TYPE_WARNING, myLOG.msg);
   }
   snprintf (myLOG.msg, LEN_PATH, "EXITING  (%.30s)", ylog_title (a_func));
   ylog__main (LVL_END , TYPE_STRUCT, myLOG.msg);
   ylog_check_exit (a_func);
   return;
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES________________o (void) {;}

void
yLOG_note          (cchar a_info [LEN_FULL])
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%.150s...", ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_info          (cchar a_subject [LEN_LABEL], cchar a_info [LEN_FULL])
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", ylog_title (a_subject), ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_delim         (cchar a_subject [LEN_LABEL], cchar a_info [LEN_FULL])
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: [%.50s]", ylog_title (a_subject), ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_char          (cchar a_subject [LEN_LABEL], const unsigned char a_char)
{
   unsigned char c  = 'Ï';
   IF_QUIET  return;
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
   sprintf (myLOG.msg, "%-10.10s: %c", ylog_title (a_subject), c);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_value         (cchar a_subject [LEN_LABEL], cint a_value)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %d", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_hex           (cchar a_subject [LEN_LABEL], const long a_value)
{
   /* used 08 format so the hex lines up top-to-bottom in lines  */
   IF_QUIET  return;
   if (a_value < 0)                 sprintf(myLOG.msg, "%-10.10s: ¢negative?", ylog_title (a_subject));
   else if (a_value > 0xFFFFFFFF)   sprintf(myLOG.msg, "%-10.10s: ¢overflow?", ylog_title (a_subject));
   else                             sprintf(myLOG.msg, "%-10.10s: 0x%08X", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_llong         (cchar a_subject [LEN_LABEL], const long long a_value)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %lld", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_double        (cchar a_subject [LEN_LABEL], const double a_value)
{
   /* used 20.6 format so the decimals line up top-to-bottom in lines  */
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %20.6lf", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void yLOG_real  (cchar a_subject [LEN_LABEL], const double a_value) { return yLOG_double (a_subject, a_value); }

void
yLOG_point         (cchar a_subject [LEN_LABEL], cvoid *a_value)
{
   IF_QUIET  return;
   sprintf (myLOG.msg, "%-10.10s: %p", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                          special                             ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;}

void
yLOG_bullet        (cint   a_num,     cchar a_info [LEN_FULL])
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "#%-9d: %.150s", a_num, ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_pair          (cint   a_num,     cint  a_value)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "#%-9d: %d", a_num, a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG__________________o (void) {;}

void
yLOG_complex       (cchar a_subject [LEN_LABEL], cchar *a_format, ...)
{
   IF_QUIET  return;
   /*---(locals)---------+-------------+-*/
   char        x_format  [LEN_FULL] = "";
   va_list     args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL, a_format, args);
   if (a_subject != NULL && strcmp (a_subject, "ERROR") == 0) {
      sprintf   (myLOG.msg, "%s", x_format);
   } else {
      sprintf   (myLOG.msg, "%-10.10s: %.150s", ylog_title (a_subject), x_format);
   }
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   va_end    (args);
   /*---(complete)-----------------------*/
   return;
}


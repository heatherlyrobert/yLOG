/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                       helper functions                       ----===*/
/*====================------------------------------------====================*/
static void      o___HELPERS_________________o (void) {;}

char*        /*--> defense for bad titles in longs ---------------------------*/
ylog_title         (const char *a_title)
{
   if (a_title == NULL)              strlcpy (myLOG.title, "¢null?"  , LEN_FULL);
   else if (strlen (a_title) <= 0)   strlcpy (myLOG.title, "¢empty?" , LEN_FULL);
   else                              strlcpy (myLOG.title, a_title   , LEN_FULL);
   return myLOG.title;
}

char*        /*--> defense for bad data in longs -----------------------------*/
ylog_data          (const char *a_data)
{
   if (a_data == NULL)               strlcpy (myLOG.data , "¢ data was null ?" , LEN_FULL);
   else if (strlen (a_data) <= 0)    strlcpy (myLOG.data , "¢ data was empty ?", LEN_FULL);
   else                              strlcpy (myLOG.data , a_data              , LEN_FULL);
   return myLOG.data;
}

char*        /*--> defense for bad data in shorts ----------------------------*/
ylog_terse         (const char *a_data)
{
   if (a_data == NULL)               strlcpy (myLOG.data , "¢null?"  , LEN_FULL);
   else if (strlen (a_data) <= 0)    strlcpy (myLOG.data , "¢empty?" , LEN_FULL);
   else                              strlcpy (myLOG.data , a_data   , LEN_FULL);
   return myLOG.data;
}



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_______________o (void) {;}

void
yLOG_enter    (const char *a_func)
{
   ylog_check_enter (a_func);
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_PATH, "ENTERING (%.30s)", ylog_title (a_func));
   ylog__main (LVL_BEG , TYPE_STRUCT, myLOG.msg);
   return;
}

void
yLOG_exit     (const char *a_func)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_PATH, "EXITING  (%.30s)", ylog_title (a_func));
   ylog__main (LVL_END , TYPE_STRUCT, myLOG.msg);
   ylog_check_exit (a_func);
   return;
}

void
yLOG_exitr    (const char *a_func, const int a_rce)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_PATH, "WARNING, rce (%d)", a_rce);
   ylog__main (LVL_SAME, TYPE_WARNING, myLOG.msg);
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
yLOG_note          (const char *a_info)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%.150s...", ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_info          (const char *a_subject, const char *a_info)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: %.150s", ylog_title (a_subject), ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_delim         (const char *a_subject, const char *a_info)
{
   IF_QUIET  return;
   snprintf (myLOG.msg, LEN_FULL, "%-10.10s: [%.50s]", ylog_title (a_subject), ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_char          (const char *a_subject, const char a_char)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %c", ylog_title (a_subject), (unsigned char) chrvisible (a_char));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_value         (const char *a_subject, const int a_value)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %d", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_hex           (const char *a_subject, const long a_value)
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
yLOG_llong         (const char *a_subject, const long long a_value)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %lld", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_double        (const char *a_subject, const double a_value)
{
   /* used 20.6 format so the decimals line up top-to-bottom in lines  */
   IF_QUIET  return;
   sprintf(myLOG.msg, "%-10.10s: %20.6lf", ylog_title (a_subject), a_value);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_point         (const char *a_subject, const void *a_value)
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
yLOG_bullet        (const int   a_num,     const char *a_info)
{
   IF_QUIET  return;
   sprintf(myLOG.msg, "#%-9d: %.150s", a_num, ylog_data (a_info));
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   return;
}

void
yLOG_pair          (const int   a_num,     const int  a_value)
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
yLOG_complex       (const char *a_subject, cchar *a_format, ...)
{
   IF_QUIET  return;
   /*---(locals)---------+-------------+-*/
   char        x_format  [LEN_FULL] = "";
   va_list     args;
   /*---(to console)---------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL, a_format, args);
   sprintf   (myLOG.msg, "%-10.10s: %.150s", ylog_title (a_subject), x_format);
   ylog__main (LVL_SAME, TYPE_INFO, myLOG.msg);
   va_end    (args);
   /*---(complete)-----------------------*/
   return;
}



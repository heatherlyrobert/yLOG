#include    "yLOG.h"
#include    "yLOG_priv.h"
#include    <yENV_uver.h>



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_quiet        (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_QUIET);
   myLOG.m_use   = '-';
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_loud         (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_NOISE);
   myLOG.m_use   = '-';
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ylog__unit_end          (void)
{
   yLOGS_end     ();
   return 0;
}

char*            /*--> unit test accessor ------------------------------*/
ylog_base__unit         (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "[]";
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "BASE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "prefix"     ) == 0) {
      sprintf (t, "[%s]", myLOG.m_prefix);
      snprintf (unit_answer, LEN_RECD, "BASE prefix      : %2d  %2d%s", myLOG.m_indent, strlen (myLOG.m_prefix), t);
   }
   else if (strcmp (a_question, "full"       ) == 0) {
      c = strlen (myLOG.m_full);
      if (c > 99)  c = 99;
      sprintf (t, "[%s]", myLOG.m_full);
      snprintf (unit_answer, LEN_RECD, "BASE full        : %2d%s", c, t);
   }
   else if (strcmp (a_question, "prog"       ) == 0) {
      sprintf (t, "[%s]", myLOG.m_prog);
      snprintf (unit_answer, LEN_RECD, "BASE prog        : %2d%s", strlen (myLOG.m_prog), t);
   }
   else if (strcmp (a_question, "loud"       ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE loud        : %c  %2d", myLOG.m_loud, myLOG.m_count);
   }
   else if (strcmp (a_question, "lines"      ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE lines       : %2d", myLOG.m_lines);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


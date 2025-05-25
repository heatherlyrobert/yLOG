/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        separators                            ----===*/
/*====================------------------------------------====================*/
static void      o___SEPARATORS______________o (void) {;}

char
yLOG_sync     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        cmd         [1000] = "";
   /*---(output line)--------------------*/
   IF_LOGGER  fprintf (myLOG.m_logger, "SYNC======= ====== === %s%s\n", myLOG.m_prefix, "============================================================");
   /*---(update)-------------------------*/
   ++myLOG.m_nsyncs;
   if (myLOG.m_nsyncs == 1)  return;
   /*---(close log)----------------------*/
   fclose (myLOG.m_logger);
   /*---(trim)---------------------------*/
   snprintf (cmd, 950, "cat %s | head -n $(grep -n \"^SYNC=====\" %s | head -n 1 | cut -d: -f 1) > temp.ulog", myLOG.m_filename, myLOG.m_filename);
   system (cmd);
   snprintf (cmd, 950, "rm -f %s", myLOG.m_filename);
   system (cmd);
   snprintf (cmd, 950, "mv -f temp.ulog %s", myLOG.m_filename);
   system (cmd);
   /*---(reopen)-------------------------*/
   myLOG.m_logger = fopen(myLOG.m_filename, "a");
   if (myLOG.m_logger == NULL) {
      printf ("FATAL, can not open logger\n");
      return -1;
   }
   /*---(complete)-----------------------*/
   return;
}

char
yLOG_break    (void)
{
   IF_LOGGER  fprintf (myLOG.m_logger, "------- --- ------ --- %s%s\n", myLOG.m_prefix, "---------------------------------------------------------");
   return;
}



/*====================------------------------------------====================*/
/*===----                     unit test specific                       ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char
yLOG_unitcond (int a_scrp, int a_cond, int a_line, char *a_desc)
{
   /*> printf ("unit cond %2.2d.%3.3d.-- at %5d, %s\n", a_scrp, a_cond, a_line, a_desc);   <*/
   IF_NOSHOW   return 0;
   IF_NOTUNIT  return 0;
   IF_LOGGER  fprintf (myLOG.m_logger, "unit=== === ====== === %s%s\n", myLOG.m_prefix, "=========================================================");
   snprintf   (myLOG.m_msg, LEN_FULL, "COND %2.2d.%3.3d.-- at %5d, %s", a_scrp, a_cond, a_line, a_desc);
   return ylog__main (LVL_SAME, TYPE_UNITTEST, myLOG.m_msg);
}

char
yLOG_unitstep (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   IF_NOSHOW   return 0;
   IF_NOTUNIT  return 0;
   IF_LOGGER  fprintf (myLOG.m_logger, "unit--- --- ------ --- %s%s\n", myLOG.m_prefix, "---------------------------------------------------------");
   snprintf   (myLOG.m_msg, LEN_FULL, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   return ylog__main (LVL_SAME, TYPE_UNITTEST, myLOG.m_msg);
}




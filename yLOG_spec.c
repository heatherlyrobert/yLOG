/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        separators                            ----===*/
/*====================------------------------------------====================*/
static void      o___SEPARATORS______________o (void) {;}

void
yLOG_sync     (void)
{
   /*---(locals)-----------+-----------+-*/
   char        cmd         [1000] = "";
   /*---(defense: quiet mode)------------*/
   IF_QUIET  return;
   /*---(output line)--------------------*/
   IF_LOGGER  fprintf (myLOG.logger, "SYNC======= ====== === %s%s\n", myLOG.prefix, "============================================================");
   /*---(update)-------------------------*/
   ++myLOG.nsyncs;
   if (myLOG.nsyncs == 1)  return;
   /*---(close log)----------------------*/
   fclose (myLOG.logger);
   /*---(trim)---------------------------*/
   snprintf (cmd, 950, "cat %s | head -n $(grep -n \"^SYNC=====\" %s | head -n 1 | cut -d: -f 1) > temp.ulog", myLOG.filename, myLOG.filename);
   system (cmd);
   snprintf (cmd, 950, "rm -f %s", myLOG.filename);
   system (cmd);
   snprintf (cmd, 950, "mv -f temp.ulog %s", myLOG.filename);
   system (cmd);
   /*---(reopen)-------------------------*/
   myLOG.logger = fopen(myLOG.filename, "a");
   if (myLOG.logger == NULL) {
      printf ("FATAL, can not open logger\n");
      return -1;
   }
   /*---(complete)-----------------------*/
   return;
}

void
yLOG_break    (void)
{
   IF_QUIET  return;
   IF_LOGGER  fprintf (myLOG.logger, "------- --- ------ --- %s%s\n", myLOG.prefix, "---------------------------------------------------------");
   return;
}



/*====================------------------------------------====================*/
/*===----                     unit test specific                       ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

void
yLOG_unitcond (int a_scrp, int a_cond, int a_line, char *a_desc)
{
   /*> printf ("unit cond %2.2d.%3.3d.-- at %5d, %s\n", a_scrp, a_cond, a_line, a_desc);   <*/
   IF_QUIET  return;
   IF_NOTUNIT      return;
   IF_LOGGER  fprintf (myLOG.logger, "unit=== === ====== [t] %s%s\n", myLOG.prefix, "=========================================================");
   snprintf   (myLOG.msg, LEN_PATH, "COND %2.2d.%3.3d.-- at %5d, %s", a_scrp, a_cond, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, myLOG.msg);
   return;
}

void
yLOG_unitstep (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   IF_QUIET  return;
   IF_NOTUNIT      return;
   IF_LOGGER  fprintf (myLOG.logger, "unit--- --- ------ [t] %s%s\n", myLOG.prefix, "---------------------------------------------------------");
   snprintf   (myLOG.msg, LEN_PATH, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, myLOG.msg);
   return;
}

void
yLOG_unitdone (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   IF_QUIET  return;
   IF_NOTUNIT      return;
   IF_LOGGER  fprintf (myLOG.logger, "unit--- --- ------ [t] %s%s\n", myLOG.prefix, "---------------------------------------------------------");
   snprintf   (myLOG.msg, LEN_PATH, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, myLOG.msg);
   return;
}




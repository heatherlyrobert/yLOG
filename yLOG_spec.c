/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                        separators                            ----===*/
/*====================------------------------------------====================*/
static void      o___STAGES__________________o (void) {;}

static char  s_on = '-';

/*> void                                                                              <* 
 *> ylog_stage_init  (void)                                                           <* 
 *> {                                                                                 <* 
 *>    /+---(big stages)---------------------+/                                       <* 
 *>    if (yURG_debug.init      == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.main_loop == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.wrap      == 'y')     s_on = 'y';                               <* 
 *>    /+---(little stages)------------------+/                                       <* 
 *>    if (yURG_debug.stage1    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage2    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage3    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage4    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage5    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage6    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage7    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage8    == 'y')     s_on = 'y';                               <* 
 *>    if (yURG_debug.stage9    == 'y')     s_on = 'y';                               <* 
 *>    /+---(react)--------------------------+/                                       <* 
 *>    if (s_on == 'y' && yURG_debug.init != 'y')  yLOG_mute ();                      <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return;                                                                        <* 
 *> }                                                                                 <*/

/*> void                                                                              <* 
 *> yLOG_stage     (cchar a_stage)                                                    <* 
 *> {                                                                                 <* 
 *>    if (a_stage == 'i')  ylog_stage_init ();                                       <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    if (s_on != 'y')  return;                                                      <* 
 *>    /+---(handle)-------------------------+/                                       <* 
 *>    yLOG_mute ();                                                                  <* 
 *>    switch (a_stage) {                                                             <* 
 *>    case 'i' :  if (yURG_debug.init      == 'y')   yLOG_unmute ();  break;         <* 
 *>    case 'm' :  if (yURG_debug.main_loop == 'y')   yLOG_unmute ();  break;         <* 
 *>    case 'w' :  if (yURG_debug.wrap      == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '1' :  if (yURG_debug.stage1    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '2' :  if (yURG_debug.stage2    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '3' :  if (yURG_debug.stage3    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '4' :  if (yURG_debug.stage4    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '5' :  if (yURG_debug.stage5    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '6' :  if (yURG_debug.stage6    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '7' :  if (yURG_debug.stage7    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '8' :  if (yURG_debug.stage8    == 'y')   yLOG_unmute ();  break;         <* 
 *>    case '9' :  if (yURG_debug.stage9    == 'y')   yLOG_unmute ();  break;         <* 
 *>    }                                                                              <* 
 *>    /+---(helpful breaks)-----------------+/                                       <* 
 *>    if (yURG_debug.main_loop == 'y')   yLOG_break  ();                             <* 
 *>    if (yURG_debug.wrap      == 'y')   yLOG_break  ();                             <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/



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
   if (RUN_QUIET)  return;
   /*---(output line)--------------------*/
   fprintf (its.logger, "SYNC======= ====== === %s%s\n", its.prefix,
         "============================================================");
   /*---(update)-------------------------*/
   ++its.nsyncs;
   if (its.nsyncs == 1)  return;
   /*---(close log)----------------------*/
   fclose (its.logger);
   /*---(trim)---------------------------*/
   snprintf (cmd, 950, "cat %s | head -n $(grep -n \"^SYNC=====\" %s | head -n 1 | cut -d: -f 1) > temp.ulog", its.filename, its.filename);
   system (cmd);
   snprintf (cmd, 950, "rm -f %s", its.filename);
   system (cmd);
   snprintf (cmd, 950, "mv -f temp.ulog %s", its.filename);
   system (cmd);
   /*---(reopen)-------------------------*/
   its.logger = fopen(its.filename, "a");
   if (its.logger == NULL) {
      printf ("FATAL, can not open logger\n");
      return -1;
   }
   /*---(complete)-----------------------*/
   return;
}

void
yLOG_break    (void)
{
   if (RUN_QUIET)  return;
   fprintf (its.logger, "------- --- ------ --- %s%s\n", its.prefix,
         "---------------------------------------------------------");
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
   if (RUN_QUIET)  return;
   fprintf (its.logger, "unit=== === ====== [t] %s%s\n", its.prefix,
         "=========================================================");
   snprintf   (its.msg, LEN_PATH, "COND %2.2d.%3.3d.-- at %5d, %s", a_scrp, a_cond, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, its.msg);
   return;
}

void
yLOG_unitstep (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (RUN_QUIET)  return;
   fprintf (its.logger, "unit--- --- ------ [t] %s%s\n", its.prefix,
         "---------------------------------------------------------");
   snprintf   (its.msg, LEN_PATH, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, its.msg);
   return;
}

void
yLOG_unitdone (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (RUN_QUIET)  return;
   fprintf (its.logger, "unit--- --- ------ [t] %s%s\n", its.prefix,
         "---------------------------------------------------------");
   snprintf   (its.msg, LEN_PATH, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   ylog__main (LVL_SAME, TYPE_UNITTEST, its.msg);
   return;
}




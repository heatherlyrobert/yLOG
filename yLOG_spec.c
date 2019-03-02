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
   if (its.quiet) return;
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
   if (its.quiet) return;
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
   if (its.quiet) return;
   fprintf (its.logger, "unit=== === ====== [t] %s%s\n", its.prefix,
         "=========================================================");
   snprintf   (its.msg, 190, "COND %2.2d.%3.3d.-- at %5d, %s", a_scrp, a_cond, a_line, a_desc);
   yLOG__main ('-', 't', its.msg);
   return;
}

void
yLOG_unitstep (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (its.quiet) return;
   fprintf (its.logger, "unit--- --- ------ [t] %s%s\n", its.prefix,
         "---------------------------------------------------------");
   snprintf   (its.msg, 190, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   yLOG__main ('-', 't', its.msg);
   return;
}

void
yLOG_unitdone (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc)
{
   if (its.quiet) return;
   fprintf (its.logger, "unit--- --- ------ [t] %s%s\n", its.prefix,
         "---------------------------------------------------------");
   snprintf   (its.msg, 190, "STEP %2.2d.%3.3d.%2.2d at %5d, %s", a_scrp, a_cond, a_step, a_line, a_desc);
   yLOG__main ('-', 't', its.msg);
   return;
}




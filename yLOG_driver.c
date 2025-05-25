/*============================[[ beg-of-code ]]===============================*/
#include    "yLOG.h"
#include    "yLOG_priv.h"



/*====================------------------------------------====================*/
/*===----                             driver                           ----===*/
/*====================------------------------------------====================*/
static void      o___DRIVERS_________________o (void) {;}

llong             /* PURPOSE : timestamp in milliseconds      */
ylog__timestamp         (void)
{
   /* second
    * millisecond  ms  0.001 sec
    * microsecond  us  0.000001 sec
    * nanosecond   ns  0.000000001 sec
    * picosecond   ps  0.000000000001 sec
    */
   llong            tint = 0;
   struct timespec  tv;
   clock_gettime (CLOCK_MONOTONIC, &tv);
   tint += (llong) tv.tv_sec  * 1000;
   tint += (llong) tv.tv_nsec / 1000000;
   return tint;
}

char
ylog__prefix            (int a_indent, int *r_indent, char r_prefix [LEN_HUND])
{  /*---(design notes)-------------------*/
   /*
    *  this function's arguments are a little awkward, but make
    *  it trivial to unit test without globals.  on the other
    *  hand, it is slightly more awkward in actual use.  fine.
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   int         x_indent    =    0;
   char        x_prefix    [LEN_HUND]  = "";
   /*---(default)------------------------*/
   if (r_prefix == NULL)  strcpy (r_prefix, "");
   /*---(rational limits)----------------*/
   x_indent = a_indent;
   if (x_indent <  0)  x_indent = 0;
   if (x_indent > 30)  x_indent = 30;
   /*---(standard prefix)----------------*/
   strncpy (x_prefix, "", LEN_HUND);
   for (i = 0; i <  x_indent; ++i   )  strncat (x_prefix, "´··", LEN_HUND);
   /*---(add marks every third)----------*/
   for (i = 2; i <  x_indent; i += 3)  x_prefix [i * 3] = '+';
   /*---(clear just before entry)--------*/
   if (x_indent > 0) {
      x_prefix [x_indent * 3 - 1] = ' ';
      x_prefix [x_indent * 3 - 2] = ' ';
   }
   /*---(save-back)----------------------*/
   if (r_indent != NULL)  *r_indent = x_indent;
   if (r_prefix != NULL)  strlcpy (r_prefix, x_prefix, LEN_HUND);
   /*---(complete)-----------------------*/
   return 1;
}

char             /* PURPOSE : write a message to the log file          */
ylog__main              (char a_change, char a_level, char a_message [LEN_FULL])
{
   /*===[[ design notes ]]====================================================#
    *   - writes a log message to the log file, no matter what
    *   - always flush buffer so message exists even in catastrophic failure
    *   - data will be fixed as a partial message is better than none
    *   - calls to log are done through specializers (this function is private)
    *   - the pCHG and pLVL standards are defined in the file header
    *=========================================================================*/
   /*---(locals)-----------+-----+-----+-*/
   llong       x_wall;                            /* timestamp                 */
   /*---(filter)-------------------------*/
   if (myLOG.m_logger == NULL)  return 0;
   /*---(first, defense)-----------------*/
   if (a_change == 0 || strchr (LVL_VALID , a_change) == NULL)   a_change = LVL_UNKNOWN;
   if (a_level  == 0 || strchr (TYPE_VALID, a_level ) == NULL)   a_level  = TYPE_UNKNOWN;
   /*---(exdent, if needed)--------------*/
   if (a_change == LVL_END)  ylog__prefix (--(myLOG.m_indent), &(myLOG.m_indent), myLOG.m_prefix);
   /*---(get wall time)----------------*/
   x_wall  = ylog__timestamp() - myLOG.m_start;
   /*---(update count)-------------------*/
   myLOG.m_count++;
   /*---(message)------------------------*/
   snprintf (myLOG.m_full, LEN_RECD, "%7lld.%03lld %6d %c%c%c %s%s",
         (x_wall / 1000) % 10000000, x_wall % 1000,
         myLOG.m_count % 1000000, myLOG.m_stage, myLOG.m_urg, a_level, myLOG.m_prefix, a_message);
   /*---(log)----------------------------*/
   IF_LOGGER {
      fprintf (myLOG.m_logger, "%s\n", myLOG.m_full);
      fflush  (myLOG.m_logger);
   }
   /*---(indent, if needed)--------------*/
   if (a_change == LVL_BEG)  ylog__prefix (++(myLOG.m_indent), &(myLOG.m_indent), myLOG.m_prefix);
   /*---(complete)-----------------------*/
   IF_NOSHOW  return 1;
   return 0;
}



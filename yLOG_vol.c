/*============================[[ beg-of-code ]]===============================*/
#include  "yLOG.h"
#include  "yLOG_priv.h"



typedef struct cTRACK  tTRACK;
static struct cTRACK {
   char        type;
   int         len;
   char        name        [LEN_LABEL];
};
static tTRACK s_tracks   [100];
static int    s_ntrack   = 0;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ylog_vol_init           (void)
{
   s_ntrack = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                            muting                            ----===*/
/*====================------------------------------------====================*/
static void      o___MUTING__________________o (void) {;}

void
yLOG_mute     (void)
{
   its.loud  = '-';
   strlcpy (its.msg , "", LEN_PATH);
   strlcpy (its.full, "", LEN_PATH);
   return;
}

void
yLOG_unmute   (void)
{
   its.loud  = 'y';
   strlcpy (its.msg , "", LEN_PATH);
   strlcpy (its.full, "", LEN_PATH);
   return;
}



/*====================------------------------------------====================*/
/*===----                            muting                            ----===*/
/*====================------------------------------------====================*/
static void      o___ENTRIES_________________o (void) {;}

char
ylog__find    (const char *a_func)
{
   char        rce         =  -10;
   int         i           =    0;
   int         x_len       =    0;
   --rce;  if (a_func == NULL)                   return rce;
   x_len = strlen (a_func);
   for (i = 0; i < s_ntrack; ++i) {
      if (s_tracks [i].len      != x_len)             continue;
      if (s_tracks [i].name [0] != a_func [0])        continue;
      if (s_tracks [i].name [1] != a_func [1])        continue;
      if (s_tracks [i].name [2] != a_func [2])        continue;
      if (strcmp (s_tracks [i].name, a_func) != 0)    continue;
      return i;
   }
   return -1;
}

char
ylog_check    (const char *a_func)
{
   char        rce         =  -10;
   int         n           =   -1;
   n = ylog__find (a_func);
   --rce;  if (n < 0)  return rce;
   --rce;  if (strchr ("exb", s_tracks [n].type) == NULL)  return rce;
   return n;
}

char
ylog_check_enter (const char *a_func)
{
   char        rce         =  -10;
   int         n           =   -1;
   if (its.loud == 'y')  return 0;
   n = ylog__find (a_func);
   --rce;  if (n < 0)  return rce;
   if (strchr ("eb" , s_tracks [n].type) == NULL)  return 0;
   yLOG_unmute ();
   return 0;
}

char
ylog_check_exit  (const char *a_func)
{
   char        rce         =  -10;
   int         n           =   -1;
   if (its.loud == '-')  return 0;
   n = ylog__find (a_func);
   --rce;  if (n < 0)  return rce;
   if (strchr ("xb" , s_tracks [n].type) == NULL)  return 0;
   yLOG_mute   ();
   return 0;
}

char
yLOG_track    (const char *a_func, const char a_type)
{
   char        rce         =  -10;
   int         x_len       =    0;
   int         n           =   -1;
   --rce;  if (a_func == NULL)                   return rce;
   x_len = strlen (a_func);
   --rce;  if (x_len <  3)                       return rce;
   --rce;  if (x_len >= LEN_LABEL)               return rce;
   --rce;  if (a_type == 0)                      return rce;
   --rce;  if (strchr ("exb", a_type) == NULL)   return rce;
   n = ylog__find (a_func);
   if (n < 0) {
      s_tracks [s_ntrack].type = a_type;
      strlcpy (s_tracks [s_ntrack].name, a_func, LEN_LABEL);
      s_tracks [s_ntrack].len = x_len;
      ++s_ntrack;
   } else {
      s_tracks [n].type = a_type;
   }
   return 0;
}

char
yLOG_untrack  (const char *a_func)
{
   char        rce         =  -10;
   int         x_len       =    0;
   int         n           =   -1;
   --rce;  if (a_func == NULL)                   return rce;
   x_len = strlen (a_func);
   --rce;  if (x_len <  3)                       return rce;
   --rce;  if (x_len >= LEN_LABEL)               return rce;
   n = ylog__find (a_func);
   --rce;  if (n < 0)  return rce;
   s_tracks [n].type = '-';
   return 0;
}


char*            /*--> unit test accessor ------------------------------*/
ylog_vol__unit          (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "[]";
   int         i           =    0;
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "VOL              : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "count"      ) == 0) {
      for (i = 0; i < s_ntrack; ++i) {
         t [i + 1]     = s_tracks [i].type;
         t [i + 2] = ']';
         t [i + 3] = '\0';
      }
      snprintf (unit_answer, LEN_RECD, "VOL count   (%2d) : %s", s_ntrack, t);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



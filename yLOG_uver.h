

#include  <stdio.h>
#include  <stdarg.h>                   /* va_arg                              */
#include  <unistd.h>                   /* unlink                              */


/*
 *  i added the complication of using a variable to hold the output
 *  rather that printing directly to enable easy unit testing.
 *
 */


/*---(simple variables)------------------*/

static char  *mylog_oneline = "clio-chrysafenios (flowering) process execution logging";
static char   mylog_debug   = '-';

static char   mylog_level   =   0;
static char   mylog_prefix  [LEN_HUND]  = "";
static char   mylog_print   [LEN_FULL]  = "";

static char   mylog_label   [LEN_LABEL] = "";
static char   mylog_func    [LEN_DESC]  = "";
static char   mylog_data    [LEN_FULL]  = "";

static char  *mylog_lstd    = "/tmp/ylog_micro.ulog";
static char   mylog_lname   [LEN_HUND]  = "";
static FILE  *mylog_lfile   = NULL;

static char  *mylog_estd    = "/tmp/ylog_errors.txt";
static char   mylog_ename   [LEN_HUND]  = "";
static FILE  *mylog_efile   = NULL;



#define  DEBUG_ULOG   if (mylog_debug == 'y')  


/*====================------------------------------------====================*/
/*===----                         specialty                            ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIAL_______o (void) {;}

char
ylog__ufile             (char a_type, char b_name [LEN_HUND], FILE **b_file)
{
   /*---(locals)---------+-----+-----+---*/
   char        rce       =  -10;
   char        rc        =    0;
   FILE       *f         = NULL;
   /*> printf ("\n");                                                                 <*/
   /*> printf ("request  (%c) å%sæ (%p)\n", a_type, b_name, *b_file);                 <*/
   /*---(defense)------------------------*/
   --rce;  if (b_name == NULL)            return rce;
   --rce;  if (b_file == NULL)            return rce;
   /*---(close-first)--------------------*/
   if (strcmp ("", b_name) != 0 && strncmp ("STD", b_name, 3) != 0) {
      /*> printf ("closing file å%sæ (%p)\n", b_name, *b_file);                       <*/
      if (*b_file != NULL) { fflush (*b_file);  fclose (*b_file); }
   }
   *b_file = NULL;
   /*> printf ("now          å%sæ (%p)\n", b_name, *b_file);                          <*/
   /*---(prepare)------------------------*/
   --rce;  switch (a_type) {
   case 'L' : strlcpy (b_name, mylog_lstd , LEN_HUND); rc = 1; break;
   case 'E' : strlcpy (b_name, mylog_estd , LEN_HUND); rc = 2; break;
   case '1' : strlcpy (b_name, "STDOUT"   , LEN_HUND); rc = 1; break;
   case '2' : strlcpy (b_name, "STDERR"   , LEN_HUND); rc = 2; break;
   case '-' : rc = 4;                                          break;  
   case 'l' : case 'ò' : case 'e' : case 'ì' :                 break;  
   default  : return rce;                                      break;
   }
   /*> printf ("prepare      å%sæ (%p)\n", b_name, *b_file);                          <*/
   /*---(close-only)--------------------*/
   if (strchr ("le", a_type) != NULL) {
      /*> printf ("close-only\n");                                                    <*/
      strcpy (b_name, "");
      /*> printf ("done         å%sæ (%p)\n", b_name, *b_file);                       <*/
      return 0;
   }
   /*---(close-delete)-------------------*/
   --rce;  if (strchr ("òì", a_type) != NULL) {
      /*> printf ("close-delete\n");                                                  <*/
      if (strcmp ("", b_name) != 0 && strncmp ("STD", b_name, 3) != 0) {
         /*> printf ("try to unlink\n");                                              <*/
         unlink (b_name);  /* remove temp file */
         /*> printf ("unlinked\n");                                                   <*/
         strcpy (b_name, "");
         rc = 3;
      } else if (strcmp ("", b_name) == 0) {
         rc = rce;
      } else {
         /*> printf ("either empty or STDERR\n");                                     <*/
         strcpy (b_name, "");
         rc = 0;
      }
      /*> printf ("done         å%sæ (%p)\n", b_name, *b_file);                       <*/
      return rc;
   }
   /*---(open)---------------------------*/
   --rce;  if (strcmp ("STDOUT", b_name) == 0) {
      f = stdout;
      /*> printf ("open STDOUT  å%sæ (%p)\n", b_name, *b_file);                       <*/
   }
   else if (strcmp ("STDERR", b_name) == 0) {
      f = stderr;
      /*> printf ("open STDERR  å%sæ (%p)\n", b_name, *b_file);                       <*/
   }
   else {
      f = fopen (b_name, "wt");
      if (f == NULL)                 return rce;
      fflush (f);
      /*> printf ("open general å%sæ (%p)\n", b_name, *b_file);                       <*/
   }
   /*---(save)---------------------------*/
   *b_file = f;
   /*> printf ("done         å%sæ (%p)\n", b_name, *b_file);                          <*/
   /*---(complete)-----------------------*/
   return rc;
}

char  ylog_uopen    (void)        { return ylog__ufile ('L', mylog_lname, &mylog_lfile); }
char  ylog_ustdout  (void)        { return ylog__ufile ('1', mylog_lname, &mylog_lfile); }
char  ylog_ureset   (void)        { return ylog__ufile ('-', mylog_lname, &mylog_lfile); }
char  ylog_uclose   (void)        { return ylog__ufile ('l', mylog_lname, &mylog_lfile); }
char  ylog_udone    (void)        { return ylog__ufile ('ò', mylog_lname, &mylog_lfile); }

char* ylog_uwhich   (void)        { return mylog_lname; }
int   ylog_ulines   (void)        { return yenv_ulines (mylog_lstd); }
char* ylog_upeek    (char a_dir)  { return yenv_upeek  (mylog_lstd, a_dir); }






/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_______o (void) {;}

char*
ylog__uprefix           (char a_level)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(default)------------------------*/
   strcpy (mylog_prefix, "");
   /*---(defence)------------------------*/
   if (a_level <  0)  return mylog_prefix;
   if (a_level > 10)  a_level = 10;
   /*---(build)--------------------------*/
   for (i = 0; i < a_level; ++i) {
      if (i == a_level - 1)  strcat (mylog_prefix, "´  ");
      else                   strcat (mylog_prefix, "´··");
   }
   /*---(complete)-----------------------*/
   return mylog_prefix;
}

char*
ylog__ustring           (char a_type, char a_string [LEN_FULL])
{
   /*---(locals)-----------+-----+-----+-*/
   int         l           =    0;
   /*---(defence)------------------------*/
   if      (a_string == NULL)            return "(NULL)";
   else if (strcmp (a_string, "") == 0)  return "(empty)";
   l = strlen (a_string);
   /*---(build)--------------------------*/
   switch (a_type) {
   case 'f' :  strlcpy (mylog_func , a_string, LEN_DESC);    if (l >= LEN_DESC ) mylog_func  [LEN_DESC  - 2] = '>';  return mylog_func;    break;
   case 'l' :  strlcpy (mylog_label, a_string, LEN_LABEL);   if (l >= LEN_LABEL) mylog_label [LEN_LABEL - 2] = '>';  return mylog_label;   break;
   case 'd' :  strlcpy (mylog_data , a_string, LEN_FULL);    if (l >= LEN_FULL ) mylog_data  [LEN_FULL  - 2] = '>';  return mylog_data;    break;
   }
   /*---(trouble)------------------------*/
   return "(bad_type)";
}



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_____o (void) {;}

char
ylog_uenter   (char a_func [LEN_DESC])
{
   int         i           =    0;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%sENTERING (%.30s)", mylog_prefix, ylog__ustring ('f', a_func));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   if (mylog_level < 10)  ++mylog_level;
   ylog__uprefix (mylog_level);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_uexit    (char a_func [LEN_DESC])
{
   int         i           =    0;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if (mylog_level >  0)  --mylog_level;
   ylog__uprefix (mylog_level);
   sprintf (mylog_print , "%sEXITING  (%.30s)", mylog_prefix, ylog__ustring ('f', a_func));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_uexitr    (char a_func [LEN_DESC], int a_rce)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if (a_rce < 0)  sprintf (mylog_print , "%sWARNING, rce (%d)", mylog_prefix, a_rce);
   else            sprintf (mylog_print , "%sRETURN,  rc  (%d)", mylog_prefix, a_rce);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return ylog_uexit (a_func);
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES______o (void) {;}

char
ylog_unote    (char a_info [LEN_FULL])
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%s", mylog_prefix, ylog__ustring ('d', a_info));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_uinfo    (char a_label [LEN_LABEL], char a_info [LEN_FULL])
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %s", mylog_prefix, ylog__ustring ('l', a_label), ylog__ustring ('d', a_info));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_uchar         (char a_label [LEN_LABEL], uchar a_char)
{
   uchar c  = 'Ï';
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if (a_char >   32 && a_char != 127)  c = a_char;
   switch (a_char) {
   case   0 : c = '£';  break;   /* null   */
   case  10 : c = '¦';  break;   /* return */
   case  13 : c = '¦';  break;   /* enter  */
   case  27 : c = '¥';  break;   /* escape */
   case  29 : c = '¨';  break;   /* group  */
   case  31 : c = '§';  break;   /* field  */
   case  32 : c = '·';  break;   /* space  */
   }
   sprintf (mylog_print , "%s%-10.10s: %c", mylog_prefix, ylog__ustring ('l', a_label), c);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_uvalue        (char a_label [LEN_LABEL], int a_value)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %d", mylog_prefix, ylog__ustring ('l', a_label), a_value);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
ylog_upoint        (char a_label [LEN_LABEL], void *a_point)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %p", mylog_prefix, ylog__ustring ('l', a_label), a_point);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG________o (void) {;}

char
ylog_ucomplex      (char a_label [LEN_LABEL], char *a_format, ...)
{
   char        x_format  [LEN_FULL] = "";
   va_list     args;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   --rce;  if (a_format  == NULL)  return rce;
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL, a_format, args);
   sprintf   (mylog_print , "%s%-10.10s: %s", mylog_prefix, ylog__ustring ('l', a_label), x_format);
   fprintf   (mylog_lfile, "%s\n", mylog_print);
   va_end    (args);
   fflush    (mylog_lfile);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                     error reporting                          ----===*/
/*====================------------------------------------====================*/
static void      o___ERRORS________o (void) {;}

char yerr_uopen   (void)       { return ylog__ufile ('E', mylog_ename, &mylog_efile); }
char yerr_ustderr (void)       { return ylog__ufile ('2', mylog_ename, &mylog_efile); }
char yerr_ureset  (void)       { return ylog__ufile ('-', mylog_ename, &mylog_efile); }
char yerr_uclose  (void)       { return ylog__ufile ('e', mylog_ename, &mylog_efile); }
char yerr_udone   (void)       { return ylog__ufile ('ì', mylog_ename, &mylog_efile); }

char
yerr_uerror            (char *a_format, ...)
{
   /*---(locals)---------+-----+-----+---*/
   char        rce         =  -10;
   char        x_format  [LEN_FULL] = "";
   va_list     args;
   /*---(defense)------------------------*/
   --rce;  if (mylog_efile == NULL)  return rce;
   /*---(write)--------------------------*/
   va_start  (args, a_format);
   vsnprintf (x_format, LEN_FULL, a_format, args);
   sprintf   (mylog_print , "%s", x_format);
   fprintf   (mylog_efile, "%s\n", mylog_print);
   va_end    (args);
   /*---(flush)--------------------------*/
   fflush    (mylog_efile);
   /*---(complete)-----------------------*/
   return 1;
}

char* yerr_uwhich  (void)        { return mylog_ename; }
int   yerr_ulines  (void)        { return yenv_ulines (mylog_estd); }
char* yerr_upeek   (char a_dir)  { return yenv_upeek  (mylog_estd, a_dir); }



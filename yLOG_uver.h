/*
 *  i added the complication of using a variable to hold the output
 *  rather that printing directly to enable easy unit testing.
 *
 */


/*---(simple variables)------------------*/

static char  *mylog_oneline = "clio-chrysafenios (flowering) process execution logging";

static char   mylog_level   =   0;
static char   mylog_prefix  [100] = "";
static char   mylog_print   [200] = "";

static char  *mylog_lname   = "/tmp/ylog_micro.ulog";
static FILE  *mylog_lfile   = NULL;

static char  *mylog_ename   = "/tmp/ylog_errors.txt";
static FILE  *mylog_efile   = NULL;



/*====================------------------------------------====================*/
/*===----                         specialty                            ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIAL_______o (void) {;}

char
yLOG__ufile             (char a_type, FILE **b_file)
{
   /*---(locals)---------+-----+-----+---*/
   char        rce       =  -10;
   char        rc        =    0;
   char        x_name    [LEN_HUND]  = "";
   FILE       *f         = NULL;
   /*---(defense)------------------------*/
   --rce;  if (b_file == NULL)            return rce;
   /*---(prepare)------------------------*/
   switch (a_type) {
   case 'L':  case 'l':  case 'ò':  strlcpy (x_name, mylog_lname, LEN_HUND);  rc = 1;  break;
   case 'E':  case 'e':  case 'ì':  strlcpy (x_name, mylog_ename, LEN_HUND);  rc = 2;  break;
   default :  return rce;
   }
   /*---(close-first)--------------------*/
   if (*b_file != NULL) { fflush (*b_file);  fclose (*b_file); }
   *b_file = NULL;
   /*---(close-request)------------------*/
   if (strchr ("le", a_type) != NULL) {  /* close only */
      return 0;
   }
   if (strchr ("òì", a_type) != NULL) {  /* close and delete */
      unlink    (x_name);  /* remove temp file */
      return 0;
   }
   /*---(open)---------------------------*/
   f = fopen (x_name, "wt");
   --rce;  if (f == NULL)                 return rce;
   fflush (f);
   /*---(save)---------------------------*/
   *b_file = f;
   /*---(complete)-----------------------*/
   return rc;
}

char yLOG_uopen       (void)  { return yLOG__ufile ('L', &mylog_lfile); }
char yLOG_uclose      (void)  { return yLOG__ufile ('l', &mylog_lfile); }
char yLOG_udone       (void)  { return yLOG__ufile ('ò', &mylog_lfile); }

int   yLOG_ulines  (void)        { return yENV_ulines (mylog_lname); }
char* yLOG_upeek   (char a_dir)  { return yENV_upeek  (mylog_lname, a_dir); }



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_____o (void) {;}

char
yLOG_uenter   (char *a_func)
{
   int         i           =    0;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if      (a_func == NULL)            sprintf (mylog_print , "%sENTERING (%.30s)", mylog_prefix, "((NULL))");
   else if (strcmp (a_func, "") == 0)  sprintf (mylog_print , "%sENTERING (%.30s)", mylog_prefix, "((empty))");
   else                                sprintf (mylog_print , "%sENTERING (%.30s)", mylog_prefix, a_func);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   if (mylog_level < 10)  ++mylog_level;
   strcpy (mylog_prefix, "");
   for (i = 0; i < mylog_level; ++i) {
      if (i == mylog_level - 1)  strcat (mylog_prefix, "´  ");
      else                   strcat (mylog_prefix, "´··");
   }
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_uexit    (char *a_func)
{
   int         i           =    0;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if (mylog_level >  0)  --mylog_level;
   strcpy (mylog_prefix, "");
   for (i = 0; i < mylog_level; ++i) {
      if (i == mylog_level - 1)  strcat (mylog_prefix, "´  ");
      else                   strcat (mylog_prefix, "´··");
   }
   if      (a_func == NULL)            sprintf (mylog_print , "%sEXITING  (%.30s)", mylog_prefix, "((NULL))");
   else if (strcmp (a_func, "") == 0)  sprintf (mylog_print , "%sEXITING  (%.30s)", mylog_prefix, "((empty))");
   else                                sprintf (mylog_print , "%sEXITING  (%.30s)", mylog_prefix, a_func);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_uexitr    (char *a_func, int a_rce)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   if (a_rce < 0)  sprintf (mylog_print , "%sWARNING, rce (%d)", mylog_prefix, a_rce);
   else            sprintf (mylog_print , "%sRETURN,  rc  (%d)", mylog_prefix, a_rce);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return yLOG_uexit (a_func);
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES______o (void) {;}

char*
yLOG__string   (char *a_string)
{
   if      (a_string == NULL)            return "(NULL)";
   else if (strcmp (a_string, "") == 0)  return "(empty)";
   else                                  return a_string;
}

char
yLOG_unote    (char *a_info)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%s", mylog_prefix, yLOG__string (a_info));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_uinfo    (char *a_subject, char *a_info)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %s", mylog_prefix, yLOG__string (a_subject), yLOG__string (a_info));
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_uchar         (char *a_subject, uchar a_char)
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
   sprintf (mylog_print , "%s%-10.10s: %c", mylog_prefix, yLOG__string (a_subject), c);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_uvalue        (char *a_subject, int a_value)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %d", mylog_prefix, yLOG__string (a_subject), a_value);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}

char
yLOG_upoint        (char *a_subject, void *a_value)
{
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   sprintf (mylog_print , "%s%-10.10s: %p", mylog_prefix, yLOG__string (a_subject), a_value);
   fprintf (mylog_lfile, "%s\n", mylog_print);
   fflush  (mylog_lfile);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG________o (void) {;}

char
yLOG_ucomplex      (char *a_subject, char *a_format, ...)
{
   char        x_format  [200] = "";
   va_list     args;
   char        rce         =  -10;
   --rce;  if (mylog_lfile   == NULL)  return rce;
   --rce;  if (a_format  == NULL)  return rce;
   va_start  (args, a_format);
   vsnprintf (x_format, 200, a_format, args);
   sprintf   (mylog_print , "%s%-10.10s: %s", mylog_prefix, yLOG__string (a_subject), x_format);
   fprintf   (mylog_lfile, "%s\n", mylog_print);
   va_end    (args);
   fflush    (mylog_lfile);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                     error reporting                          ----===*/
/*====================------------------------------------====================*/
static void      o___ERRORS________o (void) {;}

char yLOG_ueopen       (void)  { return yLOG__ufile ('E', &mylog_efile); }
char yLOG_ueclose      (void)  { return yLOG__ufile ('e', &mylog_efile); }
char yLOG_uedone       (void)  { return yLOG__ufile ('ì', &mylog_efile); }

char
yLOG_uerr               (char *a_format, ...)
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

int   yLOG_uelines (void)        { return yENV_ulines (mylog_ename); }
char* yLOG_uepeek  (char a_dir)  { return yENV_upeek  (mylog_ename, a_dir); }



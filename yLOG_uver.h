/*
 *  i added the complication of using a variable to hold the output
 *  rather that printing directly to enable easy unit testing.
 *
 */


/*---(simple variables)------------------*/
static char   s_level   =   0;
static char   s_prefix  [100] = "";
static FILE  *s_logger  = NULL;
static char   s_print   [200] = "";



/*====================------------------------------------====================*/
/*===----                           helpers                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_______o (void) {;}

FILE* yLOG_ufile   (char *a_file)  { s_logger = fopen (a_file, "wt");  s_level = 0; strcpy (s_prefix, "");  return s_logger;  }
void  yLOG_udest   (FILE *a_dest)  { s_level =  0;  strcpy (s_prefix, "");  s_logger = a_dest;  return 0; }
char *yLOG_ulast   (void)          { return s_print; }
char  yLOG_uclear  (void)          { strcpy (s_print, ""); return 0;  }



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_____o (void) {;}

void
yLOG_uenter   (char *a_func)
{
   int         i           =    0;
   sprintf (s_print , "%sENTERING (%.30s)", s_prefix, a_func);
   fprintf (s_logger, "%s\n", s_print);
   if (s_level < 10)  ++s_level;
   strcpy (s_prefix, "");
   for (i = 0; i < s_level; ++i) {
      if (i == s_level - 1)  strcat (s_prefix, "´  ");
      else                   strcat (s_prefix, "´··");
   }
   return;
}

void
yLOG_uexit    (char *a_func)
{
   int         i           =    0;
   if (s_level >  0)  --s_level;
   strcpy (s_prefix, "");
   for (i = 0; i < s_level; ++i) {
      if (i == s_level - 1)  strcat (s_prefix, "´  ");
      else                   strcat (s_prefix, "´··");
   }
   sprintf (s_print , "%sEXITING  (%.30s)", s_prefix, a_func);
   fprintf (s_logger, "%s\n", s_print);
   return;
}

void
yLOG_uexitr    (char *a_func, int a_rce)
{
   sprintf (s_print , "%sWARNING, rce (%d)", s_prefix, a_rce);
   fprintf (s_logger, "%s\n", s_print);
   return yLOG_uexit (a_func);
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES______o (void) {;}

void
yLOG_unote    (char *a_info)
{
   sprintf (s_print , "%s%s", s_prefix, a_info);
   fprintf (s_logger, "%s\n", s_print);
   return;
}

void
yLOG_uinfo    (char *a_subject, char *a_info)
{
   sprintf (s_print , "%s%-10.10s: %s", s_prefix, a_subject, a_info);
   fprintf (s_logger, "%s\n", s_print);
   return;
}

void
yLOG_uchar         (char *a_subject, uchar a_char)
{
   uchar c  = 'Ï';
   if (a_char >   32 && a_char != 127)  c = a_char;
   switch (a_char) {
   case   0 : c = '£';  break;   /* null   */
   case  10 : c = '¦';  break;   /* return */
   case  13 : c = '¦';  break;   /* enter  */
   case  27 : c = '¥';  break;   /* escape */
   case  29 : c = '¨';  break;   /* group  */
   case  31 : c = '§';  break;   /* escape */
   case  32 : c = '·';  break;   /* space  */
   }
   sprintf (s_print , "%s%-10.10s: %c", s_prefix, a_subject, c);
   fprintf (s_logger, "%s\n", s_print);
   return;
}

void
yLOG_uvalue        (char *a_subject, int a_value)
{
   sprintf (s_print , "%s%-10.10s: %d", s_prefix, a_subject, a_value);
   fprintf (s_logger, "%s\n", s_print);
   return;
}

void
yLOG_upoint        (char *a_subject, void *a_value)
{
   sprintf (s_print , "%s%-10.10s: %p", s_prefix, a_subject, a_value);
   fprintf (s_logger, "%s\n", s_print);
   return;
}



/*====================------------------------------------====================*/
/*===----                       variable args                          ----===*/
/*====================------------------------------------====================*/
static void      o___VARARG________o (void) {;}

void
yLOG_ucomplex      (char *a_subject, char *a_format, ...)
{
   char        x_format  [200] = "";
   va_list     args;
   va_start  (args, a_format);
   vsnprintf (x_format, 200, a_format, args);
   sprintf   (s_print , "%s%-10.10s: %s", s_prefix, a_subject, x_format);
   fprintf   (s_logger, "%s\n", s_print);
   va_end    (args);
   return;
}

void
yLOGS_err          (char *a_format, ...)
{
   char        x_format  [200] = "";
   va_list     args;
   va_start  (args, a_format);
   vsnprintf (x_format, 200, a_format, args);
   sprintf   (s_print , "%s", x_format);
   fprintf   (s_logger, "%s\n", s_print);
   va_end    (args);
   return;
}


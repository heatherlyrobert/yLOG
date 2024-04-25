

/*---(simple variables)------------------*/
static char   s_level   =   0;
static char   s_prefix  [100] = "";



/*====================------------------------------------====================*/
/*===----                          structure                           ----===*/
/*====================------------------------------------====================*/
static void      o___STRUCTURE_____o (void) {;}

void
yLOG_uenter   (char *a_func)
{
   int         i           =    0;
   printf ("%sENTERING (%.30s)\n", s_prefix, a_func);
   if (s_level < 10)  ++s_level;
   strcpy (s_prefix, "");
   for (i = 0; i < s_prefix; ++i)  strcat (s_prefix, "   ");
   return;
}

void
yLOG_uexit    (char *a_func)
{
   int         i           =    0;
   if (s_level >  0)  --s_level;
   strcpy (s_prefix, "");
   for (i = 0; i < s_prefix; ++i)  strcat (s_prefix, "   ");
   printf ("%sEXITING  (%.30s)\n", s_prefix, a_func);
   return;
}

void
yLOG_uexitr    (char *a_func, int a_rce)
{
   printf ("%sWARNING, rce (%d)\n", s_prefix, a_rce);
   yLOG_uexit (a_func);
   return;
}



/*====================------------------------------------====================*/
/*===----                     messages (complete)                      ----===*/
/*====================------------------------------------====================*/
static void      o___MESSAGES______o (void) {;}

void
yLOG_unote    (char *a_info)
{
   printf ("%s%s\n", s_prefix, a_info);
   return;
}

void
yLOG_uinfo    (char *a_subject, char *a_info)
{
   printf ("%s%-10.10s: %s\n", s_prefix, a_subject, a_info);
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
   printf ("%s%-10.10s: %c\n", s_prefix, a_subject, c);
   return;
}

void
yLOG_uvalue        (char *a_subject, int a_value)
{
   printf ("%s%-10.10s: %d\n", s_prefix, a_subject, a_value);
   return;
}

void
yLOG_upoint        (char *a_subject, void *a_value)
{
   printf ("%s%-10.10s: %p\n", s_prefix, a_subject, a_value);
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
   sprintf   ("%s%-10.10s: %.150s\n", s_prefix, a_subject, x_format);
   va_end    (args);
   return;
}

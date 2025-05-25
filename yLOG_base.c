/*============================[[ beg-of-code ]]===============================*/
#include    "yLOG.h"
#include    "yLOG_priv.h"

tITS        myLOG;
static int  s_lines  = 0;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char*      /* ---- : return library versioning information -------------------*/
yLOGS_version           (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (myLOG.m_version, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return myLOG.m_version;
}



/*====================------------------------------------====================*/
/*===----                        data accessors                        ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSORS_______________o (void) {;}

int   yLOGS_lognum   (void) { if (myLOG.m_logger == NULL) return -1; else return fileno (myLOG.m_logger); }

llong yLOGS_time     (void) { return ylog__timestamp(); }

char *yLOGS_path     (void) { return myLOG.m_path; };

char *yLOGS_filename (void) { return myLOG.m_filename; };





/*====================------------------------------------====================*/
/*===----                   specialty testing support                  ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALTY_______________o (void) {;};

static char s_ylog_curr [LEN_TERSE] = "";

char 
yLOG_curr               (char a_stage, char a_urg)
{
   /*> printf ("specific area\n");                                                    <*/
   /*> printf ("start %c %c, orig   %c %c\n", a_stage, a_urg, myLOG.m_stage, myLOG.m_urg);   <*/
   myLOG.m_stage  = a_stage;
   myLOG.m_urg    = a_urg;
   if (a_stage <= 32 || (a_stage >= 127 && a_stage <= 159))  myLOG.m_stage = '·';
   if (a_urg   <= 32 || (a_urg   >= 127 && a_urg   <= 159))  myLOG.m_urg   = '·';
   /*> printf ("given %c %c, set to %c %c\n", a_stage, a_urg, myLOG.m_stage, myLOG.m_urg);   <*/
   return 0;
}

char*
yLOG_curr_show          (void)
{
   sprintf (s_ylog_curr, "%c %c", myLOG.m_stage, myLOG.m_urg);
   /*> printf ("yLOG_curr_show å%sæ   (%c)   (%c)\n", s_ylog_curr, myLOG.m_stage, myLOG.m_urg);   <*/
   return s_ylog_curr;
}

char
yLOGS_verify            (char *a_name, char a_log, char a_line)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_path      [LEN_PATH];
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_name      [LEN_PATH];
   int         x_len       =    0;
   char       *p           = NULL;
   tSTAT       s;
   char        c           =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD] = "";
   /*---(header)-------------------------*/
   DEBUG_YLOGS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YLOGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YLOGS  yLOG_info    ("a_name"    , a_name);
   /*---(location)-----------------------*/
   DEBUG_YLOGS  yLOG_char    ("a_log"     , a_log);
   --rce;  switch (a_log) {
   case YLOG_SYS  : strcpy (x_path, LOGDIR); break;
   case YLOG_HIST : strcpy (x_path, HISDIR); break;
   case YLOG_ROOT : strcpy (x_path, ROOTDIR); break;
   case YLOG_USB  : strcpy (x_path, USBDIR); break;
   case YLOG_TMP  : strcpy (x_path, TMPDIR); break;
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_YLOGS  yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_YLOGS  yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_YLOGS  yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_YLOGS  yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_YLOGS  yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_YLOGS  yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_YLOGS  yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_YLOGS  yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_YLOGS  yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YLOGS  yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check good result)--------------*/
   DEBUG_YLOGS  yLOG_value   ("c"         , c);
   --rce;  if (c != 1) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return c;
   }
   /*---(check on crontab file)----------*/
   rc = stat (x_name, &s);
   DEBUG_YLOGS  yLOG_value   ("stat"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (!S_ISREG (s.st_mode))  {
      DEBUG_YLOGS  yLOG_note    ("can only use regular files");
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get a line)------------------*/
   s_lines = 0;
   --rce;  if (a_line >= 0) {
      strncpy (myLOG.m_full, "-", LEN_PATH);
      f = fopen (x_name, "rt");
      if (rc < 0) {
         DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      while (1) {
         fgets (x_recd, LEN_RECD, f);
         if (feof (f))   break;
         x_len = strlen (x_recd);
         if (x_recd [x_len - 1] == '\n') x_recd [--x_len] = '\0';
         if (s_lines == a_line) strncpy (myLOG.m_full, x_recd, LEN_PATH);
         ++s_lines;
      }
      if (myLOG.m_full [0] == '-') {
         DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YLOGS  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yLOGS_remove            (char *a_name, char a_log)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   char        x_path      [LEN_PATH];
   DIR        *x_dir       = NULL;
   tDIRENT    *x_file      = NULL;
   char        x_name      [LEN_PATH];
   int         x_len       =    0;
   char       *p           = NULL;
   tSTAT       s;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YLOGS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YLOGS  yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YLOGS  yLOG_info    ("a_name"    , a_name);
   /*---(location)-----------------------*/
   DEBUG_YLOGS  yLOG_char    ("a_log"     , a_log);
   --rce;  switch (a_log) {
   case YLOG_SYS  : strcpy (x_path, LOGDIR); break;
   case YLOG_HIST : strcpy (x_path, HISDIR); break;
   case YLOG_ROOT : strcpy (x_path, ROOTDIR); break;
   case YLOG_USB  : strcpy (x_path, USBDIR); break;
   case YLOG_TMP  : strcpy (x_path, TMPDIR); break;
   default        :
                    DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
                    break;
   }
   DEBUG_YLOGS  yLOG_info    ("x_path"    , x_path);
   /*---(open dir)-----------------------*/
   DEBUG_YLOGS  yLOG_info    ("f_path"    , x_path);
   x_dir = opendir (x_path);
   DEBUG_YLOGS  yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   while (1) {
      /*---(pick file)-------------------*/
      x_file = readdir (x_dir);
      DEBUG_YLOGS  yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      DEBUG_YLOGS  yLOG_info    ("name"      , x_file->d_name);
      /*---(filter by name)--------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_YLOGS  yLOG_value   ("x_len"     , x_len);
      if (x_len < 20)  continue;
      DEBUG_YLOGS  yLOG_info    ("suffix"    , x_file->d_name + x_len - 5);
      rc = strcmp (x_file->d_name  + x_len - 5, ".ulog");
      DEBUG_YLOGS  yLOG_value   ("match"     , rc);
      if (rc != 0)  continue;
      DEBUG_YLOGS  yLOG_info    ("potential" , x_file->d_name + 18);
      p  = strstr (x_file->d_name + 18, a_name);
      DEBUG_YLOGS  yLOG_point   ("p"         , p);
      if (p == NULL)  continue;
      /*---(found it)--------------------*/
      ++c;
      sprintf (x_name, "%s%s", x_path, x_file->d_name);
      unlink  (x_name);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = closedir (x_dir);
   DEBUG_YLOGS  yLOG_point   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YLOGS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YLOGS  yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;};

char          unit_answer [LEN_RECD];

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_quiet       (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_QUIET);
   myLOG.m_use   = 'u';
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ylog__unit_loud        (void)
{
   yLOGS_begin ("yLOG_unit", YLOG_SYS, YLOG_NOISE);
   myLOG.m_use   = 'u';
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ylog__unit_end         (void)
{
   yLOGS_end     ();
   return 0;
}

char*            /*--> unit test accessor ------------------------------*/
ylog_base__unit         (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD]  = "[]";
   int         c           =    0;
   /*---(prepare)------------------------*/
   strncpy  (unit_answer, "BASE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "prefix"     ) == 0) {
      sprintf (t, "[%s]", myLOG.m_prefix);
      snprintf (unit_answer, LEN_RECD, "BASE prefix      : %2d  %2d%s", myLOG.m_indent, strlen (myLOG.m_prefix), t);
   }
   else if (strcmp (a_question, "full"       ) == 0) {
      c = strlen (myLOG.m_full);
      if (c > 99)  c = 99;
      sprintf (t, "[%s]", myLOG.m_full);
      snprintf (unit_answer, LEN_RECD, "BASE full        : %2d%s", c, t);
   }
   else if (strcmp (a_question, "prog"       ) == 0) {
      sprintf (t, "[%s]", myLOG.m_prog);
      snprintf (unit_answer, LEN_RECD, "BASE prog        : %2d%s", strlen (myLOG.m_prog), t);
   }
   else if (strcmp (a_question, "loud"       ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE loud        : %c  %2d", myLOG.m_loud, myLOG.m_count);
   }
   else if (strcmp (a_question, "lines"      ) == 0) {
      snprintf (unit_answer, LEN_RECD, "BASE lines       : %2d", s_lines);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===[[ END ]]================================================================*/

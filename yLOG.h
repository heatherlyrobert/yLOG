/*============================[[    beg-code    ]]============================*/
#ifndef   YLOG_HGUARD
#define   YLOG_HGUARD       loaded



/*===[[ CONSTANTS ]]======================================*/
#define   YLOG_NONE         '-'
#define   YLOG_SYS          's'
#define   YLOG_HIST         'h'
#define   YLOG_STDOUT       'o'
#define   YLOG_ROOT         'r'
#define   YLOG_USB          'u'
#define   YLOG_NULL         '0'
#define   YLOG_VALIDS       "-shoru0"

#define   YLOG_NOISE        'N'
#define   YLOG_QUIET        'Q'



/*===[[ TYPES ]]==========================================*/
typedef   const char   cchar;
typedef   long long    llong;
typedef   const int    cint;



/*===[[ MACROS ]]=========================================*/
#define   yLOG_hintx(FMT,...)   ylog_errors ("HINT"   , 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_warnx(FMT,...)   ylog_errors ("WARNING", 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_errorx(FMT,...)  ylog_errors ("ERROR"  , 'e', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_fatalx(FMT,...)  ylog_errors ("FATAL"  , 'g', __FILE__, __LINE__, FMT, __VA_ARGS__)



/*===[[ PUBLIC FUNCTIONS (non-strip) ]]===================*/
/*---(program)--------------*/
char        yLOGS_begin        (const char *a_program, const char a_location, const char a_quiet);
void        yLOGS_end          (void);
/*---(support)--------------*/
char       *yLOGS_version      (void);
int         yLOGS_lognum       (void);
long long   yLOGS_time         (void);
char       *yLOGS_path         (void);
char       *yLOGS_filename     (void);
/*---(testing support)------*/
char        yLOGS_verify       (cchar *a_name, cchar a_log);
char        yLOGS_remove       (cchar *a_name, cchar a_log);



/*===[[ PUBLIC FUNCTIONS (stripped) ]]====================*/
/*---(function (2))---------*/
void        yLOG_enter         (const char *a_func);
void        yLOG_exit          (const char *a_func);
void        yLOG_exitr         (const char *a_func   , const int a_rce);
/*---(normal (12))----------*/
void        yLOG_note          (const char *a_info);
void        yLOG_info          (const char *a_subject, const char    *a_info);
void        yLOG_delim         (const char *a_subject, const char    *a_info);
void        yLOG_value         (const char *a_subject, const int      a_value);
void        yLOG_llong         (const char *a_subject, const llong    a_value);
void        yLOG_hex           (const char *a_subject, const long     a_value);
void        yLOG_double        (const char *a_subject, const double   a_value);
void        yLOG_char          (const char *a_subject, const char     a_char);
void        yLOG_point         (const char *a_subject, const void    *a_value);
void        yLOG_bullet        (const int   a_num,     const char    *a_info);
void        yLOG_pair          (const int   a_num,     const int      a_value);
void        yLOG_complex       (const char *a_subject, cchar *a_format, ...);
/*---(breaks (2))-----------*/
void        yLOG_break         (void);
void        yLOG_sync          (void);
void        yLOG_unitcond      (int a_scrp, int a_cond, int a_line, char *a_desc);
void        yLOG_unitstep      (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc);
/*---(compact (9))----------*/
void        yLOG_senter        (const char *a_func);
void        yLOG_sexit         (const char *a_func);
void        yLOG_sexitr        (const char *a_func,    const int   a_rce);
void        yLOG_snote         (const char *a_info);
void        yLOG_sinfo         (const char *a_subject, const char *a_info);
void        yLOG_sint          (const int   a_value);
void        yLOG_sdouble       (const double  a_value);
void        yLOG_shex          (const long  a_value);
void        yLOG_schar         (const char  a_char);
void        yLOG_spoint        (const void *a_pointer);
void        yLOG_svalue        (const char *a_subject, const int   a_value);
/*---(warnings (4))---------*/
void        yLOG_warn          (const char *a_issue);
void        yLOG_error         (const char *a_issue);
void        yLOG_fatal         (const char *a_issue);
void        yLOG_boom          (const char *a_issue);
void        yLOG_signal        (const int   a_signal);
void        yLOG_errors        (cchar *a_desc, cchar a_type, cchar *a_file, cint a_line, cchar *a_format, ...);
/*---(done)-----------------*/


#endif

/*===[[ END ]]================================================================*/

/*============================[[    beg-code    ]]============================*/
#ifndef   YLOG_HGUARD
#define   YLOG_HGUARD       loaded


#include <ySTR_solo.h>

/*===[[ CONSTANTS ]]======================================*/
#define   YLOG_SYS          's'
#define   YLOG_HIST         'h'
#define   YLOG_STDOUT       'o'
#define   YLOG_ROOT         'r'
#define   YLOG_USB          'u'
#define   YLOG_NULL         '0'
#define   YLOG_TMP          't'
#define   YLOG_VALIDS       "shoru0t"

#define   YLOG_NOISE        'N'
#define   YLOG_QUIET        'Q'

#define   YLOG_ONENTER      'e'
#define   YLOG_ONEXIT       'x'
#define   YLOG_ONBOTH       'b'


/*===[[ TYPES ]]==========================================*/
typedef   unsigned char   uchar;
typedef   long long       llong;
typedef   const char      cchar;
typedef   const int       cint;
typedef   const long      clong;
typedef   const long long cllong;
typedef   const double    cdouble;
typedef   const void      cvoid;
typedef   const unsigned char   cuchar;



/*===[[ MACROS ]]=========================================*/
#define   yLOG_hintx(FMT,...)   ylog_errors ("HINT"   , 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_warnx(FMT,...)   ylog_errors ("WARNING", 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_errorx(FMT,...)  ylog_errors ("ERROR"  , 'e', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_fatalx(FMT,...)  ylog_errors ("FATAL"  , 'g', __FILE__, __LINE__, FMT, __VA_ARGS__)



/*===[[ PUBLIC FUNCTIONS (non-strip) ]]===================*/
/*---(program)--------------*/
char        yLOGS_begin        (cchar *a_program, cchar a_location, cchar a_quiet);
void        yLOGS_end          (void);
/*---(support)--------------*/
char       *yLOGS_version      (void);
int         yLOGS_lognum       (void);
long long   yLOGS_time         (void);
char       *yLOGS_path         (void);
char       *yLOGS_filename     (void);
/*---(testing support)------*/
char        yLOGS_verify       (cchar *a_name, cchar a_log, cchar a_line);
char        yLOGS_remove       (cchar *a_name, cchar a_log);



/*===[[ PUBLIC FUNCTIONS (stripped) ]]====================*/
/*---(tracking)-------------*/
void        yLOGS_curr         (uchar a_stage, uchar a_urg);
char*       yLOG_curr_show     (void);
/*---(general)--------------*/
void        yLOGS_mute         (void);
void        yLOGS_unmute       (void);
char        yLOGS_mute_check   (void);
char        yLOGS_track        (cchar a_func    [LEN_TITLE], cchar a_type);
char        yLOGS_untrack      (cchar a_func    [LEN_TITLE]);
/*---(function (2))---------*/
void        yLOG_enter         (cchar a_func    [LEN_TITLE]);
void        yLOG_exit          (cchar a_func    [LEN_TITLE]);
void        yLOG_exitr         (cchar a_func    [LEN_TITLE]   , cint a_rce);
/*---(normal (12))----------*/
void        yLOG_note          (cchar a_info [LEN_FULL]);
void        yLOG_info          (cchar a_subject [LEN_LABEL], cchar     a_info [LEN_FULL]);
void        yLOG_delim         (cchar a_subject [LEN_LABEL], cchar     a_info [LEN_FULL]);
void        yLOG_value         (cchar a_subject [LEN_LABEL], cint      a_value);
void        yLOG_llong         (cchar a_subject [LEN_LABEL], cllong    a_value);
void        yLOG_hex           (cchar a_subject [LEN_LABEL], clong     a_value);
void        yLOG_double        (cchar a_subject [LEN_LABEL], cdouble   a_value);
void        yLOG_real          (cchar a_subject [LEN_LABEL], cdouble   a_value);
void        yLOG_char          (cchar a_subject [LEN_LABEL], cuchar    a_char);
void        yLOG_point         (cchar a_subject [LEN_LABEL], cvoid    *a_value);
void        yLOG_bullet        (cint  a_num,                 cchar     a_info [LEN_FULL]);
void        yLOG_pair          (cint  a_num,                 cint      a_value);
void        yLOG_complex       (cchar a_subject [LEN_LABEL], cchar *a_format, ...);
/*---(breaks (2))-----------*/
void        yLOG_break         (void);
void        yLOG_sync          (void);
void        yLOG_unitcond      (int a_scrp, int a_cond, int a_line, char *a_desc);
void        yLOG_unitstep      (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc);
/*---(compact (9))----------*/
void        yLOG_senter        (cchar    a_func [LEN_TITLE]);
void        yLOG_sexit         (cchar    a_func [LEN_TITLE]);
void        yLOG_sexitr        (cchar    a_func [LEN_TITLE],    cint   a_rce);
void        yLOG_snote         (cchar    a_info [LEN_FULL]);
void        yLOG_sinfo         (cchar    a_subject [LEN_LABEL], cchar a_info [LEN_FULL]);
void        yLOG_sint          (cint     a_value);
void        yLOG_sdouble       (cdouble  a_value);
void        yLOG_sreal         (cdouble  a_value);
void        yLOG_shex          (clong    a_value);
void        yLOG_schar         (cuchar   a_char);
void        yLOG_spoint        (cvoid   *a_pointer);
void        yLOG_svalue        (cchar    a_subject [LEN_LABEL], cint   a_value);
/*---(warnings (4))---------*/
void        yLOG_warn          (cchar *a_issue);
void        yLOG_error         (cchar *a_issue);
void        yLOG_fatal         (cchar *a_issue);
void        yLOG_boom          (cchar *a_issue);
void        yLOG_signal        (cint   a_signal);
void        yLOG_errors        (cchar *a_desc, cchar a_type, cchar *a_file, cint a_line, cchar *a_format, ...);
/*---(done)-----------------*/


#endif

/*===[[ END ]]================================================================*/

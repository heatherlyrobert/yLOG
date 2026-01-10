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

#define   DEBUG_UNIT        if (1) 


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
char        yLOGS_begin        (char *a_program, char a_location, char a_quiet);
char        yLOGS_end          (void);
/*---(support)--------------*/
char       *yLOGS_version      (void);
int         yLOGS_lognum       (void);
llong       yLOGS_time         (void);
char       *yLOGS_path         (void);
char       *yLOGS_filename     (void);
/*---(testing support)------*/
char        yLOGS_verify       (char *a_name, char a_log, char a_line);
char        yLOGS_remove       (char *a_name, char a_log);



/*===[[ PUBLIC FUNCTIONS (stripped) ]]====================*/
/*---(tracking)-------------*/
char        yLOG_curr          (uchar a_stage, uchar a_urg);
char*       yLOG_curr_show     (void);
/*---(general)--------------*/
char        yLOGS_mute         (void);
char        yLOGS_unmute       (void);
char        yLOGS_mute_check   (void);
char        yLOGS_track        (char a_func  [LEN_TITLE], char a_type);
char        yLOGS_untrack      (char a_func  [LEN_TITLE]);
/*---(function (2))---------*/
char        yLOG_enter         (char a_func  [LEN_TITLE]);
char        yLOG_exit          (char a_func  [LEN_TITLE]);
char        yLOG_exitr         (char a_func  [LEN_TITLE], int a_rce);
/*---(normal (12))----------*/
char        yLOG_note          (char a_info  [LEN_RECD]);
char        yLOG_info          (char a_label [LEN_LABEL], char     a_info [LEN_RECD]);
char        yLOG_delim         (char a_label [LEN_LABEL], char     a_info [LEN_RECD]);
char        yLOG_value         (char a_label [LEN_LABEL], int      a_value);
char        yLOG_llong         (char a_label [LEN_LABEL], llong    a_value);
char        yLOG_hex           (char a_label [LEN_LABEL], long     a_value);
char        yLOG_double        (char a_label [LEN_LABEL], double   a_value);
char        yLOG_real          (char a_label [LEN_LABEL], double   a_value);
char        yLOG_char          (char a_label [LEN_LABEL], uchar    a_char);
char        yLOG_point         (char a_label [LEN_LABEL], void    *a_pointer);
char        yLOG_bullet        (int  a_num,               char     a_info [LEN_RECD]);
char        yLOG_pair          (int  a_num,               int      a_value);
char        yLOG_complex       (char a_label [LEN_LABEL], char *a_format, ...);
/*---(breaks (2))-----------*/
char        yLOG_break         (void);
char        yLOG_sync          (void);
char        yLOG_unitcond      (int a_scrp, int a_cond, int a_line, char *a_desc);
char        yLOG_unitstep      (int a_scrp, int a_cond, int a_step, int a_line, char *a_desc);
/*---(compact (9))----------*/
char        yLOG_senter        (char a_func  [LEN_TITLE]);
char        yLOG_sexit         (char a_func  [LEN_TITLE]);
char        yLOG_sexitr        (char a_func  [LEN_TITLE],  int   a_rce);
char        yLOG_snote         (char a_info  [LEN_FULL]);
char        yLOG_sinfo         (char a_label [LEN_LABEL], char a_info [LEN_FULL]);
char        yLOG_sint          (int  a_value);
char        yLOG_sdouble       (double  a_value);
char        yLOG_sreal         (double  a_value);
char        yLOG_shex          (long    a_value);
char        yLOG_schar         (uchar   a_char);
char        yLOG_spoint        (void   *a_pointer);
char        yLOG_svalue        (char a_label [LEN_LABEL], int   a_value);


/*---(warnings (4))---------*/
char        yLOG_warn          (char *a_issue);
char        yLOG_error         (char *a_issue);
char        yLOG_fatal         (char *a_issue);
char        yLOG_boom          (char *a_issue);
char        yLOG_signal        (int   a_signal);
char        yLOG_errors        (char *a_desc, char a_type, char *a_file, int a_line, char *a_format, ...);
/*---(done)-----------------*/


#endif

/*===[[ END ]]================================================================*/

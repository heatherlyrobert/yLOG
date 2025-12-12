/*============================[[    beg-code    ]]============================*/
#ifndef   YLOG_SOLO   
#define   YLOG_SOLO         loaded

/*
 *  pre-yLOG installation micro-logging services
 *     - same calling structure/args
 *     - automatic indentation
 *     - less controls and defense
 *     - more limited, but core selection
 *     - straight to specific files
 *     - used as a header inclusion (not a library)
 *
 *  ONLY required for short-path to getting unit testing working, i.e.,
 *  yUNIT and koios.  these two only include "_solo.h" headers and
 *  standard libraries.  after they are working, we test and use full
 *  yLOG and yURG.
 *
 *  inclusion...
 *     - add "#include <yLOG_solo.h>" into shared header
 *     - add "#include <yLOG_uver.h>" into one source/code file
 *
 *  CRITICAL
 *
 *     yLOG only exists within non-debug versions so all functions
 *     prefixed with "yLOG_" are stripped from source code.
 *
 *     also, since error messages must survive stripping, they
 *     MUST be prefixed differently (to keep it simple) -- "yERR_".
 *
 */


#include  <ySTR_solo.h>

typedef unsigned char uchar;

#define   DEBUG_PROG    if (1) 
#define   DEBUG_UNIT    if (1) 


/*---(micro logging)---------------------*/
char        ylog_uopen         (void);
char        ylog_ustdout       (void);
char        ylog_ureset        (void);
char        ylog_uclose        (void);
char        ylog_udone         (void);

/*---(micro logging unit)----------------*/
char*       ylog_uwhich        (void);
int         ylog_ulines        (void);
char*       ylog_upeek         (char a_dir);

/*---(micro structure)-------------------*/
char        ylog_uenter        (char a_func [LEN_DESC]);
char        ylog_uexit         (char a_func [LEN_DESC]);
char        ylog_uexitr        (char a_func [LEN_DESC], int a_rce);

/*---(micro data)------------------------*/
char        ylog_unote         (char a_info [LEN_FULL]);
char        ylog_uinfo         (char a_label [LEN_LABEL], char a_info [LEN_FULL]);
char        ylog_uchar         (char a_label [LEN_LABEL], uchar a_char);
char        ylog_uvalue        (char a_label [LEN_LABEL], int a_value);
char        ylog_upoint        (char a_label [LEN_LABEL], void *a_point);
char        ylog_ucomplex      (char a_label [LEN_LABEL], char *a_format, ...);

/*---(micro errors)----------------------*/
char        yerr_uopen         (void);
char        yerr_ustderr       (void);
char        yerr_ureset        (void);
char        yerr_uclose        (void);
char        yerr_udone         (void);

/*---(micro error writing)---------------*/
char        yerr_uerror        (char *a_format, ...);

/*---(micro error unit)------------------*/
char*       yerr_uwhich        (void);
int         yerr_ulines        (void);
char*       yerr_upeek         (char a_dir);


#endif

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
 *  inclusion...
 *     - add "#include <yLOG_solo.h>" into shared header
 *     - add "#include <yLOG_uver.h>" into one source/code file
 *
 */


#include  <stdio.h>
#include  <stdarg.h>                   /* va_arg                              */
#include  <unistd.h>                   /* unlink                              */

#include  <ySTR_solo.h>

#include  <yENV_solo.h>
#include  <yENV_uver.h>

typedef unsigned char uchar;

#define   DEBUG_PROG    if (1) 
#define   DEBUG_UNIT    if (1) 


/*---(micro logging)---------------------*/
char        yLOG_uopen         (void);
int         yLOG_ulines        (void);
char*       yLOG_upeek         (char a_dir);
char        yLOG_uclose        (void);
char        yLOG_udone         (void);

/*---(micro structure)-------------------*/
char        yLOG_uenter        (char *a_func);
char        yLOG_uexit         (char *a_func);
char        yLOG_uexitr        (char *a_func, int a_rce);

/*---(micro data)------------------------*/
char        yLOG_unote         (char *a_info);
char        yLOG_uinfo         (char *a_subject, char *a_info);
char        yLOG_uchar         (char *a_subject, uchar a_char);
char        yLOG_uvalue        (char *a_subject, int a_value);
char        yLOG_upoint        (char *a_subject, void *a_value);
char        yLOG_ucomplex      (char *a_subject, char *a_format, ...);

/*---(micro errors)----------------------*/
char        yLOG_ueopen        (void);
int         yLOG_uelines       (void);
char*       yLOG_uepeek        (char a_dir);
char        yLOG_ueclose       (void);
char        yLOG_uedone        (void);

/*---(micro error writing)---------------*/
char        yLOG_uerr          (char *a_format, ...);


#endif

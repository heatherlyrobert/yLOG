/*============================[[    beg-code    ]]============================*/
#ifndef   YLOG_SOLO   
#define   YLOG_SOLO         loaded

/*
 *  pre-yLOG installation micro-logging services
 *     - same calling structure/args
 *     - automatic indentation
 *     - less controls and defense
 *     - more limited, but core selection
 *     - straight to stdout only
 *     - used as a header inclusion (not a library)
 *
 */


#include  <stdarg.h>                   /* va_arg                              */

typedef unsigned char uchar;

#define   DEBUG_PROG    if (1) 


/*---(micro log functions)---------------*/
void        yLOG_uenter        (char *a_func);
void        yLOG_uexit         (char *a_func);
void        yLOG_uexitr        (char *a_func, int a_rce);
void        yLOG_unote         (char *a_info);
void        yLOG_uinfo         (char *a_subject, char *a_info);
void        yLOG_uchar         (char *a_subject, uchar a_char);
void        yLOG_uvalue        (char *a_subject, int a_value);
void        yLOG_upoint        (char *a_subject, void *a_value);
void        yLOG_ucomplex      (char *a_subject, char *a_format, ...);

/*---(specialty functions)---------------*/
void        yLOGS_ufile        (char *a_file);
void        yLOGS_udest        (FILE *a_dest);
void        yLOGS_err          (char *a_format, ...);
void        yLOGS_uend         (void);

/*---(debugging)-------------------------*/
char       *yLOG_ulast         (void);
void        yLOG_uclear        (void);


#endif

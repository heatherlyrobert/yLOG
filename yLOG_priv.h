/*============================[[ beg-of-code ]]===============================*/
#ifndef YLOG_pguard
#define YLOG_pguard loaded



/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "SA (system administration)"
#define     P_NICHE     "pm (process monitoring)"
#define     P_PURPOSE   "simple, consistent, clean process execution logging"

#define     P_NAMESAKE  "clio-chrysafenios (flowering)"
#define     P_HERITAGE  "greek muse of written and oral history, song, and poetry"
#define     P_IMAGERY   "golden young woman holding a scroll, seated by a chest of books"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-07"
#define     P_DEPENDS   "ySTR"

#define     P_VERNUM    "1.2v"
#define     P_VERTXT    "added basic signal logging capability"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "i know there are many better options, but i *own* this one"

#define     P_GREEK     \
 "clio is one of the nine greek muses (mousai) who are the goddesses of art¦" \
 "literature, and science.  the muses are the daughters of zeus and¦" \
 "mnemosyne (the titan of memory).  as a group they inspire creation,¦" \
 "enthusiasm, and the creative impulses.  clio, the proclaimer) is the muse¦" \
 "of written and oral history, song, and poetry.  she is typically shown¦" \
 "holding a scroll and near a chest of books or tablets.¦"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_SUMMARY   \
 "yLOG is a simple, direct, consistent, and clean shared library to enable¦" \
 "process execution logging and encourge monitoring, process flow¦" \
 "understanding, and early issue detection in my custom programs.¦
#define     P_CURRENT   \
 "my code base is growing quickly and much of that code executes either¦" \
 "continuously, frequently, or at critical moments -- big code base,¦" \
 "audacious plans, and one programmer to rule it all ;)¦"
#define     P_ALTERNS   "syslog,systemd,printf,gdb"
#define     P_CONCERN   \
 "the art of logging and messaging seems to have died with the system¦" \
 "operator and is now done using expensive commercial tools with incoherent¦" \
 "streams of one dimensional messages.¦"
#define     P_USERBASE  \
 "never confuse tailored, technical, super-user systems and general, easy-¦" \
 "to-use, zero effort required systems built to get end-users up and happy¦" \
 "as quickly as possible.¦"
#define     P_COURSE    \
 "i need something configurable, built-in, and ready for immediate use.  it¦" \
 "must include structure/flow logging as well as values, contents, and¦" \
 "warning messages and be easy to search and filter.¦"
#define     P_ASSUME    \
 "-- create a standard, indented flow that is easy to follow¦" \
 "-- partners with yURG to allow up front and run-time configuration¦" \
 "-- easy to build into any c program and improve overtime¦" \
 "-- make can filter out to produce both debug and production versions¦" \
 "-- all messages are categorized, indented, and include timestamps¦" \
 "-- will log onto a ram-drive for speed (/var/yLOG)¦"

/*
 *  all intenting is by threes (no configuration so the eyes standardize)
 *  timestamps and counts are perfectly aligned to avoid eye tracking issues
 *  message types are always in same column to help sorting and filtering
 *  indentation includes markers to help line up top-to-bottom
 *  all data titles are 10 characters so everything lines up perfect
 *
 *
 *
 *
 *
 */



#include  "yLOG.h"

#include  <stdio.h>
#include  <stdlib.h>                  /* getenv()                            */
#include  <string.h>
#include  <ctype.h>
#include  <time.h>              /* clock, time                                */
#include  <sys/time.h>          /* gettimeofday                               */
#include  <sys/types.h>         /* open */
#include  <sys/stat.h>          /* open */
#include  <fcntl.h>             /* open */
#include  <sys/unistd.h>        /* gethostname, getpid, getppid               */
#include  <stdarg.h>                   /* va_arg                              */
#include  <ySTR.h>
#include  <yURG.h>
#include  "signal.h"

/*-> to support the 'uname' call to get machine and system names  */
#include  <sys/utsname.h>


#define           LOGDIR     "/var/log/yLOG/"
#define           HISDIR     "/var/log/yLOG.historical/"
#define           ROOTDIR    "/"
#define           USBDIR     "/mnt/usb1/"


/*===[[ STANDARDS ]]===============================================#
/*---(indentation)----------------------*/
#define           LVL_BEG         '>'    /* indent, beg of function           */
#define           LVL_SAME        '-'    /* level stays the same, content     */
#define           LVL_END         '<'    /* exdent, end of function           */
/*---(mortal, dangerous)----------------*/
#define           TYPE_NUCLEAR    'n'    /* fatal, non-graceful, system-wide  */
#define           TYPE_CLUMSY     'c'    /* fatal, non-graceful, local        */
#define           TYPE_GRACEFUL   'g'    /* fatal, graceful, handlable        */
/*---(debugging)------------------------*/
#define           TYPE_ERROR      'e'    /* difficult, but recoverable        */
#define           TYPE_WARNING    'w'    /* handled, easily recoverable       */
#define           TYPE_UPDATE     'u'    /* new data or versions              */
/*---(review)---------------------------*/
#define           TYPE_DEBUG      'd'    /* temp checkpoint or data           */
#define           TYPE_UNITTEST   't'    /* unit testing framework            */
/*---(context)--------------------------*/
#define           TYPE_MARK       'm'    /* mark, sync point, tag             */
#define           TYPE_INFO       'i'    /* norml data and checkpoints        */
#define           TYPE_STRUCT     's'    /* entering and exiting routines     */
/*---(call-back)------------------------*/
#define           TYPE_CALLBACK   'x'    /* asyncronous endpoints             */
/*---(validators)-----------------------*/
#define           LVL_VALID       "<->"
#define           TYPE_VALID      "ncgewudtmisx"
#define           LVL_UNKNOWN     '?'
#define           TYPE_UNKNOWN    '?'
/*---(done)-----------------------------*/


typedef struct tm   tTIME;

#define           RUN_QUIET      its.loud != 'y'

typedef    struct  cITS  tITS;
struct cITS {
   char        loud;  
   char        quiet;
   char        prog        [LEN_TITLE];     /* calling program name           */
   FILE       *logger;                      /* file to receive messages       */
   char        full        [LEN_RECD];      /* full message to be written     */
   char        core;                        /* log core heatherly libraries   */
   llong       wall_start;                  /* start wall msec time           */
   int         count;                       /* message count                  */
   int         indent;                      /* level of indent (0 - 9)        */
   char        prefix      [LEN_HUND];      /* actual indent text (of spaces) */
   char        msg         [LEN_PATH];      /* full message to log            */
   char        single      [LEN_PATH];      /* short form cum message         */
   int         nsyncs;                      /* count of sync calls            */
   char        filename    [LEN_PATH];
   char        version     [LEN_HUND];
   char        title       [LEN_FULL];      /* title for messages             */
   char        data        [LEN_FULL];      /* string for messages            */
   char        temp        [LEN_FULL];      /* string for short working area  */
};
extern  tITS  its;

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
llong       ylog__timestamp         (void);
char        ylog__prefix            (void);
void        ylog__main              (char a_change, char a_level, char *a_message);

char*       ylog_title              (const char *a_title);
char*       ylog_data               (const char *a_data);
char*       ylog_terse              (const char *a_data);

char        ylog__unit_quiet        (void);
char        ylog__unit_loud         (void);
char        ylog__unit_end          (void);
char*       ylog_base__unit         (char *a_question, int a_num);

#endif

/*============================[[ beg-of-code ]]===============================*/
#ifndef YLOG_pguard
#define YLOG_pguard loaded



/*===[[ BEG_HEADER ]]=========================================================*/

#define     P_FOCUS     "SA (system administration)"
#define     P_NICHE     "pm (process monitoring)"
#define     P_PURPOSE   "simple, automated, consistent process execution logging"

#define     P_NAMESAKE  "clio-chrysafenios (flowering)"
#define     P_HERITAGE  "greek muse of written and oral history, song, and poetry"
#define     P_IMAGERY   "golden young woman holding a scroll, seated by a chest of books"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-07"
#define     P_DEPENDS   "ySTR"

#define     P_VERMAJOR  "1.--, working and advancing"
#define     P_VERMINOR  "1.3-, continue to refine while useing"
#define     P_VERNUM    "1.3e"
#define     P_VERTXT    "added mute checking and change a couple function names to help unit test yURG"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

#define     P_GREEK     \
 "clio is one of the nine greek muses (mousai) who are the goddesses of art�" \
 "literature, and science.  the muses are the daughters of zeus and�" \
 "mnemosyne (the titan of memory).  as a group they inspire creation,�" \
 "enthusiasm, and the creative impulses.  clio, the proclaimer) is the muse�" \
 "of written and oral history, song, and poetry.  she is typically shown�" \
 "holding a scroll and near a chest of books or tablets.�"

#define     P_DEFINE    \
 "process execution logging is a method for process self-journalling in order�" \
 "to gain insight into status, internal settings, execution paths, function�" \
 "sequencing, and duration/timing.�"
#define     P_CURRENT   \
 "my code base is growing quickly and much of that code executes either�" \
 "continuously, frequently, or at critical moments -- big code base,�" \
 "audacious plans, and one programmer to rule it all ;)�"
#define     P_CONCERN   \
 "the art of logging and messaging seems to have died with the system�" \
 "operator and is now done using expensive commercial tools with incoherent�" \
 "streams of one dimensional, ad-hoc messages.�"
#define     P_ALTERNS   "syslog, systemd, printf, gdb"
#define     P_VALUE     \
 "process logging is a rapid way to diagnose process issues.  it is a huge�" \
 "time saver in build/testing, recreating prodution issues, and regaining�" \
 "logic/flow knowledge.  saves a lot of debugger time.�"
#define     P_USERBASE  \
 "never confuse tailored, technical, super-user systems and general, easy-�" \
 "to-use, zero effort required systems built to get end-users up and happy�" \
 "as quickly as possible.�"
#define     P_NEED      \
 "i need something configurable, built-in, and ready for immediate use.  it�" \
 "must include structure/flow logging as well as values, contents, and�" \
 "warning messages and be easy to search and filter.�"
#define     P_SUMMARY   \
 "yLOG is a simple, direct, consistent, and clean shared library to enable�" \
 "process execution logging and encourge monitoring, process flow�" \
 "understanding, and early issue detection in my custom programs.�"
#define     P_OBJECTIVE \
 "a) allow programs to be observed without significantly altering them�" \
 "b) provide a forensic trail for programs to aid reproduction of issues�" \
 "c) keep it simple so that it does not require huge learning curve�" \
 "d) cleanly incorporated so it can remain permenantly in source code�" \
 "e) maximize reuse so i don't have to recreate each time�" \
 "f) standardize so data can be scanned quickly and troubles found fast�" \
 "g) easy and automatic to remove so as to not hamper production�" \
 "h) allows programmers to see the true program execution  path�" \
 "i) cut significant time from tracing, debugging, and maintaining�" \
 "j) speed education of new maintainers and unit testers (watch flow)�" \
 "k) re-enforce a disciplined development culture and building-to-last�" \
 "l) avoid a product that will require me to switch every few years�"
#define     P_WARNINGS  \
 "a) logging eats up cpu, disk, and other resources�" \
 "b) is rarely reviewed (only because existing methods are complicated)�" \
 "c) can distract when nothing needs to be reviewed (configurable)�" \
 "d) is one more thing that can go wrong (always funny)�" \
 "e) must be very different for high volume apps�" \
 "f) has to be built ahead of time and therefore can slow projects�" \
 "g) since its shared, changes can effect all programs�" \
 "h) drives a single method of thinking (myopia requires self-review)�"

/*===[[ END_HEADER ]]=========================================================*/



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
#include  <signal.h>
#include  <dirent.h>

/*-> to support the 'uname' call to get machine and system names  */
#include  <sys/utsname.h>


#define           LOGDIR     "/var/log/yLOG/"
#define           HISDIR     "/var/log/yLOG.historical/"
#define           ROOTDIR    "/"
#define           USBDIR     "/mnt/usb1/"


/*===[[ STANDARDS ]]===============================================#*/
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
#define           LOG_FD          99
#define           RUN_QUIET       its.loud != 'y'



typedef struct tm        tTIME;
typedef struct stat      tSTAT;
typedef struct dirent    tDIRENT;






typedef    struct  cITS  tITS;
struct cITS {
   char        loud;  
   char        prog        [LEN_LABEL];     /* calling program name           */
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
   char        timestamp   [LEN_LABEL];     /* log file timestamp             */
   char        filename    [LEN_PATH];      /* log file name                  */
   char        path        [LEN_PATH];      /* path to log file               */
   char        version     [LEN_HUND];      /* ylog version string            */
   char        title       [LEN_FULL];      /* title for messages             */
   char        data        [LEN_FULL];      /* string for messages            */
   char        temp        [LEN_FULL];      /* string for short working area  */
};
extern  tITS  its;



extern char unit_answer [LEN_RECD];

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
llong       ylog__timestamp         (void);
char        ylog__prefix            (void);
void        ylog__main              (char a_change, char a_level, char *a_message);

char        ylogs__progname         (cchar *a_prog);
char*       ylogs__logname          (cchar *a_prog, cchar a_loc);

char        ylog_vol_init           (void);
char        ylog_check              (const char *a_func);
char        ylog_check_enter        (const char *a_func);
char        ylog_check_exit         (const char *a_func);

char*       ylog_title              (const char *a_title);
char*       ylog_data               (const char *a_data);
char*       ylog_terse              (const char *a_data);

char        ylog__unit_quiet        (void);
char        ylog__unit_loud         (void);
char        ylog__unit_end          (void);
char*       ylog_base__unit         (char *a_question, int a_num);

void        ylog_stage_init         (void);


#endif

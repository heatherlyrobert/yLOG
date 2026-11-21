/*============================[[ beg-of-code ]]===============================*/
#ifndef    YLOG_priv_guard
#define    YLOG_priv_guard   loaded



/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2008 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ GNU GENERAL PUBLIC LICENSE (GPL) ]]===================================*/



/*===[[ ONE_LINERS ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "SA (system administration)"
#define     P_NICHE     "pm (process monitoring)"
#define     P_SUBJECT   "process execution logging"
#define     P_PURPOSE   "simple, automated, consistent process execution logging"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "clio-chrysafenios (flowering)"
#define     P_PRONOUNCE ""
#define     P_HERITAGE  "greek muse of written and oral history, song, and poetry"
#define     P_BRIEFLY   ""
#define     P_IMAGERY   "golden young woman holding a scroll, by a chest of books"
#define     P_REASON    "greek muse of beautiful, poetic, historical writings"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yLOG.exec_logger"
#define     P_BASENAME  "yLOG"
#define     P_FULLPATH  "/usr/local/lib64/libyLOG.so"
#define     P_SUFFIX    "ulog"
#define     P_CONTENT   "process logging journal"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2008-07"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, stable in production"
#define     P_VERMINOR  "2.2-, catch-up with prod fixes"
#define     P_VERNUM    "2.2c"
#define     P_VERTXT    "added yLOG_llong and yLOG_ullong (plus shorts) to test ySTR_format.c"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
#define     P_DEPANSI   ""
#define     P_DEPPOSIX  ""
#define     P_DEPCORE   ""
#define     P_DEPVIKEY  ""
#define     P_DEPGRAPH  ""
#define     P_DEPOTHER  ""
#define     P_DEPSOLO   "ySTR_solo"
#define     P_DEPALIEN  ""
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ END ONE_LINERS ]]=====================================================*/



/*===[[ REASONING ]]==========================================================*/

#define     P_GREEK     \
 "clio is one of the nine greek muses (mousai) who are the goddesses of art¦" \
 "literature, and science.  the muses are the daughters of zeus and¦" \
 "mnemosyne (the titan of memory).  as a group they inspire creation,¦" \
 "enthusiasm, and the creative impulses.  clio, the proclaimer) is the muse¦" \
 "of written and oral history, song, and poetry.  she is typically shown¦" \
 "holding a scroll and near a chest of books or tablets.¦"

#define     P_DEFINE    \
 "process execution logging is a method for process self-journalling in order¦" \
 "to gain insight into status, internal settings, execution paths, function¦" \
 "sequencing, and duration/timing.¦"
#define     P_CURRENT   \
 "my code base is growing quickly and much of that code executes either¦" \
 "continuously, frequently, or at critical moments -- big code base,¦" \
 "audacious plans, and one programmer to rule it all ;)¦"
#define     P_CONCERN   \
 "the art of logging and messaging seems to have died with the system¦" \
 "operator and is now done using expensive commercial tools with incoherent¦" \
 "streams of one dimensional, ad-hoc messages.¦"
#define     P_ALTERNS   "syslog, systemd, printf, gdb"
#define     P_VALUE     \
 "process logging is a rapid way to diagnose process issues.  it is a huge¦" \
 "time saver in build/testing, recreating prodution issues, and regaining¦" \
 "logic/flow knowledge.  saves a lot of debugger time.¦"
#define     P_USERBASE  \
 "never confuse tailored, technical, super-user systems and general, easy-¦" \
 "to-use, zero effort required systems built to get end-users up and happy¦" \
 "as quickly as possible.¦"
#define     P_NEED      \
 "i need something configurable, built-in, and ready for immediate use.  it¦" \
 "must include structure/flow logging as well as values, contents, and¦" \
 "warning messages and be easy to search and filter.¦"
#define     P_SUMMARY   \
 "yLOG is a simple, direct, consistent, and clean shared library to enable¦" \
 "process execution logging and encourge monitoring, process flow¦" \
 "understanding, and early issue detection in my custom programs.¦"
#define     P_OBJECTIVE \
 "a) allow programs to be observed without significantly altering them¦" \
 "b) provide a forensic trail for programs to aid reproduction of issues¦" \
 "c) keep it simple so that it does not require huge learning curve¦" \
 "d) cleanly incorporated so it can remain permenantly in source code¦" \
 "e) maximize reuse so i don't have to recreate each time¦" \
 "f) standardize so data can be scanned quickly and troubles found fast¦" \
 "g) easy and automatic to remove so as to not hamper production¦" \
 "h) allows programmers to see the true program execution  path¦" \
 "i) cut significant time from tracing, debugging, and maintaining¦" \
 "j) speed education of new maintainers and unit testers (watch flow)¦" \
 "k) re-enforce a disciplined development culture and building-to-last¦" \
 "l) avoid a product that will require me to switch every few years¦"
#define     P_WARNINGS  \
 "a) logging eats up cpu, disk, and other resources¦" \
 "b) is rarely reviewed (only because existing methods are complicated)¦" \
 "c) can distract when nothing needs to be reviewed (configurable)¦" \
 "d) is one more thing that can go wrong (always funny)¦" \
 "e) must be very different for high volume apps¦" \
 "f) has to be built ahead of time and therefore can slow projects¦" \
 "g) since its shared, changes can effect all programs¦" \
 "h) drives a single method of thinking (myopia requires self-review)¦"

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
#include  <signal.h>
#include  <dirent.h>
/*-> to support the 'uname' call to get machine and system names  */
#include  <sys/utsname.h>



#define           LOGDIR     "/var/log/yLOG/"
#define           HISDIR     "/var/log/yLOG.historical/"
#define           ROOTDIR    "/"
#define           USBDIR     "/mnt/usb1/"
#define           TMPDIR     "/tmp/"


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
#define           IF_QUIET        if (myLOG.m_loud   != 'y' )
#define           IF_LOGGER       if (myLOG.m_logger != NULL)
#define           IF_NOSHOW       if (myLOG.m_logger == NULL || myLOG.m_loud   != 'y')
#define           IF_NOTUNIT      if (myLOG.m_use    != 'u' )
#define           DEBUG_YLOGS     if (myLOG.m_use    == 'd' )
#define           DEBUG_PROG      if (myLOG.m_use    == 'd' )
#define           DEBUG_TOPS      if (myLOG.m_use    == 'd' )



typedef unsigned char    uchar;
typedef struct tm        tTIME;
typedef struct stat      tSTAT;
typedef struct dirent    tDIRENT;

typedef struct timeval   tTIMEVAL;





typedef    struct  cITS  tITS;
struct cITS {
   char        m_loud;  
   char        m_use;                         /* (-) normal, (d)ebug, or (u)nit      */
   char        m_prog        [LEN_TITLE];     /* calling program name           */
   FILE*       m_logger;                      /* file to receive messages       */
   char        m_full        [LEN_RECD];      /* full message to be written     */
   char        m_core;                        /* log core heatherly libraries   */
   llong       m_start;                       /* start wall msec time           */
   int         m_count;                       /* message count                  */
   int         m_indent;                      /* level of indent (0 - 9)        */
   char        m_prefix      [LEN_HUND];      /* actual indent text (of spaces) */
   char        m_msg         [LEN_RECD];      /* full message to log            */
   char        m_single      [LEN_PATH];      /* short form cum message         */
   int         m_nsyncs;                      /* count of sync calls            */
   char        m_timestamp   [LEN_TITLE];     /* log file timestamp             */
   char        m_filename    [LEN_PATH];      /* log file name                  */
   char        m_path        [LEN_PATH];      /* path to log file               */
   char        m_version     [LEN_HUND];      /* ylog version string            */
   char        m_title       [LEN_FULL];      /* title for messages             */
   char        m_data        [LEN_FULL];      /* string for messages            */
   char        m_temp        [LEN_FULL];      /* string for short working area  */
   uchar       m_urg;                         /* called by which urgent         */
   uchar       m_stage;                       /* called in which stage          */
   int         m_lines                        /* count of lines in log          */
};
extern  tITS  myLOG;



extern char unit_answer [LEN_RECD];

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
llong       ylog__timestamp         (void);
char        ylog__prefix            (int a_indent, int *r_indent, char r_prefix [LEN_HUND]);
char        ylog__main              (char a_change, char a_level, char a_message [LEN_RECD]);

char        ylogs_init              (void);
char        ylogs__progname         (char *a_prog);
char*       ylogs__logname          (char *a_prog, char a_loc);


char*       ylog_title              (char *a_title);
char*       ylog_data               (char *a_data);
char*       ylog_terse              (char *a_data);


char        ylog_stage_init         (void);


char        ylog_vol_init           (void);
char        ylog__find              (char *a_func);
char        ylog_check              (char *a_func);
char        ylog_check_enter        (char *a_func);
char        ylog_check_exit         (char *a_func);
char*       ylog_vol__unit          (char *a_question, int a_num);



#endif

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

#define     P_VERNUM    "1.2p"
#define     P_VERTXT    "moved logger to fd 99 as a new standard"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "i know there are many better options, but i *own* this one"

#define     P_GREEK     \
 "clio is one of the nine greek muses (mousai) who are the goddesses of art�" \
 "literature, and science.  the muses are the daughters of zeus and�" \
 "mnemosyne (the titan of memory).  as a group they inspire creation,�" \
 "enthusiasm, and the creative impulses.  clio, the proclaimer) is the muse�" \
 "of written and oral history, song, and poetry.  she is typically shown�" \
 "holding a scroll and near a chest of books or tablets.�"

/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_SUMMARY   \
 "yLOG is a simple, direct, consistent, and clean shared library to enable�" \
 "process execution logging and encourge monitoring, process flow�" \
 "understanding, and early issue detection in my custom programs.�
#define     P_CURRENT   \
 "my code base is growing quickly and much of that code executes either�" \
 "continuously, frequently, or at critical moments -- big code base,�" \
 "audacious plans, and one programmer to rule it all ;)�"
#define     P_ALTERNS   "syslog,systemd,printf,gdb"
#define     P_CONCERN   \
 "the art of logging and messaging seems to have died with the system�" \
 "operator and is now done using expensive commercial tools with incoherent�" \
 "streams of one dimensional messages.�"
#define     P_USERBASE  \
 "never confuse tailored, technical, super-user systems and general, easy-�" \
 "to-use, zero effort required systems built to get end-users up and happy�" \
 "as quickly as possible.�"
#define     P_COURSE    \
 "i need something configurable, built-in, and ready for immediate use.  it�" \
 "must include structure/flow logging as well as values, contents, and�" \
 "warning messages and be easy to search and filter.�"
#define     P_ASSUME    \
 "-- create a standard, indented flow that is easy to follow�" \
 "-- partners with yURG to allow up front and run-time configuration�" \
 "-- easy to build into any c program and improve overtime�" \
 "-- make can filter out to produce both debug and production versions�" \
 "-- all messages are categorized, indented, and include timestamps�" \
 "-- will log onto a ram-drive for speed (/var/yLOG)�"



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

/*-> to support the 'uname' call to get machine and system names  */
#include  <sys/utsname.h>

#define     LEN_PREFIX       100

#define           LOGDIR     "/var/log/yLOG/"
#define           HISDIR     "/var/log/yLOG.historical/"
#define           ROOTDIR    "/"
#define           USBDIR     "/mnt/usb1/"



#endif

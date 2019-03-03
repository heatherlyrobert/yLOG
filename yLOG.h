/*============================[[    beg-code    ]]============================*/
/*===[[ PURPOSE ]]============================================================*/

/*   yLOG is a simple, direct, and lucid strategy for logging program activities
 *   in order to encourage program monitoring, execution profiling, and issue
 *   detection in both a testing and production environment.
 *
 *   the tragedy is that the art of logging and messaging seems to have died
 *   with the passing of the "operator" and now is done on a prorietary basis
 *   using expensive commercial tools.  not good.  or, as an incoherent stream
 *   of one-dimensional messages.  bloody worse.
 *
 *   so, yLOG provides a set of shared functions for logging program activities
 *   which report to a structured, searchable message file that supports tracing
 *   monitoring, warning, debugging, and maintenance.  it is designed to take a
 *   repetative, tedious, haphazard, neglected, and error-prone task and make it
 *   easy, systematic, shared, consistent, and maintainable.
 *
 *   yLOG focuses on improving the self-diagnostic capabilities by...
 *     - logging program start and conclusion
 *     - entry and exit to all major functions
 *     - indenting messages to make flow clear
 *     - categorizing messages to allow quick filtering and searching
 *     - showing critical informational and context messages
 *     - provide a standard for warning and errors
 *     - giving a true sense of durations and elapsed time
 *
 *   while this can not replace a program's own awareness, it can supplement it
 *   in a way that promotes fast, accurate production monitoring
 *
 *   many existing libraries and utilities have been built by better programmers
 *   which are likely superior in speed, size, capability, and reliability; BUT,
 *   i would not have learned nearly as much using them, so i follow the adage...
 *
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 *
 */
/*===[[ PROS AND CONS ]]=======================================================*

 *   ADVANTAGES, to shared logging...
 *     - allows programmers to understand the "actual" program flow
 *     - makes early and unit testing much easier
 *     - makes formal testing (and educating testers) much more productive
 *     - speeds production debugging by orders of magnitude
 *     - allows easier transition of program maintenance responsibilities
 *     - re-enforces a disciplined development culture
 *     - makes operators smarter about what's going on
 *     - allows normal debugging and mtce to be less invasive
 *     - allows a programmer to "relearn" a program quickly
 *
 *   DISADVANTAGES...
 *     - takes up cpu cycles
 *     - takes up disk space
 *     - is rarely reviewed
 *     - can distract when nothing needs to be reviewed
 *     - is one more thing that can go wrong (always funny)
 *     - must be very different for high volume apps
 *     - has to be built ahead of time and therefore can slow projects
 *     - since its shared, changes can effect all programs
 *     - drives a single method of thinking
 *
 */

/*===[[ DECISION -- TO LOG OR NOT TO LOG ]]===================================*

 *   SITUATION (s)
 *      as a programmer, i develop a great deal of custom code that executes
 *      either continuously, frequently, or at least at critical times.  this
 *      code is both for unique purposes as well as to replace existing tools to
 *      enhance and validate my skills.  bottom line, big code base, bigger
 *      plans, and one programmer to keep it all moving.
 *
 *   COMPLICATION (c)
 *      there are six areas where i feel a certain unacceptable blindness. each
 *      of these areas has tools and techniques that can help, but can be slow,
 *      overkill, or modify the programs and therefore introduce more issues...
 *      -- intermediate debugging, between one-off printf and weeds-level gdb
 *      -- program flow validation, to verify execution path and sequencing
 *      -- execution monitoring, to understand real-life program input/responses
 *      -- unknown unknowns, that simply aren't draw into normal testing in time
 *      -- lingering paranoia, some programs need to be ready to debug and fix
 *      -- lost touch with details, ability to reaquiant myself quickly
 *
 *   QUESTION (q)
 *      are there ways i can effectively plug these gaps without huge effort?
 *
 *   ANSWER (a)
 *      clean, automated, consistent logging that can be automagically removed
 *
 *   BENEFITS (b)
 *      -- allows programmers to understand the "actual" program flow
 *      -- makes development debugging and unit testing much easier
 *      -- makes formal testing (and educating testers) much more productive
 *      -- speeds production debugging by orders of magnitude
 *      -- allows easier transition of program maintenance responsibilities
 *      -- re-enforces a disciplined development culture
 *      -- makes operators smarter about what's going on
 *      -- allows normal debugging and mtce to be less invasive
 *      -- allows a programmer to "relearn" a program quickly
 *
 *   DISADVANTAGES (d)
 *      -- takes up cpu cycles
 *      -- takes up disk space
 *      -- is rarely reviewed
 *      -- can distract when nothing needs to be reviewed
 *      -- is one more thing that can go wrong (always funny)
 *      -- must be very different for high volume apps
 *      -- has to be built ahead of time and therefore can slow projects
 *      -- since its shared, changes can effect all programs
 *      -- drives a single method of thinking
 * 
 *   OBJECTIVES (o)
 *      a) allow programs to be observed without significantly altering them
 *      b) provide a forensic trail for programs to aid reproduction of issues
 *      c) keep it simple so that it does not require huge learning curve
 *      d) maximize reuse so i don't have to recreate each time
 *      e) standardize so data can be scanned quickly and troubles found fast
 *      f) easy and automatic to remove so as to not hamper production
 *      g) easy to see flow between functions
 *      h) keep it small and easy
 * 
 *   ALTERNATIVES (a)
 *      -- ---desc-----------------------  a b c d e f g h  ---summary----------
 *      1) do nothing                      - - y - - - - -  retarded
 *      2) use printf/other outputs        y - y - - - - -  dangerous to remove
 *      3) write to system logs            y y y y - - - -  garbage to syslogs
 *      4) use a serious debugger          y - - y - y - -  way too detailed
 *      5) use a third-party logger        y y y y y y y -  nice, no learning
 *      6) write a custom library          y y y y y y y y  of course
 * 
 *   JUDGEMENT (j)
 *      build a small, reusable library to allow standard logging of programs
 *
 */
/*===[[ BEST PRACTICES ]]==========================================#

 *   GOOD...
 *      - build calls so they can be removed by simple text processor or macro
 *      - don't store data that can be derived
 *      - allow applications to tune logging parameters
 *      - use "processing x of y recs" strategy on high volume areas
 *      - do a good job of trapping signals and errors
 *      - store in "gzipped" files as its fast and smaller
 *      - make a vim-syntax that makes log reading easier
 * 
 *   BAD...
 *      - build defensive measures each time to specific circumstances
 *      - try to cover the defensive issues through a checklist or templates
 */
/*===[[ STANDARDS ]]===============================================#

 *   MESSAGE LEVELS (based on unix/linux)
 *      - used alpha rather than pure numeric to make them more real
 *      === mortal and dangerous ======
 *       n) nuclear/wicked   : non-graceful, system-wide consequences
 *       c) clumsy/critical  : non-recoverable, non-graceful, local consequences
 *       g) graceful/mortal  : non-recoverable, but graceful, no real consequence
 *      === debugging =================
 *       e) error/serious    : more difficult, but recoverable
 *       w) warn/notice      : easily recoverable error
 *       u) update/versions  : new data or program versions
 *      === review ====================
 *       d) debug/temp       : temp checkpoints and data
 *       t) test enablement  : unit testing framework
 *      === context ===================
 *       m) mark             : regular marker to help parsing/rolling logs
 *       i) info/context     : checkpoints and critical data
 *       s) structure/flow   : entering and exiting routines
 *      === callback ==================
 *       x) callback         : asyncronous endpoints
 * 
 *   STRUCTURE LEVELS
 *     > indent after
 *     - stay at level
 *     < exdent before
 * 
 *   TRACKING DATA
 *     KEY FIELDS
 *       host              : for multihost applications
 *       process id        : for tie to system logs
 *       timestamp         : human readable
 *       msecs counter     : to accurately track, and to do math
 *       function          : what's executing
 *       level of message  : 0-7
 *       indentation level : fantastic to find logic issues
 *       message           : specific notice
 *     REJECTED FIELDS
 *       source file       : knowable from function name
 *       line number       : structure/info messages make clear
 */
/*===[[ END HDOC ]]===========================================================*/


#ifndef   YLOG_HGUARD
#define   YLOG_HGUARD       loaded



#define   LOG_FD     99


/*===[[ CONSTANTS ]]======================================*/
#define   yLOG_NONE         '-'
#define   yLOG_SYSTEM       's'
#define   yLOG_HISTORICAL   'h'
#define   yLOG_PERSONAL     'p'
#define   yLOG_STDOUT       'o'
#define   yLOG_ROOT         'r'
#define   yLOG_USB          'u'
#define   yLOG_NULL         '0'

#define   yLOG_NOISE        'N'
#define   yLOG_QUIET        'Q'



/*===[[ TYPES ]]==========================================*/
typedef   const char   cchar;
typedef   long long    llong;
typedef   const int    cint;



/*===[[ MACROS ]]=========================================*/
#define   yLOG_hintx(FMT,...)   ylog_errors ("HINT"   , 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_warnx(FMT,...)   ylog_errors ("WARNING", 'w', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_errorx(FMT,...)  ylog_errors ("ERROR"  , 'e', __FILE__, __LINE__, FMT, __VA_ARGS__)
#define   yLOG_fatalx(FMT,...)  ylog_errors ("FATAL"  , 'g', __FILE__, __LINE__, FMT, __VA_ARGS__)



/*===[[ PUBLIC FUNCTIONS ]]===============================*/
/*---(program)--------------*/
char        yLOG_begin         (const char *a_program, const char a_location, const char a_quiet);
void        yLOG_end           (void);
/*---(support)--------------*/
char       *yLOG_version       (void);
int         yLOG_lognum        (void);
long long   yLOG_time          (void);
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

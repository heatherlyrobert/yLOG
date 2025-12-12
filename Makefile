#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = yLOG
# additional standard and outside libraries
LIB_STD    = 
# all heatherly libraries used, debug versions whenever available
LIB_MINE   =
# directory for production code, no trailing slash
INST_DIR   = 



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 
# files to be included in editing session (maybe conf, data, ...)
EDIT_TOO   = ulog.sh



#===(post-processing)======================================#
# create a rule for...
#install_prep       :
#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/zeno_make



#===(post-processing)======================================#
# create a rule for...
install_post       :
	# add ulog helper to install directory
	@cp -f ulog.sh        /usr/local/bin/ulog
	@chmod +x             /usr/local/bin/ulog
	@sha1sum              /usr/local/bin/ulog
	# add ulog links to alter execution
	ln --force --physical /usr/local/bin/ulog   /usr/local/bin/ulog_debug
	ln --force --symbolic /usr/local/man/man6/yLOG_ulog.6.bz2   /usr/local/man/man6/ulog.6
#remove_post        :



#================================[[ end-code ]]================================#

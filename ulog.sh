##===[[ BEG-OF-CODE ]]========================================================##



##---(( verify version of ulog))----------------------------------------------##
declare x_debug="-"
if [[ "$0" == "/usr/local/bin/ulog_debug" ]]; then
   declare x_debug="y"
fi



##---(( preparation ))--------------------------------------------------------##
declare  x_file=""
declare x_handled="-"
declare x_count="$(ls -1 /var/log/yLOG/*.ulog  2>/dev/null | wc -l)"

if [[ "$x_debug" == "y" ]]; then
   echo "who  $0"
   echo "dir  $1"
   echo "pos  $2"
   echo "cnt  $x_count"
fi




##---(( defense against no files ))-------------------------------------------##
if [[ $x_count == "0" ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "no ulog files in /var/log/yLOG/, nothing to do"
   fi
   exit
fi



##---(( modify arguments ))---------------------------------------------------##
declare x_target="$2"
if [[ $x_target == "" ]]; then
   declare x_target="1"
fi
if [[ $x_debug == "y" ]]; then
   echo "trg  $x_target"
fi
declare  -i c=$(($x_count + 0))
declare  -i t=$(($x_target + 0))
if [[ $t -lt 0 ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "target can not be negative"
   fi
   exit
fi
if [[ $t -gt $c ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "target can not be greater than count"
   fi
   exit
fi



##---(( action >> clear/purge files ))----------------------------------------##
if [[ $1 == "x" ]]; then
   if [[ "$x_debug" == "y" ]]; then
      echo "act  remove existing ulog files"
   fi
   rm -f /var/log/yLOG/*.ulog
   if [[ "$x_debug" == "y" ]]; then
      declare x_count="$(ls -1 /var/log/yLOG/*.ulog  2>/dev/null | wc -l)"
      echo "cnt  $x_count"
   fi
   declare x_handled="y"
   exit
fi



##---(( action >> list files ))-----------------------------------------------##
if [[ $1 == "l" ]]; then
   if [[ "$x_debug" == "y" ]]; then
      echo "act  list all ulog files"
   fi
   ls -1 /var/log/yLOG/*.ulog | nl -w2 -s"   "
   declare x_handled="y"
fi



##---(( action >> edit from oldest ))-----------------------------------------##
if [[ $1 == "[" ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "act  edit/view ulog relative to oldest"
   fi
   if [[ $2 == "l" ]]; then
      ls -1 /var/log/yLOG/*.ulog | nl -w2 -s"   "
   else
      declare x_file="$(ls -1 /var/log/yLOG/*.ulog | head -n $x_target | tail -n 1)"
   fi
   declare x_handled="y"
fi



##---(( action >> edit from newest ))-----------------------------------------##
if [[ $1 == "]" ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "act  edit/view ulog relative to newest"
   fi
   if [[ $2 == "l" ]]; then
      ls -1 -r /var/log/yLOG/*.ulog | nl -w2 -s"   "
   else
      declare x_file="$(ls -1 /var/log/yLOG/*.ulog | tail -n $x_target | head -n 1)"
   fi
   declare x_handled="y"
fi



##---(( action >> edit latest ))----------------------------------------------##
if [[ $x_debug == "y" ]]; then
   echo "han  $x_handled"
fi
if [[ "$x_handled" != "y" ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "act  edit/view latest ulog"
   fi
   declare x_file="$(ls -1 /var/log/yLOG/*.ulog | tail -n 1)"
   declare x_handled="y"
fi



##---(( action >> edit latest ))----------------------------------------------##
if [[ $x_file != "" ]]; then
   if [[ $x_debug == "y" ]]; then
      echo "nam  $x_file"
   else
      vi $x_file
   fi
fi



##===[[ END-OF-CODE ]]========================================================##

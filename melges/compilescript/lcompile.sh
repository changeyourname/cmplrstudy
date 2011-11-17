#!/bin/bash
if [ $# -lt 3 ]
then
  echo "Используйте: $0 [source] [your-flag] [destination]"
  exit 1
fi
mkdir $3/withopt
llvmc $1 -$2 -opt -o $3/withopt
mkdir $3/withoutopt
llvmc $1 -o $3/withoutopt

exit 0


#! /bin/sh
line=1
# read from 1 line to 5 line in a.txt
sed -n "`echo $line`, 5p" a.txt

#! /bin/sh
line=3
line1=6
diff=`expr $line1 \- $line`
echo $diff
# read from 1 line to 5 line in a.txt
sed -n "`echo $line`, 5p" a.txt >> f.txt
sed -n "`echo $diff`, 5p" a.txt >> diff.txt

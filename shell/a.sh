#! /bin/sh
line=3
line1=6
linea=1

#if linea variblea is defined, enter
if [ -n "$linea" ]; then
   echo "linea is defined"
   diff=`expr $line1 \- $linea`
else
   diff=1
   echo "linea is not defined" 
fi

echo "diff is:" $diff
# read from 1 line to 5 line in a.txt
sed -n "`echo $line`, 5p" a.txt >> f.txt
sed -n "`echo $diff`, `echo $line1`p" a.txt
tar hcjvf 1.tar.bz2 a.txt f.txt c.txt

#!/bin/sh

currentDir=`dirname $0`
if [ ! -d $currentDir ]
then
	currentDir=`which $0`
	currentDir=`dirname $currentDir`
fi
classpath=$currentDir
cp=$classpath/LamportClocks.jar

java -cp "$cp" org.bits.distributed.assignment.LogicalClkMain 5 1

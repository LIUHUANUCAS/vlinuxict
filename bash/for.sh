#########################################################################
# File Name: for.sh
# Author: LIUHUAN
# mail: liu2012huan@126.com
# Created Time: 2015年07月02日 星期四 16时27分19秒
#########################################################################
#!/bin/bash
echo "enter password1"
read pass
while [ "$pass" != "liuhuan" ]
do 
	echo "sorry ..."
	read pass
done

echo "you are pass 1..."
echo "enter password2"
read pass
until [  "$pass" == "zhangsan" ]
do
	echo "you are not pass 22..."
	read pass
done

echo "you are pass all test..."

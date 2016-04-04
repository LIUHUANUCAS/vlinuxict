#########################################################################
# File Name: case.sh
# Author: LIUHUAN
# mail: liu2012huan@126.com
# Created Time: 2015年07月02日 星期四 16时55分37秒
#########################################################################
#!/bin/bash
read i
while [ "$i" != "c" ]
do
	case "$i" in 
		1 ) echo "1..";;
		2 ) echo "2..";;
		3 ) echo "3..";;
		4 ) echo "4..";;
		5 ) echo "5..";;
		* ) echo "sorry ...";;
	esca
read i


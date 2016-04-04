#########################################################################
# File Name: var.sh
# Author: LIUHUAN
# mail: liu2012huan@126.com
# Created Time: 2015年07月02日 星期四 16时06分33秒
#########################################################################
#!/bin/bash

sa="Hello world"
echo $sa
echo "filename is $0"
echo "argv[1] = $1"
echo "argv[2] = $2"
echo " '$*' ->  $*"
echo "HOME is $HOME"
read sa
echo "your input is $sa"


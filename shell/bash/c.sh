#!/bin/bash
echo "0->$0"
echo "1->$1"
echo "2->$2"
echo $@
echo $?
echo $$
echo $$
for e in "$*"
do
	echo "$e"
done
for e in "$@"
do
	echo "$e"
done
read num
case $num in
	1) echo "1 "
		;;
	2) echo "->2->" ;;
	3) echo "->>>3" ;;
	4) echo "->4" ;;
	5) echo "5->" ;;
	*) echo "default ..."
		;;
esac
val=0
function func(){
	i=100
	let "i++"
	val=$i
	val="zhangsan"
}
func
echo $val
i=0
while [ "$i" -lt "$#" ]
do
	echo $"$i"
	let "i++"
done


#!/bin/bash

echo "Enter First Number"
read num1

echo "Enter Second Number"
read num2

echo "Enter Operation:"
echo "1. Add"
echo "2. Subtract"

read num3

case $num3 in
	1) result=$(echo "$num1+$num2"|bc)
		echo "Sum is $result"
		;;
	2)result=$(echo "$num1-$num2"|bc)
		echo "Diff is $result"
		;;
	*)echo "Invalid Operation"
		exit 1
		;;
esac


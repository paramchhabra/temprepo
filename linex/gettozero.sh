#!/bin/bash
echo "Enter the number to get to 0"
read num

if [ "$num" -lt 0 ]; then
	while [ "$num" -ne 0 ]; do
		echo "Increasing Number $num"
		num=$((num + 1))
	done

elif [ "$num" -gt 0 ]; then
	while [ "$num" -ne 0 ]; do
		echo "Decreasing Number $num"
		num=$(( num - 1))
	done
else
	echo "Number is 0"
fi

echo "Number is 0"


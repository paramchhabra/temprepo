#!/bin/bash

sum=0
for((i=0;i<=5;i++));do
	sum=$((sum+i))
done
echo "$sum"

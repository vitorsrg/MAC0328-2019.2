#!/usr/bin/env bash

rm -f 10258862.bin

set -e

make 10258862

for (( v=20; v<=500; v++ ))
do
   for (( a=0; a<v*v; a+=2*v ))
   do
       ./10258862.bin $v $a 0
   done
done

#!/usr/bin/env bash

rm -f 862.bin

set -e

make 862

for (( v=0; v<=300; v++ ))
do
   for (( a=0; a<v*(v-1)/2; a+=2*v ))
   do
       ./862.bin $v $a 0
   done
done

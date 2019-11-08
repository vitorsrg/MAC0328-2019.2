#!/usr/bin/env bash

wget    --directory-prefix=./bib/                               \
        --recursive                                             \
        --no-parent                                             \
        --accept c,h                                            \
        --no-directories                                        \
        https://www.ime.usp.br/~pf/mac0328-2019/SANDBOX/bib/ 

rm -f 862.bin

set -e

make 862


waitforjobs() {
    export running=$(ps -af | grep $$ | wc -l)
    if [[ $running -ge $1 ]]; then 
        wait -n
    fi
}

for (( v=0; v<=500; v+=2 )); do
    for (( a=0; a<v*(v-1)/2; a+=10*v )); do
        ./862.bin $v $a 0 &
        waitforjobs $(($(nproc --all) - 4))
    done
done

wait

# bash test.sh

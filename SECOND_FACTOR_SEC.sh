#!/bin/bash

trap ctrl_c INT
trap '' TSTP   # ASSIM QUE SE FAZ COM O CTRL_Z

function ctrl_c(){
    echo "FOI MAL... BOA TENTATIVA."
}

clear

function fsociety(){
echo -e '\xa\xa\xa\xa\xa'
echo -n '                     digite a senha:\n>>> '
read k
k=$(echo $k |sha256sum |cut -d " " -f1)
ha='0e80bb47f86d0b6841a319d8598eeb79d1ac40388f854be0a76443a99fa7f1ec'  # Relaxa, amigo. Esta em HASH ksks.

if [ "$k" == "$ha" ]; then 
  echo OK
else clear
echo "NAO NAO NAO..."
fsociety
fi
}

fsociety

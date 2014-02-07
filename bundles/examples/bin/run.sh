#!/bin/bash

if [ -z "$1" ] ; then
    echo "usage: $0 binaryName"
    exit 0
fi

LD_LIBRARY_PATH=`cd ../../../kernel/lib && pwd`:`cd ../../unittest/lib && pwd` ./$1

#!/bin/bash

perl <(curl -s https://raw.githubusercontent.com/curl/curl/master/scripts/mk-ca-bundle.pl)

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)

if test -f "ca-bundle.crt"; then
    echo "ca-bundle.crt exists."

    diff=$(diff -rpuN -I '^##' ca-bundle.crt $SCRIPT_DIR/../data/ca-bundle.crt)
    if [ -n "${diff}" ]; then
        echo "ca-bundle.crt is changed"
        cp ca-bundle.crt $SCRIPT_DIR/../data/ca-bundle.crt
    else
        echo "ca-bundle.crt no change"
    fi
else
    echo "Download fail"
    exit -1
fi
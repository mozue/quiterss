#!/bin/bash

URL="https://curl.se/ca/cacert.pem"

tempfile=$(mktemp)

code=$(curl -s $URL --write-out '%{http_code}' -o $tempfile)

if [[ $code != 200  ]] ; then
    echo "$URL SAID $code"
    rm -f $tempfile
    exit -1
else
    echo "Download $URL is successful"
    mv $tempfile "./data/ca-bundle.crt"
fi
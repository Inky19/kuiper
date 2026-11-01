#!/bin/bash

SCRIPTPATH=$(dirname $0)
echo $SCRIPTPATH
if [ ! -d "$SCRIPTPATH/build" ]; then
    mkdir $SCRIPTPATH/build
fi
cd $SCRIPTPATH/build
cmake ..
make
mv Kuiper ../kuiper

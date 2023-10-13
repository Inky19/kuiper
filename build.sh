#!/bin/bash

SCRIPTPATH=$(dirname $0)
echo $SCRIPTPATH
cd $SCRIPTPATH/build
cmake ..
make
mv Kuiper ../kuiper

#!/bin/sh
LEARNENV=/home/stw4198/Documents/learn
PATH=$LEARNENV:$PATH
export LEARNENV PATH
function learn { $LEARNENV/learn $*; }

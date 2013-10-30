#!/bin/bash

echo "Starting $OSTYPE client."

if [[ "$OSTYPE" == "linux-gnu" ]]
then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/TAEvalCommons/
elif [[ "$OSTYPE" == *darwin* ]]
then
	export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PWD/TAEvalCommons/
fi

TAEval-Server/TAEval-Server
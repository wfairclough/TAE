#!/bin/bash

echo "Starting $OSTYPE client."

if [[ "$OSTYPE" == "linux-gnu" ]]
then
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/TAEvalCommons/
	TAEval-Client/TAEval-Client
elif [[ "$OSTYPE" == *darwin* ]]
then
	export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PWD/TAEvalCommons/
	TAEval-Client/TAEval-Client.app/Contents/MacOS/TAEval-Client
fi

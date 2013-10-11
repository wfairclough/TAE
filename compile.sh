#!/bin/bash




cd TAEvalCommons
qmake TAEvalCommons.pro
make clean
make
cd ..

cd TAEval-Server
qmake TAEval-Server.pro
make clean
make
cd ..

cd TAEval-Client
qmake TAEval-Client.pro
make clean
make
cd ..


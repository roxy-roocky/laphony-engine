#!/bin/bash

rm -r ./LaphonyEngineLib

mkdir ./LaphonyEngineLib
mkdir ./LaphonyEngineLib/include
mkdir ./LaphonyEngineLib/lib
mkdir ./LaphonyEngineLib/bin

cp ./dist/Lib_Linux/GNU-Linux/* ./LaphonyEngineLib/lib/
cp ./dist/Lib_Linux/GNU-Linux/* ./LaphonyEngineLib/bin/

cp ./dist/Lib_Win64/mingw-64-Linux/* ./LaphonyEngineLib/bin/
cp ./dist/Lib_Win64/mingw-64-Linux/* ./LaphonyEngineLib/lib/

find . -not -path "./Test*" -not -path "./LaphonyEngineLib*" -name '*.h' -exec cp --parents \{\} ./LaphonyEngineLib/include \;
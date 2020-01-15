#!/bin/bash

rm -r ./LaphonyEngineLib

mkdir ./LaphonyEngineLib
mkdir ./LaphonyEngineLib/include
mkdir ./LaphonyEngineLib/lib
mkdir ./LaphonyEngineLib/bin

cp ./dist/Lib_linux/GNU-Linux/* ./LaphonyEngineLib/lib/
cp ./dist/Lib_linux/GNU-Linux/* ./LaphonyEngineLib/bin/

find . -not -path "./Test*" -not -path "./LaphonyEngineLib*" -name '*.h' -exec cp --parents \{\} ./LaphonyEngineLib/include \;
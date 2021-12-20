#!/bin/sh
g++ src/*.cc `root-config --cflags --glibs` -o runsim
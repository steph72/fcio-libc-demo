#!/bin/sh

set -e
rm -rf res/*
mkdir -p res

# convert  images and shift palette
for filename in images-src/*.png; do
  python3 tools/png2fci.py -vr $filename res/$(basename $filename .png).fci
done
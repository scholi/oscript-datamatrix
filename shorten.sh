#!/bin/bash
F=main.c
echo "Shorten variables"
sed -i "s/glog/G/g" $F
sed -i "s/alog/A/g" $F
sed -i "s/ncol/X/g" $F
sed -i "s/nrow/Y/g" $F
sed -i "s/row/R/g" $F
sed -i "s/col/C/g" $F
sed -i "s/ldata/L/g" $F
sed -i "s/data/D/g" $F
sed -i "s/lmsg/B/g" $F
sed -i "s/txt/T/g" $F
sed -i "s/array/U/g" $F

echo "Shorten functioin names"
sed -i "s/corner1/E/g" $F
sed -i "s/corner2/F/g" $F
sed -i "s/corner3/H/g" $F
sed -i "s/corner4/I/g" $F
sed -i "s/module/J/g" $F
sed -i "s/utah/K/g" $F
sed -i "s/encodeASCII/M/g" $F
sed -i "s/getSize/N/g" $F
sed -i "s/mapDataMatrix/O/g" $F

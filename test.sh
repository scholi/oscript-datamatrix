#!/bin/bash

OK=1

function datamatrix_test {
  testname="$1"
  msg="$2"
  dmsize="$3"

  ./datamatrix.py "$msg" | tail -n $dmsize >tmp.out 
  if [ "$(./datamatrix "$msg" 2>/dev/null | tail -n $dmsize | diff tmp.out -)" ]; then
    echo "$testname Test Failed!"
    OK=0
  fi

  rm tmp.out
}

datamatrix_test "Alphacharacters" "Hello" 12
datamatrix_test "Numeric" "0123456789" 12
datamatrix_test "Alphanum" "01ab5cd876fFf" 12
datamatrix_test "Symbols" "01abAB+-!?" 12
datamatrix_test "ExtASCII" "`cat extascii.txt`" 12

# various DM sizes
sizes=(8 10 12 14 16 18 20 22 24 28 32 36 40 44)
datalens=( 3 5 8 12 18 22 30 36 44 62 86 114 144 174)

for (( i=0; i<14; ++i )); do
  datamsg=`python2 -c "print 'e' * ${datalens[$i]}"`
  datamatrix_test "DM Size ${sizes[$i]}" "$datamsg" ${sizes[$i]}
done

if (( OK == 1 )); then
  echo "All tests ok!"
fi

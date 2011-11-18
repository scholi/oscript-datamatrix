#!/bin/bash

OK=1

function datamatrix_test {
  testname="$1"
  msg="$2"
  dmsize="$3"

  python datamatrix.py "$msg" | tail -n $dmsize >tmp.out 
  if [ "$(./datamatrix "$msg" | tail -n $dmsize | diff tmp.out -)" ]; then
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

if (( OK == 1 )); then
  echo "All tests ok!"
fi

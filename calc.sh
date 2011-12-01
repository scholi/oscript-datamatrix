#!/bin/bash

size1=`cat main.c | tr -d ' ' | wc | awk '{print $3}'`
sizeSpaces=`cat main.c | tr -cd ' ' | wc | awk '{print $3}'`

echo -e "main.c\t${size1}\t${sizeSpaces}"
size1=`cat stack.c | tr -d ' ' | wc | awk '{print $3}'`
sizeSpaces=`cat stack.c | tr -cd ' ' | wc | awk '{print $3}'`

echo -e "stack.c\t${size1}\t${sizeSpaces}"

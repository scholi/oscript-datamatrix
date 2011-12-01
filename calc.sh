#!/bin/bash

white=' \n\t'

size1=`cat main.c | tr -d "$white" | wc | awk '{print $3}'`
sizeSpaces=`cat main.c | tr -cd "$white" | wc | awk '{print $3}'`

echo -e "main.c\t\t${size1}\t${sizeSpaces}"
size1=`cat stack.c | tr -d "$white" | wc | awk '{print $3}'`
sizeSpaces=`cat stack.c | tr -cd "$white" | wc | awk '{print $3}'`

echo -e "stack.c\t\t${size1}\t${sizeSpaces}"

size1=`cat combined.c | tr -d "$white" | wc | awk '{print $3}'`
sizeSpaces=`cat combined.c | tr -cd "$white" | wc | awk '{print $3}'`
echo -e "combined.c\t${size1}\t${sizeSpaces}"

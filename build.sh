#!/bin/bash

echo "Running Bison..."
bison -d bison.y
if [ $? -ne 0 ]; then
    echo "Bison failed."
    exit 1
fi

echo "Running Flex..."
flex flex.l
if [ $? -ne 0 ]; then
    echo "Flex failed."
    exit 1
fi

echo "Compiling with gcc..."
gcc bison.tab.c lex.yy.c -o parser -lfl
if [ $? -ne 0 ]; then
    echo "ompilation failed."
    exit 1
fi

echo "Build successful. Run with: ./parser final_example.myhtml"

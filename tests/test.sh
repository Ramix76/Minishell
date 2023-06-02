#!/bin/bash

TEST_FILE=test_ft_getenv.c

echo Compiling\ "$TEST_FILE"...
echo

gcc "$TEST_FILE" -I ../src/ -I ../src/libft/src -I ../src/builtins -L ../src/libft -lft 
./a.out
rm a.out

echo
echo OK

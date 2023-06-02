#!/bin/bash

INC="-I ../src/ -I ../src/libft/src -I ../src/builtins -L ../src/libft -lft "
INC+="-I test.utils.h"
OUT=a.out

function execute_test() {
	if [[ "$1" ]]
	then
		gcc $INC $TEST_FILE "test.utils.c" -o $OUT
		./$OUT
		rm $OUT
	fi
}

# Main

for TEST_FILE in test_*.c
do
	execute_test "$TEST_FILE"
done

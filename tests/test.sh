#!/bin/bash

INC="-I ../src/ -I ../src/libft/src -I ../src/builtins -L ../src/libft -lft"
OUT=a.out

function execute_test() {
	if [[ "$1" ]]
	then
		gcc $INC $TEST_FILE -o $OUT
		./$OUT
		rm $OUT
	fi
}

# Main

for TEST_FILE in test_*.c
do
	execute_test "$TEST_FILE"
done

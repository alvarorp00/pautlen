#!/bin/bash

# info: checks if file_source is same to file_result
# args: 
#     (0): script exec
#     (1): file_source
#     (2): file_result

ON_ERROR="TEST FAILURE."
ON_SUCCESS="TEST SUCCESS."

# Main

file_source=$1
file_result=$2

if [ $# -eq 2 ]; then
  printf 'Test Result: '
  DIFF=$(diff -Bb $file_source $file_result)
  if [ "$DIFF" != "" ]; then
    printf '%s\n' "$ON_ERROR"
  else
    printf '%s\n' "$ON_SUCCESS"
  fi
else
  printf 'Bad args: %s FILE_SOURCE FILE_RESULT\n' "$0"
fi

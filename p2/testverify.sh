#!/bin/bash

# info: checks if file_source is same to file_result
# args:
#     (0): script exec
#     (1): file_source
#     (2): file_result

ON_ERROR="TEST FAILURE."
ON_SUCCESS="TEST SUCCESS."

red=$'\e[1;31m'
grn=$'\e[1;32m'
end=$'\e[0m'

# Main

file_source=$1
file_result=$2

if [ $# -eq 2 ]; then
  printf 'Test Result: '
  DIFF=$(diff -Bb $file_source $file_result)
  if [ "$DIFF" != "" ]; then
    printf "${red}%s${end}\n" "$ON_ERROR"
  else
    printf "${grn}%s${end}\n" "$ON_SUCCESS"
  fi
else
  printf 'Bad args: %s FILE_SOURCE FILE_RESULT\n' "$0"
fi

#!/bin/bash

# info: checks if file_source is same to file_result
# args: 
#     (0): script exec
#     (1): file_source
#     (2): file_result

ON_ERROR="TEST FAILURE."
ON_EXIT="TEST SUCCESS."

# Main

file_source=$1
file_result=$2

echo "$#"

if [ $# -eq 2 ]; then
  printf 'Test Result: '
  if cmp -s "$file_source" "$file_result"; then
    printf '%s\n' "$ON_EXIT"
  else
    printf '%s\n' "$ON_ERROR"
  fi
else
  printf 'Bad args: %s FILE_SOURCE FILE_RESULT\n' "$0"
fi
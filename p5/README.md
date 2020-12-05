# Pautlen

Pautlen UAM | 2020 - 2021

**Authors**

> Víctor Perea Riquelme     | victor.perea@estudiante.uam.es
 
> Álvaro Rodríguez Palacios | alvaro.rodriguezp@estudiante.uam.es

> Javier Romera Llave       | javier.romeral@estudiante.uam.es

##

Assignment 4 - Symbols Table

---

## Makefile

For help, run: 

  **`make help`**
```
❯ make help
all                            Compile all. 
clean                          Cleans output files
default                        Equivalent to 'make all'
explain                        Prints exec process in stdout
help                           This guide
test                           Executes test and compares result
```

<div style="page-break-after: always"></div>

### Folder structure

**Important:** shown tree before **`make`** and after **`make clean`**:

```
root
.
├── inc
│   ├── alfa.h
│   ├── hash.h
│   ├── symbol.h
│   └── symbolsTable.h
├── Makefile
├── README.html
├── README.md
├── README.pdf
├── src
│   ├── hash.c
│   ├── pruebaTS.c
│   ├── symbol.c
│   └── symbolsTable.c
├── testfiles
│   ├── expectedResTS.txt
│   └── pruebaTS.txt
├── testresults
└── testverify.sh
```

<div style="page-break-after: always"></div>

**Important:** shown tree after **`make`**, **`make test`** and before **`make clean`**

```
root
.
├── inc
│   ├── alfa.h
│   ├── hash.h
│   ├── symbol.h
│   └── symbolsTable.h
├── Makefile
├── pruebaTabla
├── README.html
├── README.md
├── README.pdf
├── src
│   ├── hash.c
│   ├── pruebaTS.c
│   ├── symbol.c
│   └── symbolsTable.c
├── testfiles
│   ├── expectedResTS.txt
│   └── pruebaTS.txt
├── testresults
│   └── testresult.txt
└── testverify.sh
```

<div style="page-break-after: always"></div>

## Tests

For running test, type `make test`

This rules execute **pruebaTabla** with it's correspondant source testfile - located at _testfiles/pruebaTS_ - and, helped by **testverify.sh**, a script which process the result of doing `diff -Bb inputfile.txt outputfile.txt`, shows a message with the result of the test. Expected return for diff is '\0'.

**testverify.sh**
```
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
    printf "Difference:\n"
    diff -Bb $file_source $file_result
  else
    printf "${grn}%s${end}\n" "$ON_SUCCESS"
  fi
else
  printf 'Bad args: %s FILE_SOURCE FILE_RESULT\n' "$0"
fi
```
<div style="page-break-after: always"></div>

## For explained execution

If explanation while executing test is deserved, you can type `make explain` to compile so next time you run the test, info will be displayer in **stdout**.

## Code documentation

In order to make README less tough, we've moved all explanations of the code to the code. So, it's documented and readable.

## Comment about pruebaTS.c

It's kinda hardcoded, but will work for related input _.txt_ files.
# Pautlen

Pautlen UAM | 2020 - 2021

**Authors**

> Víctor Perea Riquelme     | victor.perea@estudiante.uam.es
 
> Álvaro Rodríguez Palacios | alvaro.rodriguezp@estudiante.uam.es

> Javier Romera Llave       | javier.romeral@estudiante.uam.es

## Assignment 5 - Compiler

This project is about a simple compiler for 'alfa' language. 'Alfa' was thought for educational purposes, so this will not be such interesting to consider as a real option language - don't waste time here!.

Despite previous line, it's been iteresting to have a general idea about compilers stuff.

---

## Makefile

For help, run: 

  **`make help`**
```
❯ make help
all                            Produces compiler
clean                          Cleans output files
default                        Equivalent to 'make all'
help                           This guide
```

Important: `y.output` is stored at **root/info/y.output**.

<div style="page-break-after: always"></div>

## Compiler Info

For running compiler, before you must have it:

```
❯ make
```

Now, you can use it as follows:

```
❯ ./alfa <source.alf> <dest.nasm>
```

For compiling resulting _nasm_ file:

```
❯ ./produce.sh <nasm_file> <program_name>
```

Finally, for executing your alfa program:

```
❯ ./<program_name>
```

If you want to launch compiler with **_DEBUG_** mode - it'll print traces, rules applied, etc - you must uncomment this at **_alfa.h_**:

```
 97 /**
 98  * Prints failure trace
 99  */
100 // #define _DEBUG_ <------ HERE!
101 #ifdef _DEBUG_
102 #define TRACE eprintf("Trace coming from:\t @ file: %s @ funct: %s @ line: >
103 #else
104 #define TRACE
105 #endif
```

## Comments about design

A common header - _alfa.h_ - contains all common stuff (buffers & related) used by _alfa.c_ - launcher -, _alfa.y_ - bison - and _alfa.l_ - flex.

The project uses the next data structures:

  - Hash, with these features:
    - Auto incremental size.
    - Does **not** support deletions.
    - Linea probing.
    - Keys are whatever is desired. _Hashcode_ prototype is at **root/inc/prototypes.h**.
  - Symbols:
    - The different options alfa language contain. Actually, as we've designed them is not as we though at the first the moment, but deadlines and stuff overload forced us to end them as quickly as possible.
  - Symbols Table:
    - Uses two Hash tables to store symbols, depending on the scope - context.
  - Generator:
    - A _Netwide Assembler_ generator library, used by _alfa.y_ - bison - to produce final code which'll be compiled as assembler to get final desired program.

#ifndef ALFA_H
#define ALFA_H

#define STRINGIFY(x) #x

#define READ(file) fopen(file, "r");
#define WRITE(file) fopen(file, "w");

#define BUFF 128

extern char errbuff[BUFF];

#endif
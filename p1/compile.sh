echo "Cleaning files..."
rm -rf out/*
rm -rf obj/*.o

echo "Clean complete. Compiling..."

gcc -I inc/ -c src/main_0_generacion.c src/generator.c
gcc -I inc/ -c src/main_2_generacion.c src/generator.c
gcc -I inc/ -c src/main_generacion.c src/generator.c
gcc -I inc/ -c src/main_4_generacion.c src/generator.c
gcc -I inc/ -c src/main_5_generacion.c src/generator.c
gcc -I inc/ -c src/main_6_generacion.c src/generator.c
gcc -I inc/ -c src/main_7_generacion.c src/generator.c

mv *.o obj/.

gcc -o main_0_generacion obj/main_0_generacion.o obj/generator.o
gcc -o main_2_generacion obj/main_2_generacion.o obj/generator.o
gcc -o main_generacion obj/main_generacion.o obj/generator.o
gcc -o main_4_generacion obj/main_4_generacion.o obj/generator.o
gcc -o main_5_generacion obj/main_5_generacion.o obj/generator.o
gcc -o main_6_generacion obj/main_6_generacion.o obj/generator.o
gcc -o main_7_generacion obj/main_7_generacion.o obj/generator.o

./main_0_generacion asm/main_0_generacion.asm
./main_2_generacion asm/main_2_generacion.asm
./main_generacion asm/main_generacion.asm
./main_4_generacion asm/main_4_generacion.asm
./main_5_generacion asm/main_5_generacion.asm
./main_6_generacion asm/main_6_generacion.asm
./main_7_generacion asm/main_7_generacion.asm

nasm -g -o obj/generator.o -f elf32 asm/main_0_generacion.asm
gcc -m32 -o out/main_0_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_2_generacion.asm
gcc -m32 -o out/main_2_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_generacion.asm
gcc -m32 -o out/main_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_4_generacion.asm
gcc -m32 -o out/main_4_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_5_generacion.asm
gcc -m32 -o out/main_5_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_6_generacion.asm
gcc -m32 -o out/main_6_generacion obj/generator.o lib/alfalib.o

nasm -g -o obj/generator.o -f elf32 asm/main_7_generacion.asm
gcc -m32 -o out/main_7_generacion obj/generator.o lib/alfalib.o

rm -rf main_0_generacion main_2_generacion main_generacion main_4_generacion main_5_generacion main_6_generacion main_7_generacion

echo "Compiled"

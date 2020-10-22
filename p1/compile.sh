echo "Cleaning files..."
rm -rf out/generacion
rm -rf obj/*.o

echo "Clean complete. Compiling..."

gcc -I inc/ -c src/main_0_generacion.c src/generacion.c
gcc -I inc/ -c src/main_2_generacion.c src/generacion.c
gcc -I inc/ -c src/main_generacion.c src/generacion.c

mv *.o obj/.

gcc -o main_0_generacion obj/main_0_generacion.o obj/generacion.o
gcc -o main_2_generacion obj/main_2_generacion.o obj/generacion.o
gcc -o main_generacion obj/main_generacion.o obj/generacion.o

./main_0_generacion asm/main_0_generacion.asm
./main_2_generacion asm/main_2_generacion.asm
./main_generacion asm/main_generacion.asm

nasm -g -o obj/generacion.o -f elf32 asm/main_0_generacion.asm
gcc -m32 -o out/main_0_generacion obj/generacion.o lib/alfalib.o

nasm -g -o obj/generacion.o -f elf32 asm/main_2_generacion.asm
gcc -m32 -o out/main_2_generacion obj/generacion.o lib/alfalib.o

nasm -g -o obj/generacion.o -f elf32 asm/main_generacion.asm
gcc -m32 -o out/main_generacion obj/generacion.o lib/alfalib.o

rm -rf main_0_generacion main_2_generacion main_generacion

echo "Compiled"

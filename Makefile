#!/bin/bash
src=sources/
INC=include/

staticlib=staticlib/
cFile=$(src)myTime.c $(src)LinkedList.c $(src)bmi.c $(src)operation.c $(src)barChart.c $(src)record.c $(src)user.c $(src)userInterface.c $(src)start.c $(src)sort.c
oFile=$(src)myTime.o $(src)LinkedList.o $(src)bmi.o $(src)operation.o $(src)barChart.o $(src)record.o $(src)user.o $(src)userInterface.o $(src)start.o $(src)sort.o

main:sta install
	gcc $(src)main.c -L. -lmylib -o $(src)dynamicmain
	gcc -o $(src)staticmain $(src)main.c -lmystaticlib -static
	gcc sources/*.c -o $(src)test
#Static
sta:sta*.o
	ar r libmystaticlib.a *.o
#sta gcc -c
sta*.o:
	gcc $(cFile) -c
#Dynamic
dync=$(src)barChart.c $(src)record.c $(src)user.c $(src)myTime.c $(src)LinkedList.c $(src)bmi.c $(src)operation.c $(src)userInterface.c $(src)start.c $(src)sort.c
lib_path=/usr/local/lib/ 
dyn:
	gcc -shared -fPIC $(dync) -o libmylib.so
install:dyn
	sudo cp libmystaticlib.a $(lib_path)
	sudo cp libmylib.so $(lib_path)
	sudo ldconfig
clean:
	rm -rf *.o $(src)dynamicmain libmystaticlib.a libmylib.so test sources/dynamicmain sources/test sources/staticmain

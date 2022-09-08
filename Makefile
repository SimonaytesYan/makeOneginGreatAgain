all: console_set str qsort
	g++ -c Main.cpp
	g++ Main.o _Strings.o ConsoleSettings.o QSORT.o -o Start.exe

clean_file: str
	g++ CleanFile.cpp _Strings.o -o Clean.exe
	.\Clean.exe

qsort:
	g++ -c QSORT.cpp

str:
	g++ -c Strings\_Strings.cpp

tests_lib:	
	g++ -c Strings\Tests.cpp

console_set:
	g++ -c Console\ConsoleSettings.cpp
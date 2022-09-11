all: console_set str qsort file_work bullshit_generator
	g++ Main.cpp _Strings.o ConsoleSettings.o QSORT.o FileWork.o BullshitGenerator.o -o Start.exe

clean_file: str
	g++ CleanFile.cpp _Strings.o -o Clean.exe
	.\Clean.exe

bullshit_generator:
	g++ -c BullshitGenerator\BullshitGenerator.cpp

qsort:
	g++ -c Qsort\QSORT.cpp

file_work:
	g++ -c FileWork\FileWork.cpp

str:
	g++ -c Strings\_Strings.cpp

tests_lib:	
	g++ -c Strings\Tests.cpp

console_set:
	g++ -c Console\ConsoleSettings.cpp
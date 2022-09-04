all: console_set str
	g++ -c Main.cpp
	g++ Main.o _Strings.o ConsoleSettings.o -o Start.exe

test: console_set str tests_lib
	g++ -c MainTest.cpp
	g++ MainTest.o _Strings.o ConsoleSettings.o Tests.o -o StartTest.exe

clean_file: str
	g++ CleanFile.cpp _Strings.o -o Clean.exe
	.\Clean.exe

str:
	g++ -c Strings\_Strings.cpp

tests_lib:	
	g++ -c Strings\Tests.cpp

console_set:
	g++ -c Console\ConsoleSettings.cpp

clean_file_linux:
	g++ -c Strings/_Strings.cpp
	g++ CleanFile.cpp _Strings.o -o Clean.exe
	./Clean.exe
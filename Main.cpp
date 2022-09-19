#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Strings\_Strings.h"
#include "Qsort\QSORT.h"
#include "Console\ConsoleSettings.h"
#include "FileWork\FileWork.h"
#include "BullshitGenerator\BullshiGenerator.h"

const char READ_FROM[]         = "Texts/ForTest.txt";
const char WRITE_TO[]          = "Texts/OUTPUT.txt";
const char WRITE_BULLSHIT_TO[] = "Texts/bullshit.txt";


/*! \mainpage Make Onegin greate again project
 *
 * You should work with all files in Windows 1251 encoding.
 * It is important to program performance
 * 
 * This program take the txt file for processing from cmd argument.
 * If file path when calling was not specified file will take from READ_FROM constant. 
 * Sorts lines in lexicographic order, output this version in the WRITE_TO file,
 * (O(n) - memery, O(n*log(n)) time)
 * then puts in WRITE_TO file original text,
 * next program puts in WRITE_TO file lines sorted in lexicographically from the end.
 * And at the end program generates 100 Onegin stanzas composed of various lines of the original work 
 * and puts it in file WRITE_BULLSHIT_TO
 * 
 * Executable file - Start.exe
 * To recompile program print "make" in CMD 
 * 
 * 
 *	SYM 
 *  2022
 */

/*!
* \file
* \brief 
* Main file from which the execution of the program begins
*/

int main(int argc, const char* argv[])
{   
    init_console();

    /*char readFrom[200]; 
    if (argc != 2)
    {
        printf("Wrong number of cmd arguments\n");
        return -1;
    }

    int i = 0; 
    for(i = 0; i < 200; i++)
    {
        if (argv[1][i] == '\0')
            break;
        readFrom[i] = argv[1][i];
    }
    if (i == 200)*/


    size_t textSize = get_text_size(READ_FROM);

    char* workText = (char*)calloc(textSize + 1, 1);
    assert(workText != NULL);

    FILE *fp = fopen(READ_FROM, "r");
    assert(fp != NULL);

    //fread(workText, 1, textSize, fp);
    //for(size_t i = 0; i < textSize; i++)
    //    printf("<%d>", workText[i]);
        
    size_t numberLines = gettext(workText, textSize, fp);
    printf("Got text\n");
    
    fclose(fp);

    const char** arrayLines = (const char**)calloc(numberLines, sizeof(char*));
    assert(arrayLines != NULL);

    getlines_from_text(arrayLines, workText);
    printf("Splited text to lines\n");

    FILE *ofp = fopen(WRITE_TO, "w");
    assert(ofp);

    QSORT(arrayLines, numberLines, sizeof(char*) , strcmp_);

    for(int i = 0; i < numberLines; i++)
        puts_(arrayLines[i], ofp);
    printf("Array sorted\n");

    puts_("\n\nOriginal test\n", ofp);
    put_text_to_file(workText, ofp, textSize);
    printf("Original printed\n");

    QSORT(arrayLines, numberLines, sizeof(char*), strcmp_reverse);

    puts_("\n\nReverse sorted array\n", ofp);
    for(int i = 0; i < numberLines; i++)
        puts_(arrayLines[i], ofp);
    printf("Reverse array sorted\n");
    
    fclose(ofp);

    if (onegin_bullshit_generator(arrayLines, numberLines, WRITE_BULLSHIT_TO) == 0)
        printf("Bullsit generated\n");
    else
        printf("Error during bullshit generation");
    
    free(arrayLines);
    free(workText);
}
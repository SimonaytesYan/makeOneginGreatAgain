#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "Strings\_Strings.h"
#include "Qsort\QSORT.h"
#include "Console\ConsoleSettings.h"
#include "FileWork\FileWork.h"

const char READ_FROM[]         = "Texts/EOnegin.txt";
const char WRITE_TO[]          = "Texts/OUTPUT.txt";
const char WRITE_BULLSHIT_TO[] = "Texts/bullshit.txt";

int _get_text_size(const char * file_name)
{
    struct stat buff = {};
    stat(file_name, &buff);
    return buff.st_size;
}

int main()
{   
    init_console();

    int text_size = _get_text_size(READ_FROM);

    char* work_text = (char*)calloc(text_size, 1);
    assert(work_text != NULL);

    FILE *fp = fopen(READ_FROM, "r");
    assert(fp != NULL);

    int numberLines = _gettext(work_text, text_size, fp);
    
    fclose(fp);

    const char** arrayLines = (const char**)calloc(numberLines, sizeof(char*));
    assert(arrayLines != NULL);

    _getlines_from_text(arrayLines, work_text);

    FILE *ofp = fopen(WRITE_TO, "w");
    assert(ofp);

    QSORT(arrayLines, numberLines, sizeof(char*) , _strcmp);

    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);

    _puts("\n\nOriginal test\n", ofp);
    _put_text_to_file(work_text, ofp, text_size);

    QSORT(arrayLines, numberLines, sizeof(char*), _strcmp_reverse);

    _puts("\n\nReverse sorted array\n", ofp);
    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);

    _bullshit_generator(arrayLines, numberLines, WRITE_BULLSHIT_TO);
    
    fclose(ofp);

    free(arrayLines);
    free(work_text);
}
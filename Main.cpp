#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "QSORT.h"
#include "Strings\_Strings.h"
#include "Console\ConsoleSettings.h"

const char READ_FROM[] = "EOnegin.txt";
const char WRITE_TO[] = "OUTPUT.txt";

int main()
{   
    init_console();
    
    struct stat buff = {};
    stat(READ_FROM, &buff);
    int text_size = buff.st_size;

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

    printf("Array was got\n");
    QSORT(arrayLines, numberLines, sizeof(char*) , _strcmp);
    printf("Array sorted\n");
    

    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);
        
    _puts("\n\n", ofp);
    printf("Array printed\n");

    _puts("Original test\n", ofp);
    _put_text_to_file(work_text, ofp, text_size);
    printf("Original array printed\n");

    QSORT(arrayLines, numberLines, sizeof(char*), _strcmp_reverse);
    printf("Array sorted reversed\n");

    _puts("\n\nReverse start", ofp);
    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);

    printf("Reversed array printed\n");

    fclose(ofp);

    free(arrayLines);
    free(work_text);
}
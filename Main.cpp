#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys\stat.h>

#include "QSORT.h"
#include "Strings\_Strings.h"
#include "Console\ConsoleSettings.h"

const char READ_FROM[] = "EOnegin.txt";
const char WRITE_TO[] = "OUTPUT.txt";

int _get_text_size(const char * file_name)
{
    struct stat buff = {};
    stat(file_name, &buff);
    return buff.st_size;
}

int main()
{   
    init_console();
    printf("ÿ = %d\n", (unsigned char)'ÿ');
    printf("à = %d\n", (unsigned char)'à');
    printf("¸ = %d\n", (unsigned char)'¸');
    
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
    printf("Splited\n");

    FILE *ofp = fopen(WRITE_TO, "w");
    assert(ofp);

    QSORT(arrayLines, numberLines, sizeof(char*) , _strcmp);
    printf("Sorted array\n");

    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);
    printf("Printed sorted\n");

    _puts("\n\nOriginal test\n", ofp);
    _put_text_to_file(work_text, ofp, text_size);

    QSORT(arrayLines, numberLines, sizeof(char*), _strcmp_reverse);
    printf("Sorted array reveresed\n");

    _puts("\n\nReverse sorted array\n", ofp);
    for(int i = 0; i < numberLines; i++)
        _puts(arrayLines[i], ofp);
    printf("Reversed sorted array printed\n");

    fclose(ofp);

    free(arrayLines);
    free(work_text);
}
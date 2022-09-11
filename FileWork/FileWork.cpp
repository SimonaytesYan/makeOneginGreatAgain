#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "FileWork.h"
#include "../Strings/_Strings.h"

//!--------------------
//!
//!
//!\return Number of lines in text
//!
//!--------------------
int _gettext(char *text, int size,  FILE *fp)
{
    assert(text != NULL);
    assert(fp != NULL);

    fread(text, sizeof(char), size, fp);

    int numberLines = 1;
    int counter = 0;

    while (text[counter] != '\0')    
    {
        if (text[counter] == '\n')
            numberLines++;

        counter++;
    }
    
    return numberLines;
}

void _getlines_from_text(const char **lines, char *text)
{

    int   n                = 0;
    int   line_num         = 0;
    bool  next_is_new_line = false;

    lines[line_num] = &text[n];

    while (text[n] != '\0')
    {
        if (next_is_new_line)
        {
            next_is_new_line = false;
            lines[line_num] = &text[n];
        }
        if (text[n] == '¸')
            text[n] = 'å';
        if (text[n] == '\n')
        {
            text[n] = '\0';
            next_is_new_line = true;
            line_num++;
        }
        n++;
    }
}

//!----------------
//!Puts text to file.
//!
//!Replaces \0 to \n and writes N symbols.
//!----------------
void _put_text_to_file(const char *text, FILE *fp, int N)
{
    while (text[N - 1] == '\0')
        N--;
    
    for(int i = 0; i < N; i++)
    {
        char c = text[i];
        if (c == '\0')
            c = '\n';
        putc(c, fp);
    }
}

void _bullshit_generator(const char** arrayLines, int numberLines, const char* fileName)
{
    FILE * fp = fopen(fileName, "w");
    bool *used = (bool *)calloc(numberLines, 1);
    srand(time(NULL));

    for(int i = 0; i < 100; i++)
    {
        int index = rand()%numberLines;
        while (used[index])
            index = rand()%numberLines;

        used[index] = true;
        _puts(arrayLines[index], fp);
        
        int counter = 0;
        int index2  = index + rand()%10 - 5;
        while (index2 < 0 || index2 >= numberLines || used[index2])
        {
            int mod = rand() % 20;
            index2 = index + rand()%mod - mod/10;
            counter++;
            if (counter > 100)
                break;
        }
        if (counter <= 100)
            _puts(arrayLines[index2], fp);
    }

    fclose(fp);
}

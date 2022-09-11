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

bool is_rhyme_in_9(const char *s1, const char *s2)
{
    const char* start_s1 = s1;
    const char* start_s2 = s2;

    while (*s1 != '\0')
        s1++;
    while (*s2 != '\0')
        s2++;

    while (s1 > start_s1 && !is_russian_letter_vowel(*s1))
        s1--;
    while (s2 > start_s2 && !is_russian_letter_vowel(*s2))
        s2--;

    if (*s1 != *s2)
        return false;
    
    s1--;
    s2--;
    while (s1 > start_s1 && !is_russian_letter_vowel(*s1))
        s1--;
    while (s2 > start_s2 && !is_russian_letter_vowel(*s2))
        s2--;
    
    return *s1 == *s2;
}

bool is_phyme_in_8(const char *s1, const char *s2)
{
    const char* start_s1 = s1;
    const char* start_s2 = s2;

    while (*s1 != '\0')
        s1++;
    while (*s2 != '\0')
        s2++;

    while (s1 > start_s1 && !is_russian_letter_vowel(*s1))
        s1--;
    while (s2 > start_s2 && !is_russian_letter_vowel(*s2))
        s2--;

    return *s1 == *s2;
}

void _bullshit_generator(const char** arrayLines, int numberLines, const char* fileName)
{
    FILE * fp = fopen(fileName, "w");
    assert(fp != nullptr);
    
    const int number_stanzas_to_generate = 10;
    const int rhyme_step                 = 12;
    srand(time(NULL));

    bool *used_8 = (bool *)calloc(numberLines, sizeof(bool));
    bool *used_9 = (bool *)calloc(numberLines, sizeof(bool));
    
    const char **lines_8_syllables = (const char**)calloc(numberLines, sizeof(char*));
    const char **lines_9_syllables = (const char**)calloc(numberLines, sizeof(char*));

    int number_8_syl = 0;
    int number_9_syl = 0;

    
    for(int i = 0; i < numberLines; i++)
    {
        //printf("Start count syllables\n");
        const char *str = arrayLines[i];
        int n_syllables = number_syllables(str);

        if (n_syllables == 8)
        {
            lines_8_syllables[number_8_syl] = arrayLines[i];
            number_8_syl++;
        }
        if (n_syllables == 9)
        {
            lines_9_syllables[number_9_syl] = arrayLines[i];
            number_9_syl++;
        }      
    }
    printf("number_8_s = %d\n", number_8_syl);
    printf("number_9_s = %d\n", number_9_syl);
    printf("Splited by number of syllables\n");

    for(int i = 0; i < number_stanzas_to_generate; i++)
    {
        const char *str1 = 0;
        const char *str2 = 0;
        const char *str3 = 0;
        const char *str4 = 0;

        int index9   = 0;
        int index9_2 = 0;
        do
        {
            index9 = rand() % number_9_syl;
            while (used_9[index9])
                index9 = rand() % number_9_syl;            

            index9_2 = index9 + (rand() % rhyme_step - rhyme_step/2);
            while (used_9[index9_2] || index9_2 < 0 || index9_2 >= number_9_syl || index9 == index9_2)
                index9_2 = index9 + (rand() % rhyme_step - rhyme_step/2);
        } 
        while(!is_rhyme_in_9(lines_9_syllables[index9], lines_9_syllables[index9_2]));
        used_9[index9]   = true;
        used_9[index9_2] = true;

        str1 = lines_9_syllables[index9];
        str3 = lines_9_syllables[index9_2];
        
        int index8   = 0;
        int index8_2 = 0;
        do 
        {
            index8 = rand() % number_8_syl;
            while (used_8[index8])
                index8 = rand() % number_8_syl;

            index8_2 = index8 + (rand() % rhyme_step - rhyme_step/2);
            while (used_8[index8_2] || index8_2 < 0 || index8_2 >= number_8_syl || index8 == index8_2)
                index8_2 = index8 + (rand() % rhyme_step - rhyme_step/2);
        }
        while(!is_phyme_in_8(lines_8_syllables[index8], lines_8_syllables[index8_2]));
        used_8[index8]   = true;
        used_8[index8_2] = true;

        str2 = lines_8_syllables[index8];
        str4 = lines_8_syllables[index8_2];

        _puts(str1, fp);
        _puts(str2, fp);
        _puts(str3, fp);
        _puts(str4, fp);
        _puts("", fp);
    }

    fclose(fp);
}

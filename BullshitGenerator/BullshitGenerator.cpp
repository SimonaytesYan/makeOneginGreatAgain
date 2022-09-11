#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../Strings/_Strings.h"

const int rhyme_step = 12;

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

bool is_rhyme_in_8(const char *s1, const char *s2)
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

void get_rhyme(const char** lines, int number_lines, bool* used, const char **s1, const char **s2, 
                           bool (*rhyme_comp)(const char *s1, const char *s2))
{
    int index   = 0;
    int index_2 = 0;
    do
    {
        index = rand() % number_lines;
        while (used[index])
            index = rand() % number_lines;            

        index_2 = index + (rand() % rhyme_step - rhyme_step/2);
        while (used[index_2] || index_2 < 0 || index_2 >= number_lines || index == index_2)
            index_2 = index + (rand() % rhyme_step - rhyme_step/2);
    } 
    while(!rhyme_comp(lines[index], lines[index_2]));

    used[index]   = true;
    used[index_2] = true;

    *s1 = lines[index]; 
    *s2 = lines[index_2];
}

void _bullshit_generator(const char** arrayLines, int numberLines, const char* fileName)
{
    FILE * fp = fopen(fileName, "w");
    assert(fp != nullptr);
    
    const int number_stanzas_to_generate = 10;
    srand(time(NULL));

    bool *used_8 = (bool *)calloc(numberLines, sizeof(bool));
    bool *used_9 = (bool *)calloc(numberLines, sizeof(bool));
    
    const char **lines_8_syllables = (const char**)calloc(numberLines, sizeof(char*));
    const char **lines_9_syllables = (const char**)calloc(numberLines, sizeof(char*));

    int number_8_syl_lines = 0;
    int number_9_syl_lines = 0;

    
    for(int i = 0; i < numberLines; i++)
    {
        //printf("Start count syllables\n");
        const char *str = arrayLines[i];
        int n_syllables = number_syllables(str);

        if (n_syllables == 8)
        {
            lines_8_syllables[number_8_syl_lines] = arrayLines[i];
            number_8_syl_lines++;
        }
        if (n_syllables == 9)
        {
            lines_9_syllables[number_9_syl_lines] = arrayLines[i];
            number_9_syl_lines++;
        }      
    }
    printf("Splited by number of syllables\n");

    for(int i = 0; i < number_stanzas_to_generate; i++)
    {
        const char *str1 = NULL;
        const char *str2 = NULL;
        const char *str3 = NULL;
        const char *str4 = NULL;

        get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str3, is_rhyme_in_9);
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str2, &str4, is_rhyme_in_8);

        _puts(str1, fp);
        _puts(str2, fp);
        _puts(str3, fp);
        _puts(str4, fp);
        
        get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str2, is_rhyme_in_9);
        _puts(str1, fp);
        _puts(str2, fp);
        
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str1, &str2, is_rhyme_in_8);
        _puts(str1, fp);
        _puts(str2, fp);
        
        get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str4, is_rhyme_in_9);
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str2, &str3, is_rhyme_in_8);

        _puts(str1, fp);
        _puts(str2, fp);
        _puts(str3, fp);
        _puts(str4, fp);
        
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str1, &str2, is_rhyme_in_8);
        _puts(str1, fp);
        _puts(str2, fp);
        _puts("", fp);

    }

    fclose(fp);
}
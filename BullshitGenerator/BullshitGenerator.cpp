#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../Strings/_Strings.h"

const int rhyme_step = 12;

/*!
* \file
* \brief 
* This file contains functions for create Onegin stanza composed of various lines of the original work
*/

//!-----------------
//! Takes two nine syllables strings and check checks if there is a rhyme.
//! Considers that the lines are written in iambic
//!
//!-----------------
bool is_rhyme_in_9(const char *s1, const char *s2)
{
    assert(s1 != nullptr);
    assert(s2 != nullptr);

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

//!-----------------
//! Takes two eight syllables strings and check checks if there is a rhyme.
//! Considers that the lines are written in iambic
//!
//!-----------------
bool is_rhyme_in_8(const char *s1, const char *s2)
{
    assert(s1 != nullptr);
    assert(s2 != nullptr);

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

//!-----------------
//! Gives two rhyming lines 
//!@param  [in]  lines        Array from lines will be selected
//!@param  [in]  number_lines Size of lines
//!@param  [in]  used         Array containing information about which lines from lines have already been used
//!@param  [out] s1           The first  line of for rhyme
//!@param  [out] s2           The second line of for rhyme
//!@param  [in]  phyme_comp   Function to check if two lines rhyme
//!@return 0 if executed correctly and -1 otherwise
//!
//!-----------------

int get_rhyme(const char** lines, size_t number_lines, bool* used, const char **s1, const char **s2, 
                           bool (*rhyme_comp)(const char *s1, const char *s2))
{
    
    if (lines      != nullptr)
        return -1;
    if (*lines     != nullptr)
        return -1;
    if (used       != nullptr)
        return -1;
    if (s1         != nullptr)
        return -1;
    if (s2         != nullptr)
        return -1;
    if (rhyme_comp != nullptr)
        return -1;

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

//!-----------------
//!Generate number_stanzas_to_generate onegin stanza
//!@param  [in] arrrayLines Array from lines to generate stazas will be selected
//!@param  [in] numberLines Size of arrayLines
//!@param  [in] fileName    File where generated stazas will be output  
//!@return 0 if executed correctly and -1 otherwise
//!
//!-----------------

int onegin_bullshit_generator(const char** arrayLines, size_t numberLines, const char* fileName)
{
    assert(arrayLines  != nullptr);
    assert(*arrayLines != nullptr);
    assert(fileName    != nullptr);

    FILE * fp = fopen(fileName, "w");
    assert(fp != nullptr);
    
    const int number_stanzas_to_generate = 100;
    srand(time(NULL));

    bool *used_8 = (bool *)calloc(numberLines, sizeof(bool));
    bool *used_9 = (bool *)calloc(numberLines, sizeof(bool));
    
    const char **lines_8_syllables = (const char**)calloc(numberLines, sizeof(char*));
    const char **lines_9_syllables = (const char**)calloc(numberLines, sizeof(char*));

    int number_8_syl_lines = 0;
    int number_9_syl_lines = 0;
    
    for(int i = 0; i < numberLines; i++)
    {
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

    for(int i = 0; i < number_stanzas_to_generate; i++)
    {
        const char *str1 = NULL;
        const char *str2 = NULL;
        const char *str3 = NULL;
        const char *str4 = NULL;

        int get_phym_retrun = get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str3, is_rhyme_in_9);
        if (get_phym_retrun != 0)
            return get_phym_retrun;
        get_phym_retrun     = get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str2, &str4, is_rhyme_in_8);
        if (get_phym_retrun != 0)
            return get_phym_retrun;

        puts_(str1, fp);
        puts_(str2, fp);
        puts_(str3, fp);
        puts_(str4, fp);
        
        get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str2, is_rhyme_in_9);
        puts_(str1, fp);
        puts_(str2, fp);
        
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str1, &str2, is_rhyme_in_8);
        puts_(str1, fp);
        puts_(str2, fp);
        
        get_rhyme(lines_9_syllables, number_9_syl_lines, used_9, &str1, &str4, is_rhyme_in_9);
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str2, &str3, is_rhyme_in_8);

        puts_(str1, fp);
        puts_(str2, fp);
        puts_(str3, fp);
        puts_(str4, fp);
        
        get_rhyme(lines_8_syllables, number_8_syl_lines, used_8, &str1, &str2, is_rhyme_in_8);
        puts_(str1, fp);
        puts_(str2, fp);
        puts_("", fp);

    }

    fclose(fp);
}
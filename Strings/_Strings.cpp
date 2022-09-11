#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

#include "_Strings.h"

int _strlen(const char *str) 
{
    int n = 0;
    while (str[n] != '\0')
        n++;

    return n;
}

char *_strcpy(char *to, const char *from) 
{
    int n = 0;
    while (from[n] != '\0')
    {
        to[n] = from[n];
        n++;
    }
    to[n] = '\0';

    return to;
}

char *_strcat(char *to, const char *from) 
{
	int to_len = _strlen(to);
    int i = 0;
    while (from[i] != '\0')
    {    
		to[to_len + i] = from[i];
        i++;
	}
    to[to_len + i] = '\0';

    return to;
}

char *_strchr(const char * str, char c) 
{
    int i = 0;
    char * answer = nullptr;

    while (str[i] != '\0')
    {
        if (str[i] == c)
            return (char *)(str + i);
        i++;
    }

    return nullptr;
}

int _strnlen(char *str, int maxLen) 
{
    int n = 0;
    while (str[n] != '\0' && n < maxLen)
        n++;

    return n;
}

char *_strncpy(char *to,const char* from, int n) 
{
    int index = 0;
    while (from[index] != '\0' && index < n) 
    {
        to[index] = from[index];
        n++;
    }
    to[index] = '\0';

    return to;
}

char *_strncat(char *to, char *from, int n) 
{
    if (n < 0)
        n = 0;

    int len_to = _strlen(to);

    int index = 0;
    while (from[index] != '\0' && index < n)
    {
        to[len_to + index] = from[index];
        n++;
    }
    to[len_to + n] = '\0';

    return to;
}

char *_strnchr(char *str, char c, int maxLen) 
{
    int i = 0;
    char* answer;
    while (i < maxLen && str[i] != '\0')
    {
        if (str[i] == c)
            return (str + i);
        i++;
    }    

    return nullptr;
}

char *_strdup(const char *str)
{
    int str_len = _strlen((char*)str);    
    char *duplicate = (char *)calloc(str_len + 1, sizeof(char));

    for(int i = 0; i < str_len; i++)
        duplicate[i] = str[i];

    duplicate[str_len] = '\0';

    return duplicate;
}

int _strcmp(void *str1, void *str2)
{
    const char * s1 = *(const char**)str1; 
    const char * s2 = *(const char**)str2;

    int n1 = 0;
    int n2 = 0;
    while (s1[n1] != '\0' && s2[n2] != '\0')
    {
        if(!(isalnum((unsigned char)s1[n1])))
        {
            n1++;
            continue;
        }
        if(!(isalnum((unsigned char)s2[n2])))
        {
            n2++;
            continue;
        }
        
        if (s1[n1] != s2[n2])
            return s1[n1] - s2[n2];

        n1++;
        n2++;
    }

    while (!isalnum((unsigned char)s1[n1]) && s1[n1] != '\0')
        n1++;
    while (!isalnum((unsigned char)s2[n1]) && s2[n2] != '\0')
        n2++;
    
    return s1[n1] - s2[n2];
}

int _strcmp_reverse(void *str1, void *str2)
{
    const char *s1 = *(const char**)str1;
    const char *s2 = *(const char**)str2;
    
    const char *s1_start = s1;
    const char *s2_start = s2;

    while (*s1 != '\0')
        s1++;
    while (*s2 != '\0')
        s2++;
    
    while (s1 >= s1_start && s2 >= s2_start)
    {
        if(!isalnum((unsigned char)(*s1)))
        {
            s1--;
            continue;
        }
        if(!isalnum((unsigned char)(*s2)))
        {
            s2--;
            continue;
        }

        if (*s1 != *s2)
            return *s1 - *s2;

        s1--;
        s2--;
    }
    
    while (!isalnum((unsigned char)(*s1)) && s1 >= s1_start)
        s1--;
    while (!isalnum((unsigned char)(*s2)) && s2 >= s2_start)
        s2--;

    if (s1 < s1_start && 
        s2 < s2_start)
        return *s1 - *s2;
    else if (s1 == s1_start)
        return -1;

    return 1;
}


char  _strncmp(const char * s1, const char* s2, int n)
{
    int index = 0;

    while (s1[index] && s2[index] && index < n - 1)
    {
        if (s1[index] > s2[index])
            return 1;
        if (s1[index] < s2[index])
            return -1;
        
        index++;
    }    

    return s1[index] - s2[index];
}

void _puts(const char *str, FILE *fp)
{   
    if (str == NULL)
    {
        _puts("(null)", fp);
        return;
    }
    assert(fp != NULL);

    int i = 0;
    while(str[i] != '\0')
    {
        putc(str[i], fp);
        i++;
    }
    putc('\n', fp);
}

int _getline(char *line, int max, FILE* fp)
{
    int n = 0;
    short c = 0;
    while ((c = getc(fp)) != '\n' && c != EOF  && n < max)
    {
        line[n] = c;
        n++;
    }
    
    line[n] = '\0';
    if (c == EOF)
        return EOF_RETURN;
    return n;
}

bool is_russian_letter_vowel(char c)
{
    return (c == 'à' ||
            c == 'å' ||
            c == '¸' ||
            c == 'è' ||
            c == 'î' ||
            c == 'ó' ||
            c == 'û' ||
            c == 'ý' ||
            c == 'þ' ||
            c == 'ÿ' ||
            c == 'À' ||
            c == 'Å' ||
            c == '¨' ||
            c == 'È' ||
            c == 'Î' ||
            c == 'Ó' ||
            c == 'Û' ||
            c == 'Ý' ||
            c == 'Þ' ||
            c == 'ß');
}

int number_syllables(const char * str)
{
    assert(str != nullptr);
    int number = 0;

    while (*str != '\0')
    {
        //printf("%c\n", *str);
        if (is_russian_letter_vowel(*str))
            number++;
        str++;
    }

    return number;
}
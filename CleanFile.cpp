#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <locale.h>

#include "Strings/_Strings.h"

const char READ_FROM[] = "Onegin.txt";

int main()
{
    //setlocale(LC_CTYPE, "");
    setlocale(LC_ALL, "Rus");

    //printf("Привет мир!\n");
    //abort();

    FILE* fp = fopen(READ_FROM, "r");
    FILE* wfp = fopen("EOnegin.txt", "w");
    
    int file_size = 0;
    while(getc(fp) != EOF)
		file_size++;
    
    fclose(fp);
    fp = fopen(READ_FROM, "r");

    char *text = (char*)calloc(file_size, 1);
    fread(text,1, file_size, fp);
    
    fclose(fp);

    //printf("%s\n", text);

    int  n          = 0;
    int  last_str_i = 0;
    bool isLit      = false;
    char line[1400]  = {0};

    while (text[n] != '\0')
    {
        if (text[n] == '\n')
        {
            if (isLit)
            {
                int len = n - last_str_i;
                _strncpy(line, (text + n - len), len);

                _puts(line, stdout);
                fprintf(wfp, line);
                //_puts(line, wfp);
            }
            isLit = false;
            last_str_i = n;
        }
        if (isalnum(text[n]))
            isLit = true;
        n++;
    }
    
    if (isLit)
    {
        int len = n - last_str_i;
        _strncpy(line, (text + n - len), len);

        _puts(line, stdout);
        _puts(line, wfp);
    }

    fclose(wfp);

}
#ifndef _STRINGS_SYM_
#define _STRINGS_SYM_

const int EOF_RETURN = -1; 

void _drivel_generator(const char** arrayLines, int numberLines, const char* fileName);

int   _strlen(const char *str);

int   _strnlen(char *str, int maxLen);

char *_strcpy(char *to, const char* from);

char *_strncpy(char *to, const char* from, int n);

char *_strcat(char *to, const char *from);

char *_strncat(char *to, char* from, int n);

int  _strcmp(void *str1, void *str2);

int  _strcmp_reverse(void *str1, void *str2);

char  _strncmp(const char * s1, const char* s2, int n);

char *_strchr(const char * str, char c);

char *_strnchr(char *str, char c, int maxLen);

char *_strdup(const char *str);

void  _puts(const char *str, FILE *fp);

int   _getline(char *line, int max, FILE *fp);

int   _gettext(char *text, int size, FILE *fp);

void  _getlines_from_text(const char **lines, char *text);

void _put_text_to_file(const char *text, FILE *fp, int N);

#endif
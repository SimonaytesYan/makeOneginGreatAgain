#ifndef _FILEWORK_SYM_
#define _FILEWORK_SYM_

int _gettext(char *text, int size,  FILE *fp);

void  _getlines_from_text(const char **lines, char *text);

void _put_text_to_file(const char *text, FILE *fp, int N);

void _bullshit_generator(const char** arrayLines, int numberLines, const char* fileName);

int _get_text_size(const char * file_name);

#endif
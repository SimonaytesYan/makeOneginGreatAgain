#include <stdio.h>
#include <stdlib.h>

#include "Tests.h"
#include "_Strings.h"

void test_strlen()
{
    char f[] = "123456789";

    printf("TEST 1: ");

    int ans = _strlen(f);
    if (ans != 9)
    {
        printf("FAILED\n");
        printf("f   = <%s>\n", f);
        printf("Len = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 2: ");
    
    ans = _strlen("");
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f   = <>\n");
        printf("Len = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 3: ");
    
    ans = _strlen("1");
    if (ans != 1)
    {
        printf("FAILED\n");
        printf("f   = <1>\n");
        printf("Len = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 4: ");
    
    ans = _strlen("11");
    if (ans != 2)
    {
        printf("FAILED\n");
        printf("f   = <11>\n", f);
        printf("Len = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 5: ");
    
    ans = _strlen("111");
    if (ans != 3)
    {
        printf("FAILED\n");
        printf("f   = <111>\n");
        printf("Len = %d\n", ans);
    }
    else
        printf("PASSED\n");
}

void test_strcpy() 
{
    char f[5] = {};
    char s[6] = {};

    printf("Start program\n");

    _strcpy(f, "lol");
    _strcpy(s, "second");

    printf("f = %s\n", f);
    printf("s = %s\n", s);

    _strcpy(f,s);
    printf("f = %s\n", f);
    printf("s = %s", s);
}

void test_strcat()
{
    //char *f = (char*)calloc(7, 1);
    //char *s = (char*)calloc(7, 1);
    char f[7] = {};
    char s[40] = {};

    _strcpy(f, "You are");
    _strcpy(s, " the best programer in the world!");

    printf("f = %s\n", f);
    printf("s = %s\n", s);

    _strcat(f, s);

    printf("f = %s\n", f);
    printf("s = %s\n", s);
}

void test_strchr()
{
    char f[10] = {};

    _strcpy(f, "haaaaaaah");
    printf("f = %s\n", f);

    char *to_h = _strchr(f, 'h');

    printf("%s\n", to_h);

    _strcpy(f, "aaa");
    printf("f = %s\n", f);

    printf("%s\n", _strchr(f, 'h'));
}

void test_strnlen()
{
    char f[] = "123456789";

    for(int i = 10; i >= 0; i--) {
        printf("_strnlen(\"123456789\", %d) = %d\n", i, _strnlen((char*)"123456789", i));
    }

    for (int i = 2; i >= 0; i--) {
        printf("_strnlen(\"1\", %d) = %d\n",         i, _strnlen((char*)"1",         i));
    }

    for (int i = 1; i >= 0; i--) {
        printf("_strnlen(\"\", %d) = %d\n",          i, _strnlen((char*)"",          i));
    }
}

void test_strncpy()
{
    char f[] = "To be ";
    char s[] = "or not to be";
    
    char res[40];
   
    for(int i = 10; i >= 0; i-- )
    {
        _strncpy(res, f, i);
        printf("_strncpy(res, \"%s\", %d) = \"%s\"\n", f, i, res);
    }

    for (int i = 20; i >= 5; i--)
    {
        _strncpy(res, s, i);
        printf("_strncpy(res, \"%s\", %d) = \"%s\"\n", s, i, res);
    }

    for (int i = 10; i >= 0; i--)
    {
        _strncpy(res, (char*)"", i);
        printf("_strncpy(res, \"\", %d) = \"%s\"\n", i, res);
    }
}

void test_strncat()
{
    char f[40] = "To be ";
    char s[] = "or not to be";
    for(int i = 25; i >= 0; i--)
    {
        _strncat(f, s, i);
        printf("_strncat(\"%s\", \"%s\", %d) = \"%s\"\n", "To be ", s, i, f);
        _strcpy(f, (char*)"To be ");
    }
}

void test_strnchr()
{
    char f[40] = "hello my dear friend!";

    for (char c = 'a'; c <= 'z'; c++)
    {
        for (int i = 25; i >= 0; i--)
        {
            printf("_strnchr(\"%s\", %c, %d) = \"%s\"\n", f, c, i, _strnchr(f, c, i));
        }
    }
}

void test_strdup()
{
    char f[20] = "123456";

    char* f2 = _strdup(f);

    printf("f  = \"%s\"\n", f);
    printf("2f = \"%s\"\n", f2); 
    
    free(f2);

    _strcpy(f, "a");
    f2 = _strdup(f);
                           
    printf("f  = \"%s\"\n", f);
    printf("2f = \"%s\"\n", f2);
                                
    free(f2);

    _strcpy(f,(char *)"");
    f2 = _strdup(f);
                           
    printf("f  = \"%s\"\n", f);
    printf("2f = \"%s\"\n", f2);

    free(f2);
}

void test_puts()
{
    _puts("Hello world", stdout);
    _puts("END IT!!", stdout);
    _puts("1", stdout);
    _puts("", stdout);
}

void test_getline()
{
    char str[100];

    printf("size = %d\n", _getline(str, 100, stdout));
    printf("%s\n", str);
}

void test_strncmp()
{
    printf("\n""Start test _strncmp()\n");

    char f[100] = "000001";
    char s[100] = "000000";
    printf("TEST 1: ");

    int ans = _strncmp(f, s, 6); 
    if (ans <= 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 2: ");
    _strcpy(f, "0000");
    _strcpy(s, "00000");
    
    ans = _strncmp(f, s, 5);
    if (ans >= 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 3: ");
    _strcpy(f, "0000");
    _strcpy(s, "0000");
    
    ans = _strncmp(f, s, 10);
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 4: ");
    _strcpy(f, "00000");
    _strcpy(s, "0000");
    
    ans = _strncmp(f, s, 10);
    if (ans <= 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 5: ");
    _strcpy(f, "000001");
    _strcpy(s, "00000");
    
    ans = _strncmp(f, s, 5);
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 6: ");
    _strcpy(f, "00000");
    _strcpy(s, "000001");
    
    ans = _strncmp(f, s, 5);
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 7: ");
    _strcpy(f, "00001");
    _strcpy(s, "000011");
    
    ans = _strncmp(f, s, 5);
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f       = <%s>\n", f);
        printf("s       = <%s>\n", s);
        printf("_strcmp = %d\n", ans);
    }
    else
        printf("PASSED\n");
}


void test_strcmp_reverse()
{
    printf("TEST 1: ");
    char f[50] = "10001";
    char s[50] = "11000";

    int ans = _strcmp_reverse(f, s);
    
    if (ans <= 0)
    {
        printf("FAILED\n");
        printf("f         = <%s>\n", f);
        printf("s         = <%s>\n", s);
        printf("_strcmp_r = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 2: ");
    _strcpy(f, "10001");
    _strcpy(s, "000011");

    ans = _strcmp_reverse(f, s);
    
    if (ans >= 0)
    {
        printf("FAILED\n");
        printf("f         = <%s>\n", f);
        printf("s         = <%s>\n", s);
        printf("_strcmp_r = %d\n", ans);
    }
    else
        printf("PASSED\n");
    
    printf("TEST 3: ");
    _strcpy(f, "1000");
    _strcpy(s, "0000");

    ans = _strcmp_reverse(f, s);
    
    if (ans <= 0)
    {
        printf("FAILED\n");
        printf("f         = <%s>\n", f);
        printf("s         = <%s>\n", s);
        printf("_strcmp_r = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 4: ");
    _strcpy(f, "0000");
    _strcpy(s, "0000");

    ans = _strcmp_reverse(f, s);
    
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f         = <%s>\n", f);
        printf("s         = <%s>\n", s);
        printf("_strcmp_r = %d\n", ans);
    }
    else
        printf("PASSED\n");

    printf("TEST 5: ");
    _strcpy(f, "00,,  00");
    _strcpy(s, "0 00  0");

    ans = _strcmp_reverse(f, s);
    
    if (ans != 0)
    {
        printf("FAILED\n");
        printf("f         = <%s>\n", f);
        printf("s         = <%s>\n", s);
        printf("_strcmp_r = %d\n", ans);
    }
    else
        printf("PASSED\n"); 
}
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#include "ConsoleSettings.h"
//!-----------------------------------------------------
//! Function sets russian language in CMD 
//! ----------------------------------------------------
void init_console()
{
    setlocale(LC_ALL, "Rus");
    //printf("\x1B[0m");
}

//!-----------------------------------------------------
//! Function sets color in CMD (two other versions: for windows and for linux) 
//! Color constant specified in ConosoleSettings.h
//! ----------------------------------------------------
#ifndef _WIN32
void set_console_color(int color)
{
    //printf("Set_color_run\n");
    //printf("Color = %d\n", color);
    printf("\x1B[0;%d;40m", color);
}

#else

void set_console_color(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}

#endif
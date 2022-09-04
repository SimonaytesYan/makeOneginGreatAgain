#ifndef CONSOLE_ATR
#define CONSOLE_ATR

#ifndef _WIN32
enum  CONSOLE_COLORS
{
    WHITE = 37,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    DEFAULT = 37
};
#else

enum  CONSOLE_COLORS
{
    WHITE = 15,
    RED = 12,
    GREEN = 10,
    YELLOW = 14,
    DEFAULT = 15
};
#endif

void init_console();

void set_console_color(int color);

#endif
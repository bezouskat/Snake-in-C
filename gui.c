#include "gui.h"

void delay(time_t d)
{
    clock_t time;

    time = clock() + d;
    while (clock() < time) {}
}

void set_color(Color c)
{
    switch (c)
    {
        case BLACK: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);  break;
        case RED: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                          FOREGROUND_INTENSITY | FOREGROUND_RED);   break;
        case GREEN: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                          FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;
        case BLUE: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                          FOREGROUND_INTENSITY | FOREGROUND_BLUE);  break;
        case WHITE: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  break;
    }
}

void goto_xy(int x, int y)
{
    COORD point;

    point.X = x;
    point.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void clear_screen()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

KeyButton get_key()
{
    int key = getch();

    if (key == 0 || key == 0xE0)
      key = getch();

    return key;
}

bool key_hit()
{
    return kbhit();
}

void set_cursor_visible(WINBOOL visible)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_window_size(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void set_window_title(const char* text)
{
    SetConsoleTitle(text);
}

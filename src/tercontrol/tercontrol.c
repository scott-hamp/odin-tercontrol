// Based on the Basic Terminal Control Library by Zackery Smith, 
// (https://github.com/ZackeryRSmith/tercontrol), 
// released under the GPLv3 license.


#include "tercontrol.h"


#ifdef _WIN32

// "l" flag is ignored, just to make it compatible with the POSIX version
char *color_id(uint8_t cid, int l)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (cid / 16) << 4 | (cid % 16));

	return "";
}

void hide_cursor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cci;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(hConsole, &cci); // Get current settings
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cci);
}

void show_cursor()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO cci;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(hConsole, &cci); // Get current settings
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cci);
}

void enter_alt_screen()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	hAlternateScreen = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hAlternateScreen);
	SetStdHandle(STD_OUTPUT_HANDLE, hAlternateScreen);
}

void exit_alt_screen()
{
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return;
	}
	SetConsoleActiveScreenBuffer(hConsole);
	CloseHandle(hAlternateScreen);
	SetStdHandle(STD_OUTPUT_HANDLE, hConsole);
}

void get_cols_rows(int *cols, int *rows)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	*cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void echo_off()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode & (~ENABLE_ECHO_INPUT));
}

void echo_on()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode | ENABLE_ECHO_INPUT);
}

void canon_on()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode | ENABLE_ECHO_INPUT);
}

void canon_off()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD old_mode;
	GetConsoleMode(hConsole, &old_mode);
	SetConsoleMode(hConsole, old_mode & (~ENABLE_ECHO_INPUT));
}

void clear_partial(int x, int y, int width, int height) // Clears a section of the screen
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	COORD homeCoords = { x, y };

	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	for (int i = 0; i < height; i++)
	{
		FillConsoleOutputCharacter(hConsole, ' ', width, homeCoords, &count);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, width, homeCoords, &count);

		homeCoords.Y++;
	}

	homeCoords.Y = y;
	SetConsoleCursorPosition(hConsole, homeCoords);

	return;
}

void get_cursor(int *x, int *y)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	*x = csbi.dwCursorPosition.X;
	*y = csbi.dwCursorPosition.Y;
}

void set_cursor(int x, int y)
{
	COORD pos = { x - 1, y - 1 };

	SetConsoleCursorPosition(hConsole, pos);
}

void move_cursor(int x, int y)
{
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int cur_x = csbi.dwCursorPosition.X + x;
	int cur_y = csbi.dwCursorPosition.Y + y;
	if (cur_x < 0)
	{
		cur_x = 0;
	}
	if (cur_y < 0)
	{
		cur_y = 0;
	}
	COORD pos = {cur_x, cur_y};
	SetConsoleCursorPosition(hConsole, pos);

}

void clear_screen()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	DWORD written;
	DWORD bufSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD homeCoords = { 0, 0 }; // Home coordinates

	FillConsoleOutputCharacter(hConsole, ' ', bufSize, homeCoords, &written);
}

void clear_entire_line()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	clear_partial(0, csbi.dwCursorPosition.Y, csbi.dwSize.X, 1);
}

void clear_line_till_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	clear_partial(0, csbi.dwCursorPosition.Y, csbi.dwCursorPosition.X, 1);
}

void clear_line_from_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	clear_partial(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwSize.X, 1);
}

void clear_from_top_to_cursor()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	clear_partial(0, 0, csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void clear_from_cursor_to_bottom()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	clear_partial(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwSize.X, csbi.dwSize.Y - csbi.dwCursorPosition.Y);
}

void print(const char *s)
{
	SetConsoleOutputCP(CP_UTF8);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), s, strlen(s), NULL, NULL);
}

int getch()
{
	int ch = _getch();

	if(ch == 0 || ch == 0xE0)
	{
		ch += 255;
	}

	return ch;
}

void delay_ms(int ms)
{
    Sleep(ms);  // Sleep time is in milliseconds
}

#else

char *color_id(uint8_t cid, int l)
{
	char *esc;

	if (!l)
	{
		asprintf(&esc, "\x1B[48;5;%dm", cid);
	}
	else
	{
		asprintf(&esc, "\x1B[38;5;%dm", cid);
	}
	return esc;
}

char *rgb(int r, int g, int b, int l)
{
	char *esc;

	if (!l)
	{
		asprintf(&esc, "\x1B[48;2;%d;%d;%dm", r, g, b);
	}
	else
	{
		asprintf(&esc, "\x1B[38;2;%d;%d;%dm", r, g, b);
	}
	return esc;
}

void get_cols_rows(int *cols, int *rows)
{
	struct winsize size;
	ioctl(1, TIOCGWINSZ, &size);
	*cols = size.ws_col;
	*rows = size.ws_row;
}

void clear_entire_line()
{
	puts("\x1B[2K");
}

void clear_line_till_cursor()
{
	puts("\x1B[1K");
}

void clear_line_from_cursor()
{
	puts("\x1B[0K");
}

void hide_cursor()
{
	puts("\033[?25l");
}

void show_cursor()
{
	puts("\033[?25h");
}

void enter_alt_screen()
{
	puts("\033[?1049h\033[H");
}

void exit_alt_screen()
{
	puts("\033[?1049l");
}

void echo_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void echo_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ECHO;
	tcsetattr(1, TCSANOW, &term);
}

void canon_on()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag |= ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void canon_off()
{
	struct termios term;
	tcgetattr(1, &term);
	term.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &term);
}

void get_cursor(int *x, int *y)
{
	echo_off();
	canon_off();
	printf("\033[6n");
	scanf("\033[%d;%dR", x, y);
}

void set_cursor(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

void move_cursor(int x, int y)
{
	if (x > 0)
	{
		printf("\033[%dC", x);
	}
	else if (x < 0)
	{
		printf("\033[%dD", (x * -1));
	}

	if (y > 0)
	{
		printf("\033[%dB", y);
	}
	else if (y < 0)
	{
		printf("\033[%dA", (y * -1));
	}
}

void clear_screen()
{ 
	puts("\033[H\033[J");
}

void clear_from_top_to_cursor()
{
	puts("\x1B[1J");
}

void clear_from_cursor_to_bottom()
{
	puts("\x1B[0J");
}

void clear_partial(int x, int y, int width, int height)
{
	char *buf = (char *)calloc(width + 1, 1);
	memset(buf, 32, width);

	set_cursor(x, y);

	for (int i = 0; i < height; i++)
	{
		set_cursor(x, y + i);
		fwrite(buf, width, 1, stdout);
	}

	free(buf);
}

void print(const char *s)
{
	setlocale(LC_CTYPE, "");

	fprintf(stdout, "%s", s);
}

int getch()
{
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );

    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return ch;
}

void delay_ms(int milliseconds)
{
    usleep(milliseconds * 1000);
}

#endif

void set_cursor_style(int style)
{
    const char* sequence = "\x1b[2 q"; // default: steady block

    switch (style)
    {
        case 0: sequence = "\x1b[1 q"; break; // blinking block
        case 1: sequence = "\x1b[2 q"; break; // steady block
        case 2: sequence = "\x1b[3 q"; break; // blinking underline
        case 3: sequence = "\x1b[4 q"; break; // steady underline
        case 4: sequence = "\x1b[5 q"; break; // blinking bar
        case 5: sequence = "\x1b[6 q"; break; // steady bar
    }

    printf("%s", sequence);
    fflush(stdout);
}

void flush()
{
	fflush(stdout);
}

void beep()
{
	putchar('\a');  // BEL character
    fflush(stdout);
}

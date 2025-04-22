// Based on the Basic Terminal Control Library by Zackery Smith, 
// (https://github.com/ZackeryRSmith/tercontrol), 
// released under the GPLv3 license.


#ifndef TC_H
#define TC_H

#include <stdarg.h>
#define _GNU_SOURCE	// So the compiler doesn't complain about using 'asprintf' or 'vasprintf'
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

#ifdef _WIN32

#include <windows.h>
#include <conio.h> // For _getch() function

HANDLE hConsole = INVALID_HANDLE_VALUE, hAlternateScreen = INVALID_HANDLE_VALUE; // WinAPI structures for console
CONSOLE_SCREEN_BUFFER_INFO csbi;
CONSOLE_CURSOR_INFO cci;

#else

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32

#define TC_NRM ""

#else

#define TC_NRM "\x1B[0m" /* Normalize color */

#endif

#define TC_RED "\x1B[1;31m" /* Red */
#define TC_GRN "\x1B[1;32m" /* Green */
#define TC_YEL "\x1B[1;33m" /* Yellow */
#define TC_BLU "\x1B[1;34m" /* Blue */
#define TC_MAG "\x1B[1;35m" /* Magenta */
#define TC_CYN "\x1B[1;36m" /* Cyan */
#define TC_WHT "\x1B[1;37m" /* White */

#define TC_B_NRM "\x1B[0m"	  /* Normalize Bright Color */
#define TC_B_RED "\x1B[0;31m" /* Bright Red */
#define TC_B_GRN "\x1B[0;32m" /* Bright Green */
#define TC_B_YEL "\x1B[0;33m" /* Bright Yellow */
#define TC_B_BLU "\x1B[0;34m" /* Bright Blue */
#define TC_B_MAG "\x1B[0;35m" /* Bright Magenta */
#define TC_B_CYN "\x1B[0;36m" /* Bright Cyan */
#define TC_B_WHT "\x1B[0;37m" /* Bright White */

#define TC_BG_NRM "\x1B[40m" /* Normalize Background Color */
#define TC_BG_RED "\x1B[41m" /* Background Red */
#define TC_BG_GRN "\x1B[42m" /* Background Green */
#define TC_BG_YEL "\x1B[43m" /* Background Yellow */
#define TC_BG_BLU "\x1B[44m" /* Background Blue */
#define TC_BG_MAG "\x1B[45m" /* Background Magenta*/
#define TC_BG_CYN "\x1B[46m" /* Background Cyan */
#define TC_BG_WHT "\x1B[47m" /* Background White */

char *color_id(uint8_t cid, int l);

#ifndef _WIN32

char *rgb(int r, int g, int b, int l);

#endif

#define TC_BLD  "\x1B[1m"  /* Bold */
#define TC_DIM  "\x1B[2m"  /* Dim */
#define TC_ITAL "\x1B[3m" /* Standout (italics) */
#define TC_UNDR "\x1B[4m" /* Underline */
#define TC_BLNK "\x1B[5m" /* Blink */
#define TC_REV  "\x1B[7m"  /* Reverse */
#define TC_INV  "\x1B[8m"  /* Invisible */

void get_cols_rows(int *cols, int *rows);

void hide_cursor();
void show_cursor();

void enter_alt_screen();
void exit_alt_screen();

void echo_off();
void echo_on();

void canon_on();
void canon_off();

void clear_partial(int x, int y, int width, int height); 	// Coordinates are 1-based

void get_cursor(int *x, int *y);	// Coordinates are 1-based
void set_cursor(int x, int y);		// Coordinates are 1-based

void move_cursor(int x, int y);

void clear_screen();
void clear_entire_line();
void clear_line_till_cursor();
void clear_line_from_cursor();
void clear_from_top_to_cursor();
void clear_from_cursor_to_bottom();

void print(const char *s);

int getch();

void delay_ms(int ms);

void set_cursor_style(int style);   // May only work in more modern terminals.

void flush();

void beep();	// This may not work in modern terminals.

#endif

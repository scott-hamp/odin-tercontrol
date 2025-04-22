package tercontrol

import "core:os"

when os.OS == .Linux {
    foreign import tercontrol "libtercontrol.so"
} else {
    foreign import tercontrol "libtercontrol.a"
}

// Color strings (ANSI codes):

TC_RED     :: "\x1B[1;31m"
TC_GRN     :: "\x1B[1;32m"
TC_YEL     :: "\x1B[1;33m"
TC_BLU     :: "\x1B[1;34m"
TC_MAG     :: "\x1B[1;35m"
TC_CYN     :: "\x1B[1;36m"
TC_WHT     :: "\x1B[1;37m"
TC_NRM     :: "\x1B[0m"

TC_BLD     :: "\x1B[1m"
TC_DIM     :: "\x1B[2m"
TC_ITAL    :: "\x1B[3m"
TC_UNDR    :: "\x1B[4m"
TC_BLNK    :: "\x1B[5m"
TC_REV     :: "\x1B[7m"
TC_INV     :: "\x1B[8m"

foreign tercontrol {

    // Get the ID for a color.
    color_id                        :: proc(u8, int) -> cstring ---
    
    // Get the ANSI code for an rgbl color, (Linux only).
    when os.OS == .Linux {
        rgb                         :: proc(r: int, g: int, b: int, l: int) -> cstring ---
    }

    // Hide the cursor.
    hide_cursor                     :: proc() ---

    // Show the cursor.
    show_cursor                     :: proc() ---
    
    // Enter an alternate terminal screen.
    enter_alt_screen                :: proc() ---

    // Exit the alternate terminal screen.
    exit_alt_screen                 :: proc() ---

    // Turn on line-buffered mode.
    canon_on                        :: proc() ---

    // Turn off line-buffered mode.
    canon_off                       :: proc() ---

    // Turn on keyboard input echo.
    echo_on                         :: proc() ---
    
    // Turn off keyboard input echo.
    echo_off                        :: proc() ---

    // Get the number of columns and rows of the terminal.
    get_cols_rows                   :: proc(cols: ^int, rows: ^int) ---
    
    // Clear the entire terminal screen.
    clear_screen                    :: proc() ---
    
    // Clear the entire line of the cursor position.
    clear_entire_line               :: proc() ---
    
    // Clear the line until the cursor position.
    clear_line_till_cursor          :: proc() ---
    
    // Clear the line following the cursor position.
    clear_line_from_cursor          :: proc() ---
    
    // Clear part of the screen. Coordinates are 1-based.
    clear_partial                   :: proc(x: int, y: int, width: int, height: int) ---
    
    // Clear from the top of the screen to the cursor.
    clear_from_top_to_cursor        :: proc() ---
    
    // Clear from the cursor to the bottom of the screen.
    clear_from_cursor_to_bottom     :: proc() ---

    // Get cursor position. Coordinates are 1-based.
    get_cursor                      :: proc(x: ^int, y: ^int) ---
    
    // Set cursor position. Coordinates are 1-based.
    set_cursor                      :: proc(x: int, y: int) ---

    // Set the style of the cursor. Style is an integer from 0 - 5.
    // 0: blinking block, 
    // 1: steady block, 
    // 2: blinking underline, 
    // 3: steady underline, 
    // 4: blinking bar, 
    // 5: steady bar.
    // May only work in more modern terminals.
    set_cursor_style                :: proc(style: int) ---
    
    // Move the cursor relative to its current position.
    move_cursor                     :: proc(x: int, y: int) ---

    // Print a string at the current cursor position.
    print                           :: proc(s: cstring) ---

    // Flush the output buffer.
    flush                           :: proc() ---

    // Get a keypress.
    getch                           :: proc() -> int ---

    // Delay for a number of milliseconds.
    delay_ms                        :: proc(ms: int) ---

    // Play a system beep. May not work in modern terminals.
    beep                            :: proc() ---
}
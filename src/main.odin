package main

import "core:c"
import "core:unicode/utf16"
import "core:fmt"
import "core:strings"
import "core:strconv"
import tc "tercontrol"

main :: proc() {

    tc.clear_screen()
    tc.hide_cursor()
    tc.set_cursor(1, 1)

    greeting := "☺︎ Hello, World! ♥︎\n"

    for c in greeting {

        cc := fmt.aprintf("%c", c)
        cstr := strings.clone_to_cstring(cc)
        tc.print(cstr)
        tc.flush()
        delete(cstr)

        tc.delay_ms(100)
    }

    tc.delay_ms(500)

    cols, rows : int
    tc.get_cols_rows(&cols, &rows)

    str1 := fmt.aprintf("%scols: %d, rows: %d%s", tc.TC_RED, cols, rows, tc.TC_NRM)
    cstr1 := strings.clone_to_cstring(str1)
    defer delete(cstr1)
    tc.print(cstr1)

    tc.delay_ms(500)

    tc.set_cursor_style(0)
    tc.show_cursor()

    key := -1

    for {

        tc.set_cursor(1, 3)

        str2 := fmt.aprintf("%sKey: %d (ESC to exit)\n", tc.TC_MAG, key)
        cstr2 := strings.clone_to_cstring(str2)
        defer delete(cstr2)
        tc.print(cstr2)

        key = tc.getch()

        if key == 27 {
            break
        }
    }
    
}
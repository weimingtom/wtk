
// This is free and unencumbered software released into the public domain.  

// Anyone is free to copy, modify, publish, use, compile, sell, or           
// distribute this software, either in source code form or as a compiled    
// binary, for any purpose, commercial or non-commercial, and by any        
// means.                                                                   

// In jurisdictions that recognize copyright laws, the author or authors    
// of this software dedicate any and all copyright interest in the           
// software to the public domain. We make this dedication for the benefit    
// of the public at large and to the detriment of our heirs and              
// successors. We intend this dedication to be an overt act of               
// relinquishment in perpetuity of all present and future rights to this     
// software under copyright law.                                             

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF        
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.    
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR         
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     
// OTHER DEALINGS IN THE SOFTWARE.                                           

// For more information, please refer to <http://unlicense.org/>       

// Author: Michael Williams (mtwilliams)        


#ifndef __WTK_CONTROLS_H_
#define __WTK_CONTROLS_H_

#include "_wtk_windows.h"
#include "_wtk_font.h"
#include "_wtk_image.h"

#include <wtk/wtk_align.h>
#include <wtk/wtk_gdi.h>
#include <wtk/wtk_mouse.h>
#include <wtk/wtk_keyboard.h>
#include <wtk/wtk_textbox.h>

struct wtk_control {
    // Shared:
    wtk_control_type type;
    void* user_ptr;
    struct wtk_font* font;
    unsigned hidden : 1;
    unsigned auto_fill : 1;
    unsigned resizable : 1;
    unsigned reserved : 5;
    int margin_top, margin_left, margin_bottom, margin_right;

    // Callbacks:
    int (WTK_API *on_create_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_destroy_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_layout_changed_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_paint_callback)( struct wtk_control* control, wtk_event event, struct wtk_gdi* gdi );

    int (WTK_API *on_pressed_callback)( struct wtk_control* control, wtk_event event, wtk_mouse_btn mouse_btn, int x, int y );
    int (WTK_API *on_released_callback)( struct wtk_control* control, wtk_event event, wtk_mouse_btn mouse_btn, int x, int y );
    int (WTK_API *on_clicked_callback)( struct wtk_control* control, wtk_event event );

    int (WTK_API *on_mouse_moved_callback)( struct wtk_control* control, wtk_event event, int x, int y );
    int (WTK_API *on_mouse_scrolled_callback)( struct wtk_control* control, wtk_event event, int scroll );

    int (WTK_API *on_key_pressed_callback)( struct wtk_control* control, wtk_event event, wtk_key_code key_code, unsigned int special_keys );
    int (WTK_API *on_key_released_callback)( struct wtk_control* control, wtk_event event, wtk_key_code key_code, unsigned int special_keys );

    // Platform specific:
    HWND hWnd;
};

struct wtk_menu {
    wtk_control control;

    // Shared:
    struct wtk_control* window;

    // Platform specific:
    HMENU hMenu;
};

struct wtk_menu_item {
    wtk_control control;

    // Shared:
    const char* text;
    struct wtk_control* parent;

    // Platform specific;
    HMENU hMenu;
};

struct wtk_window {
    wtk_control control;

    // Shared:
    const char* title;
    struct wtk_icon* icons[2];
    struct wtk_menu* menu;

    // Callbacks:
    int (WTK_API *on_close_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_minimized_callback)( struct wtk_control* control, wtk_event event, int width, int height );
    int (WTK_API *on_maximized_callback)( struct wtk_control* control, wtk_event event, int width, int height );
    int (WTK_API *on_resized_callback)( struct wtk_control* control, wtk_event event, int width, int height );
};

struct wtk_label {
    wtk_control control;

    // Shared:
    const char* text;
    wtk_align text_align;
};

struct wtk_frame {
    wtk_control control;

    // Shared:
    const char* text;
};

struct wtk_button {
    wtk_control control;

    // Shared:
    const char* text;
    struct wtk_icon* icon;
    wtk_align text_h_align;
    wtk_align text_v_align;
};

struct wtk_checkbox {
    wtk_control control;

    // Shared:
    const char* text;
    struct wtk_icon* icon;
    wtk_align text_align;

    // Callbacks:
    int (WTK_API *on_value_changed_callback)( struct wtk_control* control, wtk_event event );
};

struct wtk_textbox {
    wtk_control control;

    // Shared:
    const char* text_buffer;
    wtk_textbox_type type;
    wtk_align text_align;
    int max_len;

    // Callbacks:
    int (WTK_API *on_value_changed_callback)( struct wtk_control* control, wtk_event event );
};

struct wtk_listbox {
    wtk_control control;

    // Shared:
    const char* text_buffer;

    // Callbacks:
    int (WTK_API *on_selection_changed_callback)( struct wtk_control* control, wtk_event event, unsigned int );
};

struct wtk_listview {
    wtk_control control;

    // Shared:
    struct wtk_image_list* img_list;

    // Platform specific:
    unsigned int num_columns;
    unsigned int num_rows;
};

struct wtk_combobox {
    wtk_control control;

    // Shared:
    const char* text_buffer;

    // Callbacks:
    int (WTK_API *on_selection_changed_callback)( struct wtk_control* control, wtk_event event, unsigned int );
};

#endif // __WTK_CONTROLS_H_

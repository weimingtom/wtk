
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


#include <wtk/wtk_app.h>

#include "_wtk_windows.h"

#include <wtk/wtk_control_types.h>
#include <wtk/wtk_mm.h>

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

typedef int (WTK_API *wtk_control_init_func)();

extern int WTK_API wtk_control_init();
extern int WTK_API wtk_window_init();
extern int WTK_API wtk_menu_init();
extern int WTK_API wtk_menu_item_init();
extern int WTK_API wtk_label_init();
extern int WTK_API wtk_frame_init();
extern int WTK_API wtk_button_init();
extern int WTK_API wtk_checkbox_init();
extern int WTK_API wtk_textbox_init();
extern int WTK_API wtk_listbox_init();
extern int WTK_API wtk_listview_init();
extern int WTK_API wtk_combobox_init();

static const wtk_control_init_func _control_init_funcs[WTK_CONTROL_TYPE_COUNT - 1] = {
    &wtk_control_init,
    &wtk_window_init,
    &wtk_menu_init,
    &wtk_menu_item_init,
    &wtk_label_init,
    &wtk_frame_init,
    &wtk_button_init,
    &wtk_checkbox_init,
    &wtk_textbox_init,
    &wtk_listbox_init,
    &wtk_listview_init,
    &wtk_checkbox_init,
    &wtk_combobox_init,
};

static void WTK_API wtk_enable_visual_styles()
{
    DWORD dwVersion;
    DWORD dwMinorVersion;
    DWORD dwMajorVersion;

    dwVersion      = GetVersion();
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));

    if( dwMajorVersion > 5 || (dwMajorVersion == 5 && dwMinorVersion >= 1) ) {
        const INITCOMMONCONTROLSEX iccx = {
            sizeof(INITCOMMONCONTROLSEX),
            ICC_STANDARD_CLASSES |
            ICC_LISTVIEW_CLASSES |
            ICC_PROGRESS_CLASS |
            ICC_TAB_CLASSES |
            ICC_TREEVIEW_CLASSES
        };
        
        InitCommonControlsEx(&iccx);
    }
}

int WTK_API wtk_init( const wtk_allocator* allocator )
{
    uint32_t i;

    WTK_ASSERT(allocator);

    wtk_set_allocator(allocator);
    wtk_enable_visual_styles();

    for( i = 0; i < WTK_CONTROL_TYPE_COUNT - 1; ++i ) {
        if( !_control_init_funcs[i]() ) return FALSE;
    }

    return TRUE;
}

static wtk_tick_callback on_tick_callback = NULL;

void WTK_API wtk_set_tick_callback( wtk_tick_callback tick_callback )
{
    on_tick_callback = tick_callback;
}

int WTK_API wtk_run_app()
{
    MSG msg;

    while( TRUE ) {
        while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if( msg.message == WM_QUIT ) return EXIT_SUCCESS;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if( on_tick_callback ) if( !on_tick_callback() ) PostQuitMessage(0);
    }

    return EXIT_FAILURE;
}

void WTK_API wtk_quit()
{
    PostQuitMessage(0);
}

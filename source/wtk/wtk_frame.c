
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


#include <wtk/wtk_frame.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"
#include "_wtk_msgs.h"
#include "_wtk_layout.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_font.h>

static LRESULT CALLBACK wtk_frame_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_frame_init()
{
    return TRUE;
}

struct wtk_frame* WTK_API wtk_frame_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_frame* frame = NULL;
    HWND hWnd;

    WTK_ASSERT(parent);

    hWnd = CreateWindowExA(0, "BUTTON", NULL, BS_GROUPBOX | WS_VISIBLE | WS_CHILD, x, y, width, height, parent->hWnd, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    frame = wtk_alloc(sizeof(struct wtk_frame));
    memset((void*)frame, 0, sizeof(struct wtk_frame));
    frame->control.type = WTK_CONTROL_TYPE(Frame);
    frame->control.hWnd = hWnd;
    frame->control.font = wtk_font_default();

    SetPropA(hWnd, "_wtk_old_proc", (HANDLE)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&wtk_frame_proc));
    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)frame);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)frame->control.font->hFont, TRUE);
    PostMessage(hWnd, WTK_ON_CREATE, 0, 0);
    return frame;
}

static BOOL CALLBACK wtk_on_layout_change_proc( HWND hWnd, LPARAM lParam ) {
    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
    return TRUE;
}

static LRESULT CALLBACK wtk_frame_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_control* control = (struct wtk_control*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_frame* frame = (struct wtk_frame*)control;
    if( !control ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WTK_ON_CREATE: {
            HWND hWndParent = GetParent(hWnd);
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
            if( hWndParent ) SendMessage(hWndParent, WTK_ON_LAYOUT_CHANGED, 0, 0);
        } break;

        case WTK_ON_LAYOUT_CHANGED: {
            wtk_on_layout_changed(control);
            EnumChildWindows(hWnd, &wtk_on_layout_change_proc, 0);
            if( control->on_layout_changed_callback ) control->on_layout_changed_callback(control, WTK_EVENT(OnLayoutChanged));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            wtk_free(frame);
        } break;

        default: {
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}

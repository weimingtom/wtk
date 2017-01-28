
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


#ifndef _WTK_COMBOBOX_H_
#define _WTK_COMBOBOX_H_

#include <wtk/wtk_control.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_combobox;
typedef struct wtk_combobox wtk_combobox;

extern WTK_EXPORT struct wtk_combobox* WTK_API wtk_combobox_create( int x, int y, int width, int height, struct wtk_control* parent );

typedef int wtk_combobox_item;

extern WTK_EXPORT wtk_combobox_item WTK_API wtk_combobox_insert( struct wtk_combobox* combobox, const char* text, void* user_ptr );
extern WTK_EXPORT void WTK_API wtk_combobox_remove( struct wtk_combobox* combobox, wtk_combobox_item id );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_COMBOBOX_H_

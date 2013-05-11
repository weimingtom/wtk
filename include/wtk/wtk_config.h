// This file is part of the minimalistic Windowing Toolkit.
//
// Copyright (C) 2012 Michael Williams <devbug@bitbyte.ca>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _WTK_CONFIG_H_
#define _WTK_CONFIG_H_

#include <wtk/wtk_foundation.h>

// Uncomment this if you're linking to this library dynamically.
// #define WTK_DYNAMICALLY_LINKED 1

#if defined(WTK_DYNAMICALLY_LINKED)
  #if defined(WTK_BUILDING)
    #define WTK_EXPORT FOUNDATION_DYNAMIC_EXPORT
  #else
    #define WTK_EXPORT FOUNDATION_DYNAMIC_IMPORT
  #endif
#else
  #define WTK_EXPORT
#endif

#define WTK_API FOUNDATION_CDECL

#endif // _WTK_CONFIG_H_

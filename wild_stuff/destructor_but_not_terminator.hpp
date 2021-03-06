// Copyright (c) 2012, Evgeny Panasyuk

// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// e-mail: E?????[dot]P???????[at]gmail.???

#ifndef DESTRUCTOR_BUT_NOT_TERMINATOR_HPP
#define DESTRUCTOR_BUT_NOT_TERMINATOR_HPP

#include <stack_unwinding.hpp>

// Note: function-try-block for "destructor but not terminator" does not catch exceptions from bases or members

// Put it into access specifier where you want to place your destructor.
// After this macro, access specifier is set to private
#define DESTRUCTOR_BUT_NOT_TERMINATOR(TYPE) \
    DESTRUCTOR_BUT_NOT_TERMINATOR_IMPL(TYPE) \
    private: \
    stack_unwinding::unwinding_indicator stack_unwinding_indicator_##TYPE; \
    void destructor_not_terminator_##TYPE()

// Put it into access specifier where you want to place your destructor.
// After this macro, access specifier is set to private
#define DESTRUCTOR_BUT_NOT_TERMINATOR_OUF_OF_CLASS_DECL(TYPE) \
    ~TYPE(); \
    private: \
    stack_unwinding::unwinding_indicator stack_unwinding_indicator_##TYPE; \
    void destructor_not_terminator_##TYPE();

// Note: defines non-inline functions
#define DESTRUCTOR_BUT_NOT_TERMINATOR_OUT_OF_CLASS_DEF(TYPE) \
    TYPE:: DESTRUCTOR_BUT_NOT_TERMINATOR_IMPL(TYPE) \
    void TYPE::destructor_not_terminator_##TYPE()


// internal details:
#define DESTRUCTOR_BUT_NOT_TERMINATOR_IMPL(TYPE) \
    ~TYPE() \
    { \
        if(stack_unwinding_indicator_##TYPE.unwinding()) \
            { try { destructor_not_terminator_##TYPE(); } catch(...) {} } \
        else \
            destructor_not_terminator_##TYPE(); \
    } \

#endif

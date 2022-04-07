//
// Created by Andromeda on 19/03/2022.
//

#ifndef SINGULARITY_CONSOLE_H
#define SINGULARITY_CONSOLE_H

#include <cstdarg>
#include <cstdio>
#include "String.h"

namespace sy
{
    void static Log( const char* _string ) { printf( _string); }
    void static Log( const char* _string, va_list _vars ) { vprintf( _string, _vars); }
}

#endif //SINGULARITY_CONSOLE_H

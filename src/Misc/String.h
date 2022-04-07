//
// Created by Andromeda on 19/03/2022.
//

#ifndef SINGULARITY_STRING_H
#define SINGULARITY_STRING_H


#include <cstdarg>

class String
{

public:

    String() = default;
    String(const char* _string) : m_string( std::string( _string ) ) {}
    String(const char* _format, ...) { va_list args; va_start(args, _format); Format( _format, args); va_end(args); }

    const char* ToChar() { return m_string.c_str(); }

private:

    void Format( const char* _format, va_list _args )
    {
        char buffer[256];
        size_t string_size = vsnprintf(buffer, 256, _format, _args);
        m_string = buffer;
        m_string.resize(string_size);
    }

    std::string m_string = "";

};

#endif //SINGULARITY_STRING_H

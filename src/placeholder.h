#pragma once

#include <string>

struct string_t
{
public:
    string_t() = default;
    string_t( std::string map ) : Map( map ) {}
    std::string Map;
};

inline const char* STRING( string_t s )
{
    return s.Map.c_str();
}

class CEngine
{
public:
    CEngine() = default;
    string_t mapname;
};

#include "CConfigContext.hpp"

#include "placeholder.h"

CEngine* gpGlobals;

int main()
{
    gpGlobals = new CEngine();

    gpGlobals->mapname = string_t( "hl_c05_a1" );

    g_ConfigurationContext.MapInit();

    return 0;
}

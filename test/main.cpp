#include <windows.h>

typedef void (*PluginInitFunc)();

int main()
{
    HMODULE dllHandle = LoadLibraryA( "LimitlessPotential.dll" );

    GetProcAddress( dllHandle, "main" )();

    FreeLibrary( dllHandle );

    return 0;
}

#include "main.hpp"

extern "C" __declspec(dllexport) void main()
{
    g_PluginManager.OnInitialize();

    // New map started
    g_ConfigurationContext.OnMapInit();
    CALL_FUNCTION( OnMapInit );
}

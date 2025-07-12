#include "main.hpp"

extern "C" __declspec(dllexport) void main()
{
    g_PluginManager.OnInitialize();
    g_PluginManager.OnMapInit();
}

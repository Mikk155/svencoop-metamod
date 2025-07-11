#include "CConfigContext.hpp"
#include "CBasePlugin.h"

#include "placeholder.h"
CEngine* gpGlobals;

int main()
{
    gpGlobals = new CEngine();

    gpGlobals->mapname = string_t( "hl_c05_a1" );

    for( CBasePlugin* plugin : CBasePlugin::GetPlugins() )
    {
        g_ConfigurationContext.CreateContext( plugin->GetName() );
        plugin->OnInitialize();
    }

    g_ConfigurationContext.OnMapInit();

    for( CBasePlugin* plugin : CBasePlugin::GetPlugins() ) {
        // How to create a macro to pass only the function name and possible args?
        if( plugin->IsActive() )
            plugin->OnMapInit();
    }

    return 0;
}

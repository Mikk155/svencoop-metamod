#include "main.hpp"

SectionContext* CBasePlugin::GetConfig()
{
    return g_ConfigurationContext.GetContext( GetName() );
}

const bool CBasePlugin::IsActive()
{
    return g_ConfigurationContext.GetContext( GetName() )->IsActive;
}

void CBasePlugin::__Register__( CBasePlugin* plugin )
{
    if( PLUGIN( plugin->GetName() ) == nullptr )
    {
        __Plugins__().push_back( plugin );
    }
    else
    {
        fmt::print( "Already registered a plugin with name {}", plugin->GetName() );
        delete plugin;
    }
}

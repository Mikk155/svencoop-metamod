#include "main.hpp"

void CPluginManager::__Register__( CBasePlugin* plugin )
{
    if( GetPlugin( plugin->GetName() ) == nullptr )
    {
        m_Plugins.push_back( plugin );
    }
    else
    {
        fmt::print( "Already registered a plugin with name {}\n", plugin->GetName() );
        delete plugin;
    }
}

CBasePlugin* CPluginManager::GetPlugin( std::string_view name )
{
    if( auto it = std::find_if( m_Plugins.begin(), m_Plugins.end(), [&]( CBasePlugin* context )
        { return std::string_view( context->GetName() ) == name; } ); it != m_Plugins.end() ) {
            return *it;
    }
    return nullptr;
}

void CPluginManager::OnInitialize()
{
    for( CBasePlugin* plugin : GetPlugins() )
    {
        g_ConfigurationContext.CreateContext( plugin->GetName() );
        fmt::print( "{}::OnInitialize\n", GetName() );
        plugin->OnInitialize();
    }
}

void CPluginManager::OnMapInit()
{
    g_ConfigurationContext.OnMapInit();

    for( CBasePlugin* plugin : GetPlugins() )
    {
        fmt::print( "{}::OnMapInit\n", GetName() );
        plugin->OnInitialize();
    }
}

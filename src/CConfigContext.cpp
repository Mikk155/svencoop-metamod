//-TODO Game's FileSystem
#include <fstream>

#include "main.hpp"

void CConfigContext::CreateContext( const char* name )
{
    auto it = std::find_if( m_contexts.begin(), m_contexts.end(), [&]( const auto& context )
        { return context.Name == name; } );

    if( it != m_contexts.end() )
    {
        fmt::print( "Plugin tried to register a existent config context with name \"{}\"\n", name );
        return;
    }

    SectionContext PluginContext = SectionContext( name );

    fmt::print( "Registered section context for \"{}\"\n", name );

    m_contexts.push_back( std::move( PluginContext ) );
}

void CConfigContext::OnMapInit()
{
    if( !LoadJsonFile( "../../lp_configuration.json" ) )
    {
        fmt::print( "Failed to read the main config file.\n" );
        return;
    }

#if 0
    if( std::string mapname = fmt::format( "maps/{}.json", STRING( gpGlobals->mapname ) ); LoadJsonFile( mapname ) )
#endif
    if( std::string mapname = fmt::format( "../../test/{}.json", "test" ); LoadJsonFile( mapname ) )
    {
        fmt::print( "Got a custom config for map \"{}\"\n", mapname );
    }
}

SectionContext* CConfigContext::GetContext( std::string_view name )
{
    auto it = std::find_if( m_contexts.begin(), m_contexts.end(), [&]( const auto& context )
        { return context.Name == name; } );

    if( it != m_contexts.end() )
    {
        return &(*it);
    }

    fmt::print( "Unexistent context name \"{}\"\n", name );

    return nullptr;
}

bool CConfigContext::LoadJsonFile( const std::string& filename )
{
    // Yo si usaria FileSystem
    std::ifstream file( filename );

    if( !file.is_open() )
        return false;

    json config;
    file >> config;

    for( const auto& section : config.items() )
    {
        std::string ContextName = section.key();

        const json& ContextData = section.value();

        if( !ContextData.is_object() )
        {
            fmt::print( "Expected object type for context name {}\n", ContextName );
            continue;
        }

        SectionContext* ContextSection = GetContext( ContextName );

        if( ContextSection == nullptr )
        {
            fmt::print( "Unknown context section {}\n", ContextName );
            continue;
        }

        ContextSection->IsActive = ContextData.value( "active", false );

        fmt::print( "Context is {} \n", ContextSection->IsActive ? "Active" : "Disabled" );
    }

    return true;
}

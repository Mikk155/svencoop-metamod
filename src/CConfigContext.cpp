#include <fstream>
#include <iostream>
#include <sstream>

#include "main.hpp"

void CConfigContext::CreateContext( const char* name )
{
    auto it = std::find_if( m_contexts.begin(), m_contexts.end(), [&]( const auto& context )
        { return context.Name == name; } );

    if( it != m_contexts.end() )
    {
        std::cout << "Plugin tried to register a existent config context with name " << name << std::endl;
        return;
    }

    SectionContext PluginContext = SectionContext( name );

    std::cout << "Registered section context for " << name << std::endl;

    m_contexts.push_back( std::move( PluginContext ) );
}

void CConfigContext::OnMapInit()
{
    if( !LoadJsonFile( "../../lp_configuration.json" ) )
    {
        std::cout << "Failed to read the main config file." << std::endl;
        return;
    }

#if 0
    if( std::string mapname = fmt::format( "maps/{}.json", STRING( gpGlobals->mapname ) ); LoadJsonFile( mapname ) )
#endif
    if( std::string mapname = fmt::format( "../../test/{}.json", "test" ); LoadJsonFile( mapname ) )
    {
        std::cout << "Got a custom config for map " << mapname << std::endl;
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

    std::cout << "Unexistent context name " << name << std::endl;

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
            std::cout << "Expected object type for context name " << ContextName << std::endl;
            continue;
        }

        SectionContext* ContextSection = GetContext( ContextName );

        if( ContextSection == nullptr )
        {
            std::cout << "Unknown context section " << ContextName << std::endl;
            continue;
        }

        ContextSection->IsActive = ContextData.value( "active", false );

        if( ContextSection->IsActive )
        {
            std::cout << "Context " << ContextName << " Is active" << std::endl;
        }
        else
        {
            std::cout << "Context " << ContextName << " Is disabled" << std::endl;
        }
    }

    return true;
}

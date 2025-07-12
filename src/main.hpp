#pragma once

#include "extdll.h"
#include "eiface.h"
#include "enginecallback.h"
#include "util.h"

#include <string>
#include <vector>
#include <variant>

#include <fmt/core.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct SectionContext
{
    SectionContext( std::string _Name ) : Name(_Name) {}

    const std::string Name;
    
    bool IsActive{false};

    std::unordered_map<std::string, std::variant<std::string, float>> Variables;
};

class CConfigContext
{
public:

    void OnMapInit();

    bool LoadJsonFile( const std::string& filename );

    SectionContext* GetContext( std::string_view name );

    void CreateContext( const char* name );

private:
    std::vector<SectionContext> m_contexts;
};

inline CConfigContext g_ConfigurationContext;

class CBasePlugin
{
public:
    CBasePlugin() = default;

    /**
    *   @brief Must be a unique name. This is used for the json configuration context.
    */
    virtual const char* GetName() = 0;

    /**
    *   @brief Called when the plugin has just been initialized
    */
    virtual void OnInitialize() {
        fmt::print( "{}::OnInitialize\n", GetName() );
    };

    /**
    *   @brief Called every time a map starts
    */
    virtual void OnMapInit() {
        fmt::print( "{}::OnMapInit\n", GetName() );
    };

    /**
    *   @brief Get the config context for this plugin
    */
    SectionContext* GetConfig();

    /**
    *   @brief Return whatever this plugin is active on this map
    */
    const bool IsActive();

    static void __Register__( CBasePlugin* plugin );

    static const std::vector<CBasePlugin*>& __GetPlugins__() {
        return __Plugins__();
    };

private:
    static std::vector<CBasePlugin*>& __Plugins__() {
        static std::vector<CBasePlugin*> reg;
        return reg;
    }
};

/**
*   @brief Get a list of all plugins
*/
inline static const std::vector<CBasePlugin*>& PLUGINS() {
    return CBasePlugin::__GetPlugins__();
}

/**
*   @brief Get a plugin by name
*/
inline static const CBasePlugin* PLUGIN( std::string_view name )
{
    const std::vector<CBasePlugin*>& plugins = PLUGINS();

    if( auto it = std::find_if( plugins.begin(), plugins.end(), [&]( CBasePlugin* context )
        { return std::string_view( context->GetName() ) == name; } ); it != plugins.end() ) {
            return *it;
    }
    return nullptr;
}

/**
*   @brief Register a class based on CBasePlugin
*/
#define REGISTER_PLUGIN( CLASS ) static CLASS _##CLASS##_instance; static struct CLASS##_reg { \
    CLASS##_reg() { CBasePlugin::__Register__(&_##CLASS##_instance); } } _##CLASS##_reg_stancein;

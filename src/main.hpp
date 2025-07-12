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

enum HookCode : int
{
    // Continue hook execution
    Continue = 0,

    // Break the iteration and stop calling other classes on this pugin
    Break
};

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
    virtual void OnInitialize() {};

    /**
    *   @brief Called every time a map starts
    */
    virtual HookCode OnMapInit() { return HookCode::Continue; };

    /**
    *   @brief Get the config context for this plugin
    */
    SectionContext* GetConfig();

    /**
    *   @brief Return whatever this plugin is active on this map
    */
    const bool IsActive();
};

class CPluginManager
{
public:

    void __Register__( CBasePlugin* plugin );

    /**
    *   @brief Get a list of all plugins
    */
    const std::vector<CBasePlugin*>& GetPlugins() {
        return m_Plugins;
    };

    /**
    *   @brief Get a plugin by name
    */
    CBasePlugin* GetPlugin( std::string_view name );

    void OnInitialize();

private:

    std::vector<CBasePlugin*> m_Plugins;
};

inline CPluginManager g_PluginManager;

/**
*   @brief Register a class based on CBasePlugin
*/
#define REGISTER_PLUGIN( CLASS ) static CLASS _##CLASS##_instance; static struct CLASS##_reg { \
    CLASS##_reg() { g_PluginManager.__Register__(&_##CLASS##_instance); } } _##CLASS##_reg_stancein;

#define CALL_FUNCTION( fnName, ... ) do { \
    for( CBasePlugin* plugin : g_PluginManager.GetPlugins() ) { \
        fmt::print( "{}::" #fnName "\n", plugin->GetName() ); \
        HookCode code = plugin->fnName( __VA_ARGS__ ); \
        if( code == HookCode::Break ) { break; } \
    } } while(false)

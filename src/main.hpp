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

    virtual const char* GetName() = 0;

    virtual void OnInitialize() {};
    virtual void OnMapInit() {};

    SectionContext* GetConfig() {
        return g_ConfigurationContext.GetContext( GetName() );
    }

    bool IsActive() {
        return GetConfig()->IsActive;
    }

    static void __Register__( CBasePlugin* plugin ) {
        Plugins().push_back( plugin );
    }

    static const std::vector<CBasePlugin*>& GetPlugins() {
        return Plugins();
    }

private:
    static std::vector<CBasePlugin*>& Plugins() {
        static std::vector<CBasePlugin*> reg;
        return reg;
    }
};

#define REGISTER_PLUGIN( CLASS ) static CLASS _##CLASS##_instance; static struct CLASS##_reg { \
    CLASS##_reg() { CBasePlugin::__Register__(&_##CLASS##_instance); } } _##CLASS##_reg_stancein;

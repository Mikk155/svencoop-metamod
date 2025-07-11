#include "CConfigContext.hpp"

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

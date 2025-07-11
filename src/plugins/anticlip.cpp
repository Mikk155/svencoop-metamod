#include "../CBasePlugin.h"
#include <iostream>

class CPluginAntiClip : public CBasePlugin
{
    virtual const char* GetName() {
        return "anticlip";
    }

    virtual void OnInitialize() {
        std::cout << GetName() << "::OnInitialize" << std::endl;
    };

    virtual void OnMapInit() {
        std::cout << GetName() << "::OnMapInit" << std::endl;
    };
};

REGISTER_PLUGIN( CPluginAntiClip )

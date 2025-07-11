#include "../main.hpp"

class CPluginAntiClip : public CBasePlugin
{
    const char* GetName() override {
        return "anticlip";
    }
};

REGISTER_PLUGIN( CPluginAntiClip )

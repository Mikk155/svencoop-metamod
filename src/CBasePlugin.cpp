#include "main.hpp"

SectionContext* CBasePlugin::GetConfig()
{
    return g_ConfigurationContext.GetContext( GetName() );
}

const bool CBasePlugin::IsActive()
{
    return g_ConfigurationContext.GetContext( GetName() )->IsActive;
}

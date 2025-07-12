#include <extdll.h>
#include <meta_api.h>
#include "sdk_util.h"

plugin_info_t Plugin_info = {
    META_INTERFACE_VERSION,
    "Limitless Potential",
    "1.0",
    "2025",
    "Not the Gaftherman",
    "discord.gg/2ErNUQh6fE",
    "LP",
    PT_ANYTIME,
    PT_STARTUP,
};

C_DLLEXPORT int Meta_Query( char *interfaceVersion, plugin_info_t **plinfo, mutil_funcs_t *pMetaUtilFuncs )
{
    *plinfo = &Plugin_info;
    return 0;
}

C_DLLEXPORT int Meta_Attach( PLUG_LOADTIME now, META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, gamedll_funcs_t *pGamedllFuncs )
{
    return 0;
}

C_DLLEXPORT int Meta_Detach( PLUG_LOADTIME now, PL_UNLOAD_REASON reason )
{
    return 0;
}

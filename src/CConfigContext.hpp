#pragma once

#include <string>
#include <vector>
#include <variant>

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

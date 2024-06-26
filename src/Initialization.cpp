#include "Config.h"
#include "Global.h"

GMLIB::Files::JsonConfig* Config = nullptr;

namespace ConfigData {
std::string                                  mFormat;
std::unordered_map<std::string, std::string> mDimMap;
} // namespace ConfigData

void initConfig() {
    Config = new GMLIB::Files::JsonConfig("./plugins/ChatFormatter/config/config.json", defaultConfig);
    Config->init();
    ConfigData::mFormat =
        Config->getValue<std::string>({"ChatFormat"}, "[%chatformatter_dimension%] {player} >> {message}");
    auto list = Config->getValue({"DimensionNameMap"}, nlohmann::json::object());
    for (nlohmann::json::iterator it = list.begin(); it != list.end(); ++it) {
        ConfigData::mDimMap[it.key()] = it.value();
    }
}

std::string getDimensionName(Player* pl) {
    if (pl) {
        auto dimName = ((GMLIB_Player*)pl)->getDimensionName();
        if (ConfigData::mDimMap.count(dimName)) {
            return ConfigData::mDimMap[dimName];
        }
        return dimName;
    }
    return "unknown";
}

void registerPAPI() {
    GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
        "chatformatter_dimension",
        [](Player* pl) { return getDimensionName(pl); },
        "ChatFormatter"
    );
}

void unregisterPAPI() { GMLIB::Server::PlaceholderAPI::unRegisterPlaceholder("chatformatter_dimension"); }

void initPlugin() { initConfig(); }

#include "Config.h"
#include "Global.h"

GMLIB::Files::JsonConfig* Config = nullptr;

namespace ConfigData {
std::string                          mFormat;
std::unordered_map<int, std::string> mDimMap;
} // namespace ConfigData

void initConfig() {
    Config = new GMLIB::Files::JsonConfig("./plugins/ChatFormatter/config/config.json", defaultConfig);
    Config->init();
    ConfigData::mFormat =
        Config->getValue<std::string>({"ChatFormat"}, "[%chatformatter_dimension%] {player} >> {message}");
    auto list = Config->getValue({"DimensionIdMap"}, nlohmann::json::object());
    for (nlohmann::json::iterator it = list.begin(); it != list.end(); ++it) {
        ConfigData::mDimMap[it.value()] = it.key();
    }
}

std::string getDimensionName(Player* pl) {
    if (pl) {
        auto dimid = pl->getDimensionId();
        if (ConfigData::mDimMap.count(dimid)) {
            return ConfigData::mDimMap[dimid];
        }
        return pl->getDimension().mName;
    }
    return "unkown";
}

void registerPAPI() {
    GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
        "chatformatter_dimension",
        [](Player* pl) { return getDimensionName(pl); },
        "ChatFormatter"
    );
}

void initPlugin() {
    initConfig();
    registerPAPI();
}

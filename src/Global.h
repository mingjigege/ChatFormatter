#pragma once
#include <include_all.h>

#define PLUGIN_NAME "ChatFormatter"

extern ll::Logger logger;

namespace ConfigData {
extern std::string                                  mFormat;
extern std::unordered_map<std::string, std::string> mDimMap;
extern std::unordered_set<std::string>              mBan;
} // namespace ConfigData

extern void initPlugin();
extern void listenEvent();
extern void removeListener();
extern void registerPAPI();
extern void unregisterPAPI();

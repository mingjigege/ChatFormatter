#pragma once
#include <include_all.h>

#define PLUGIN_NAME "ChatFormatter"

extern ll::Logger logger;

namespace ConfigData {
extern std::string                          mFormat;
extern std::unordered_map<int, std::string> mDimMap;
}

extern void initPlugin();
extern void loadHook();
extern void unloadHook();
#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace ChatFormatter {

std::unique_ptr<Entry>& Entry::getInstance() {
    static std::unique_ptr<Entry> instance;
    return instance;
}

bool Entry::load() {
    initPlugin();
    return true;
}

bool Entry::enable() {
    registerPAPI();
    listenEvent();
    logger.info("ChatFormatter Loaded!");
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/ChatFormatter");
    return true;
}

bool Entry::disable() {
    removeListener();
    unregisterPAPI();
    return true;
}

bool Entry::unload() {
    getInstance().reset();
    return true;
}

} // namespace ChatFormatter

LL_REGISTER_PLUGIN(ChatFormatter::Entry, ChatFormatter::Entry::getInstance());
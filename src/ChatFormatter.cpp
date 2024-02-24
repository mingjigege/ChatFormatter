#include "Global.h"

std::string formatMessage(std::string_view author, std::string_view message, Player* pl) {
    std::string result = ConfigData::mFormat;
    GMLIB::Server::PlaceholderAPI::translate(result, pl);
    ll::utils::string_utils::replaceAll(result, "{player}", author);
    ll::utils::string_utils::replaceAll(result, "{message}", message);
    return result;
}

LL_TYPE_INSTANCE_HOOK(
    TextPacketHook,
    HookPriority::Highest,
    TextPacket,
    "?write@TextPacket@@UEBAXAEAVBinaryStream@@@Z",
    void,
    class BinaryStream& stream
) {
    if (mType == TextPacketType::Chat) {
        auto pl  = ll::service::getLevel()->getPlayer(mAuthor);
        mMessage = formatMessage(mAuthor, mMessage, pl);
        mAuthor.clear();
    }
    origin(stream);
}

void loadHook() { ll::memory::HookRegistrar<TextPacketHook>().hook(); }

void unloadHook() { ll::memory::HookRegistrar<TextPacketHook>().unhook(); }
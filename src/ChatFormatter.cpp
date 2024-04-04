#include "Global.h"

std::string formatMessage(std::string_view author, std::string_view message, Player* pl) {
    std::string result         = ConfigData::mFormat;
    auto&       forbiddenWords = ConfigData::mBan;
    GMLIB::Server::PlaceholderAPI::translate(result, pl);
    ll::utils::string_utils::replaceAll(result, "{player}", author);
    ll::utils::string_utils::replaceAll(result, "{message}", message);


    for (const auto& word : forbiddenWords) {
        if (result.find(word) != std::string::npos) {
            if (message.size() > 15) {
                result = "太长啦";
                break;
            }
            std::string replacement(word.length(), '*');
            ll::utils::string_utils::replaceAll(result, word, replacement);
        }
    }

    return result;
}

void listenEvent() {
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.emplaceListener<GMLIB::Event::PacketEvent::TextPacketWriteBeforeEvent>(
        [](GMLIB::Event::PacketEvent::TextPacketWriteBeforeEvent& ev) {
            auto& pkt = ev.getPacket();
            if (pkt.mType == TextPacketType::Chat) {
                auto pl      = ll::service::getLevel()->getPlayer(pkt.mAuthor);
                pkt.mMessage = formatMessage(pkt.mAuthor, pkt.mMessage, pl);
                pkt.mAuthor.clear();
            }
        }
    );
}

void removeListener() {
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.removePluginListeners("ChatFormatter");
}

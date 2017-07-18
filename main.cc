#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
namespace asio = boost::asio;

#include <discordpp/bot.hh>
#include <discordpp/rest-curlpp.hh>
#include <discordpp/websocket-websocketpp.hh>

#include <lib/nlohmannjson/src/json.hpp>

std::string readTokenFile(std::string tokenFilePath);

using json = nlohmann::json;
using aios_ptr = std::shared_ptr<asio::io_service>;

int main() {
    std::cout << "Starting bot...\n\n";

    /*/
     * Read token from token file.
     * Tokens are required to communicate with Discord, and hardcoding tokens is a bad idea.
     * If your bot is open source, make sure it's ignore by git in your .gitignore file.
    /*/
    std::string token;
    if(boost::filesystem::exists("token.dat")){
        token = readTokenFile("token.dat");
    } else {
        std::cerr << "CRITICAL: There is no valid way for Discord++ to obtain a token! Copy the example login.dat or token.dat to make one.\n";
        exit(1);
    }

    discordpp::Bot bot(
            token,
            std::make_shared<discordpp::RestCurlPPModule>(),
            std::make_shared<discordpp::WebsocketWebsocketPPModule>()
    );

    bot.addHandler("MESSAGE_CREATE", [](discordpp::Bot* bot, aios_ptr asio_ios, json msg){
        //std::cout << bot->me_.dump(4) << '\n';
        //std::cout << msg.dump() << '\n';
        bool mentioned = false;
        for(auto mention : msg["mentions"]) {
            if(mention["id"] == bot->me_["id"]){
                mentioned = true;
                break;
            }
        }
        if(mentioned){
            std::string mentioncode = "<@" + bot->me_["id"].get<std::string>() + ">";
            std::string content = msg["content"];
            while(content.find(mentioncode) != std::string::npos) {
                content = content.substr(0, content.find(mentioncode)) + content.substr(content.find(mentioncode) + mentioncode.size());
            }
            bot->call(
                    asio_ios,
                    "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                    {{"content", content}},
                    "POST"
            );
        }
        return std::vector<json>();
    });

    bot.addHandler("PRESENCE_UPDATE", [](discordpp::Bot* bot, aios_ptr asio_ios, json jmessage) {
        // ignore
        return std::vector<json>();
    });
    bot.addHandler("TYPING_START", [](discordpp::Bot* bot, aios_ptr asio_ios, json jmessage) {
        // ignore
        return std::vector<json>();
    });

    aios_ptr asio_ios = std::make_shared<asio::io_service>();
    bot.init(asio_ios);
    asio_ios->run();

    return 0;
}

std::string readTokenFile(std::string tokenFilePath){
    std::ifstream tokenFile;
    tokenFile.open(tokenFilePath);

    std::string token;

    if (tokenFile.is_open()) {
        std::getline(tokenFile, token);
    } else {
        std::cerr << "CRITICAL: There is no such file as " + tokenFilePath + "! Copy the example login.dat to make one.\n";
        exit(1);
    }
    tokenFile.close();
    std::cout << "Retrieved token.\n\n";

    return token;
}
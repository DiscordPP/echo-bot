#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;

#include <discordpp/bot.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-beast.hh>

//#include <lib/nlohmannjson/src/json.hpp>
//#include <nlohmann/json.hpp>

std::string readTokenFile(std::string tokenFilePath);

//using aios_ptr = std::shared_ptr<asio::io_service>;
using json = nlohmann::json;
namespace dpp = discordpp;
using DppBot = dpp::WebsocketBeast<dpp::RestBeast<dpp::Bot> >;

int main() {
    std::cout << "Starting bot...\n\n";

    /*/
     * Read token from token file.
     * Tokens are required to communicate with Discord, and hardcoding tokens is a bad idea.
     * If your bot is open source, make sure it's ignore by git in your .gitignore file.
    /*/
    std::string token;
    if (boost::filesystem::exists("token.dat")) {
        token = readTokenFile("token.dat");
    } else {
        std::cerr
                << "CRITICAL: There is no valid way for Discord++ to obtain a token! Copy the example login.dat or token.dat to make one.\n";
        exit(1);
    }

    DppBot bot;

    json self;
    bot.handlers.insert(
            {
                    "READY",
                    [&bot, &self](json data) {
                        self = data["user"];
                        //std::cout << data.dump(4) << std::endl;
                    }
            }
    );
    bot.handlers.insert(
            {
                    "MESSAGE_CREATE",
                    [&bot, &self](json msg) {
                        //std::cout << msg.dump(4) << std::endl;
                        bool mentioned = false;
                        for(const json &mention : msg["mentions"]){
                            mentioned = mentioned or mention["id"] == self["id"];
                        }
                        if(mentioned){

                            std::string mentioncode = "<@" + self["id"].get<std::string>() + ">";
                            std::string content = msg["content"];
                            while(content.find(mentioncode + ' ') != std::string::npos) {
                                content = content.substr(0, content.find(mentioncode + ' ')) + content.substr(content.find(mentioncode + ' ') + (mentioncode + ' ').size());
                            }
                            while(content.find(mentioncode) != std::string::npos) {
                                content = content.substr(0, content.find(mentioncode)) + content.substr(content.find(mentioncode) + mentioncode.size());
                            }
                            bot.call(
                                    "POST",
                                    "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                                    {{"content", content}}
                            );
                            bot.send(3, {
                                    {"game", {
                                                     {"name", "with " + msg["author"]["username"].get<std::string>()},
                                                     {"type", 0}
                                             }},
                                    {"status", "online"},
                                    {"afk", false},
                                    {"since", "null"}
                            });
                        }
                    }
            }
    );
    bot.handlers.insert({"GUILD_CREATE",   [](json){}}); // Ignoring
    bot.handlers.insert({"PRESENCE_UPDATE",[](json){}}); // Ignoring
    bot.handlers.insert({"TYPING_START",   [](json){}}); // Ignoring

    auto aioc = std::make_shared<asio::io_context>();

    bot.initBot(6, token, aioc);

    bot.run();

    /*aios_ptr aios = std::make_shared<asio::io_service>();

    discordpp::Bot bot(
            aios,
            token,
            std::make_shared<discordpp::RestCurlPPModule>(aios, token),
            std::make_shared<discordpp::WebsocketWebsocketPPModule>(aios, token)
    );

    bot.addHandler("MESSAGE_CREATE", [](discordpp::Bot* bot, json msg){
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
            while(content.find(mentioncode + ' ') != std::string::npos) {
                content = content.substr(0, content.find(mentioncode + ' ')) + content.substr(content.find(mentioncode + ' ') + (mentioncode + ' ').size());
            }
            while(content.find(mentioncode) != std::string::npos) {
                content = content.substr(0, content.find(mentioncode)) + content.substr(content.find(mentioncode) + mentioncode.size());
            }
            bot->call(
                    "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                    {{"content", content}},
                    "POST"
            );
            bot->send(3, {
                    {"game", {
                        {"name", "with " + msg["author"]["username"].get<std::string>()},
                        {"type", 0}
                    }},
                    {"status", "online"},
                    {"afk", false},
                    {"since", "null"}
            });
        }
    });

    bot.addHandler("PRESENCE_UPDATE", [](discordpp::Bot*, json) {
        // ignore
    });
    bot.addHandler("TYPING_START", [](discordpp::Bot*, json) {
        // ignore
    });

    aios->run();*/

    return 0;
}

std::string readTokenFile(std::string tokenFilePath) {
    std::ifstream tokenFile;
    tokenFile.open(tokenFilePath);

    std::string token;

    if (tokenFile.is_open()) {
        std::getline(tokenFile, token);
    } else {
        std::cerr << "CRITICAL: There is no such file as " + tokenFilePath +
                     "! Copy the example login.dat to make one.\n";
        exit(1);
    }
    tokenFile.close();
    std::cout << "Retrieved token.\n\n";

    return token;
}
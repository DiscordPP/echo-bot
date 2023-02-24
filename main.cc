#include "include.hh"

#ifndef ASIO_STANDALONE
namespace asio = boost::asio;
#endif
using json = nlohmann::json;
namespace dpp = discordpp;

std::string getToken();

std::istream &safeGetline(std::istream &is, std::string &t);

void filter(std::string &target, const std::string &pattern);

int main() {
    dpp::log::filter = dpp::log::info;
    dpp::log::out = &std::cerr;

    std::cout << "Howdy, and thanks for trying out Discord++!\n"
              << "Feel free to drop into the official server at "
                 "https://discord.gg/VHAyrvspCx if you have any questions.\n\n"
              << std::flush;

    std::cout << "Starting bot...\n\n";

    std::string token = getToken();
    if (token.empty()) {
        std::cerr << "CRITICAL: "
                  << "There is no valid way for Echo to obtain a token! Use "
                     "one of the following ways:"
                  << std::endl
                  << "(1) Fill the BOT_TOKEN environment variable with the "
                     "token (e.g. 'Bot 123456abcdef')."
                  << std::endl
                  << "(2) Copy the example `token.eg.dat` as `token.dat` and "
                     "write your own token to it.\n";
        exit(1);
    }

    // Create Bot object
    auto bot = std::make_shared<DppBot>();

    // Don't complain about unhandled events
    bot->debugUnhandled = true;

    // Declare the intent to receive guild messages
    // You don't need `NONE` it's just to show you how to declare multiple
    bot->intents = dpp::intents::NONE | dpp::intents::GUILD_MESSAGES;

    /*/
     * Create handler for the READY payload, this may be handled by the bot in
    the future.
     * The `self` object contains all information about the 'bot' user.
    /*/
    dpp::User self;
    bot->handlers.insert(
        {"READY", [&self](dpp::ReadyEvent ready) { self = *ready.user; }});

    bot->prefix = "~";

    bot->respond("help", "Mention me and I'll echo your message back!");

    bot->respond("about", [&bot](dpp::MessageCreateEvent msg) {
        std::ostringstream content;
        content << "Sure thing, "
                << *(msg.member->nick ? msg.author->username : msg.member->nick)
                << "!\n"
                << "I'm a simple bot meant to demonstrate the "
                   "Discord++ library.\n"
                << "You can learn more about Discord++ at "
                   "https://discord.gg/VHAyrvspCx";
        bot->createMessage()
            ->channel_id(*msg.channel_id)
            ->content(content.str())
            ->run();
    });

    bot->respond("lookatthis", [&bot](dpp::MessageCreateEvent msg) {
        std::ifstream ifs("image.jpg", std::ios::binary);
        if (!ifs) {
            std::cerr << "Couldn't load file 'image.jpg'!\n";
            return;
        }
        ifs.seekg(0, std::ios::end);
        std::ifstream::pos_type fileSize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        auto file = std::make_shared<std::string>(fileSize, '\0');
        ifs.read(file->data(), fileSize);

        bot->createMessage()
            ->channel_id(*msg.channel_id)
            ->content("Look at this photograph")
            ->filename("image.jpg")
            ->filetype("image/jpg")
            ->file(file)
            ->run();
    });

    bot->respond("channelinfo", [&bot](dpp::MessageCreateEvent msg) {
        bot->getChannel()
            ->channel_id(*msg.channel_id)
            ->onRead([&bot, msg](bool error, json res) {
                bot->createMessage()
                    ->channel_id(*msg.channel_id)
                    ->content("```json\n" + res["body"].dump(4) + "\n```")
                    ->run();
            })
            ->run();
    });

    bot->respond("registerslash", [&bot, &self](dpp::MessageCreateEvent msg) {
        if (*msg.author->id == 106615803402547200) {
            bot->createGuildApplicationCommand()
                ->application_id(*self.id)
                ->guild_id(*msg.guild_id)
                ->name("echo")
                ->description("Echoes what you say")
                ->options({dpp::ApplicationCommandOption(
                    dpp::ApplicationCommandOptionType::STRING,
                    std::string("message"), dpp::omitted, std::string("The message to echo"),
                    dpp::omitted, true)})
                ->command_type(dpp::ApplicationCommandType::CHAT_INPUT)
                ->onRead([](bool error, json res) {
                    std::cout << res.dump(4) << std::endl;
                })
                ->run();
        }
    });

    bot->interactionHandlers.insert(
        {881674285683470376, [&bot](dpp::Interaction msg) {
             bot->createResponse()
                 ->interaction_id(*msg.id)
                 ->interaction_token(*msg.token)
                 ->interaction_type(
                     dpp::InteractionCallbackType::CHANNEL_MESSAGE_WITH_SOURCE)
                 ->data({{
                     "content",
                     *std::get<dpp::ApplicationCommandData>(*msg.data).options->at(0).value
                 }})
                 ->run();
         }});

    // Create handler for the MESSAGE_CREATE payload, this receives all messages
    // sent that the bot can see.
    bot->handlers.insert(
        {"MESSAGE_CREATE", [&bot, &self](const dpp::MessageCreateEvent msg) {
             // Ignore messages from other bots
             if (msg.webhook_id || (msg.author->bot && *msg.author->bot)) {
                 return;
             }

             // Scan through mentions in the message for self
             bool mentioned = false;
             for (const dpp::User &mention : *msg.mentions) {
                 mentioned = mentioned || (*mention.id == *self.id);
             }
             if (mentioned) {
                 // Identify and remove mentions of self from the message
                 std::string content = *msg.content;
                 unsigned int oldlength, length = content.length();
                 do {
                     oldlength = length;
                     content = std::regex_replace(
                         content,
                         std::regex(R"(<@!?)" + std::to_string(*self.id) +
                                    R"(> ?)"),
                         "");
                     length = content.length();
                 } while (oldlength > length);

                 // Get the target user's display name
                 std::string name = *(msg.member->nick ? msg.member->nick
                                                       : msg.author->username);

                 std::cout << "Echoing " << name << '\n';

                 // Echo the created message
                 bot->createMessage()
                     ->channel_id(*msg.channel_id)
                     ->content(content)
                     ->run();

                 // Set status to Playing "with [author]"
                 bot->send(3,
                           {{"game", {{"name", "with " + name}, {"type", 0}}},
                            {"status", "online"},
                            {"afk", false},
                            {"since", "null"}});
             }
         }});

    // Create Asio context, this handles async stuff.
    auto aioc = std::make_shared<asio::io_context>();

    // Set the bot up
    bot->initBot(9, token, aioc);

    // Run the bot!
    bot->run();

    return 0;
}

std::string getToken() {
    std::string token;

    /*
                    First attempt to read the token from the BOT_TOKEN
       environment variable.
    */
    char const *env = std::getenv("BOT_TOKEN");
    if (env != nullptr) {
        token = std::string(env);
    } else {
        /*/
         * Read token from token file.
         * Tokens are required to communicate with Discord, and hardcoding
        tokens is a bad idea.
         * If your bot is open source, make sure it's ignore by git in your
        .gitignore file.
        /*/
        std::ifstream tokenFile("token.dat");
        if (!tokenFile) {
            return "";
        }
        safeGetline(tokenFile, token);
        tokenFile.close();
    }
    return token;
}

/*/
 * Source: https://stackoverflow.com/a/6089413/1526048
/*/
std::istream &safeGetline(std::istream &is, std::string &t) {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf *sb = is.rdbuf();

    for (;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if (sb->sgetc() == '\n') {
                sb->sbumpc();
            }
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line ending
            if (t.empty()) {
                is.setstate(std::ios::eofbit);
            }
            return is;
        default:
            t += (char)c;
        }
    }
}

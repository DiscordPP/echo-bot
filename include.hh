//
// Created by Aidan on 10/2/2020.
//

#pragma once

#include <fstream>
#include <iostream>
#include <regex>

#include <boost/asio.hpp>

#include <discordpp/bot.hh>
#include <discordpp/log.hh>
#include <discordpp/plugin-overload.hh>
#include <discordpp/plugin-ratelimit.hh>
#include <discordpp/plugin-responder.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-simpleweb.hh>

template class discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>;
using DppBot = discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>;

std::shared_ptr<DppBot> newBot(){
    return std::make_shared<DppBot>();
}

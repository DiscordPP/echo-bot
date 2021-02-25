//
// Created by Aidan on 10/2/2020.
//

#pragma once

#ifndef ECHO_EXTERN

#include <fstream>
#include <iostream>
#include <regex>

#include <boost/asio.hpp>

// Put more non-plugin `include`s here

#endif

#include <discordpp/bot.hh>
#include <discordpp/plugin-overload.hh>
#include <discordpp/plugin-ratelimit.hh>
#include <discordpp/plugin-responder.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-simpleweb.hh>

// Put more D++ plugin `include`s here

#ifndef ECHO_EXTERN

extern template class discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>;
using DppBot = discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>;

#undef DPPBOTDEF

#endif

//
// Created by Aidan on 10/2/2020.
//

#pragma once

#include <discordpp/macros.hh>

#define MY_BOT_DEF BOT_DEF(ALL_DISCORDPP_PLUGINS)

#ifndef ECHO_EXTERN

#include <fstream>
#include <iostream>
#include <regex>

#include <boost/asio.hpp>

// Put more non-plugin `include`s here

#endif

#include <discordpp/bot.hh>
#include <discordpp/plugin-endpoints.hh>
#include <discordpp/plugin-interactionhandler.hh>
#include <discordpp/plugin-overload.hh>
#include <discordpp/plugin-ratelimit.hh>
#include <discordpp/plugin-responder.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-simpleweb.hh>

// Put more D++ plugin `include`s here

#ifndef ECHO_EXTERN

extern template class MY_BOT_DEF;
using DppBot = MY_BOT_DEF;

#undef DPPBOTDEF

#endif

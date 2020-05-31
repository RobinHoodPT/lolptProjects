//
// Created by Robin on 31/05/2020.
//

#pragma once

#ifndef LEAGUE_PROJECTS_BOTMANAGER_H
#define LEAGUE_PROJECTS_BOTMANAGER_H

#endif //LEAGUE_PROJECTS_BOTMANAGER_H

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <discordpp/bot.hh>
#include <discordpp/plugin-overload.hh>
#include <discordpp/rest-beast.hh>
#include <discordpp/websocket-beast.hh>
#include <discordpp/plugin-responder.hh>

//#include <Commands/AddStaffMember.h>

namespace asio = boost::asio;
using json = nlohmann::json;
namespace dpp = discordpp;

using DppBot =
dpp::PluginResponder<
        dpp::PluginOverload<
                dpp::WebsocketBeast<
                        dpp::RestBeast<
                                dpp::Bot
                        >
                >
        >
>;

class BotManager {
public:
    static BotManager& GetInstance(){
        static BotManager instance;

        return instance;
    }
    BotManager(BotManager const&) = delete;
    void operator=(BotManager const&) = delete;

    void InitializeBot();
    std::shared_ptr<DppBot> bot;
private:
    BotManager(){}

    static std::string getToken();
    static std::istream &safeGetline(std::istream &is, std::string &t);
    static void filter(std::string &target, const std::string &pattern);
};


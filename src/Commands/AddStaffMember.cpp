//
// Created by Robin on 31/05/2020.
//

#include "Commands/AddStaffMember.h"

void AddStaffMember::SetupCommand() {
//    bot->respond("addStaff", [&bot](json msg) {
//        std::cout << msg << std::endl;
//        std::ostringstream content;
//        content << "Sure thing, "
//                << (msg["member"]["nick"].is_null() ? msg["author"]["username"].get<std::string>() : msg["member"]["nick"].get<std::string>())
//                << "!\n"
//                << "I'm a simple bot meant to demonstrate the Discord++ library.\n"
//                << "You can learn more about Discord++ at https://discord.gg/0usP6xmT4sQ4kIDh";
//        bot->call(
//                "POST",
//                "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
//                json({{"content", content.str()}})
//        );
//    });
}

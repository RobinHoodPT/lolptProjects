//
// Created by Robin on 29/05/2020.
//

#pragma once
#include <string>

#ifndef LEAGUE_PROJECTS_STAFFMEMBER_H
#define LEAGUE_PROJECTS_STAFFMEMBER_H

#endif //LEAGUE_PROJECTS_STAFFMEMBER_H


class StaffMember {
public:
    StaffMember(long *discordID, std::string *localidade, std::string *email, std::string *extraInfo);

    void SaveToDatabase(bool newUser);

    bool operator==(const StaffMember &obj2) const {
        if (this->discordID == obj2.discordID) {
            return true;
        } else {
            return false;
        }
    }

    long GetDiscordID();

    std::string *localidade;
    std::string *email;
    std::string *extraInfo;

private:
    long *discordID;
};
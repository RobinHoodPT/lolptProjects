//
// Created by Robin on 30/05/2020.
//
#pragma once

#include <string>
#include <SQLiteCpp/Database.h>


#ifndef LEAGUE_PROJECTS_DATABASEOPERATIONS_H
#define LEAGUE_PROJECTS_DATABASEOPERATIONS_H
const std::string LP_DB = "leagueProject.db";
#endif //LEAGUE_PROJECTS_DATABASEOPERATIONS_H


class DataBaseOperations {
public:
    static bool ExecuteStatementNoReturn(std::string &sqlStatement);
    static void SetupDatabase();

    static bool CheckIfUserProjectMember(const long discordID, const std::string projectName);
    static bool CheckIfUserProjectOrganizer(const long discordID,const std::string projectName);
    static bool CheckIfProjectContainsChannel(const long channelID, const std::string projectName);

};
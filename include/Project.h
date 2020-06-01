//
// Created by Robin on 29/05/2020.
//

#pragma once
#include <string>
#include <vector>
#include "StaffMember.h"

#ifndef LEAGUE_PROJECTS_PROJECT_H
#define LEAGUE_PROJECTS_PROJECT_H

#endif //LEAGUE_PROJECTS_PROJECT_H

enum ProjectType {
    Public = 1,
    Protected = 2,
    Private = 3,
};

class Project {
public:
    Project(std::string *name, ProjectType *type, long *roleID);

    void AddMember(const long *discordID, const bool isOrganizer);

    void RemoveMember(long *discordID);

    void EditOrganizer(const long *discordID, const bool isOrganizer);

    bool IsMember(const long *discordID);

    bool IsOrganizer(const long *discordID);

    void AddChannel(const long *channelID);

    void RemoveChannel(const long *channelID);

    void SaveNewProjectToDatabase();

    void UpdateName(std::string *newName);

    void UpdateType(ProjectType *newType);

    void Archive();

    void UnArchive();
private:
    std::string *name;
    ProjectType *type;
    long *roleID;

    void UpdateToPublicType();

    void UpdateToProtectedType();

    void UpdateToPrivateType();


};




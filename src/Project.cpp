//
// Created by Robin on 29/05/2020.
//

#include <Project.h>
#include <DatabaseOperations.h>
#include <boost/format.hpp>

Project::Project(std::string *name, ProjectType *type, long *roleID) {
    this->name = name;
    this->type = type;
    this->roleID = roleID;
}

void Project::SaveNewProjectToDatabase() {

    std::string sql = str(boost::format("INSERT INTO Project (Name,Type,RoleID) VALUES ('%1%',%2%,%3%);\n") % *name % *type % *roleID);
    if (!sql.empty()) {
        DataBaseOperations::ExecuteStatementNoReturn(sql);
    }
}

void Project::AddMember(const long *discordID, const bool isOrganizer) {
    if (!DataBaseOperations::CheckIfUserProjectMember(*discordID, *name)) {
        std::string sql = str(boost::format(
                "INSERT INTO ProjectMembers (ProjectID,DiscordID,isOrganizer) SELECT ID,%2%,%3% from Project where Name = '%1%';\n") % *name %
                              *discordID % isOrganizer);
        if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
            //TODO DISCORD CONNECT: Add user to channels/Add role depending on the project typ
        }
    }
}

void Project::RemoveMember(long *discordID) {
    std::string sql = str(boost::format(
            "DELETE FROM ProjectMembers WHERE DiscordID = %1% AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = '%2%');\n") % *discordID % *name);
    if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
        //TODO DISCORD CONNECT: Remove user off channels/Remove role depending on the project type
    }
}

void Project::EditOrganizer(const long *discordID, const bool isOrganizer) {
    std::string sql = str(boost::format(
            "UPDATE ProjectMembers SET isOrganizer = %3% WHERE DiscordID = %1% AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = '%2%');\n") % *discordID % *name %isOrganizer);
    if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
        //TODO DISCORD CONNECT: A new organizer got added
    }
}

bool Project::IsMember(const long *discordID) {
    return DataBaseOperations::CheckIfUserProjectMember(*discordID, *name);
}

bool Project::IsOrganizer(const long *discordID) {
    return DataBaseOperations::CheckIfUserProjectOrganizer(*discordID, *name);
}

void Project::AddChannel(const long *channelID) {
    if (!DataBaseOperations::CheckIfProjectContainsChannel(*channelID, *name)) {
        std::string sql = str(boost::format(
                "INSERT INTO ProjectChannels (ProjectID,ChannelID) SELECT ID,%2% from Project where Name = '%1%';\n") % *name % *channelID);
        if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
            //TODO DISCORD CONNECT: Add user(s) or role to newly created channel depending on the project type
        }
    }
}

void Project::RemoveChannel(const long *channelID) {
    if (DataBaseOperations::CheckIfProjectContainsChannel(*channelID, *name)) {
        std::string sql = str(boost::format(
                "DELETE FROM ProjectChannels WHERE ChannelID = %2% AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = '%1%');\n") % *name % *channelID);
        if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
            //TODO DISCORD CONNECT: Delete discord channel
        }
    }
}

void Project::UpdateName(std::string *newName) {
    std::string sql = str(boost::format(
            "UPDATE Project SET Name = '%1%' WHERE Name = '%2%';\n") % *newName % *name);
    if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
        name = newName;
        //TODO DISCORD CONNECT: Update the message with all the projects and update role name if exists.
    }
}

void Project::UpdateType(ProjectType *newType) {
    std::string sql = str(boost::format(
            "UPDATE Project SET Type = '%1%' WHERE Name = '%2%';\n") % *newType % *name);
    if (DataBaseOperations::ExecuteStatementNoReturn(sql)) {
        type = newType;
        switch(*type){
            case Public:
                UpdateToPublicType();
                break;
            case Protected:
                UpdateToProtectedType();
                break;
            case Private:
                UpdateToPrivateType();
                break;
        }

    }
}

void Project::UpdateToPublicType() {
//TODO DISCORD CONNECT: Update discord to the correct type.
//Create Role with the same name as the project name if it doesn't exist.
//Clear all permissions of the role.
//Set role to mentionable if the user requested it
//Set all the channels of the project to use that role.

//Sets on all channels of the project the following permissions on the role of the project:
//    Read Messages - ✅
//    Send messages - ✅
//    Manage Messages - ✅

//Sets on all channels of the project the following permissions on the Staff Role:
//    Read Messages - ✅
//    Send messages - ✅
//    Manage Messages - ✅

}

void Project::UpdateToProtectedType() {
//TODO DISCORD CONNECT: Update discord to the correct type.
//Create Role with the same name as the project name if it doesn't exist.
//Clear all permissions of the role.
//Set role to mentionable if the user requested it
//Set all the channels of the project to use that role.

//Sets on all channels of the project the following permissions on the role of the project:
//    Read Messages - ✅
//    Send messages - ✅
//    Manage Messages - ✅

//Sets on all channels of the project the following permissions on the Staff Role:
//    Read Messages - ✅
//    Send messages - ❌
//    Manage Messages - ❌

}

void Project::UpdateToPrivateType() {
//TODO DISCORD CONNECT: Update discord to the correct type.
//Create Role with the same name as the project name if it doesn't exist.
//Clear all permissions of the role.
//Set role to mentionable if the user requested it
//Set all the channels of the project to use that role.

//Sets on all channels of the project the following permissions on the role of the project:
//    Read Messages - ✅
//    Send messages - ✅
//    Manage Messages - ✅

//Sets on all channels of the project the following permissions on the Staff Role:
//    Read Messages - ❌
//    Send messages - ❌
//    Manage Messages - ❌
}

void Project::Archive() {
//TODO DISCORD CONNECT: Archive the project
//Deletes the role
//moves all channels to Archive category
//Check on what would be the best way to setup the permissions on this channel
}

void Project::UnArchive() {
//TODO DISCORD CONNECT: Reinstantiate the project
//recreated the project.
}










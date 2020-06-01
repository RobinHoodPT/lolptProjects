//
// Created by Robin on 30/05/2020.
//

#include <DatabaseOperations.h>
#include <iostream>

bool DataBaseOperations::ExecuteStatementNoReturn(std::string &sqlStatement) {
    try {

        SQLite::Database db(LP_DB, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";
        db.exec(sqlStatement);
        std::cout << "Executed statement: " << sqlStatement << std::endl;
        return true;
    } catch (std::exception &e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }
}

void DataBaseOperations::SetupDatabase() {
//Setup the database if it doesn't already exist.

    //Create members table
    std::string sql = "CREATE TABLE IF NOT EXISTS Member("  \
      "DiscordID INT PRIMARY KEY NOT NULL," \
      "Localidade TEXT NOT NULL," \
      "Email TEXT," \
      "ExtraContactInfo TEXT );";

    ExecuteStatementNoReturn(sql);

    sql.clear();
    sql = "CREATE TABLE IF NOT EXISTS Project("  \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT ," \
      "Name TEXT NOT NULL UNIQUE," \
      "RoleID INT NOT NULL UNIQUE," \
      "Type INT NOT NULL);";

    ExecuteStatementNoReturn(sql);

    sql.clear();
    sql = "CREATE TABLE IF NOT EXISTS ProjectMembers("  \
      "ProjectID INTEGER NOT NULL," \
      "DiscordID INT NOT NULL," \
      "isOrganizer BOOLEAN NOT NULL,"\
      "PRIMARY KEY(ProjectID,DiscordID)," \
      "FOREIGN KEY(ProjectID) REFERENCES Project(ID),"\
      "FOREIGN KEY(DiscordID) REFERENCES Member(DiscordID));";

    ExecuteStatementNoReturn(sql);

    sql = "CREATE TABLE IF NOT EXISTS ProjectChannels("  \
      "ProjectID INTEGER NOT NULL," \
      "ChannelID INT NOT NULL," \
      "PRIMARY KEY(ProjectID,ChannelID)," \
      "FOREIGN KEY(ProjectID) REFERENCES Project(ID));";

    ExecuteStatementNoReturn(sql);

}

bool DataBaseOperations::CheckIfUserProjectMember(const long discordID, const std::string projectName) {
    try {
        SQLite::Database db(LP_DB, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT count(*) FROM ProjectMembers WHERE DiscordID = ? AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = ?);");
        query.bind(1, discordID);
        query.bind(2,projectName);
        query.executeStep();
        std::cout << "Executed statement: " << query.getQuery() << std::endl;

        int count = query.getColumn(0);

        return count != 0;
    } catch (std::exception &e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DataBaseOperations::CheckIfUserProjectOrganizer(const long discordID,const std::string projectName) {
    try {
        SQLite::Database db(LP_DB, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT count(*) FROM ProjectMembers WHERE DiscordID = ? AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = ?) AND isOrganizer = 1;");
        query.bind(1, discordID);
        query.bind(2,projectName);
        query.executeStep();
        std::cout << "Executed statement: " << query.getQuery() << std::endl;

        int count = query.getColumn(0);

        return count != 0;
    } catch (std::exception &e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}

bool DataBaseOperations::CheckIfProjectContainsChannel(const long channelID, const std::string projectName) {
    try {
        SQLite::Database db(LP_DB, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT count(*) FROM ProjectChannels WHERE ChannelID = ? AND ProjectID = (SELECT ProjectID FROM Project WHERE Name = ?);");
        query.bind(1, channelID);
        query.bind(2, projectName);
        query.executeStep();
        std::cout << "Executed statement: " << query.getQuery() << std::endl;

        int count = query.getColumn(0);

        return count != 0;
    } catch (std::exception &e) {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return 0;
    }
}





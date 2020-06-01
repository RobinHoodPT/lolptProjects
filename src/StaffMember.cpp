//
// Created by Robin on 30/05/2020.
//
#include <StaffMember.h>
#include <DatabaseOperations.h>
#include <boost/format.hpp>


StaffMember::StaffMember(long *discordID, std::string *localidade, std::string *email,
                         std::string *extraInfo) {
    this->discordID = discordID;
    this->localidade = localidade;
    this->email = email;
    this->extraInfo = extraInfo;
}

void StaffMember::SaveToDatabase(bool newUser) {
    std::string sql;
    if(newUser){
         sql = str(boost::format("INSERT INTO Member (DiscordID,Localidade,Email,ExtraContactInfo) " \
        "VALUES (%1%,'%2%','%3%','%4%');\n") % *discordID % *localidade % *email % *extraInfo);
    } else {
        //Input update statement.
        sql = str(boost::format("UPDATE Member SET Localidade = '%2%', email = '%3%', ExtraContactInfo = '%4%' WHERE DiscordID = %1%;\n") \
                % *discordID %  *localidade % *email % *extraInfo);
    }

    if(!sql.empty()){
        DataBaseOperations::ExecuteStatementNoReturn(sql);
    }
}

long StaffMember::GetDiscordID() {
    return *discordID;
}

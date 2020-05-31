
#include <BotManager.h>


int main(){
//    DataBaseOperations::SetupDatabase();
//
//    long id = 94070985212313600;
//    std::string testString = "Robin22";
//    StaffMember staffMember(&id,&testString,&testString,&testString);
//    staffMember.SaveToDatabase(true);
//    std::string testString2 = "Robin12345";
//    staffMember.localidade = &testString2;
//    staffMember.SaveToDatabase(false);
//
//    ProjectType type = ProjectType::Public;
//    Project project(&testString, &type, &id);
//    project.SaveNewProjectToDatabase();
//
//    long id2 = 94070985212313602;
//    std::string testString3 = "Robin23";
//    StaffMember staffMember2(&id2,&testString3,&testString3,&testString3);
//    staffMember2.SaveToDatabase(true);
//
//    project.AddMember(&id, false);
//    project.AddMember(&id2, false);
//    project.RemoveMember(&id2);
//    project.EditOrganizer(&id,true);
//
//    std::cout <<"is project Organizer? "<< project.IsMember(&id) << std::endl;
//    std::cout <<"is project Organizer? "<< project.IsOrganizer(&id) << std::endl;
//
//    project.AddChannel(&id2);
//    project.RemoveChannel(&id2);
//
//    project.UpdateName(&testString3);
//    ProjectType type2 = ProjectType::Private;
//    project.UpdateType(&type2);

    BotManager::GetInstance().InitializeBot();
	return 0;
}

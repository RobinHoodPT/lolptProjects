//
// Created by Robin on 31/05/2020.
//

#include <BotManager.h>


void BotManager::InitializeBot(){

    //Region of how the bot works.
    std::string token = getToken();
    if(token.empty()) {
        std::cerr << "CRITICAL: "
                  << "There is no valid way for Echo to obtain a token! Use one of the following ways:" << std::endl
                  << "(1) Fill the BOT_TOKEN environment variable with the token (e.g. 'Bot 123456abcdef')." << std::endl
                  << "(2) Copy the example `token.dat` as `token.dat` and write your own token to it.\n";
        exit(1);
    }

    // Create Bot object
    bot = std::make_shared<DppBot>();
    // Don't complain about unhandled events
    bot->debugUnhandled = false;

    /*/
     * Create handler for the READY payload, this may be handled by the bot in the future.
     * The `self` object contains all information about the 'bot' user.
    /*/
    json self;
    bot->handlers.insert(
            {
                    "READY",
                    [this, &self](json data){
                        self = data["user"];
                    }
            }
    );

    bot->prefix = "!";

//    AddStaffMember cmd;
//    cmd.SetupCommand();


    bot->respond("p", "You have the following commands:\n **!p create**\n");



    bot->respond(
            "about", [this](json msg){
                std::cout << msg << std::endl;
                std::ostringstream content;
                content << "Sure thing, "
                        << (msg["member"]["nick"].is_null() ? msg["author"]["username"].get<std::string>() : msg["member"]["nick"].get<std::string>())
                        << "!\n"
                        << "I'm a simple bot meant to demonstrate the Discord++ library.\n"
                        << "You can learn more about Discord++ at https://discord.gg/0usP6xmT4sQ4kIDh";
                bot->call(
                        "POST",
                        "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                        json({{"content", content.str()}})
                );
            }
    );

    // Create handler for the MESSAGE_CREATE payload, this receives all messages sent that the bot can see.
    bot->handlers.insert(
            {
                    "MESSAGE_CREATE",
                    [this, &self](json msg){
                        // Scan through mentions in the message for self
                        bool mentioned = false;
                        for(const json &mention : msg["mentions"]){
                            mentioned = mentioned or mention["id"] == self["id"];
                        }
                        if(mentioned){
                            // Identify and remove mentions of self from the message
                            std::string content = msg["content"];
                            std::string mentioncode = "<@" + self["id"].get<std::string>() + ">";
                            std::string nickedcode = "<@!" + self["id"].get<std::string>() + ">";
                            filter(content, mentioncode + ' ');
                            filter(content, nickedcode + ' ');
                            filter(content, mentioncode);
                            filter(content, nickedcode);

                            while(content.find(mentioncode) != std::string::npos){
                                content = content.substr(0, content.find(mentioncode)) +
                                          content.substr(content.find(mentioncode) + mentioncode.size());
                            }

                            // Echo the created message
                            bot->call(
                                    "POST",
                                    "/channels/" + msg["channel_id"].get<std::string>() + "/messages",
                                    json({{"content", content}})
                            );

                            // Set status to Playing "with [author]"
                            bot->send(
                                    3, {
                                            {
                                                    "game",   {
                                                                      {
                                                                              "name", "with " + (
                                                                              msg["member"]["nick"].is_null()
                                                                              ? msg["author"]["username"].get<std::string>()
                                                                              : msg["member"]["nick"].get<std::string>()
                                                                      )
                                                                      },
                                                                      {"type", 0}
                                                              }
                                            },
                                            {       "status", "online"},
                                            {       "afk",    false},
                                            {       "since",  "null"}
                                    }
                            );
                        }
                    }
            }
    );

    // Create Asio context, this handles async stuff.
    auto aioc = std::make_shared<asio::io_context>();

    // Set the bot up
    bot->initBot(6, token, aioc);

    // Run the bot!
    bot->run();
}

std::string BotManager::getToken() {
    std::string token;

    /*
        First attempt to read the token from the BOT_TOKEN environment variable.
    */
    char const* env = std::getenv("BOT_TOKEN");
    if(env != nullptr) {
        token = std::string(env);
    } else {
        /*/
         * Read token from token file.
         * Tokens are required to communicate with Discord, and hardcoding tokens is a bad idea.
         * If your bot is open source, make sure it's ignore by git in your .gitignore file.
        /*/
        std::ifstream tokenFile("token.dat");
        if(!tokenFile){
            return "";
        }
        safeGetline(tokenFile, token);
        tokenFile.close();
    }
    return token;
}

/*/
 * Source: https://stackoverflow.com/a/6089413/1526048
/*/
std::istream &BotManager::safeGetline(std::istream &is, std::string &t){
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf *sb = is.rdbuf();

    for(;;){
        int c = sb->sbumpc();
        switch(c){
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n'){
                    sb->sbumpc();
                }
                return is;
            case std::streambuf::traits_type::eof():
                // Also handle the case when the last line has no line ending
                if(t.empty()){
                    is.setstate(std::ios::eofbit);
                }
                return is;
            default:
                t += (char)c;
        }
    }
}

void BotManager::filter(std::string &target, const std::string &pattern){
    while(target.find(pattern) != std::string::npos){
        target = target.substr(0, target.find(pattern)) +
                 target.substr(target.find(pattern) + (pattern).size());
    }
}
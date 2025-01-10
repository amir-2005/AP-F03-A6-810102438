#include "./Utaste.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"
using namespace std;

void mapServerPaths(Server& server, UTaste &utaste) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/login", new ShowPage("static/login.html"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/login", new LoginHandler(utaste));
    server.post("/signup", new SignUpHandler(utaste));
    server.get("/real_homepage", new ShowPage(""));

}

int main(int argc, char** argv) {
    try {
        int port = argc > 1 ? std::stoi(argv[1]) : 5000;
        Server server(port);
        UTaste utaste(argv[2], argv[3], argv[4]);
        mapServerPaths(server, utaste);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}

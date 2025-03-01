#include "./Utaste.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"
using namespace std;

void mapServerPaths(Server &server, UTaste &utaste)
{
    server.setNotFoundErrPage("static/404.html");
    server.get("/image", new ShowImage("static/image.png"));
    server.get("/", new ShowPage("static/home.html"));
    server.get("/login", new ShowLoginSignUp("template/login.html", utaste));
    server.get("/signup", new ShowLoginSignUp("template/signup.html", utaste));
    server.post("/login", new LoginHandler(utaste));
    server.post("/signup", new SignUpHandler(utaste));
    server.get("/dashboard", new DashboardHandler("template/dashboard.html", utaste));
    server.get("/reservation", new ReservationForm("template/reservation.html", utaste));
    server.post("/reservation", new ReservationHandler(utaste));
    server.get("/reserve_list", new ReserveListHandler("template/reserve_list.html", utaste));
    server.get("/budget", new BudgetPage("template/budget.html", utaste));
    server.post("/budget", new BudgetHandler(utaste));
    server.get("/logout", new LogoutHandler(utaste));
    server.get("/restaurants", new RestaurantHandler(utaste));
    server.post("/restaurants", new RestaurantHandler(utaste));
}

int main(int argc, char **argv)
{
    try
    {
        int port = argc > 1 ? std::stoi(argv[1]) : 5000;
        Server server(port);
        UTaste utaste(argv[2], argv[3], argv[4]);
        mapServerPaths(server, utaste);
        cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception &e)
    {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}

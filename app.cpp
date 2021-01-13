#include <iostream>
#include "app.h"
#include "user_interface.h"

App::App(std::istream& is, std::ostream& os): is(is), os(os){
    // TODO
}

void App::run() {
    // TODO
    static UserInterface* ui = new UserInterface(is, os);
    static BackEnd* backEnd = new BackEnd();
    static FrontEnd* frontEnd = new FrontEnd(backEnd);
    ui->createUI(frontEnd);
    ui->run(is, os);
}

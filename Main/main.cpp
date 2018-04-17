#include "game.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game g;
    g.show();
    WelcomeScreen ws;
    ws.show();
    return a.exec();
}

/**
  Settlers of War: A catan-based game
  Kathryn Osborn
  Final Project Checkpoint 2 CSCI 3010
  */

#include "game.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game g;
    g.show();
    return a.exec();
}

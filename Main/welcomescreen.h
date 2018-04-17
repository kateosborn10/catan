#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QDialog>
#include <game.h>



namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();
    int get_number_players(){return number_players_;}
    Ui::WelcomeScreen *ui;


private slots:


private:
    int number_players_;
};

#endif // WELCOMESCREEN_H

/**
 Dialog box that pops up first to give instructions to user
*/
#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QDialog>

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
    int get_number_human_players(){return human_players_;}
    void ResetComboBoxes();
    Ui::WelcomeScreen* ui;


private slots:
    void OnNumberPlayersChanged(int index);
    void OnHumanNumberPlayersChanged(int index);


private:
    int number_players_;
    int human_players_;
};

#endif // WELCOMESCREEN_H

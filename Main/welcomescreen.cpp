#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);



}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

//void WelcomeScreen::on_numPlayersComboBox_currentIndexChanged(int index)
//{
//    number_players_ = index + 2;

//}

#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <iostream>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
    ui->startGameButtonBox->setDisabled(true);
    connect(ui->numberPlayerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnNumberPlayersChanged(int)));




}

WelcomeScreen::~WelcomeScreen()
{
    std::cout << "deleting ui " << std::endl;
    delete ui;
}

/**
 * @brief WelcomeScreen::OnNumberPlayersChanged
 * @param index
 */
void WelcomeScreen::OnNumberPlayersChanged(int index){
  if(index != 0){
      number_players_ = index + 1;
      ui->startGameButtonBox->setDisabled(false);
  }

}


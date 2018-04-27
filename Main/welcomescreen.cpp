#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <iostream>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
    ui->startGameButtonBox->setDisabled(true);
    ui->numHumanPlayerComboBox->setDisabled(true);
    connect(ui->totalNumPlayerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnNumberPlayersChanged(int)));
    connect(ui->numHumanPlayerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(OnHumanNumberPlayersChanged(int)));





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
    ui->startGameButtonBox->setDisabled(true);
    // clear human combo box each time so we can set the right options
    ui->numHumanPlayerComboBox->clear();
    ui->numHumanPlayerComboBox->setDisabled(true);

  if(index != 0){
      QStringList human_player_options;
      number_players_ = index + 1;
      switch(index){
      case 1:
          // 2 players selected
          human_player_options << "Select One" << "1" << "2";
          break;
      case 2:
          // 3 players selected
          human_player_options << "Select One" << "1" << "2" << "3";
          break;
      case 3:
          // 4 players selected
          human_player_options << "Select One" << "1" << "2" << "3" << "4";
      default:
          break;
      }
      ui->numHumanPlayerComboBox->addItems(human_player_options);
      ui->numHumanPlayerComboBox->setDisabled(false);
  }

}

/**
 * @brief WelcomeScreen::OnHumanNumberPlayersChanged
 * @param index
 */
void WelcomeScreen::OnHumanNumberPlayersChanged(int index){
  if(index != 0){
      human_players_ = index;
  }
  if(index != 0 && ui->totalNumPlayerComboBox->currentIndex() != 0){
      ui->startGameButtonBox->setDisabled(false);
  }else{
      ui->startGameButtonBox->setDisabled(true);
  }

}

void WelcomeScreen::ResetComboBoxes(){
    ui->totalNumPlayerComboBox->setCurrentIndex(0);
    ui->numHumanPlayerComboBox->setCurrentIndex(0);
}


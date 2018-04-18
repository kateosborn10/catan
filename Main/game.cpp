/**
* Game Class: Contains the ui object and controls the state of the game.
*
*/


#include "game.h"
#include "ui_game.h"
#include "aiplayer.h"
#include "humanplayer.h"
#include <iostream>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QtWidgets>
#include <string>


#include "playerdisplayhandler.h"
#include "playerdashboard.h"

/**
 * @brief Game::Game constructor for the Game class. Responsible
 * for creating and setting QGraphics scences, and connecting play,
 * advance turn, end game, start over, and number of players buttons
 * to slots in Game class.
 * @param parent is default parameter passed to a Qt widget class
 */
Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    screen_.show();
    screen_.exec();
    game_scene_ = new QGraphicsScene;
    player_scene_ = new QGraphicsScene;
    hand_scene_ = new QGraphicsScene;
    ui->boardGraphicsView->setScene(game_scene_);
    ui->playerGraphicsView->setScene(player_scene_);
    ui->handGraphicsView->setScene(hand_scene_);
    ui->handGraphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    ui->playerGraphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    connect(ui->playGameButton, SIGNAL(released()), this, SLOT(PlayGame()));
    connect(ui->advanceTurnButton, SIGNAL(released()), this, SLOT(AdvanceTurn()));
    connect(ui->endGameButton, SIGNAL(released()), this, SLOT(EndGame()));
    connect(ui->startOverButton, SIGNAL(released()), this, SLOT(StartOver()));
    connect(ui->numberOfPlayersComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetNumberOfPlayers(int)));
    QStringList playerOptions;
    //http://doc.qt.io/qt-5/qstringlist.html
    playerOptions << "2" << "3" << "4";
    ui->numberOfPlayersComboBox->addItems(playerOptions);
    set_game_state(GameState::Initial);

}


/**
 * @brief Game::~Game dtor for Game class, deletes ui instance
 */
Game::~Game()
{
    delete ui;
}

/**
 * @brief Game::SetInitialState is called by set_game_state() and is
 * reponsible for disabling all user buttons except play and numbers
 * of players.
 */
void Game::SetInitialState() {
    std::cout << "Initial State!" << std::endl;
    ui->playGameButton->setDisabled(false);
    ui->advanceTurnButton->setDisabled(true);
    ui->endGameButton->setDisabled(true);
    ui->startOverButton->setDisabled(true);
    ui->numberOfPlayersComboBox->setDisabled(false);
    ui->handGraphicsView->hide();
    ui->playerGraphicsView->setDisabled(false);
}

/**
 * @brief Game::PlayGame is a slot that is signaled when a user presses
 * the play button on the ui. It calls set_game_state with PlayerTurn as the new_state,
 * calls CreatePlayers to populate players_ list, and sets current_player_ field to the first
 * player.
 */
void Game::PlayGame() {
    //player goes first
    set_game_state(GameState::PlayerTurn);
    CreatePlayers();
    // set current player to player1
    current_player_index_ = -1;
    current_player_ = GetNextPlayer();
    UpdatePlayerDashboard();
    ui->handGraphicsView->show();
}
/**
 * @brief Game::AdvanceTurn is a slot that is signaled when a user presses advance
 * turn button. Is responsible for grabbing the next player in line and setting
 * the game state to either NonPlayerTurn or PlayerTurn depending
 * on if the Player is AI or Human controlled.
 */
void Game::AdvanceTurn() {
    current_player_ = GetNextPlayer();
    if(current_player_->get_is_ai()){
        set_game_state(GameState::NonPlayerTurn);
        ui->handGraphicsView->scene()->clear();

    }
    else{
        set_game_state(GameState::PlayerTurn);
        UpdatePlayerDashboard();
    }

}
/**
 * @brief Game::EndGame is a slot that is signaled when a user pressed end game
 * button and sets game state to GameOver
 */
void Game::EndGame() {
    set_game_state(GameState::GameOver);
    ui->handGraphicsView->hide();

}

/**
 * @brief Game::StartOver is a slot that is signaled when a user presses start
 * over button. Sets game state to Initial and clears the players vector
 */
void Game::StartOver() {
    set_game_state(GameState::Initial);
    // clear the player list
    players_.clear();
}

/**
 * @brief Game::SetPlayerTurnState disables all user buttons except
 * advance turn and end game buttons.
 */
void Game::SetPlayerTurnState() {
    std::cout << "Player Turn State!" << std::endl;
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(false);
    ui->endGameButton->setDisabled(false);
    ui->startOverButton->setDisabled(true);
    ui->numberOfPlayersComboBox->setDisabled(true);
    ui->playerGraphicsView->setDisabled(true);


}

/**
 * @brief Game::SetNonPlayerTurnState disables all user buttons except
 * advance turn and end game buttons.
 */
void Game::SetNonPlayerTurnState() {
    std::cout << "NonPlayer Turn State!" << std::endl;
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(false);
    ui->endGameButton->setDisabled(false);
    ui->startOverButton->setDisabled(true);
    ui->numberOfPlayersComboBox->setDisabled(true);
    ui->playerGraphicsView->setDisabled(true);
\
}

/**
 * @brief Game::SetGameOverState disable all user buttons except start over
 * button
 */
void Game::SetGameOverState() {
    std::cout << "Game Over State!" << std::endl;
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(true);
    ui->endGameButton->setDisabled(true);
    ui->startOverButton->setDisabled(false);
    ui->numberOfPlayersComboBox->setDisabled(true);
}

/**
 * @brief Game::set_game_state calls the method that corresponds to the new_state
 * of the game in order to change the state. Also sets current_state_ field on game.
 * @param new_state is the desired next state of the game
 */
void Game::set_game_state(GameState new_state) {
    switch(new_state) {
    case GameState::Initial:
        SetInitialState();
        break;
    case GameState::PlayerTurn:
        SetPlayerTurnState();
        break;
    case GameState::NonPlayerTurn:
        SetNonPlayerTurnState();
        break;
    case GameState::GameOver:
        SetGameOverState();
        break;
    default:
        break;
    }
    current_state_ = new_state;
}

/**
 * @brief Game::SetNumberOfPlayers is a slot that is signaled by the number of players combo box.
 * When a user selects a number of players this method updates the list of player configs, dynamically
 * adapts to changing number of players.
 * @param index
 */
void Game::SetNumberOfPlayers(int index) {
    int new_number_of_players = index + 2;
    int current_number_of_players = player_configs_.size();
    //do nothing if number of players selected by user equals current number
    if(current_number_of_players == new_number_of_players)
        return;
    //add new players if player selected a greater number of players
    else if (new_number_of_players > current_number_of_players) {
        int players_to_add = new_number_of_players - current_number_of_players;
        while (players_to_add > 0) {
            PlayerConfig* pc = new PlayerConfig();
            pc->name = "";
            player_configs_.push_back(pc);
            players_to_add--;
            UpdatePlayersView();
        }
    }
    //remove new players if player selected a smaller number of players
    else {
        int players_to_remove = current_number_of_players - new_number_of_players;
        while (players_to_remove > 0) {
            player_configs_.pop_back();
            players_to_remove--;
            UpdatePlayersView();
        }
    }
}

/**
 * @brief Game::UpdatePlayersView sets the players-view scene on the ui to show
 * A playerWidget for each player selected. A playerWidget contains a line edit
 * where user can enter a name and a checkbox where they can select AI or not.
 *
 */
void Game::UpdatePlayersView() {
    player_scene_->clear();
    QGroupBox* playerWidgets = new QGroupBox;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    //make the layout fit the graphics view
    mainLayout->setMargin(9);
    int next_player_number = 1;
    for(PlayerConfig* config :player_configs_){
        PlayerDisplayHandler* pdh = new PlayerDisplayHandler(config, next_player_number);
        mainLayout->addWidget(pdh->get_group_box());
        next_player_number ++;
    }
    playerWidgets->setLayout(mainLayout);
    player_scene_->addWidget(playerWidgets);
 }

/**
 * @brief Game::CreatePlayers iterates through the player config list and creates
 * either an AiPlayer or HumanPlayer depending on the is_ai bool in the PlayerConfig
 */
void Game::CreatePlayers(){
    for(PlayerConfig* pc: player_configs_){
        Player* player;
        if(pc->is_ai){
            player = new AiPlayer(pc);
        }
        else{
            player = new HumanPlayer(pc);
        }
        players_.push_back(player);
    }
    player_count_ = players_.size();
}

/**
 * @brief Game::GetNextPlayer gets the next player in the list in a circular fashion
 * @return the player object of the next player
 */
Player* Game::GetNextPlayer(){
    Player* next_player;
    if(current_player_index_ >= player_count_-1){
        current_player_index_ = 0;
    }
    else{
        current_player_index_++;
    }
    next_player = players_[current_player_index_];
    std::cout << "new player is: " << next_player->get_name() << " and is AI = " << next_player->get_is_ai() << std::endl;
    return next_player;
}

/**
 * @brief Game::UpdatePlayerDashboard
 */
void Game::UpdatePlayerDashboard(){
    PlayerDashboard* pd = new PlayerDashboard();
    Hand* current_hand = new Hand;
    current_hand->oil = 2;
    current_hand->food = 4;
    current_hand->steel = 6;
    current_player_->set_hand(current_hand);
    pd->set_current_player(current_player_);
    pd->UpdateCounts();
    QGroupBox* resourceWidgets = new QGroupBox;
    QVBoxLayout* resourceLayout = new QVBoxLayout;
    resourceLayout->addWidget(pd->get_group_box());
    resourceLayout->setMargin(.25);
    resourceWidgets->setLayout(resourceLayout);
    hand_scene_->addWidget(resourceWidgets);
}


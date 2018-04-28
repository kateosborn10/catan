
#include "game.h"
#include "ui_game.h"
#include "aiplayer.h"
#include "humanplayer.h"
#include <iostream>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QtWidgets>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>
#include "dicerollnumber.h"
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
    ShowWelcomeScreen();
    // instantiate graphics scenes
    CreateScenes();
    // set scences and alignments for graphics views
    SetScenes();
    // connect signals to slots on the game
    connect(ui->playGameButton, SIGNAL(released()), this, SLOT(PlayGame()));
    connect(ui->advanceTurnButton, SIGNAL(released()), this, SLOT(AdvanceTurn()));
    connect(ui->endGameButton, SIGNAL(released()), this, SLOT(EndGame()));
    connect(ui->startOverButton, SIGNAL(released()), this, SLOT(StartOver()));
//    connect(ui->numberOfPlayersComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetNumberOfPlayers(int)));
//    // add items to number of players combo box
    QStringList playerOptions;
    //http://doc.qt.io/qt-5/qstringlist.html
    playerOptions << "2" << "3" << "4";
    ui->numberOfPlayersComboBox->addItems(playerOptions);
//     set the game state to Initial to begin
    set_game_state(GameState::Initial);

}


/**
 * @brief Game::~Game dtor for Game class, deletes ui instance
 */
Game::~Game()
{
    delete ui;
}

void Game::ShowWelcomeScreen(){
    // the following two lines will show the welcome screen and wait for it to finish before executing game window
    screen_.show();
    screen_.exec();
}

void Game::CreateScenes(){
    game_scene_ = new QGraphicsScene;
    player_scene_ = new QGraphicsScene;
    hand_scene_ = new QGraphicsScene;
    build_card_scene_ = new QGraphicsScene;
}
void Game::SetScenes(){
    ui->boardGraphicsView->setScene(game_scene_);
    ui->playerGraphicsView->setScene(player_scene_);
    ui->handGraphicsView->setScene(hand_scene_);
    ui->buildCardGraphicsView->setScene(build_card_scene_);
    ui->handGraphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    ui->playerGraphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
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
    ui->numberOfPlayersComboBox->setDisabled(true);
    ui->handGraphicsView->hide();
    ui->buildCardGraphicsView->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    // allow users to enter their names and check AI box
    CreatePlayerWidgets();
    ui->playerGraphicsView->setDisabled(false);

}

/**
 * @brief Game::PlayGame is a slot that is signaled when a user presses
 * the play button on the ui. It calls set_game_state with PlayerTurn as the new_state,
 * calls CreatePlayers to populate players_ list, sets current_player_ field to the first
 * player, and calls method to update the player dashboard.
 */
void Game::PlayGame() {
    //player goes first
    set_game_state(GameState::PlayerTurn);
    CreatePlayers();
    // set current player to player1
    current_player_index_ = -1;
    current_player_ = GetNextPlayer();
    dashboard_ = new PlayerDashboard();
    connect(this, SIGNAL(DisableBuild(bool)), dashboard_, SLOT(EnableBuild(bool)));
    SetPlayerDashboard();
    UpdatePlayerDashboard();
    // show the dashboard to the user
    ui->handGraphicsView->show();
    ui->buildCardGraphicsView->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    board_ = new Board();
    CreateBoard();
    DisplayDiceRollNumbers();
    CreateNodes();
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
        // if player is AI then don't show their hand
        ui->handGraphicsView->hide();

    }
    else{
        ui->handGraphicsView->show();
        set_game_state(GameState::PlayerTurn);
        UpdatePlayerDashboard();
    }
}
/**
 * @brief Game::EndGame is a slot that is signaled when a user pressed end game
 * button. Sets game state to GameOver and clears the hand graphics view
 */
void Game::EndGame() {
    set_game_state(GameState::GameOver);
    ui->handGraphicsView->hide();
    delete dashboard_;

}

/**
 * @brief Game::StartOver is a slot that is signaled when a user presses start
 * over button. Sets game state to Initial and clears the players vector
 */
void Game::StartOver() {
    ClearGame();
    DeleteAllDisplays();
    CreateScenes();
    SetScenes();
    screen_.ResetComboBoxes();
    ShowWelcomeScreen();
    set_game_state(GameState::Initial);
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
    // prevent users from changing number of players or player info now that game play has begun
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


void Game::CreatePlayerWidgets(){
    //get number of players from welcomescreen
    num_players_ = screen_.get_number_players();
    human_players_ = screen_.get_number_human_players();
    QColor human_colors[4] = {"red", "green", "darkyellow", "black"};
    QColor ai_colors[4] = {"blue", "orange", "brown"};
    // create human players
    for(int i = 0; i < human_players_; i++){
        PlayerConfig* pc = new PlayerConfig();
        pc->name = "Enter name here";
        pc->is_ai = false;
        pc->color = human_colors[i];
        player_configs_.push_back(pc);
    }

    // create ai players
    for(int i = 0; i < num_players_ - human_players_; i++){
        PlayerConfig* pc = new PlayerConfig();
        pc->name = "Computer " + std::to_string(i+1);
        pc->is_ai = true;
        pc->color = ai_colors[i];
        player_configs_.push_back(pc);
    }

    UpdatePlayersView();
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
}

/**
 * @brief Game::GetNextPlayer gets the next player in the list in a circular fashion
 * @return the player object of the next player
 */
Player* Game::GetNextPlayer(){
    Player* next_player;
    if(current_player_index_ >= num_players_-1){
        current_player_index_ = 0;
    }
    else{
        current_player_index_++;
    }
    next_player = players_[current_player_index_];
    return next_player;
}

/**
 * @brief Game::UpdatePlayerDashboard sets the current player
 * of the dashboard, updates the resource counts,
 * and calls reset button method on dashboard to get ready for new player.
 */
void Game::UpdatePlayerDashboard(){
    // this is for testing purposes, in future will not hard-code hand for players
    Hand* current_hand = new Hand;
    current_hand->oil = 2;
    current_hand->food = 4;
    current_hand->steel = 6;
    current_player_->set_hand(current_hand);
    dashboard_->set_current_player(current_player_);
    dashboard_->UpdateCounts();
    dashboard_->ResetButtons();


}

/**
 * @brief Game::SetPlayerDashboard connects PlaceBuilding signal on dashboard to game
 * and sets the handscene to the resourceWidgets from player dashboard.
 */
void Game::SetPlayerDashboard(){
    connect(dashboard_, SIGNAL(PlaceBuilding(Buildings)), this, SLOT(BuildButtonPressed(Buildings)));
    QGroupBox* resourceWidgets = new QGroupBox;
    QVBoxLayout* resourceLayout = new QVBoxLayout;
    resourceLayout->addWidget(dashboard_->get_group_box());
    resourceLayout->setMargin(1);
    resourceWidgets->setLayout(resourceLayout);
    hand_scene_->addWidget(resourceWidgets);
}


/**
 * @brief Game::CreateBoard
 * Creates a semi-random board.Try to maintain same numbers of resources
 */
void Game:: CreateBoard(){
    Resource tile_resource;
    int dice_roll_numbers[19] = {11, 12, 9, 4, 6, 5, 10, 3, 11, 4, 8, 2, 8, 10, 9, 3, 5, 2, 6};
    srand(time(NULL));
    int start_number = rand() % 3 + 1; // random number between 1 and 3 decides which tile we start with
    QBrush brush;
    QPen pen(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    int i = 0;
    for(QPolygonF poly: board_->get_polygon()){

        switch(start_number){
        case 1:
            brush.setColor(QColor(64, 64, 64, 150));
            tile_resource = Resource::Oil;
            break;
        case 2:
            brush.setColor(QColor(255, 255, 102, 150));
            tile_resource = Resource::Food;
            break;
        case 3:
            brush.setColor(QColor(102, 153, 204, 150));
            tile_resource = Resource::Steel;
            break;
        }

        game_scene_->addPolygon(poly, pen, brush);
        tiles_.push_back(new Tile(poly, tile_resource, dice_roll_numbers[i]));
        if(start_number == 3)
            start_number = 1;
        else
            start_number++;
         i++;
    }
}


void Game::DisplayDiceRollNumbers(){
    for(Tile* t: tiles_){
        QPointF mid_point = t->GetMidPoint();
        DiceRollNumber* drn = new DiceRollNumber(mid_point, t->get_dice_roll_number());
        game_scene_->addItem(drn);

    }

}
/**
 * @brief Game::CreateNodes
 */
void Game::CreateNodes(){


    std::vector<QPointF> tmp_vertices;
    // fill tmp_vertices with all vertices on board, including repeats
    for(Tile* t: tiles_){
        for(QPointF p: t->get_polygon()){
            tmp_vertices.push_back(p);

        }
    }

    // clean the list of duplicates
    std::vector<QPointF> clean_vertices;
    bool found;
    for(int i = 0; i < tmp_vertices.size(); i++){
        found = false;
        for(int j = 0; j < clean_vertices.size(); j++ ){
            if(tmp_vertices.at(i) == clean_vertices.at(j)){
                found = true;
                break;
            }
        }
        if(!found){
            clean_vertices.push_back(tmp_vertices.at(i));
        }
    }
    // make nodes
    for(QPointF p: clean_vertices){
        std::vector<Tile*> neighboring_tiles;
        for(Tile* t: tiles_){
            for(QPointF p2: t->get_polygon()){
                if(p == p2)
                    neighboring_tiles.push_back(t);
            }
        }
        Node* n = new Node(p, neighboring_tiles);
        //connect(n,SIGNAL(NodeSelected(Node*)), this, SLOT(Build(Node*)));
        connect(n,SIGNAL(NodeSelected(Node*)), this, SLOT(Select(Node*)));
        connect(n, SIGNAL(secondNodeForWallSelected(Node*,Node*)), this, SLOT(WallNodesSelected(Node*,Node*)));

        game_scene_->addItem(n);
        nodes_.push_back(n);
    }

}


void Game::Select(Node* selected_node){
    current_node_ = selected_node;
    for(Node* n: nodes_)
        n->set_is_selected(false);
    current_node_->set_is_selected(true);
    // check if player can build what they want to
    if(current_player_->get_build_validate()){
        // now check if the node they selected is viable for building type
        switch(current_player_->get_current_build()){
        case Buildings::Outpost:
            if(current_node_->get_building() == Buildings::None)
                emit DisableBuild(false);
            break;
        case Buildings::Base:
            // Can build a Base if either no building on node, or current building is an outpost and you own it
            if(current_node_->get_building() == Buildings::None || ( current_node_->get_building() == Buildings::Outpost && current_node_->get_player() == current_player_))
                emit DisableBuild(false);
            break;
        case Buildings::Wall:
            // don't know how I am going to do this yet..
            break;
        default:
            break;
        }
    }
}

/**
 * @brief Game::BuildButtonPressed is a slot called by player dashboard when
 * player pressed the build button. Responsible for decrementing the player's hand
 * based on what building they would like to build. Note that validation for the build
 * has already occurred. Also increments the associated buildings_owned count on player.
 * @param building
 */
void Game::BuildButtonPressed(Buildings building){
    //decrement resources
    switch(building){
    case Buildings::Wall:{
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        QPen pen;
        pen.setColor(current_player_->get_color());
        pen.setWidth(3);
        Wall* wall = new Wall(wall_from_node_, current_node_, current_player_);
        walls_.push_back(wall);
        game_scene_->addLine(wall->get_wall(), pen);
        current_node_->ClearWallFrom();
        break;
    }

    case Buildings::Outpost:
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        current_player_->RemoveResourceFromHand(Resource::Food, 1);
        break;

    case Buildings::Base:
        current_player_->RemoveResourceFromHand(Resource::Oil, 2);
        current_player_->RemoveResourceFromHand(Resource::Steel, 2);
        current_player_->RemoveResourceFromHand(Resource::Food, 2);
        break;
    default:
        break;
    }
    current_node_->Build(building, current_player_);
    current_player_->AddBuildingToBuildingsOwned(building);
    current_player_->set_build_validate(false);
    dashboard_->UpdateCounts();
}

/**
 * @brief Game::WallNodesSelected
 * @param from
 * @param to
 */
void Game::WallNodesSelected(Node *from, Node *to){
    // checks if player has enough resources && if they have selected wall in build dropdown
    if((current_player_->get_build_validate()) && (current_player_->get_current_build() == Buildings::Wall)){
        bool disable_val;
        current_node_ = to;
        wall_from_node_ = from;
        Player* from_player = from->get_player();
        Player* to_player = to->get_player();
        // check to see if player can build wall
        // case 1: player owns both nodes
        if(from_player == current_player_ && to_player == current_player_ ){
            disable_val = false;
        }
        // case 2: player owns from node OR to node
        else if(from_player == current_player_ || to_player == current_player_){
            disable_val = false;
        }
        //case 3: player owns road leading to from node



        else{
            disable_val = true;
        }

//        // case 4: no one owns either but player has road leading to from node
//        else if()


        emit DisableBuild(disable_val);
    }else{
        from->ClearWallFrom();
    }
}

// on the even of a player pressing start over we need to clear all game state
void Game::ClearGame(){
    players_.clear();
    player_configs_.clear();
    nodes_.clear();
    tiles_.clear();
}
void Game::DeleteAllDisplays(){
    delete board_;
    delete player_scene_;
    delete hand_scene_;
    delete game_scene_;
    delete build_card_scene_;
}

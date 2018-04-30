
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
//     set the game state to Initial to begin
    set_game_state(GameState::Initial);
}


/**
 * @brief Game::~Game dtor for Game class, deletes ui instance
 */
Game::~Game(){
    delete ui;
}

/**
 * @brief Game::ShowWelcomeScreen show the welcome screen and wait for it to finish before executing game window
 */
void Game::ShowWelcomeScreen(){
    screen_.show();
    screen_.exec();
}

/**
 * @brief Game::CreateScenes creates the scenes for all graphics views for game
 */
void Game::CreateScenes(){
    game_scene_ = new QGraphicsScene;
    player_scene_ = new QGraphicsScene;
    hand_scene_ = new QGraphicsScene;
    build_card_scene_ = new QGraphicsScene;
}

/**
 * @brief Game::SetScenes sets the scenes of each graphics view
 */
void Game::SetScenes(){
    ui->boardGraphicsView->setScene(game_scene_);
    ui->playerGraphicsView->setScene(player_scene_);
    ui->handGraphicsView->setScene(hand_scene_);
    ui->buildCardGraphicsView->setScene(build_card_scene_);
    ui->handGraphicsView->setAlignment(Qt::AlignCenter|Qt::AlignTop);
    ui->playerGraphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
}

/**
 * @brief Game::SetInitialState is called by set_game_state() and is
 * reponsible for disabling all user buttons except play and numbers
 * of players.
 */
void Game::SetInitialState() {
    ui->playGameButton->setDisabled(false);
    ui->advanceTurnButton->setDisabled(true);
    ui->endGameButton->setDisabled(true);
    ui->startOverButton->setDisabled(true);
    ui->handGraphicsView->hide();
    ui->buildCardGraphicsView->hide();
    CreatePlayerConfigs();
    ui->playerGraphicsView->setDisabled(false);
    ui->diceLineEdit->setDisabled(true);

}

/**
 * @brief Game::PlayGame is a slot that is signaled when a user presses
 * the play button on the ui. It calls set_game_state with PlayerTurn as the new_state,
 * calls CreatePlayers to populate players_ list, sets current_player_ field to the first
 * player, and calls method to update the player dashboard.
 */
void Game::PlayGame() {
    set_game_state(GameState::PlayerTurn);
    CreatePlayers();
    // set current player index to -1
    current_player_index_ = -1;
    current_player_ = GetNextPlayer();
    DisplayTurnIndicator();
    CreateDashboard();
    SetPlayerDashboard();
    UpdatePlayerDashboard();
    SetPlayerView();
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
    if(current_player_->get_is_initial_turn()){
        GiveInitialResources();
        current_player_->set_is_initial_turn(false);
    }
    current_player_ = GetNextPlayer();
    SetPlayerView();
    DisplayTurnIndicator();
    if(!current_player_->get_is_initial_turn()){
        int dice_val = RollDice();
        ui->diceLineEdit->setText(QString::number(dice_val));
        AllocateResources(dice_val);
    }
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
 * over button. Resets the state of the game.
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
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(false);
    ui->endGameButton->setDisabled(false);
    ui->startOverButton->setDisabled(true);
    ui->playerGraphicsView->setDisabled(true);


}

/**
 * @brief Game::SetNonPlayerTurnState disables all user buttons except
 * advance turn and end game buttons.
 */
void Game::SetNonPlayerTurnState() {
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(false);
    ui->endGameButton->setDisabled(false);
    ui->startOverButton->setDisabled(true);
    ui->playerGraphicsView->setDisabled(true);
\
}

/**
 * @brief Game::SetGameOverState disable all user buttons except start over
 * button
 */
void Game::SetGameOverState() {
    ui->playGameButton->setDisabled(true);
    ui->advanceTurnButton->setDisabled(true);
    ui->endGameButton->setDisabled(true);
    ui->startOverButton->setDisabled(false);
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
 * @brief Game::CreatePlayerWidgets grabs the user input from the welcome screen
 * and uses it to create the player configs.
 */
void Game::CreatePlayerConfigs(){
    //get number of players from welcomescreen
    num_players_ = screen_.get_number_players();
    human_players_ = screen_.get_number_human_players();
    QColor human_colors[4] = {"red", "green", "magenta", "darkCyan"};
    QColor ai_colors[4] = {"blue", "orange", "brown"};
    // create human players
    for(int i = 0; i < human_players_; i++){
        PlayerConfig* pc = new PlayerConfig();
        pc->name = "Player " + std::to_string(i+1);
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
    dashboard_->set_current_player(current_player_);
    dashboard_->UpdateCounts();
    dashboard_->ResetButtons();


}

/**
 * @brief Game::SetPlayerDashboard connects PlaceBuilding signal on dashboard to game
 * and sets the handscene to the resourceWidgets from player dashboard.
 */
void Game::SetPlayerDashboard(){
    connect(dashboard_, SIGNAL(PlaceBuilding(BuildingType)), this, SLOT(BuildButtonPressed(BuildingType)));
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
    board_ = new Board();
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
        case BuildingType::Outpost:
            if(current_node_->get_building() == BuildingType::None)
                emit DisableBuild(false);
            break;
        case BuildingType::Base:
            // Can build a Base if either no building on node, or current building is an outpost and you own it
            if(current_node_->get_building() == BuildingType::None || ( current_node_->get_building() == BuildingType::Outpost && current_node_->get_player() == current_player_))
                emit DisableBuild(false);
            break;
        case BuildingType::Wall:
            selected_node->ClearWallFrom();
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
 * has already occurred. Also increments the associated BuildingType_owned count on player.
 * @param building
 */
void Game::BuildButtonPressed(BuildingType building_type){
    Building* building;
    switch(building_type){
    case BuildingType::Wall:{
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        QPen pen;
        pen.setColor(current_player_->get_color());
        pen.setWidth(3);
        building = new Wall(current_player_, building_type, wall_from_node_, current_node_);
        game_scene_->addLine(building->get_wall(), pen);
        current_node_->ClearWallFrom();
        break;
    }

    case BuildingType::Outpost:
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        current_player_->RemoveResourceFromHand(Resource::Food, 1);
        building = new Building(current_player_, building_type);
        break;

    case BuildingType::Base:
        current_player_->RemoveResourceFromHand(Resource::Oil, 2);
        current_player_->RemoveResourceFromHand(Resource::Steel, 2);
        current_player_->RemoveResourceFromHand(Resource::Food, 2);
        building = new Building(current_player_, building_type);
        break;
    default:
        break;
    }
    current_node_->Build(building);
    current_player_->AddBuildingToBuildingTypeOwned(building_type);
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
    if((current_player_->get_build_validate()) && (current_player_->get_current_build() == BuildingType::Wall)){
        bool disable_val = true;
        current_node_ = to;
        wall_from_node_ = from;
        Player* from_player = from->get_player();
        Player* to_player = to->get_player();
        // check to see if player can build wall
        // case 1: player owns both nodes
        if(from_player == current_player_ && to_player == current_player_ ){
            disable_val = false;
        }
        // case 2: player owns from-node OR to-node
        else if(from_player == current_player_ || to_player == current_player_){
            disable_val = false;
        }
        //case 3: player owns road leading to from node or to the to-node
        else{
            std::vector<Building*> walls_from = from->get_incoming_walls();
            for(Building* wall: walls_from){
                if(wall->get_player() == current_player_)
                    disable_val = false;
            }
            std::vector<Building*> walls_to = to->get_incoming_walls();
            for(Building* wall: walls_to){
                if(wall->get_player() == current_player_)
                    disable_val = false;
            }
        }

        emit DisableBuild(disable_val);
    }else{
        from->ClearWallFrom();
    }
}


int Game::RollDice(){
    srand(time(NULL));
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return die1 + die2;

}


void Game::GiveInitialResources(){
    std::vector<Tile*> tiles_on_node;
    for(Node* n: nodes_){
        if(n->get_player() == current_player_){
             tiles_on_node = n->get_tiles();
             for(Tile* t: tiles_on_node){
                 current_player_->AddResourceToHand(t->get_resource_type(), 1);
             }
        }
    }
}

void Game::AllocateResources(int dice_val){
    std::vector<Tile*> tiles_on_node;
    for(Node* n: nodes_){
        tiles_on_node = n->get_tiles();
        for(Tile* t: tiles_on_node){
            if(t->get_dice_roll_number() == dice_val){
                std::cout << "Found a match! " << std::endl;
                int increment_by = 1;
                if(n->get_building() == BuildingType::Base)
                    increment_by = 2;
                if(n->get_player() != NULL){
                    std::cout << " you shouldn't be seeing this statement!!!!!" << std::endl;
                    n->get_player()->AddResourceToHand(t->get_resource_type(), increment_by);
                }

            }
        }

    }

}


void Game::DisplayTurnIndicator(){
    QString current_player_turn_indicator = QString::fromStdString(current_player_->get_name())+ "'s Turn!";
    ui->playerTurnLabel->setText(current_player_turn_indicator);
}

void Game::CreateDashboard(){
    dashboard_ = new PlayerDashboard();
    connect(this, SIGNAL(DisableBuild(bool)), dashboard_, SLOT(EnableBuild(bool)));
}

void Game::SetPlayerView(){
    ui->handGraphicsView->show();
    ui->buildCardGraphicsView->show();
    QLabel* build_card_label = new QLabel();
    QPixmap map(":/images/buildingcosts");
    int width = build_card_label->width();
    int height = build_card_label->height();
    QPixmap scaled = map.scaled(width/3,height/3, Qt::KeepAspectRatio);
    build_card_label->setPixmap(scaled);
    build_card_scene_->addWidget(build_card_label);
    build_card_palette.setColor(QPalette::Base, current_player_->get_color());
    build_card_palette.setColor(QPalette::Text, Qt::white);
    ui->buildCardGraphicsView->setPalette(build_card_palette);
    ui->buildCardGraphicsView->update();


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

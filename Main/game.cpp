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
//#include "playerdashboard.h"
#include "game.h"
#include "ui_game.h"
#include "aiplayer.h"
#include "humanplayer.h"



/**
 * @brief Game::Game constructor for the Game class. Responsible
 * for calling methods that create and set the QGraphics scences,
 * and connecting play, advance turn, end game, start over slots.
 * @param parent is default parameter passed to a Qt widget class
 */
Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    ShowWelcomeScreen();
    CreateScenes();
    SetScenes();
    // connect signals to slots on the game
    connect(ui->playGameButton, SIGNAL(released()), this, SLOT(PlayGame()));
    connect(ui->advanceTurnButton, SIGNAL(released()), this, SLOT(AdvanceTurn()));
    connect(ui->endGameButton, SIGNAL(released()), this, SLOT(EndGame()));
    connect(ui->startOverButton, SIGNAL(released()), this, SLOT(StartOver()));
    set_game_state(GameState::Initial);
}

/**
 * @brief Game::AllocateResources gives resources to players who own nodes
 * with tiles corresponding to the dice_val.
 * @param dice_val is the value of the dice roll by current player
 */
void Game::AllocateResources(int dice_val){
    std::vector<Tile*> tiles_on_node;
    // for every node grab the tiles they touch and check the dice roll number
    // if the numbers match and a non-null player owns the node then give the
    // player resources, 1 for an outpost and 2 for a base.
    for(Node* n: nodes_){
        tiles_on_node = n->get_tiles();
        for(Tile* t: tiles_on_node){
            if(t->get_dice_roll_number() == dice_val){
                int increment_by = 1;
                if(n->get_building_type() == BuildingType::Base)
                    increment_by = 2;
                if(n->get_player() != NULL){
                    n->get_player()->AddResourceToHand(t->get_resource_type(), increment_by);
                }
            }
        }
    }
}


/**
 * @brief Game::Attack carries out the logic to see if an attack is allowed at the given node.
 * Attacks are not allowed for walls.
 * @param selected_node is the node the current player wants to attack
 * @return true if the attack was successful and false if not
 */
bool Game::Attack(Node* selected_node){
    Player* enemy_player = selected_node->get_player();
    BuildingType attack_building_type = selected_node->get_building_type();
    if(attack_building_type == BuildingType::Wall){
        std::cout << "Cannot attack a wall! " << std::endl;
        return false;
    }
   if(enemy_player != 0 && enemy_player != current_player_){
       // if node is a valid attack node then check if player has enough resources to take-over building
        if(current_player_->ValidateCanBuild(attack_building_type)){
            selected_node->RemoveBuilding();
            current_node_ = selected_node;
            enemy_player->RemoveBuildingToBuildingTypeOwned(attack_building_type);
            BuildButtonPressed(attack_building_type);
            current_player_->DecrementTroopCount(3);
            return true;
        }else{
            std::cout << "Can't attack not enough resources!" << std::endl;
            return false;
        }
     }else{
       std::cout << "Can't attack, can only attack another players building" << std::endl;
       return false;
    }
}

/**
 * @brief Game::CalculatePossibleMoves
 * @return
 */
std::vector<Move> Game::CalculatePossibleMoves(){
    std::vector<Move> possible_moves;
    for(Node* n: nodes_){
        int rating = 0;
        if(n->get_player() == 0){
            std::vector<Tile*> neighbor_tiles = n->get_tiles();
            if(neighbor_tiles.size() == 3){
                rating += 2;
                Resource first_resource = neighbor_tiles.at(0)->get_resource_type();
                if(first_resource != neighbor_tiles.at(1)->get_resource_type() && first_resource != neighbor_tiles.at(2)->get_resource_type() && neighbor_tiles.at(1)->get_resource_type() != neighbor_tiles.at(2)->get_resource_type()){
                    rating +=3;
                }else if(first_resource != neighbor_tiles.at(1)->get_resource_type() || first_resource != neighbor_tiles.at(2)->get_resource_type()){
                    rating +=1;
                }
                int sum = neighbor_tiles.at(0)->get_dice_roll_number() + neighbor_tiles.at(1)->get_dice_roll_number() + neighbor_tiles.at(1)->get_dice_roll_number() ;
                if(sum == 15 || sum == 17 || sum == 19){
                    rating += 2;
                }else if(sum == 18 || sum == 20){
                    rating += 1;
                }
            }else if(neighbor_tiles.size() == 2){
                rating += 1;
                Resource first_resource = neighbor_tiles.at(0)->get_resource_type();
                if(first_resource != neighbor_tiles.at(1)->get_resource_type()){
                    rating +=1;
                }
                int sum = neighbor_tiles.at(0)->get_dice_roll_number() + neighbor_tiles.at(1)->get_dice_roll_number();
                if(sum == 9|| sum == 7 || sum == 13){
                    rating += 1;
                }
            }

            std::cout << "The rating for this move is: " << rating << std::endl;
            Move m = {n, 0, rating};
            possible_moves.push_back(m);
        }

    }

  return possible_moves;
}

/**
 * @brief Game::CanBuildOnNode
 * @return
 */
bool Game::CanBuildOnNode(){
    switch(current_player_->get_current_build()){
    case BuildingType::Outpost:
        // case 1: Initial Build
        if(current_player_->get_is_initial_turn()){
            // can build anywhere so long as no one else has built there yet
            if(current_node_->get_building_type() == BuildingType::None)
                return true;
        }else{
            // you need a wall coming into the node to build an outpost
            std::vector<Player*> players_with_incoming_walls = current_node_->get_players_with_incoming_walls();
            for(Player* p:players_with_incoming_walls){
                if(p == current_player_){
                  return true;
                }
            }
            std::cout<< "Cannot build an outpost without a wall! " << std::endl;
            return false;
        }
    case BuildingType::Base:
        // Can build a Base if current building is an outpost and you own it
        if((current_node_->get_building_type() == BuildingType::Outpost && current_node_->get_player() == current_player_))
            return true;
        else
            return false;
    default:
        return false;

    }

}

/**
 * @brief Game::ClearGame clears all vector fields on Game and resets all int/bool fields.
 * Used on the Restart Event
 */
void Game::ClearGame(){
    players_.clear();
    player_configs_.clear();
    nodes_.clear();
    tiles_.clear();
    walls_.clear();
    current_player_= 0;
    current_node_ = 0;
    wall_from_node_ = 0;
    wall_in_progress_ = 0;
    num_players_ = 0;
    human_players_ = 0;
}

/**
 * @brief Game::CreateBoard Creates tiles on board in semi-random fashion
 * in order to to maintain same numbers of resources.Iterates through
 * polygons on board, sets color based on resources, assigns dice roll number
 * and encapsulates this information in an object Tile, stored in tiles_ vector.
 */
void Game:: CreateBoard(){
    board_ = new Board();
    Resource tile_resource;
    //dice roll numbers are static
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

/**
 * @brief Game::CreateBuildCard creates the build card image
 * and adds it to the scene
 */
void Game::CreateBuildCard(){
    QLabel* build_card_label = new QLabel();
    QPixmap map(":/images/buildingcosts");
    int width = build_card_label->width();
    int height = build_card_label->height();
    QPixmap scaled = map.scaled(width/3,height/3, Qt::KeepAspectRatio);
    build_card_label->setPixmap(scaled);
    build_card_scene_->addWidget(build_card_label);
}

/**
 * @brief Game::CreateDashboard creates a player dashboard object
 * which is shared amongst all human-players.
 */
void Game::CreateDashboard(){
    dashboard_ = new PlayerDashboard();

}
/**
 * @brief Game::CreateNodes creates a list of nodes, which are playable
 * and clickable intersections on the board. Iterates through all points
 * on every polygon on the board and deletes duplicates.
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
    // finds all the tiles that each node touches and pass a vector of these tiles to the Node constructor
    for(QPointF p: clean_vertices){
        std::vector<Tile*> neighboring_tiles;
        for(Tile* t: tiles_){
            for(QPointF p2: t->get_polygon()){
                if(p == p2)
                    neighboring_tiles.push_back(t);
            }
        }
        Node* n = new Node(p, neighboring_tiles);
        // connect the signals emitted from nodes to the game
        connect(n,SIGNAL(NodeSelected(Node*)), this, SLOT(Select(Node*)));
        connect(n, SIGNAL(WallNodeSelected(Node*)), this, SLOT(WallNodeSelected(Node*)));
        // add to scene
        game_scene_->addItem(n);
        // keep a list on game
        nodes_.push_back(n);
    }

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
 * @brief Game::CreateScenes creates the scenes for all graphics views for game
 */
void Game::CreateScenes(){
    game_scene_ = new QGraphicsScene;
    player_scene_ = new QGraphicsScene;
    hand_scene_ = new QGraphicsScene;
    build_card_scene_ = new QGraphicsScene;
}

/**
 * @brief Game::DeleteAllDisplays deletes all the scenes on the main window
 */
void Game::DeleteAllDisplays(){
    delete board_;
    delete player_scene_;
    delete hand_scene_;
    delete game_scene_;
    delete build_card_scene_;
}


/**
 * @brief Game::DisplayDiceRollNumbers creates dice roll number objects
 * for each tile on the board and draws them to the scene.
 */
void Game::DisplayDiceRollNumbers(){
    for(Tile* t: tiles_){
        QPointF mid_point = t->GetMidPoint();
        DiceRollNumber* drn = new DiceRollNumber(mid_point, t->get_dice_roll_number());
        game_scene_->addItem(drn);

    }

}

/**
 * @brief Game::DisplayTurnIndicator draws current player's name on top right of board scene
 */
void Game::DisplayTurnIndicator(){
    QString current_player_turn_indicator = QString::fromStdString(current_player_->get_name())+ "'s Turn!";
    ui->playerTurnLabel->setText(current_player_turn_indicator);
}

/**
 * @brief Game::DoesWallExist checks if a wall going to->from already exists
 * @param to is the node the wall will be drawn to
 * @param from is the node the wall will be drawn from
 * @return true if the wall already exists, false otherwise.
 */
bool Game::DoesWallExist(Node* to, Node* from){
    Wall* temp_wall = new Wall(BuildingType::Wall, to, from);
    for(Wall* wall: walls_){
        if(temp_wall->Equals(wall)){
            delete temp_wall;
            return true;
        }
    }
    delete temp_wall;
    return false;

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
 * @brief Game::GiveInitialResources gives players the resources corresponding to their initial
 * build sites. Does not require a dice roll.
 */
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


/**
 * @brief Game::IsWinner checks if the current player has enough points to win
 * @return true if player has won
 */
bool Game::IsWinner(){
    if(current_player_->CalculateScore() >= 8)
        return true;
    else
        return false;
}

/**
 * @brief Game::MakeAiMove
 * @param possible_moves
 * @return
 */
Move Game::MakeAiMove(std::vector<Move> possible_moves){
    Move best_move;
    if(current_player_->get_is_initial_turn()){
        best_move = possible_moves.at(0);
        for(Move m: possible_moves){
            if(m.rating > best_move.rating){
                best_move = m;
            }
        }

    }
    std::cout << best_move.rating << std::endl;
  return best_move;
}
int Game::RollDice(){
    srand(time(NULL));
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return die1 + die2;

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
 * @brief Game::SetInitialState is called by set_game_state() and is
 * reponsible for disabling all user buttons except play, hiding hand
 * and build card graphics views.
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
 * @brief Game::SetPlayerDashboard connects signals on dashboard to the game
 * and sets the handscene to the resourceWidgets from player dashboard.
 */
void Game::SetPlayerDashboard(){
    QGroupBox* resourceWidgets = new QGroupBox;
    QVBoxLayout* resourceLayout = new QVBoxLayout;
    resourceLayout->addWidget(dashboard_->get_group_box());
    resourceLayout->setMargin(1);
    resourceWidgets->setLayout(resourceLayout);
    hand_scene_->addWidget(resourceWidgets);
    connect(dashboard_, SIGNAL(PlaceBuilding(BuildingType)), this, SLOT(BuildButtonPressed(BuildingType)));
    connect(this, SIGNAL(DisableBuild(bool)), dashboard_, SLOT(EnableBuild(bool)));
    connect(dashboard_, SIGNAL(ToggleBuildWall(bool)), this, SLOT(ToggleBuildWall(bool)));
    connect(dashboard_, SIGNAL(Attack()), this, SLOT(AttackButtonPressed()));

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
 * @brief Game::ShowWelcomeScreen show the welcome screen and wait for it to finish before executing game window
 */
void Game::ShowWelcomeScreen(){
    screen_.show();
    screen_.exec();
}
/**
 * @brief Game::TakeInitialTurn displays a QMessageBox to user informing them of the instructions
 */
void Game::TakeInitialTurn(){
    if(!current_player_->get_is_ai()){
        const QString title = "Initial Turn Instructions! ";
        const QString content = "To begin build two outposts followed by two walls. To build an outpost select Outpost from the build options, then click on one of the white circular intersections. "
                                "Build a wall that connects to your outpost by selecting Wall from the build options, then right-clicking on your outpost and right-clicking on an open intersection.";
        QMessageBox* initial_turn_instructions = new QMessageBox(QMessageBox::Icon::Information, title, content, QMessageBox::StandardButton::Ok);
        initial_turn_instructions->show();
    }
}

/**
 * @brief Game::TakeHumanTurn holds logic for a player turn. Responsible for updating
 * the player dashboard and color of the build card to reflect the current player's information.
 */
void Game::TakeHumanTurn(){
    ui->handGraphicsView->show();
    UpdateBuildCard(current_player_->get_color());
    UpdatePlayerDashboard();
    if(!current_player_->get_is_initial_turn()){
        int dice_val = RollDice();
        ui->diceLineEdit->setText(QString::number(dice_val));
        if(dice_val == 7){
            QString troop_content = "Congrats, you earned a new troop! By rolling a 7 you gained a troop for your army. Once you have three troops you can attack one of your enemies.";
            QMessageBox* troop_notification = new QMessageBox(QMessageBox::Icon::Information, "Congrats!", troop_content, QMessageBox::StandardButton::Ok);
            troop_notification->show();
            current_player_->IncrementTroopCount(1);
            dashboard_->UpdateCounts();
        }else{
            AllocateResources(dice_val);
            dashboard_->UpdateCounts();
        }

    }
}

/**
 * @brief Game::TakeAiTurn holds the logic for a non-player turn.
 * Responsible or changing the color of the build card and hiding the
 * hand graphics view.
 */
void Game::TakeAiTurn(){
    // so human players can't see
    ui->handGraphicsView->hide();
    UpdateBuildCard(current_player_->get_color());
    if(current_player_->get_is_initial_turn()){
       Move m1 =  MakeAiMove(CalculatePossibleMoves());
       if(current_player_->ValidateCanBuild(BuildingType::Outpost)){
           current_node_ = m1.node;
           if(CanBuildOnNode()){
               BuildButtonPressed(BuildingType::Outpost);
           }
       }
       Move m2 = MakeAiMove(CalculatePossibleMoves());
       if(current_player_->ValidateCanBuild(BuildingType::Outpost)){
           current_node_ = m2.node;
           if(CanBuildOnNode()){
               BuildButtonPressed(BuildingType::Outpost);
           }
       }

    }else{
        int dice_val = RollDice();
        if(dice_val == 7){
            current_player_->IncrementTroopCount(1);
        }else{
            ui->diceLineEdit->setText(QString::number(dice_val));
            AllocateResources(dice_val);
        }

    }


}

/**
 * @brief Game::UpdateBuildCard sets the color behind the build card
 * to the color passed in. Allows user to easily see who's turn it is.
 * @param color is typically the color of the current player or white in the
 * case of a restart event
 */
void Game::UpdateBuildCard(QColor color){
    ui->buildCardGraphicsView->show();
    build_card_palette.setColor(QPalette::Base, color);
    ui->buildCardGraphicsView->setPalette(build_card_palette);
    ui->buildCardGraphicsView->update();

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
 * @brief Game::~Game dtor for Game class, deletes ui instance
 */
Game::~Game(){
    delete ui;
}



//////SLOTS

/**
 * @brief Game::AdvanceTurn is a slot that is signaled when a user presses advance
 * turn button. Is responsible for calling GiveInitialResources method
 * when the current player is finishing their initial turn. It then grabs the next player
 * in line and sets the game state to either NonPlayerTurn or PlayerTurn depending
 * on if the Player is AI or Human controlled.
 */
void Game::AdvanceTurn() {
    current_node_ = 0;
    if(current_player_->get_is_initial_turn()){
        GiveInitialResources();
        current_player_->set_is_initial_turn(false);
    }
    current_player_ = GetNextPlayer();
    DisplayTurnIndicator();

    if(current_player_->get_is_ai()){
        set_game_state(GameState::NonPlayerTurn);
        TakeAiTurn();
    }else{
        set_game_state(GameState::PlayerTurn);
        TakeHumanTurn();
    }
}


/**
 * @brief Game::AttackButtonPressed is a slot executed when the
 * attack button is pressed. Sets cursor to cross if in attack mode.
 */
void Game::AttackButtonPressed(){
    QCursor newCursor = cursor();
    // done attacking
    if(cursor().shape() == Qt::CrossCursor){
        newCursor.setShape(Qt::ArrowCursor);
        current_player_->set_attack_under_way(false);

    }else{
        newCursor.setShape(Qt::CrossCursor);
        current_player_->set_attack_under_way(true);
    }

    setCursor(newCursor);


}

/**
 * @brief Game::BuildButtonPressed is a slot called by player dashboard when
 * player pressed the build button. Responsible for decrementing the player's hand
 * based on what building they would like to build. Note that validation for the build
 * has already occurred. Also increments the associated BuildingType_owned count on player.
 * Finally, it checks after each build if the current player has won.
 * @param building
 */
void Game::BuildButtonPressed(BuildingType building_type){
    switch(building_type){
    case BuildingType::Wall:{
        std::cout << "building wall " << std::endl;
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        QPen pen;
        pen.setColor(current_player_->get_color());
        pen.setWidth(3);
        Wall* w = new Wall(building_type, wall_from_node_, current_node_);
        walls_.push_back(w);
        QLineF line = w->get_wall();
        game_scene_->addLine(line, pen);
        break;
    }

    case BuildingType::Outpost:
        current_player_->RemoveResourceFromHand(Resource::Oil, 1);
        current_player_->RemoveResourceFromHand(Resource::Steel, 1);
        current_player_->RemoveResourceFromHand(Resource::Food, 1);
        break;

    case BuildingType::Base:
        current_player_->RemoveResourceFromHand(Resource::Oil, 2);
        current_player_->RemoveResourceFromHand(Resource::Steel, 2);
        current_player_->RemoveResourceFromHand(Resource::Food, 2);
        // if building a base then we must remove the outpost there
        current_player_->RemoveBuildingToBuildingTypeOwned(BuildingType::Outpost);
        break;
    default:
        break;
    }
    current_node_->Build(building_type, current_player_);
    current_player_->AddBuildingToBuildingTypeOwned(building_type);
    current_player_->set_build_validate(false);
    dashboard_->UpdateCounts();

    // check if this building makes the current player the winner. If so, call end game method.
    if(IsWinner()){
        QMessageBox* winner = new QMessageBox(QMessageBox::Icon::Information, "hello", "CONGRATS! YOU WIN! ", QMessageBox::StandardButton::Ok);
        winner->show();
        EndGame();
    }
}

/**
 * @brief Game::EndGame is a slot that is signaled when a user pressed end game
 * button. Sets game state to GameOver and clears the hand graphics view
 */
void Game::EndGame() {
    set_game_state(GameState::GameOver);
    delete dashboard_;

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
    CreateBuildCard();
    CreateBoard();
    DisplayDiceRollNumbers();
    CreateNodes();
    UpdateBuildCard(current_player_->get_color());
    ui->handGraphicsView->show();
    ui->boardGraphicsView->show();
    ui->diceLineEdit->show();
    ui->label_4->show();
    ui->playerTurnLabel->show();
    TakeHumanTurn();
}

/**
 * @brief Game::Select
 * @param selected_node
 */
void Game::Select(Node* selected_node){
    if(current_player_->get_attack_under_way()){
        if(Attack(selected_node)){
            std::cout << "Success! You Attacked! " << std::endl;
        }
    }else{
        current_node_ = selected_node;
        for(Node* n: nodes_)
            n->set_is_selected(false);
        current_node_->set_is_selected(true);
        // check if player can build what they want to
        if(current_player_->get_build_validate()){
            if(CanBuildOnNode()){
                emit DisableBuild(false);
            }else{
                std::cout << "Cannot Build here!" << std::endl;
            }
       }
    }
}

/**
 * @brief Game::StartOver is a slot that is signaled when a user presses start
 * over button. Resets the state of the game.
 */
void Game::StartOver() {
    ClearGame();
    DeleteAllDisplays();
    ui->diceLineEdit->hide();
    ui->label_4->hide();
    ui->playerTurnLabel->hide();
    UpdateBuildCard("white");
    CreateScenes();
    SetScenes();
    screen_.ResetComboBoxes();
    ShowWelcomeScreen();
    set_game_state(GameState::Initial);
}

/**
 * @brief Game::ToggleBuildWall is a slot that is signaled by a user when they
 * select Wall from the dropdown build list. Resets fields on Game that store
 * current wall information.
 * @param value
 */
void Game::ToggleBuildWall(bool value){
    current_node_ = 0;
    wall_from_node_ = 0;
    wall_in_progress_ = value;
    possible_to_nodes_.clear();

}

/**
 * @brief Game::WallNodeSelected holds the logic for building walls.
 * Sets the current_node and wall_from_node fields in appropriate order and under
 * specific conditions. If wall is valid the build button is signaled to be enabled.
 * @param selected_node is the node the user right-clicked on to build a wall from/to.
 */
void Game::WallNodeSelected(Node* selected_node){
    bool valid_wall = false;
    // first make sure user has selected Wall from drop down
    if(wall_in_progress_){
        // if no wall_from_ node then set it to selected node
        if(wall_from_node_ == 0){
            // Allow wall_from_node to be a node that the player owns
            if(selected_node->get_player() == current_player_){
                valid_wall = true;
            }else{
                // or allow wall_from_node to be a node that a player has a wall to
                std::vector<Player*> players_with_walls = selected_node->get_players_with_incoming_walls();
                for(Player* p: players_with_walls){
                    if(p == current_player_)
                        valid_wall = true;
                }
            }
            if(valid_wall == true){
             // if node passes the above tests and is a valid choice the set it as wall_from_node
                wall_from_node_ = selected_node;
                for(Node* n: nodes_){
                    // make a vector of possible to nodes by checking distance
                    int dist = wall_from_node_->CalculateDistance(n);
                    if(dist > 0 && dist < 60){
                        possible_to_nodes_.push_back(n);
                    }
                }

            }else{
                std::cout << "Not a valid choice to build a wall from, must own the node or have a wall to that node" << std::endl;
            }
         // case where wall_from_node already set but current_node is unset
        }else if(current_node_ == 0){
            // check if selected node is in the list of possible to nodes
                for(Node* n: possible_to_nodes_){
                    if(selected_node == n){
                        current_node_ = selected_node;
                    }
                }
                if(current_node_ == 0){
                    std::cout << "Too far away to build a wall!" << std::endl;
                }
            }

        // case where both current and wall_from nodes are set and valid
        if(current_node_ != 0 && wall_from_node_ != 0){
            // lastly must check the wall doesn't exists. If it doesn't then enable the build button
            if(!DoesWallExist(current_node_, wall_from_node_))
                emit DisableBuild(false);
            else {
                std::cout << "Wall already exists! " << std::endl;
                current_node_ = 0;
                wall_from_node_ = 0;
             }

        }
    }
}

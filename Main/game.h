/**
Responsible for all the logic for playing the game
Contains reference to the main window and the welcome screen
Creates and maintains a list of players
*/

#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "player.h"
#include <vector>
#include <QGraphicsScene>
#include "welcomescreen.h"
#include "playerdashboard.h"
#include "board.h"
#include "tile.h"
//#include "node.h"
#include "wall.h"


namespace Ui {
class Game;
}

enum class GameState { Initial, PlayerTurn, NonPlayerTurn, GameOver, Trade, Build };

// had to put this here to avoid circular dependencies
struct Move

{
    Move(Node* node = 0, Node* node_from = 0, BuildingType type= BuildingType::None, int rating = 0): node(node), node_from(node_from), type(type), rating(rating) {}
    Node* node;
    Node* node_from; // used for a wall
    BuildingType type;
    int rating;
};



class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    void AllocateResources(int dice_val);
    bool Attack(Node* selected_node);
    int AssignNodeRating(Node* node);
//    std::vector<Move> CalculatePossibleBaseNodes();
    std::vector<Move> CalculatePossibleMoves(BuildingType type);
    std::vector<Move> CalculatePossibleWalls();
    bool CanBuildOnNode();
    void ClearGame();
    void CreateBoard();
    void CreateBuildCard();
    void CreateDashboard();
    void CreateNodes();
    void CreatePlayerConfigs();
    void CreatePlayers();
    void CreateScenes();
    void DeleteAllDisplays();
    void DisplayDiceRollNumbers();
    void DisplayTurnIndicator();
    bool DoesWallExist(Node* to, Node* from);
    Player* GetNextPlayer();
    void GiveInitialResources();
    bool IsWinner();
    Move MakeAiMove(std::vector<Move> possible_moves);
    Move MakeAiWallMove(std::vector<Move> possible_walls);
    int RollDice();
    void SetGameOverState();
    void SetInitialState();
    void SetPlayerDashboard();
    void SetPlayerTurnState();
    void SetNonPlayerTurnState();
    void SetScenes();
    void ShowWelcomeScreen();
    void TakeInitialTurn();
    void TakeHumanTurn();
    void TakeAiTurn();
    void UpdateBuildCard(QColor color);
    void UpdatePlayerDashboard();
    void UpdatePlayersView();
    void set_game_state(GameState new_state);
    GameState get_game_state() { return current_state_; }
    ~Game();

signals:
    void DisableBuild(bool disable_value);


public slots:
    void AdvanceTurn();
    void AttackButtonPressed();
    void BuildButtonPressed(BuildingType building);
    void EndGame();
    void PlayGame();
    void Select(Node* selected_node);
    void StartOver();
    void ToggleBuildWall(bool value);
    void WallNodeSelected(Node* selected_node);



private:
    Board* board_;
    PlayerDashboard* dashboard_;
    Ui::Game *ui;
    WelcomeScreen screen_;
    GameState current_state_;


    // scenes
    QGraphicsScene* game_scene_;
    QGraphicsScene* hand_scene_;
    QGraphicsScene* player_scene_;
    QGraphicsScene* build_card_scene_;


    Player* current_player_;
    Node* current_node_ = 0;
    Node* wall_from_node_ = 0;

    int num_players_;
    int human_players_;
    int current_player_index_;
    QPalette build_card_palette;
    bool wall_in_progress_;

    std::vector<Player*> players_;
    std::vector<PlayerConfig*> player_configs_;
    std::vector<Tile*> tiles_;
    std::vector<Node*> nodes_;
    std::vector<Wall*> walls_;
    std::vector<Node*> possible_to_nodes_;





};



#endif // GAME_H

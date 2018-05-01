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
#include "node.h"
#include "wall.h"
#include "move.h"

namespace Ui {
class Game;
}

enum class GameState { Initial, PlayerTurn, NonPlayerTurn, GameOver, Trade, Build };

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    void ShowWelcomeScreen();
    void CreateScenes();
    void SetScenes();
    void CreatePlayers();
    void CreateNodes();
    void DisplayDiceRollNumbers();
    void DisplayTurnIndicator();
    void CreateDashboard();
    void UpdateBuildCard();
    Player* GetNextPlayer();
    void ClearGame();
    void DeleteAllDisplays();
    int RollDice();
    void GiveInitialResources();
    void SetInitialState();
    void SetPlayerTurnState();
    void SetNonPlayerTurnState();
    void SetGameOverState();
    void UpdatePlayersView();
    void UpdatePlayerDashboard();
    void SetPlayerDashboard();
    void CreateBoard();
    void CreatePlayerConfigs();
    void CreateBuildCard();
    void AllocateResources(int dice_val);
    void TakeInitialTurn();
    void TakeHumanTurn();
    void TakeAiTurn();
    std::vector<Move> CalculatePossibleMoves();
    bool IsWinner();
    void set_game_state(GameState new_state);
    GameState get_game_state() { return current_state_; }
    ~Game();

signals:
    void DisableBuild(bool disable_value);


public slots:
    void PlayGame();
    void AdvanceTurn();
    void EndGame();
    void StartOver();
    void BuildButtonPressed(BuildingType building);
    void Select(Node* selected_node);
    void WallNodesSelected(Node* from, Node* to);
    void ToggleBuildWall(bool value);


private:
    Ui::Game *ui;
    WelcomeScreen screen_;
    GameState current_state_;
    PlayerDashboard* dashboard_;
    std::vector<Player*> players_;
    std::vector<PlayerConfig*> player_configs_;
    // scenes
    QGraphicsScene* game_scene_;
    QGraphicsScene* hand_scene_;
    QGraphicsScene* player_scene_;
    QGraphicsScene* build_card_scene_;

    Board* board_;
    Player* current_player_;
    Node* current_node_;
    Node* wall_from_node_;

    int num_players_;
    int human_players_;
    int current_player_index_;

    std::vector<Tile*> tiles_;
    std::vector<Node*> nodes_;
    std::vector<Wall*> walls_;

    QPalette build_card_palette;
    bool wall_in_progress_;


};



#endif // GAME_H

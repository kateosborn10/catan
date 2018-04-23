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

namespace Ui {
class Game;
}

enum class GameState { Initial, PlayerTurn, NonPlayerTurn, GameOver, Trade, Build };

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    void CreatePlayers();
    Player* GetNextPlayer();
    void set_game_state(GameState new_state);
    GameState get_game_state() { return current_state_; }
    ~Game();

signals:

public slots:
    void PlayGame();
    void AdvanceTurn();
    void EndGame();
    void StartOver();
    void SetNumberOfPlayers(int index);
    void BuildButtonPressed(Buildings building);

private:
    Ui::Game *ui;
    WelcomeScreen screen_;
    GameState current_state_;
    PlayerDashboard* dashboard_;
    std::vector<Player*> players_;
    std::vector<PlayerConfig*> player_configs_;
    QGraphicsScene* game_scene_;
    QGraphicsScene* hand_scene_;
    QGraphicsScene* player_scene_;
    Player* current_player_;
    int player_count_;
    int num_players_;
    int current_player_index_;
    void SetInitialState();
    void SetPlayerTurnState();
    void SetNonPlayerTurnState();
    void SetGameOverState();
    void UpdatePlayersView();
    void UpdatePlayerDashboard();
    void SetPlayerDashboard();
};



#endif // GAME_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Board.h"
#include "library.h"
#include "gamerecord.h"

// Added LEADERBOARD to GameState
enum class GameState { MENU, RULES, CREDITS, LEADERBOARD, PLAYING, GAMEOVER, NAME_INPUT };

// Struct to hold parsed file data
struct LeaderboardEntry {
    std::string white;
    std::string black;
    std::string result;
    std::string date;
};

class SFMLEngine {
private:
    sf::RenderWindow window;
    GameState currentState;
    Board board;
    std::string currentTurn;

    sf::Font font;
    std::map<std::string, sf::Texture> pieceTextures;

    int selectedX;
    int selectedY;

    // UI Elements for Menu
    sf::RectangleShape btnStart;
    sf::RectangleShape btnRules;
    sf::RectangleShape btnLeaderboard; // New Button
    sf::RectangleShape btnCredits;
    sf::RectangleShape btnRawConsole;
    sf::RectangleShape btnExit;

    // UI Element for Gameplay
    sf::RectangleShape btnQuitGame;
    sf::Text txtQuitGame;

    sf::Text txtStart;
    sf::Text txtRules;
    sf::Text txtLeaderboard; // New Text
    sf::Text txtCredits;
    sf::Text txtRawConsole;
    sf::Text txtExit;
    sf::Text txtTitle;
    sf::Text txtEscapeHint;

    std::string winnerName;
    bool isDrawGame;
    bool playInConsole;

    // Player Data & Error Handling
    std::string playerWhiteName;
    std::string playerBlackName;
    std::string inputText;
    bool isEnteringPlayerBlack;
    std::string errorMessage;

    // Leaderboard Data Container
    std::vector<LeaderboardEntry> leaderboardData;

    void loadAssets();
    void setupUI();
    void processEvents();
    void update();
    void render();

    void loadLeaderboardData(); // New Data Parser

    void renderMenu();
    void renderRules();
    void renderCredits();
    void renderLeaderboard(); // New Render Screen
    void renderBoard();
    void renderGameOver();
    void renderNameInput();

    void handleMouseClick(int x, int y);
    void handleTextInput(sf::Uint32 unicode);

public:
    SFMLEngine();
    ~SFMLEngine();
    void run();
    bool shouldPlayInConsole() const;
};
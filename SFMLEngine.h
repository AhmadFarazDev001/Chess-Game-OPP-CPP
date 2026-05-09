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

// Game states for screen navigation
enum class GameState { MENU, RULES, CREDITS, LEADERBOARD, PLAYING, GAMEOVER, NAME_INPUT };

// Structure for match history entries
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

    // Background textures
    sf::Texture texMainBg;
    sf::Texture texMenuBg;
    sf::Sprite sprMainBg;
    sf::Sprite sprMenuBg;

    int selectedX;
    int selectedY;

    // Menu interactables
    sf::RectangleShape btnStart;
    sf::RectangleShape btnRules;
    sf::RectangleShape btnLeaderboard;
    sf::RectangleShape btnCredits;
    sf::RectangleShape btnRawConsole;
    sf::RectangleShape btnExit;

    // In-game interactables
    sf::RectangleShape btnQuitGame;
    sf::Text txtQuitGame;

    // Text labels
    sf::Text txtStart;
    sf::Text txtRules;
    sf::Text txtLeaderboard;
    sf::Text txtCredits;
    sf::Text txtRawConsole;
    sf::Text txtExit;
    sf::Text txtEscapeHint;

    std::string winnerName;
    bool isDrawGame;
    bool playInConsole;

    // Input handling buffers
    std::string playerWhiteName;
    std::string playerBlackName;
    std::string inputText;
    bool isEnteringPlayerBlack;
    std::string errorMessage;

    // Match history container
    std::vector<LeaderboardEntry> leaderboardData;

    // Core lifecycle functions
    void loadAssets();
    void setupUI();
    void processEvents();
    void update();
    void render();

    // Data parsing
    void loadLeaderboardData();

    // Screen renderers
    void renderMenu();
    void renderRules();
    void renderCredits();
    void renderLeaderboard();
    void renderBoard();
    void renderGameOver();
    void renderNameInput();

    // Input logic
    void handleMouseClick(int x, int y);
    void handleTextInput(sf::Uint32 unicode);

public:
    SFMLEngine();
    ~SFMLEngine();
    void run();
    bool shouldPlayInConsole() const;
};
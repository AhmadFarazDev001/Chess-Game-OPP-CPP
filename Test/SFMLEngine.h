#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <iostream>
#include "Board.h"
#include "library.h"

enum class GameState { MENU, RULES, CREDITS, PLAYING, GAMEOVER, NAME_INPUT };

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
    sf::RectangleShape btnCredits;
    sf::RectangleShape btnRawConsole;
    sf::RectangleShape btnExit;

    // UI Element for Gameplay
    sf::RectangleShape btnQuitGame;
    sf::Text txtQuitGame;

    sf::Text txtStart;
    sf::Text txtRules;
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

    void loadAssets();
    void setupUI();
    void processEvents();
    void update();
    void render();

    void renderMenu();
    void renderRules();
    void renderCredits();
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
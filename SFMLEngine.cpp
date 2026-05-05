#include "SFMLEngine.h"

SFMLEngine::SFMLEngine()
    : window(sf::VideoMode(1200, 800), "Chess Engine", sf::Style::Titlebar | sf::Style::Close),
    currentState(GameState::MENU),
    currentTurn("White"),
    selectedX(-1),
    selectedY(-1),
    isDrawGame(false),
    playInConsole(false),
    isEnteringPlayerBlack(false),
    errorMessage("")
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    board.setupStartingPosition();
    loadAssets();
    setupUI();
}

SFMLEngine::~SFMLEngine() {}

bool SFMLEngine::shouldPlayInConsole() const {
    return playInConsole;
}

void SFMLEngine::loadAssets() {
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cout << "Error: Could not load assets/font.ttf" << std::endl;
    }

    std::string pieces[] = {
        "black-bishop", "black-king", "black-knight", "black-pawn", "black-queen", "black-rook",
        "white-bishop", "white-king", "white-knight", "white-pawn", "white-queen", "white-rook"
    };

    for (const auto& piece : pieces) {
        if (!pieceTextures[piece].loadFromFile("assets/" + piece + ".png")) {
            std::cout << "Error: Could not load assets/" << piece << ".png" << std::endl;
        }
        pieceTextures[piece].setSmooth(true);
    }
}

void SFMLEngine::setupUI() {
    auto setupButton = [&](sf::RectangleShape& btn, sf::Text& txt, float yOffset, const std::string& label) {
        btn.setSize(sf::Vector2f(400, 60));
        btn.setPosition(400, yOffset);
        btn.setFillColor(sf::Color(45, 50, 60));
        btn.setOutlineThickness(1);
        btn.setOutlineColor(sf::Color(80, 90, 110));

        txt.setFont(font);
        txt.setString(label);
        txt.setCharacterSize(22);
        txt.setFillColor(sf::Color(240, 240, 245));

        sf::FloatRect textRect = txt.getLocalBounds();
        txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        txt.setPosition(btn.getPosition().x + btn.getSize().x / 2.0f, btn.getPosition().y + btn.getSize().y / 2.0f);
        };

    txtTitle.setFont(font);
    txtTitle.setString("CHESS");
    txtTitle.setCharacterSize(75);
    txtTitle.setStyle(sf::Text::Bold);
    txtTitle.setFillColor(sf::Color(255, 255, 255));
    sf::FloatRect textRect = txtTitle.getLocalBounds();
    txtTitle.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txtTitle.setPosition(600, 130);

    txtEscapeHint.setFont(font);
    txtEscapeHint.setString("Press ESC to return / exit");
    txtEscapeHint.setCharacterSize(16);
    txtEscapeHint.setFillColor(sf::Color(120, 130, 150));
    txtEscapeHint.setPosition(20, 760);

    // Adjusted Y-offsets to fit the new Leaderboard button gracefully
    setupButton(btnStart, txtStart, 260, "Start New Game");
    setupButton(btnRules, txtRules, 340, "Rules");
    setupButton(btnLeaderboard, txtLeaderboard, 420, "Leaderboard");
    setupButton(btnCredits, txtCredits, 500, "Credits");
    setupButton(btnRawConsole, txtRawConsole, 580, "Play in Raw Console");
    setupButton(btnExit, txtExit, 660, "Exit");

    btnQuitGame.setSize(sf::Vector2f(300, 50));
    btnQuitGame.setPosition(850, 700);
    btnQuitGame.setFillColor(sf::Color(210, 60, 60));
    btnQuitGame.setOutlineThickness(0);

    txtQuitGame.setFont(font);
    txtQuitGame.setString("Quit Game");
    txtQuitGame.setCharacterSize(20);
    txtQuitGame.setFillColor(sf::Color::White);
    textRect = txtQuitGame.getLocalBounds();
    txtQuitGame.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txtQuitGame.setPosition(btnQuitGame.getPosition().x + btnQuitGame.getSize().x / 2.0f, btnQuitGame.getPosition().y + btnQuitGame.getSize().y / 2.0f);
}

// Loads and parses the gamehistory.txt file
void SFMLEngine::loadLeaderboardData() {
    leaderboardData.clear();
    std::ifstream file("gamehistory.txt");
    if (!file.is_open()) return; // If file doesn't exist yet, just render empty board

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        LeaderboardEntry entry;

        // Split using the pipe delimiter you established
        std::getline(ss, entry.white, '|');
        std::getline(ss, entry.black, '|');
        std::getline(ss, entry.result, '|');
        std::getline(ss, entry.date, '|');

        // Insert at the beginning so the newest games appear at the top
        leaderboardData.insert(leaderboardData.begin(), entry);
    }
    file.close();
}

void SFMLEngine::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void SFMLEngine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (currentState == GameState::MENU) {
                window.close();
            }
            else {
                currentState = GameState::MENU;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (event.type == sf::Event::TextEntered && currentState == GameState::NAME_INPUT) {
            handleTextInput(event.text.unicode);
        }
    }
}

void SFMLEngine::handleTextInput(sf::Uint32 unicode) {
    if (unicode == 8) {
        if (!inputText.empty()) inputText.pop_back();
    }
    else if (unicode == 13) {
        if (!inputText.empty()) {
            if (!isEnteringPlayerBlack) {
                playerWhiteName = inputText;
                inputText = "";
                isEnteringPlayerBlack = true;
            }
            else {
                playerBlackName = inputText;
                inputText = "";
                currentState = GameState::PLAYING;
            }
        }
    }
    else if (unicode < 128 && inputText.length() < 15) {
        inputText += static_cast<char>(unicode);
    }
}

void SFMLEngine::handleMouseClick(int x, int y) {
    if (currentState == GameState::MENU) {
        sf::Vector2f mousePos(x, y);
        if (btnStart.getGlobalBounds().contains(mousePos)) {
            board.~Board();
            new(&board) Board();
            board.setupStartingPosition();
            currentTurn = "White";
            isDrawGame = false;
            errorMessage = "";
            selectedX = -1;
            selectedY = -1;

            currentState = GameState::NAME_INPUT;
            inputText = "";
            isEnteringPlayerBlack = false;
        }
        else if (btnRules.getGlobalBounds().contains(mousePos)) {
            currentState = GameState::RULES;
        }
        else if (btnLeaderboard.getGlobalBounds().contains(mousePos)) {
            loadLeaderboardData(); // Read the file before opening screen
            currentState = GameState::LEADERBOARD;
        }
        else if (btnCredits.getGlobalBounds().contains(mousePos)) {
            currentState = GameState::CREDITS;
        }
        else if (btnRawConsole.getGlobalBounds().contains(mousePos)) {
            playInConsole = true;
            window.close();
        }
        else if (btnExit.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }
    else if (currentState == GameState::RULES || currentState == GameState::CREDITS || currentState == GameState::GAMEOVER || currentState == GameState::LEADERBOARD) {
        // Exiting sub-menus handles by ESC, but clicking can also exit
        currentState = GameState::MENU;
    }
    else if (currentState == GameState::PLAYING) {
        sf::Vector2f mousePos(x, y);
        if (x >= 800) {
            if (btnQuitGame.getGlobalBounds().contains(mousePos)) {
                currentState = GameState::MENU;
            }
            return;
        }

        int col = x / 100;
        int row = y / 100;

        if (selectedX == -1 && selectedY == -1) {
            Piece* p = board.getPiece(col, row);
            if (p != nullptr && p->getcolor() == currentTurn) {
                selectedX = col;
                selectedY = row;
                errorMessage = "";
            }
        }
        else {
            int startX = selectedX + 1;
            int startY = selectedY + 1;
            int endX = col + 1;
            int endY = row + 1;

            if (startX != endX || startY != endY) {
                if (board.executeMove(startX, startY, endX, endY, currentTurn)) {
                    errorMessage = "";
                    std::string opponent = (currentTurn == "White") ? "Black" : "White";
                    board.recordPosition(currentTurn);

                    if (board.isCheckmate(opponent)) {
                        winnerName = currentTurn;

                        // We must save the GUI game history here as well!
                        RecordGame rg;
                        rg.WhiteName = playerWhiteName;
                        rg.BlackName = playerBlackName;
                        rg.result = currentTurn + " Win due to CheckMate";
                        rg.getTime();
                        rg.record();

                        currentState = GameState::GAMEOVER;
                    }
                    else if (board.isDraw(opponent)) {
                        isDrawGame = true;

                        RecordGame rg;
                        rg.WhiteName = playerWhiteName;
                        rg.BlackName = playerBlackName;
                        rg.result = "Draw between Both Players";
                        rg.getTime();
                        rg.record();

                        currentState = GameState::GAMEOVER;
                    }
                    else {
                        currentTurn = opponent;
                    }
                }
                else {
                    errorMessage = "Invalid Move! Try again.";
                }
            }
            selectedX = -1;
            selectedY = -1;
        }
    }
}

void SFMLEngine::update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(mousePos.x, mousePos.y);

    if (currentState == GameState::MENU) {
        auto updateHover = [&](sf::RectangleShape& btn) {
            if (btn.getGlobalBounds().contains(mousePosF)) {
                btn.setFillColor(sf::Color(65, 75, 90));
            }
            else {
                btn.setFillColor(sf::Color(45, 50, 60));
            }
            };
        updateHover(btnStart);
        updateHover(btnRules);
        updateHover(btnLeaderboard); // Hover logic for new button
        updateHover(btnCredits);
        updateHover(btnRawConsole);
        updateHover(btnExit);
    }
    else if (currentState == GameState::PLAYING) {
        if (btnQuitGame.getGlobalBounds().contains(mousePosF)) {
            btnQuitGame.setFillColor(sf::Color(240, 80, 80));
        }
        else {
            btnQuitGame.setFillColor(sf::Color(210, 60, 60));
        }
    }
}

void SFMLEngine::render() {
    sf::VertexArray bg(sf::Quads, 4);
    bg[0].position = sf::Vector2f(0, 0);       bg[0].color = sf::Color(20, 25, 35);
    bg[1].position = sf::Vector2f(1200, 0);    bg[1].color = sf::Color(15, 20, 30);
    bg[2].position = sf::Vector2f(1200, 800);  bg[2].color = sf::Color(10, 12, 18);
    bg[3].position = sf::Vector2f(0, 800);     bg[3].color = sf::Color(15, 18, 25);

    window.clear();
    window.draw(bg);

    if (currentState == GameState::MENU) renderMenu();
    else if (currentState == GameState::NAME_INPUT) renderNameInput();
    else if (currentState == GameState::RULES) renderRules();
    else if (currentState == GameState::CREDITS) renderCredits();
    else if (currentState == GameState::LEADERBOARD) renderLeaderboard();
    else if (currentState == GameState::PLAYING) renderBoard();
    else if (currentState == GameState::GAMEOVER) {
        renderBoard();
        renderGameOver();
    }

    window.display();
}

void SFMLEngine::renderMenu() {
    sf::Text titleShadow = txtTitle;
    titleShadow.setFillColor(sf::Color(0, 0, 0, 150));
    titleShadow.move(4.0f, 4.0f);
    window.draw(titleShadow);
    window.draw(txtTitle);

    auto drawBtn = [&](sf::RectangleShape& btn, sf::Text& txt) {
        sf::RectangleShape shadow = btn;
        shadow.setFillColor(sf::Color(0, 0, 0, 100));
        shadow.move(4.0f, 4.0f);
        window.draw(shadow);
        window.draw(btn);
        window.draw(txt);
        };

    drawBtn(btnStart, txtStart);
    drawBtn(btnRules, txtRules);
    drawBtn(btnLeaderboard, txtLeaderboard); // Draw new button
    drawBtn(btnCredits, txtCredits);
    drawBtn(btnRawConsole, txtRawConsole);
    drawBtn(btnExit, txtExit);

    window.draw(txtEscapeHint);
}

void SFMLEngine::renderLeaderboard() {
    sf::Text title;
    title.setFont(font);
    title.setString("MATCH HISTORY");
    title.setCharacterSize(45);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color(255, 215, 0)); // Gold title
    sf::FloatRect bounds = title.getLocalBounds();
    title.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    title.setPosition(600, 80);
    window.draw(title);

    // Table Headers
    sf::Text header;
    header.setFont(font);
    header.setCharacterSize(22);
    header.setFillColor(sf::Color(150, 160, 180));

    header.setString("WHITE");  header.setPosition(100, 150); window.draw(header);
    header.setString("BLACK");  header.setPosition(300, 150); window.draw(header);
    header.setString("RESULT"); header.setPosition(500, 150); window.draw(header);
    header.setString("DATE");   header.setPosition(880, 150); window.draw(header);

    // Separator Line
    sf::RectangleShape line(sf::Vector2f(1000, 2));
    line.setPosition(100, 190);
    line.setFillColor(sf::Color(100, 100, 100));
    window.draw(line);

    // Render Data
    int y = 210;
    sf::Text entryTxt;
    entryTxt.setFont(font);
    entryTxt.setCharacterSize(18);

    if (leaderboardData.empty()) {
        entryTxt.setString("No game history found. Play a match first!");
        entryTxt.setFillColor(sf::Color::White);
        entryTxt.setPosition(400, 300);
        window.draw(entryTxt);
    }
    else {
        // Display up to 12 recent games to fit the screen
        for (size_t i = 0; i < leaderboardData.size() && i < 12; ++i) {
            entryTxt.setFillColor(sf::Color::White);
            entryTxt.setString(leaderboardData[i].white); entryTxt.setPosition(100, y); window.draw(entryTxt);
            entryTxt.setString(leaderboardData[i].black); entryTxt.setPosition(300, y); window.draw(entryTxt);

            // Highlight the result in bright blue
            entryTxt.setFillColor(sf::Color(100, 200, 255));
            entryTxt.setString(leaderboardData[i].result); entryTxt.setPosition(500, y); window.draw(entryTxt);

            // Date in grey
            entryTxt.setFillColor(sf::Color(200, 200, 200));
            entryTxt.setString(leaderboardData[i].date);   entryTxt.setPosition(880, y); window.draw(entryTxt);

            y += 40;
        }
    }

    sf::Text escHint;
    escHint.setFont(font);
    escHint.setString("Press ESC to return to Menu");
    escHint.setCharacterSize(20);
    escHint.setFillColor(sf::Color(150, 150, 150));
    escHint.setPosition(470, 750);
    window.draw(escHint);
}

void SFMLEngine::renderNameInput() {
    sf::Text promptText;
    promptText.setFont(font);
    promptText.setCharacterSize(35);
    promptText.setFillColor(sf::Color::White);
    promptText.setString(isEnteringPlayerBlack ? "Enter name for Black Player:" : "Enter name for White Player:");

    sf::FloatRect bounds = promptText.getLocalBounds();
    promptText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    promptText.setPosition(600, 300);

    sf::Text inputDisplay;
    inputDisplay.setFont(font);
    inputDisplay.setString(inputText + "_");
    inputDisplay.setCharacterSize(45);
    inputDisplay.setStyle(sf::Text::Bold);
    inputDisplay.setFillColor(sf::Color(100, 200, 255));
    bounds = inputDisplay.getLocalBounds();
    inputDisplay.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    inputDisplay.setPosition(600, 400);

    sf::Text instrText;
    instrText.setFont(font);
    instrText.setString("Press ENTER to confirm\nPress ESC to return to Menu");
    instrText.setCharacterSize(18);
    instrText.setFillColor(sf::Color(150, 160, 180));
    bounds = instrText.getLocalBounds();
    instrText.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    instrText.setPosition(600, 550);

    window.draw(promptText);
    window.draw(inputDisplay);
    window.draw(instrText);
}

void SFMLEngine::renderRules() {
    sf::Text rulesText;
    rulesText.setFont(font);
    rulesText.setString("CHESS RULES\n\n"
        "1. White always moves first.\n"
        "2. Pawns move forward 1 square (or 2 on their first move), but capture diagonally.\n"
        "3. Knights move in an 'L' shape and can jump over pieces.\n"
        "4. Bishops move diagonally, Rooks straight, and Queens both.\n"
        "5. The King moves 1 square in any direction.\n"
        "6. Check: When the King is under direct threat, it must escape.\n"
        "7. Checkmate: If the King is in Check and cannot escape, the game ends.\n"
        "8. Stalemate: If a player is NOT in Check but has no legal moves, it is a Draw.\n"
        "9. Insufficient Material: E.g., King vs King is an automatic Draw.\n"
        "10. Threefold Repetition: The exact board position occurring 3 times is a Draw.\n\n"
        "Press ESC to return to Menu.");
    rulesText.setCharacterSize(22);
    rulesText.setFillColor(sf::Color(230, 230, 240));
    rulesText.setPosition(100, 100);
    window.draw(rulesText);
}

void SFMLEngine::renderCredits() {
    sf::Text creditsText;
    creditsText.setFont(font);
    creditsText.setString("CREDITS\n\n\n\nAhmad Faraz (25F-0510)\n\nUbaid Ur Rehman (25F-0570)\n\n\n\n\nPress ESC to return to Menu.");
    creditsText.setCharacterSize(28);
    creditsText.setFillColor(sf::Color(100, 200, 255));
    creditsText.setPosition(150, 200);
    window.draw(creditsText);
}

void SFMLEngine::renderBoard() {
    sf::Color lightSquare(238, 238, 210);
    sf::Color darkSquare(118, 150, 86);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
            square.setPosition(col * 100.0f, row * 100.0f);

            bool isLight = ((row + col) % 2 == 0);
            square.setFillColor(isLight ? lightSquare : darkSquare);
            window.draw(square);

            if (col == selectedX && row == selectedY) {
                sf::RectangleShape highlight(sf::Vector2f(100.0f, 100.0f));
                highlight.setPosition(col * 100.0f, row * 100.0f);
                highlight.setFillColor(sf::Color(255, 255, 50, 100));
                window.draw(highlight);
            }

            if (col == 0) {
                sf::Text numTxt;
                numTxt.setFont(font);
                numTxt.setString(std::to_string(8 - row));
                numTxt.setCharacterSize(16);
                numTxt.setStyle(sf::Text::Bold);
                numTxt.setFillColor(isLight ? darkSquare : lightSquare);
                numTxt.setPosition(5.0f, row * 100.0f + 5.0f);
                window.draw(numTxt);
            }
            if (row == 7) {
                sf::Text alphaTxt;
                alphaTxt.setFont(font);
                alphaTxt.setString(std::string(1, 'A' + col));
                alphaTxt.setCharacterSize(16);
                alphaTxt.setStyle(sf::Text::Bold);
                alphaTxt.setFillColor(isLight ? darkSquare : lightSquare);
                alphaTxt.setPosition(col * 100.0f + 85.0f, 780.0f);
                window.draw(alphaTxt);
            }

            Piece* p = board.getPiece(col, row);
            if (p != nullptr) {
                std::string color = p->getcolor();
                std::string symbol = p->getsymbol();
                std::string pName = "";

                if (symbol == "\u2659" || symbol == "\u265F") pName = "pawn";
                else if (symbol == "\u2658" || symbol == "\u265E") pName = "knight";
                else if (symbol == "\u2657" || symbol == "\u265D") pName = "bishop";
                else if (symbol == "\u2656" || symbol == "\u265C") pName = "rook";
                else if (symbol == "\u2655" || symbol == "\u265B") pName = "queen";
                else if (symbol == "\u2654" || symbol == "\u265A") pName = "king";

                if (!pName.empty()) {
                    std::string texName = (color == "White" ? "white-" : "black-") + pName;
                    sf::Sprite sprite(pieceTextures[texName]);

                    sf::FloatRect bounds = sprite.getLocalBounds();
                    float scale = std::min(85.0f / bounds.width, 85.0f / bounds.height);
                    sprite.setScale(scale, scale);
                    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

                    sf::Sprite shadow = sprite;
                    shadow.setColor(sf::Color(0, 0, 0, 80));
                    shadow.setPosition(col * 100.0f + 54.0f, row * 100.0f + 54.0f);
                    window.draw(shadow);

                    sprite.setPosition(col * 100.0f + 50.0f, row * 100.0f + 50.0f);
                    window.draw(sprite);
                }
            }
        }
    }

    sf::RectangleShape uiPanel(sf::Vector2f(400.0f, 800.0f));
    uiPanel.setPosition(800.0f, 0.0f);
    uiPanel.setFillColor(sf::Color(30, 34, 40));

    sf::RectangleShape panelShadow(sf::Vector2f(10.0f, 800.0f));
    panelShadow.setPosition(790.0f, 0.0f);
    panelShadow.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(panelShadow);
    window.draw(uiPanel);

    sf::Text uiText;
    uiText.setFont(font);
    uiText.setCharacterSize(22);

    uiText.setFillColor(sf::Color(120, 130, 150));
    uiText.setString("PLAYERS");
    uiText.setPosition(840.0f, 60.0f);
    window.draw(uiText);

    uiText.setFillColor(sf::Color::White);
    uiText.setString("White: " + playerWhiteName);
    uiText.setPosition(840.0f, 100.0f);
    window.draw(uiText);

    uiText.setString("Black: " + playerBlackName);
    uiText.setPosition(840.0f, 140.0f);
    window.draw(uiText);

    uiText.setFillColor(sf::Color(120, 130, 150));
    uiText.setString("CURRENT TURN");
    uiText.setPosition(840.0f, 240.0f);
    window.draw(uiText);

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(35);
    turnText.setStyle(sf::Text::Bold);
    std::string activePlayer = (currentTurn == "White") ? playerWhiteName : playerBlackName;
    turnText.setString(currentTurn + "\n(" + activePlayer + ")");
    turnText.setFillColor(currentTurn == "White" ? sf::Color(255, 255, 255) : sf::Color(150, 200, 255));
    turnText.setPosition(840.0f, 280.0f);
    window.draw(turnText);

    if (!errorMessage.empty()) {
        sf::Text errorText;
        errorText.setFont(font);
        errorText.setString(errorMessage);
        errorText.setCharacterSize(20);
        errorText.setFillColor(sf::Color(255, 80, 80));
        errorText.setPosition(840.0f, 420.0f);
        window.draw(errorText);
    }

    sf::RectangleShape btnShadow = btnQuitGame;
    btnShadow.setFillColor(sf::Color(0, 0, 0, 100));
    btnShadow.move(4.0f, 4.0f);
    window.draw(btnShadow);
    window.draw(btnQuitGame);
    window.draw(txtQuitGame);
}

void SFMLEngine::renderGameOver() {
    sf::RectangleShape overlay(sf::Vector2f(1200.0f, 800.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    sf::Text text;
    text.setFont(font);
    if (isDrawGame) {
        text.setString("GAME OVER\n\nDRAW!");
    }
    else {
        std::string winName = (winnerName == "White") ? playerWhiteName : playerBlackName;
        text.setString("CHECKMATE\n\n" + winnerName + " (" + winName + ") Wins!");
    }

    text.setCharacterSize(65);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color(255, 215, 0));
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(600.0f, 350.0f);

    sf::Text tShadow = text;
    tShadow.setFillColor(sf::Color(100, 80, 0, 150));
    tShadow.move(5.0f, 5.0f);
    window.draw(tShadow);
    window.draw(text);

    sf::Text subText;
    subText.setFont(font);
    subText.setString("Press ESC to return to Menu");
    subText.setCharacterSize(22);
    subText.setFillColor(sf::Color(200, 200, 200));
    bounds = subText.getLocalBounds();
    subText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    subText.setPosition(600.0f, 500.0f);

    window.draw(subText);
}
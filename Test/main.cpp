#include "library.h"
#include "gameexecution.h"
#include "SFMLEngine.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    // Enable Windows ANSI Colors
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    SFMLEngine engine;
    engine.run();
    
    if (engine.shouldPlayInConsole()) {
        executeGame();
    }

	return 0;
}

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cmath>
#include <fstream>
using namespace std;

// globals
#define numOfLaserBullets 100
#define numOfBattleShips 10
#define numOfHelicopters 10
#define numOfCannons 10
int numberOfPatterns = 0;
int mazeMoveCount = 0;
int score = 0;
int currentHealth;
int previousHealth;
bool gameRunning = false;
int mazeEnemyCount = 0;
int mazeRandomEnemy = 30;
double timeElapsed;
bool statsUpdateFlag = true;
clock_t startTime;
clock_t stopTime;
int mazePos = 30 - 1;
int mazeNumber = 0;
int previousMazeNumber = 0;
char screen[30][81];
char screenSingleLine[81];
char c254 = 254;
char c219 = 219;
char m = 219;
// logo
char logo[16][54] = {
    ".______       __  ____    ____  _______ .______      ",
    "|   _  \\     |  | \\   \\  /   / |   ____||   _  \\     ",
    "|  |_)  |    |  |  \\   \\/   /  |  |__   |  |_)  |    ",
    "|      /     |  |   \\      /   |   __|  |      /     ",
    "|  |\\  \\----.|  |    \\    /    |  |____ |  |\\  \\----.",
    "| _| `._____||__|     \\__/     |_______|| _| `._____|",
    "                                                     ",
    "   .______          ___       __   _______           ",
    "   |   _  \\        /   \\     |  | |       \\          ",
    "   |  |_)  |      /  ^  \\    |  | |  .--.  |         ",
    "   |      /      /  /_\\  \\   |  | |  |  |  |         ",
    "   |  |\\  \\----./  _____  \\  |  | |  '--'  |         ",
    "   | _| `._____/__/     \\__\\ |__| |_______/          "};
// game over
char gameOverLogo[16][54] = {
    "  _______      ___      .___  ___.  _______   ",
    " /  _____|    /   \\     |   \\/   | |   ____|  ",
    "|  |  __     /  ^  \\    |  \\  /  | |  |__     ",
    "|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|    ",
    "|  |__| |  /  _____  \\  |  |  |  | |  |____   ",
    " \\______| /__/     \\__\\ |__|  |__| |_______|  ",
    "                                              ",
    "  ______   ____    ____  _______ .______      ",
    " /  __  \\  \\   \\  /   / |   ____||   _  \\     ",
    "|  |  |  |  \\   \\/   /  |  |__   |  |_)  |    ",
    "|  |  |  |   \\      /   |   __|  |      /     ",
    "|  `--'  |    \\    /    |  |____ |  |\\  \\----.",
    " \\______/      \\__/     |_______|| _| `._____|"};

// hanger
char hanger[26][101];
// mazes
char patterns[20][30][81];
string planeInfo[] = {
    "F-32",
    "Lasor:Yellow",
    "Lasors:2",
    "F-47",
    "Lasor:Red",
    "Lasors:3",
    "F-420",
    "Lasor:Blue",
    "Lasors:1",
};

// player variables
int playerX = 20, playerY = 15;
int currentPlayer;
int playerLaserX[numOfLaserBullets];
int playerLaserY[numOfLaserBullets];
int currentPlayerLaserColor = 0x0;
int currentLaserBulletsCount = 0;

// health powerup
int healthPowerupX = 50;
int healthPowerupY = 0;
bool healthPowerUpMovement = true;
bool healthPowerUpVisibility = false;
int healthPowerupCount = 0;
int healthPowerUpRandomSpawn = 100;
int healthPowerUpRandomSpawnCount = 0;

// battleShip variables
int battleShipsX[numOfBattleShips];
int battleShipsY[numOfBattleShips];
bool battleShipsMovement[numOfBattleShips];
int battleShipMovementTimer[numOfBattleShips];
int battleShipRocketX[numOfBattleShips];
int battleShipRocketY[numOfBattleShips];
int battleShipRocketReady[numOfBattleShips];
int currentBattleShipRocketsCount = 0;
int currentBattleShipsCount = 0;

// helicopter variables
int helicoptersX[numOfHelicopters];
int helicoptersY[numOfHelicopters];
bool helicoptersMovement[numOfHelicopters];
int helicoptersMovementTimer[numOfHelicopters];
int helicopterBulletsX[numOfHelicopters];
int helicopterBulletsY[numOfHelicopters];
int helicoptersBulletsReady[numOfHelicopters];
int currenthelicoptersBulletsCount = 0;
int currenthelicoptersCount = 0;

// cannon variables
int cannonX[numOfCannons];
int cannonY[numOfCannons];
int cannonRocketX[numOfCannons];
int cannonRocketY[numOfCannons];
int cannonRocketType[numOfCannons];
int cannonRocketsReady[numOfCannons];
int currentCannonRocketCount = 0;

int currentCannonCount = 0;

string mainMenuItems[] = {"Continue game...", "New game", "exit"};
string pauseMenuItems[] = {"resume", "save game", "exit to main menu", "exit"};

// function prototypes

char getCharxy(short x, short y);
void halt();
void gotoxy(int x, int y);
void setColor(short color);
void consoleCursor(bool visibility);
int takeChoice(int offset, int size, short color);
string getStringAtxy(short int x, short int y);
void printMenuItems(int offset, string items[], int startingIndex, int endingIndex);
void movePointer(int previousPos, int pointerPos, int offset, short color);
void copyCharArray(char arr1[], char arr2[], int size);
int digitCount(int number);

void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();
void drawPlayer(int x, int y);
void printPlayer1(int x, int y);
void printPlayer2(int x, int y);
void printPlayer3(int x, int y);
void erasePlayer(int x, int y);
void createLaserBullet(int x, int y);
void moveLaserBullets();
bool checkCollisionWithPlayer(int x, int y);
void handleRocketLasorBulletCollision();
// player on foot
void playerMoveOnFootUp(int &playerX, int &playerY);
void playerMoveOnFootDown(int &playerX, int &playerY);
void playerMoveOnFootLeft(int &playerX, int &playerY);
void playerMoveOnFootRight(int &playerX, int &playerY);
int handleBoxHighlight(int playerX, int playerY, int previousState);
void printPlayerOnFoot(int playerX, int playerY);
void selectPlane();

void eraseGeneric(int x, int y, int rows, int cols);
void destroyGeneric(int x, int y, int rows, int cols, int duration);

void removeElementFromIntArray(int arr[], int elementIndex, int arraySize);
void removeElementFromBoolArray(bool arr[], int elementIndex, int arraySize);
void removeLaserBullet(int i);
int findElementIndex(int xVal, int yVal, int arr1[], int arr2[], int arrSize);
void collisionHandling(int x, int y, char next);

void init();
void moveMaze();
void drawMaze();
void render();
void pauseMenu();
void drawStatsWindow();
void handleEdges();
void saveGame();
void loadGame();
void loadMaze();
void printLogo();
void printGameOver();
void printScore(int x, int y);
void handleRandomEnemySpawn();
void printEmptyMaze();
void printStats();
void showAfterGameScreen();
void clearUnprocessedKeys();
void changeMazeCharacters();
void loadPatterns();
void moveMazeAndGameElements();
bool isSaveGameExists();
void currentPlayerLaser(int currentPlayerType);
string parseData(string line, int fieldNumber);
void coordsArrayPull(string line, int arrayX[], int arrayY[], int &countVar);
void coordsArrayPush(fstream &file, int arrayX[], int arrayY[], int arraySize);
// battleship function prototypes
void printBattleShip(int x, int y);
void createBattleShip();
void battleShipHandler();
void battleShipRocketCreate(int x, int y);
void moveBattleShipVertically();
void moveBattleShipHorizontally(int i);
void moveBattleShipRocket(int i);
void removeBattleShip(int i);
void removeBattleShipRocket(int i);
bool checkCollisionWithBattleShip(int i);
// helicopter function prototypes
void printHelicopter(int x, int y);
void createHelicopter();
void helicopterHandler();
void helicopterBulletCreate(int x, int y);
void moveHelicopterVertically();
void moveHelicopterHorizontally(int i);
void moveHelicopterBullet(int i);
void removeHelicopter(int i);
void removeHelicopterBullet(int i);
bool checkCollisionWithHelicopter(int i);
// cannon function prototypes
void printCannon(int x, int y);
void createCannon();
void cannonHandler();
void cannonRocketCreate(int x, int y);
void moveCannonVertically();
void moveCannonRocket(int i);
bool checkCannonRocketBound(int i);
void removeCannon(int i);
void removeCannonRocket(int i);
bool checkCollisionWithCannon(int i);
// health powerup function prototypes
void moveHealthPowerupHorizontally();
void healthPowerupHandler();
void printHealthPowerup(int x, int y);
void moveHealthPowerupVertically();

void addScore(int value);
void decreasePlayerHealth(int value);

int main()
{
    loadPatterns();
    changeMazeCharacters();
    int choice = 0;
    consoleCursor(false);
    while (1)
    {
        system("cls");
        printLogo();
        if (isSaveGameExists())
        {
            printMenuItems(16, mainMenuItems, 0, 3);
            choice = takeChoice(16, 3, 0x3);
            if (choice == 0)
            {
                cin.sync();
                init();
                loadGame();
                drawStatsWindow();
                render();
            }
            else if (choice == 1)
            {
                cin.sync();
                selectPlane();
                printEmptyMaze();
                init();
                drawStatsWindow();
                render();
            }
            else if (choice == 2)
            {
                exit(0);
            }
        }
        else
        {
            printMenuItems(15, mainMenuItems, 1, 3);
            choice = takeChoice(16, 2, 0x3);
            if (choice == 0)
            {
                cin.sync();
                selectPlane();
                printEmptyMaze();
                init();
                drawStatsWindow();
                render();
            }
            else if (choice == 1)
            {
                exit(0);
            }
        }
    }
}
bool isSaveGameExists()
{
    fstream file;
    file.open("savegame.txt", ios::in);
    if (file)
    {
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
void loadPatterns()
{
    fstream file;
    char newline = '\n';
    string line;
    file.open("gameData.txt", ios::in);
    if (file)
    {
        for (int i = 0; i < 26; i++) // load hanger
        {
            getline(file, line);
            for (int j = 0; j < line.length(); j++)
            {
                hanger[i][j] = line[j];
            }
        }
        getline(file, line);
        numberOfPatterns = stoi(parseData(line, 1)); // get number of patterns in data
        for (int i = 0; i < numberOfPatterns; i++)   // load the patterns
        {
            for (int j = 0; j < 30; j++)
            {
                getline(file, line);
                for (int k = 0; k < line.length(); k++)
                {
                    patterns[i][j][k] = line[k];
                }
            }
        }
    }
    file.close();
}
void saveGame()
{
    fstream file;
    char newline = '\n';
    file.open("savegame.txt", ios::out);
    if (file)
    {
        file << currentPlayer << ',' << playerX << ',' << playerY;
        file << newline << previousMazeNumber << ',' << mazeNumber << ',' << mazePos;
        file << newline << currentHealth << ',' << score << ',' << mazeEnemyCount;
        file << newline << healthPowerUpVisibility << ',' << healthPowerupX << ',' << healthPowerupY << ',' << healthPowerUpRandomSpawnCount << ',' << healthPowerUpRandomSpawn << ',' << healthPowerupCount;
        // battleships block
        coordsArrayPush(file, battleShipsX, battleShipsY, currentBattleShipsCount);
        coordsArrayPush(file, battleShipRocketX, battleShipRocketY, currentBattleShipRocketsCount);
        // helicopters block
        coordsArrayPush(file, helicoptersX, helicoptersY, currenthelicoptersCount);
        coordsArrayPush(file, helicopterBulletsX, helicopterBulletsY, currenthelicoptersBulletsCount);
        // cannon block
        coordsArrayPush(file, cannonX, cannonY, currentCannonCount);
        coordsArrayPush(file, cannonRocketX, cannonRocketY, currentCannonRocketCount);
        // player bullets block
        coordsArrayPush(file, playerLaserX, playerLaserY, currentLaserBulletsCount);
    }
    file.close();
}
void loadGame()
{
    fstream file;
    char newline = '\n';
    string line;
    file.open("savegame.txt", ios::in);
    if (file)
    {
        getline(file, line); // first line
        currentPlayer = stoi(parseData(line, 1));
        playerX = stoi(parseData(line, 2));
        playerY = stoi(parseData(line, 3));

        getline(file, line); // second line
        previousMazeNumber = stoi(parseData(line, 1));
        mazeNumber = stoi(parseData(line, 2));
        mazePos = stoi(parseData(line, 3));

        getline(file, line); // third line
        currentHealth = stoi(parseData(line, 1));
        score = stoi(parseData(line, 2));
        mazeEnemyCount = stoi(parseData(line, 3));

        getline(file, line); // fourth line
        healthPowerUpVisibility = stoi(parseData(line, 1));
        healthPowerupX = stoi(parseData(line, 2));
        healthPowerupY = stoi(parseData(line, 3));
        healthPowerUpRandomSpawnCount = stoi(parseData(line, 4));
        healthPowerUpRandomSpawn = stoi(parseData(line, 5));
        healthPowerupCount = stoi(parseData(line, 6));

        // battleships block
        getline(file, line);
        coordsArrayPull(line, battleShipsX, battleShipsY, currentBattleShipsCount);
        getline(file, line);
        coordsArrayPull(line, battleShipRocketX, battleShipRocketY, currentBattleShipRocketsCount);
        // helicopters block
        getline(file, line);
        coordsArrayPull(line, helicoptersX, helicoptersY, currenthelicoptersCount);
        getline(file, line);
        coordsArrayPull(line, helicopterBulletsX, helicopterBulletsY, currenthelicoptersBulletsCount);
        // cannons block
        getline(file, line);
        coordsArrayPull(line, cannonX, cannonY, currentCannonCount);
        getline(file, line);
        coordsArrayPull(line, cannonRocketX, cannonRocketY, currentCannonRocketCount);
        // player bullets block
        getline(file, line);
        coordsArrayPull(line, playerLaserX, playerLaserY, currentLaserBulletsCount);
        loadMaze();
        currentPlayerLaser(currentPlayer);
    }
    file.close();
}
void loadMaze()
{
    for (int i = 0; i <= mazePos; i++)
    {
        copyCharArray(screen[i], patterns[mazeNumber][i], 80);
    }
    for (int i = 0; i < 30 - mazePos; i++)
    {
        copyCharArray(screen[i + mazePos], patterns[mazeNumber][i], 80);
    }
    mazePos--;
    drawMaze();
}
string parseData(string line, int fieldNumber)
{
    int initialPos = 0;
    int finalPos = 0;
    int fieldCount = 0;
    string result = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            fieldCount++;
            if (fieldNumber != fieldCount)
            {
                initialPos = i + 1;
            }
            else
            {
                finalPos = i;
            }
        }
        else if (i == line.length() - 1)
        {
            fieldCount++;
            finalPos = i + 1;
        }
        if (fieldNumber == fieldCount)
        {
            for (int j = initialPos; j < finalPos; j++)
            {
                result += line[j];
            }
            return result;
        }
    }
}
void coordsArrayPush(fstream &file, int arrayX[], int arrayY[], int arraySize)
{
    char newline = '\n';
    file << newline << arraySize;
    for (int i = 0; i < arraySize; i++)
    {
        file << ',' << arrayX[i] << ',' << arrayY[i];
    }
}
void coordsArrayPull(string line, int arrayX[], int arrayY[], int &countVar)
{
    countVar = stoi(parseData(line, 1));
    if (countVar)
    {
        for (int i = 0, j = 2; i < countVar; i++, j += 2)
        {
            arrayX[i] = stoi(parseData(line, j));
            arrayY[i] = stoi(parseData(line, j + 1));
        }
    }
}
void changeMazeCharacters()
{
    for (int patternNumber = 0; patternNumber < numberOfPatterns; patternNumber++)
    {
        for (int y = 0; y < 30; y++)
        {
            for (int x = 0; x < 80; x++)
            {
                if (patterns[patternNumber][y][x] == '*')
                    patterns[patternNumber][y][x] = m;
            }
        }
    }
}
void printStats()
{
    setColor(0x88);
    if (previousHealth == 100)
    {
        gotoxy(92, 5);
    }
    else
    {
        gotoxy(95 - digitCount(previousHealth), 5 + (100 - previousHealth) * 20 / 100);
    }
    cout << previousHealth << '%';
    if (previousHealth > currentHealth)
    {
        setColor(0x88);
        for (int i = 0; i < (100 - currentHealth) * 20 / 100; i++)
        {
            gotoxy(93, 5 + i);
            cout << c254 << c254;
        }
    }
    else if ((previousHealth < currentHealth))
    {
        setColor(0x44);
        for (int i = 20; i >= (100 - currentHealth) * 20 / 100; i--)
        {
            gotoxy(93, 5 + i);
            cout << c254 << c254;
        }
    }
    setColor(0x84);
    gotoxy(95 - digitCount(currentHealth), 5 + (100 - currentHealth) * 20 / 100);
    cout << currentHealth << '%';
    previousHealth = currentHealth;
    setColor(0x87);
    gotoxy(92, 1);
    cout << "Score: " << score;
    setColor(0x17);
    statsUpdateFlag = false;
}
void printPlaneInfo(int x, int y, int index)
{
    gotoxy(x, y);
    cout << planeInfo[3 * index];
    gotoxy(x, y + 1);
    cout << planeInfo[3 * index + 1];
    gotoxy(x, y + 2);
    cout << planeInfo[3 * index + 2];
}
void buildHanger()
{
    for (int y = 0; y < 26; y++)
    {
        gotoxy(5, y + 2);
        for (int x = 0; x < 100; x++)
        {
            if (hanger[y][x] == '*')
            {
                setColor(0x88);
            }
            else
            {
                setColor(0x0);
            }
            cout << hanger[y][x];
        }
    }
    setColor(0x7);

    int x = 52, y = 21;
    char s = 205;
    char t = 30;
    setColor(0x07);
    printPlaneInfo(44, 5, 0);
    setColor(0x06); // plane1
    gotoxy(x, y - 1);
    cout << t;
    setColor(0x07);
    gotoxy(x - 2, y);
    setColor(0x06);
    cout << s << s;
    setColor(0x07);
    cout << m;
    setColor(0x06);
    cout << s << s;
    setColor(0x07);
    gotoxy(x, y + 1);
    cout << m;
    gotoxy(x - 1, y + 2);
    setColor(0x06);
    cout << s << m << s;
    setColor(0x07);

    x = 92;
    y = 22;
    printPlaneInfo(86, 5, 1);
    setColor(0x07); // plane2
    gotoxy(x - 2, y - 1);
    cout << (char)205 << (char)202 << (char)206 << (char)202 << (char)205;
    gotoxy(x, y);
    cout << (char)186;
    gotoxy(x - 1, y + 1);
    cout << (char)205 << (char)202 << (char)205;
    setColor(0x07);

    x = 72;
    y = 21;
    printPlaneInfo(66, 5, 2);
    setColor(0x06); // plane 3
    gotoxy(x, y - 1);
    cout << '^';
    setColor(0x07);
    gotoxy(x - 2, y);
    setColor(0x06);
    cout << '/' << '/';
    setColor(0x07);
    cout << '|';
    setColor(0x06);
    cout << '\\' << '\\';
    setColor(0x07);
    gotoxy(x, y + 1);
    cout << '|';
    gotoxy(x - 1, y + 2);
    setColor(0x06);
    cout << '/' << '|' << '\\';
    setColor(0x07);
}
int handleBoxHighlight(int playerX, int playerY, int previousState)
{
    int currentState = -1;
    if (playerX >= 42 && playerX < 63 && playerY >= 17)
    {
        setColor(0x06);
        printPlaneInfo(44, 5, 0);
        gotoxy(13, 15);
        cout << "Press ENTER to Confirm";
        currentState = 1;
    }
    else if (playerX >= 84 && playerX < 104 && playerY >= 17)
    {
        setColor(0x06);
        printPlaneInfo(86, 5, 1);
        gotoxy(13, 15);
        cout << "Press ENTER to Confirm";
        currentState = 2;
    }
    else if (playerX >= 64 && playerX < 83 && playerY >= 17)
    {
        setColor(0x06);
        printPlaneInfo(66, 5, 2);
        gotoxy(13, 15);
        cout << "Press ENTER to Confirm";
        currentState = 3;
    }
    else if (previousState == 1)
    {
        setColor(0x07);
        printPlaneInfo(44, 5, 0);
        eraseGeneric(13, 15, 22, 1);
    }
    else if (previousState == 2)
    {
        setColor(0x07);
        printPlaneInfo(86, 5, 1);
        eraseGeneric(13, 15, 22, 1);
    }
    else if (previousState == 3)
    {
        setColor(0x07);
        printPlaneInfo(66, 5, 2);
        eraseGeneric(13, 15, 22, 1);
    }
    setColor(0x07);
    return currentState;
}
void selectPlane()
{
    int playerOnFootX = 60;
    int playerOnFootY = 10;
    int previousState = 0;
    system("cls");
    buildHanger();
    printPlayerOnFoot(playerOnFootX, playerOnFootY);
    while (1)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            playerMoveOnFootLeft(playerOnFootX, playerOnFootY);
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            playerMoveOnFootRight(playerOnFootX, playerOnFootY);
        }
        if (GetAsyncKeyState(VK_UP))
        {
            playerMoveOnFootUp(playerOnFootX, playerOnFootY);
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            playerMoveOnFootDown(playerOnFootX, playerOnFootY);
        }
        previousState = handleBoxHighlight(playerOnFootX, playerOnFootY, previousState);
        if (GetAsyncKeyState(VK_RETURN) && previousState != -1)
        {
            currentPlayer = previousState;
            currentPlayerLaser(currentPlayer);
            break;
        }
        Sleep(100);
    }
}
void currentPlayerLaser(int currentPlayerType)
{
    if (currentPlayerType == 1)
    {
        currentPlayerLaserColor = 0x1e;
    }
    else if (currentPlayerType == 2)
    {
        currentPlayerLaserColor = 0x1c;
    }
    else if (currentPlayerType == 3)
    {
        currentPlayerLaserColor = 0x19;
    }
}
void playerMoveOnFootUp(int &playerX, int &playerY)
{
    if (getCharxy(playerX, playerY - 1) == ' ')
    {
        eraseGeneric(playerX, playerY, 1, 1);
        playerY--;
        printPlayerOnFoot(playerX, playerY);
    }
}
void playerMoveOnFootDown(int &playerX, int &playerY)
{
    if (getCharxy(playerX, playerY + 1) == ' ')
    {
        eraseGeneric(playerX, playerY, 1, 1);
        playerY++;
        printPlayerOnFoot(playerX, playerY);
    }
}
void playerMoveOnFootLeft(int &playerX, int &playerY)
{
    if (getCharxy(playerX - 1, playerY) == ' ')
    {
        eraseGeneric(playerX, playerY, 1, 1);
        playerX--;
        printPlayerOnFoot(playerX, playerY);
    }
}
void playerMoveOnFootRight(int &playerX, int &playerY)
{
    if (getCharxy(playerX + 1, playerY) == ' ')
    {
        eraseGeneric(playerX, playerY, 1, 1);
        playerX++;
        printPlayerOnFoot(playerX, playerY);
    }
}
void printPlayerOnFoot(int playerX, int playerY)
{
    gotoxy(playerX, playerY);
    cout << (char)248;
}
void init()
{
    gameRunning = true;
    statsUpdateFlag = true;
    system("cls");
    currentBattleShipRocketsCount = 0;
    currentBattleShipsCount = 0;
    currenthelicoptersBulletsCount = 0;
    currenthelicoptersCount = 0;
    currentCannonCount = 0;
    currentCannonRocketCount = 0;
    currentLaserBulletsCount = 0;
    mazeEnemyCount = 0;
    mazePos = 30 - 1;
    mazeMoveCount = 0;
    currentHealth = 100;
    previousHealth = 0;
    mazeNumber = 0;
    previousMazeNumber = 0;
    score = 0;
}
void printEmptyMaze()
{
    setColor(0x22);
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            screen[i][j] = patterns[0][i][j];
        }
    }
}
void drawStatsWindow()
{
    setColor(0x88);
    for (int i = 0; i < 30; i++) // stats window
    {
        for (int j = 80; j < 120; j++)
        {
            gotoxy(j, i);
            cout << c254;
        }
    }
    setColor(0x84);
    for (int i = 20; i >= (100 - currentHealth) * 20 / 100; i--) // health bar
    {
        gotoxy(93, 5 + i);
        cout << (char)219;
    }
    setColor(0x84); // health text
    gotoxy(91, 26);
    cout << "Health";
    setColor(0x17);
}
void copyCharArray(char arr1[], char arr2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr1[i] = arr2[i];
    }
}
void removeElementFromIntArray(int arr[], int elementIndex, int arraySize)
{
    for (int i = elementIndex; i < arraySize - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
}
void removeElementFromBoolArray(bool arr[], int elementIndex, int arraySize)
{
    for (int i = elementIndex; i < arraySize - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
}
void createLaserBullet(int x, int y)
{
    // x += 3;
    y -= 2;
    gotoxy(x, y);
    setColor(currentPlayerLaserColor);
    cout << '|';
    setColor(0x17);
    playerLaserX[currentLaserBulletsCount] = x;
    playerLaserY[currentLaserBulletsCount] = y;
    currentLaserBulletsCount++;
}
int findElementIndex(int xVal, int yVal, int arr1[], int arr2[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr1[i] == xVal && arr2[i] == yVal)
        {
            return i;
        }
    }
    return -1;
}
void addScore(int value)
{
    score += value;
    statsUpdateFlag = true;
}
void decreasePlayerHealth(int value)
{
    currentHealth -= value;
    statsUpdateFlag = true;
    if (currentHealth <= 0)
    {
        gameRunning = false;
    }
}
bool checkCollisionWithBattleShip(int i)
{
    for (int j = 0; j < currentBattleShipsCount; j++)
    {
        if (playerLaserY[i] - 1 == battleShipsY[j] || playerLaserY[i] == battleShipsY[j])
        {
            if ((playerLaserX[i] >= battleShipsX[j] - 2) && (playerLaserX[i] <= battleShipsX[j] + 2))
            {
                addScore(10);
                removeBattleShip(j);
                return true;
            }
        }
    }
    return false;
}
bool checkCollisionWithCannon(int i)
{
    for (int j = 0; j < currentCannonCount; j++)
    {
        if (playerLaserY[i] - 1 == cannonY[j] || playerLaserY[i] == cannonY[j] || playerLaserY[i] - 2 == cannonY[j])
        {
            if ((playerLaserX[i] >= cannonX[j] - 1) && (playerLaserX[i] <= cannonX[j] + 1))
            {
                addScore(30);
                removeCannon(j);
                return true;
            }
        }
    }
    return false;
}
bool checkCollisionWithHelicopter(int i)
{
    for (int j = 0; j < currenthelicoptersCount; j++)
    {
        if (playerLaserY[i] - 1 == helicoptersY[j] || playerLaserY[i] == helicoptersY[j])
        {
            if ((playerLaserX[i] >= helicoptersX[j] - 1) && (playerLaserX[i] <= helicoptersX[j] + 1))
            {
                addScore(5);
                removeHelicopter(j);
                return true;
            }
        }
    }
    return false;
}
bool checkCollisionWithPlayer(int x, int y)
{
    if (x >= playerX - 3 && x <= playerX + 3 && y >= playerY - 3 && y <= playerY + 3)
    {
        return true;
    }
    return false;
}
void removeLaserBullet(int index)
{
    gotoxy(playerLaserX[index], playerLaserY[index]);
    removeElementFromIntArray(playerLaserX, index, currentLaserBulletsCount);
    removeElementFromIntArray(playerLaserY, index, currentLaserBulletsCount);
    cout << " ";
    currentLaserBulletsCount--;
}
void moveLaserBullets()
{
    for (int i = currentLaserBulletsCount - 1; i >= 0; i--)
    {
        if (checkCollisionWithBattleShip(i) || checkCollisionWithHelicopter(i) || checkCollisionWithCannon(i))
        {
            Beep(1000, 5);
            removeLaserBullet(i);
            continue;
        }
        char next = getCharxy(playerLaserX[i], playerLaserY[i] - 1);
        if (next == ' ' && next != '.')
        {

            gotoxy(playerLaserX[i], playerLaserY[i]);
            cout << ' ';
            playerLaserY[i]--;
            gotoxy(playerLaserX[i], playerLaserY[i]);
            setColor(currentPlayerLaserColor);
            cout << '|';
            setColor(0x17);
        }
        else
        {
            removeLaserBullet(i);
        }
    }
}
void moveMaze()
{
    if (mazeMoveCount == 2)
    {
        mazePos++;
        if (mazePos == 30)
        {
            previousMazeNumber = mazeNumber;
            mazeNumber = rand() % numberOfPatterns;
            mazePos = 0;
        }
        copyCharArray(screenSingleLine, patterns[mazeNumber][30 - mazePos - 1], 80);
    }
    else if (mazeMoveCount == 4)
    {
        copyCharArray(screen[0], screenSingleLine, 80);
        for (int i = 30 - 1; i > 0; i--)
        {
            copyCharArray(screen[i], screen[i - 1], 80);
        }
        drawMaze();
    }
}
void drawMaze()
{
    setColor(0x12);
    for (int y = 0; y < 30; y++)
    {
        gotoxy(0, y);
        cout << screen[y];
    }
    setColor(0x17);
}
void handleRandomEnemySpawn()
{
    mazeEnemyCount++;
    if (mazeEnemyCount >= mazeRandomEnemy)
    {
        int randomEnemy = rand() % 3;
        if (randomEnemy == 0)
        {
            createBattleShip();
        }
        else if (randomEnemy == 1)
        {
            createHelicopter();
        }
        else if (randomEnemy == 2)
        {
            createCannon();
        }
        mazeEnemyCount = 0;
        mazeRandomEnemy = rand() % 50 + 20;
    }
}
void moveMazeAndGameElements()
{
    mazeMoveCount++;
    moveMaze();
    if (mazeMoveCount == 4)
    {
        moveBattleShipVertically();
        moveHelicopterVertically();
        moveCannonVertically();
        healthPowerupHandler();
        drawPlayer(playerX, playerY);
        mazeMoveCount = 0;
    }
}
void moveBattleShipVertically()
{
    for (int i = currentBattleShipsCount - 1; i >= 0; i--)
    {
        if (battleShipsY[i] < 29)
        {
            eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
            battleShipsY[i]++;
            printBattleShip(battleShipsX[i], battleShipsY[i]);
        }
        else
        {
            removeBattleShip(i);
        }
    }
}
void moveHelicopterVertically()
{
    for (int i = currenthelicoptersCount - 1; i >= 0; i--)
    {
        if (helicoptersY[i] < 29)
        {
            eraseGeneric(helicoptersX[i], helicoptersY[i], 1, 1);
            helicoptersY[i]++;
            printHelicopter(helicoptersX[i], helicoptersY[i]);
        }
        else
        {
            removeHelicopter(i);
        }
    }
}
void moveCannonVertically()
{
    for (int i = currentCannonCount - 1; i >= 0; i--)
    {
        if (cannonY[i] < 28)
        {
            eraseGeneric(cannonX[i] - 1, cannonY[i] - 1, 3, 3);
            cannonY[i]++;
            printCannon(cannonX[i], cannonY[i]);
        }
        else
        {
            removeCannon(i);
        }
    }
}
void battleShipRocketCreate(int x, int y)
{
    y++;
    gotoxy(x, y);
    cout << "#";
    battleShipRocketX[currentBattleShipRocketsCount] = x;
    battleShipRocketY[currentBattleShipRocketsCount] = y;
    currentBattleShipRocketsCount++;
    Beep(2400, 10);
}
void cannonRocketCreate(int x, int y)
{
    gotoxy(x, y + 2);
    cout << "#";
    cannonRocketX[currentCannonRocketCount] = x;
    cannonRocketY[currentCannonRocketCount] = y + 2;
    cannonRocketType[currentCannonRocketCount] = 0;
    currentCannonRocketCount++;
    gotoxy(x + 2, y);
    cout << "#";
    cannonRocketX[currentCannonRocketCount] = x + 2;
    cannonRocketY[currentCannonRocketCount] = y;
    cannonRocketType[currentCannonRocketCount] = 1;
    currentCannonRocketCount++;
    gotoxy(x, y - 2);
    cout << "#";
    cannonRocketX[currentCannonRocketCount] = x;
    cannonRocketY[currentCannonRocketCount] = y - 2;
    cannonRocketType[currentCannonRocketCount] = 2;
    currentCannonRocketCount++;
    gotoxy(x - 2, y);
    cout << "#";
    cannonRocketX[currentCannonRocketCount] = x - 2;
    cannonRocketY[currentCannonRocketCount] = y;
    cannonRocketType[currentCannonRocketCount] = 3;
    currentCannonRocketCount++;
    Beep(2400, 10);
}
void HelicopterBulletCreate(int x, int y)
{
    y++;
    gotoxy(x, y);
    cout << ".";
    helicopterBulletsX[currenthelicoptersBulletsCount] = x;
    helicopterBulletsY[currenthelicoptersBulletsCount] = y;
    currenthelicoptersBulletsCount++;
    Beep(1900, 2);
}
void createBattleShip()
{
    int x = (rand() % 36) + 14;
    int y = 0;
    battleShipsX[currentBattleShipsCount] = x;
    battleShipsY[currentBattleShipsCount] = y;
    battleShipRocketReady[currentBattleShipsCount] = 0;
    battleShipsMovement[currentBattleShipsCount] = rand() % 2;
    printBattleShip(x, y);
    currentBattleShipsCount++;
}
void createHelicopter()
{
    int x = (rand() % 36) + 14;
    int y = 0;
    helicoptersX[currenthelicoptersCount] = x;
    helicoptersY[currenthelicoptersCount] = y;
    helicoptersBulletsReady[currenthelicoptersCount] = 0;
    helicoptersMovement[currenthelicoptersCount] = rand() % 2;
    printHelicopter(helicoptersX[currenthelicoptersCount], helicoptersY[currenthelicoptersCount]);
    currenthelicoptersCount++;
}
void createCannon()
{
    int x = 40;
    int y = 1;
    cannonX[currentCannonCount] = x;
    cannonY[currentCannonCount] = y;
    cannonRocketsReady[currentCannonCount] = 0;
    printCannon(cannonX[currentCannonCount], cannonY[currentCannonCount]);
    currentCannonCount++;
}
void removeBattleShip(int i)
{
    destroyGeneric(battleShipsX[i] - 1, battleShipsY[i], 3, 1, 10);
    eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
    removeElementFromIntArray(battleShipsX, i, currentBattleShipsCount);
    removeElementFromIntArray(battleShipsY, i, currentBattleShipsCount);
    removeElementFromIntArray(battleShipRocketReady, i, currentBattleShipsCount);
    removeElementFromBoolArray(battleShipsMovement, i, currentBattleShipsCount);
    currentBattleShipsCount--;
}
void removeHelicopter(int i)
{
    destroyGeneric(helicoptersX[i], helicoptersY[i], 1, 1, 10);
    eraseGeneric(helicoptersX[i], helicoptersY[i], 1, 1);
    removeElementFromIntArray(helicoptersX, i, currenthelicoptersCount);
    removeElementFromIntArray(helicoptersY, i, currenthelicoptersCount);
    removeElementFromIntArray(helicoptersBulletsReady, i, currenthelicoptersCount);
    removeElementFromBoolArray(helicoptersMovement, i, currenthelicoptersCount);
    currenthelicoptersCount--;
}
void removeCannon(int i)
{
    destroyGeneric(cannonX[i], cannonY[i] + 1, 1, 1, 1);
    destroyGeneric(cannonX[i] - 1, cannonY[i], 3, 1, 2);
    destroyGeneric(cannonX[i], cannonY[i] - 1, 1, 1, 1);
    eraseGeneric(cannonX[i] - 1, cannonY[i] - 1, 3, 3);
    removeElementFromIntArray(cannonX, i, currentCannonCount);
    removeElementFromIntArray(cannonY, i, currentCannonCount);
    removeElementFromIntArray(cannonRocketsReady, i, currentCannonCount);
    currentCannonCount--;
}
void printBattleShip(int x, int y)
{
    char b = 219;
    char c = 254;
    gotoxy(x - 2, y);
    setColor(0x18);
    cout << '<';
    cout << b;
    setColor(0x13);
    cout << c;
    setColor(0x18);
    cout << b;
    cout << '>';
    setColor(0x17);
}
void printHelicopter(int x, int y)
{
    setColor(0x17);
    gotoxy(x, y);
    cout << '%';
    setColor(0x17);
}
void printCannon(int x, int y)
{
    char c16 = 16;
    char c17 = 17;
    char c30 = 30;
    char c31 = 31;
    setColor(0x10);
    gotoxy(x, y - 1);
    cout << c30;
    gotoxy(x - 1, y);
    cout << c17;
    setColor(0x14);
    cout << '+';
    setColor(0x10);
    cout << c16;
    if (y != 30)
    {
        gotoxy(x, y + 1);
        cout << c31;
    }
    setColor(0x17);
}
void battleShipHandler()
{
    for (int i = currentBattleShipsCount - 1; i >= 0; i--)
    {
        if (checkCollisionWithPlayer(battleShipsX[i], battleShipsY[i]) || checkCollisionWithPlayer(battleShipsX[i] + 1, battleShipsY[i]) || checkCollisionWithPlayer(battleShipsX[i] - 1, battleShipsY[i]) || checkCollisionWithPlayer(battleShipsX[i] + 2, battleShipsY[i]) || checkCollisionWithPlayer(battleShipsX[i] - 2, battleShipsY[i]))
        {
            removeBattleShip(i);
            decreasePlayerHealth(50);
            continue;
        }
        moveBattleShipHorizontally(i);
        battleShipRocketReady[i]++;
        if (battleShipRocketReady[i] >= 15)
        {
            battleShipRocketCreate(battleShipsX[i], battleShipsY[i]);
            battleShipRocketReady[i] = 0;
        }
    }
    for (int i = currentBattleShipRocketsCount - 1; i >= 0; i--)
    {
        char next = screen[battleShipRocketY[i] + 1][battleShipRocketX[i]];
        if (checkCollisionWithPlayer(battleShipRocketX[i], battleShipRocketY[i]))
        {
            removeBattleShipRocket(i);
            decreasePlayerHealth(25);
        }
        else if (battleShipRocketY[i] < 29 && next == ' ')
        {
            moveBattleShipRocket(i);
        }
        else
        {
            removeBattleShipRocket(i);
        }
    }
}
void helicopterHandler()
{
    for (int i = currenthelicoptersCount - 1; i >= 0; i--)
    {
        if (checkCollisionWithPlayer(helicoptersX[i], helicoptersY[i]))
        {
            removeHelicopter(i);
            decreasePlayerHealth(20);
            continue;
        }
        moveHelicopterHorizontally(i);
        helicoptersBulletsReady[i]++;
        if (helicoptersBulletsReady[i] >= 7)
        {
            HelicopterBulletCreate(helicoptersX[i], helicoptersY[i]);
            helicoptersBulletsReady[i] = 0;
        }
    }
    for (int i = currenthelicoptersBulletsCount - 1; i >= 0; i--)
    {
        char next = screen[helicopterBulletsY[i] + 1][helicopterBulletsX[i]];
        if (checkCollisionWithPlayer(helicopterBulletsX[i], helicopterBulletsY[i]))
        {
            removeHelicopterBullet(i);
            decreasePlayerHealth(1);
        }
        else if (helicopterBulletsY[i] < 29 && next == ' ')
        {
            moveHelicopterBullet(i);
        }
        else
        {
            removeHelicopterBullet(i);
        }
    }
}
void cannonHandler()
{
    for (int i = currentCannonCount - 1; i >= 0; i--)
    {
        if (checkCollisionWithPlayer(cannonX[i], cannonY[i]) || checkCollisionWithPlayer(cannonX[i] + 1, cannonY[i]) || checkCollisionWithPlayer(cannonX[i] - 1, cannonY[i]) || checkCollisionWithPlayer(cannonX[i], cannonY[i] + 1) || checkCollisionWithPlayer(cannonX[i], cannonY[i] - 1))
        {
            removeCannon(i);
            decreasePlayerHealth(30);
            continue;
        }
        cannonRocketsReady[i]++;
        if (cannonRocketsReady[i] >= 25)
        {
            cannonRocketCreate(cannonX[i], cannonY[i]);
            cannonRocketsReady[i] = 0;
        }
    }
    for (int i = currentCannonRocketCount - 1; i >= 0; i--)
    {
        if (checkCollisionWithPlayer(cannonRocketX[i], cannonRocketY[i]))
        {
            removeCannonRocket(i);
            decreasePlayerHealth(25);
        }
        else if (checkCannonRocketBound(i))
        {
            moveCannonRocket(i);
        }
        else
        {
            removeCannonRocket(i);
        }
    }
}
void healthPowerupHandler()
{

    healthPowerUpRandomSpawnCount++;
    if (healthPowerUpRandomSpawnCount == healthPowerUpRandomSpawn)
    {
        healthPowerUpRandomSpawn = rand() % 300 + 50;
        healthPowerUpMovement = rand() % 2;
        healthPowerUpRandomSpawnCount = 0;
        healthPowerUpVisibility = true;
    }
    if (healthPowerUpVisibility)
    {
        if (checkCollisionWithPlayer(healthPowerupX, healthPowerupY))
        {
            currentHealth += 20;
            if (currentHealth > 100)
            {
                currentHealth = 100;
            }
            statsUpdateFlag = true;
            healthPowerUpVisibility = false;
            eraseGeneric(healthPowerupX, healthPowerupY, 1, 1);
            healthPowerupY = 0;
            healthPowerupX = 50;
        }
        else if (healthPowerupY < 29)
        {
            healthPowerupCount++;
            if (healthPowerupCount == 2)
            {
                healthPowerupCount = 0;
                moveHealthPowerupHorizontally();
                moveHealthPowerupVertically();
            }
        }
        else
        {
            healthPowerUpVisibility = false;
            eraseGeneric(healthPowerupX, healthPowerupY, 1, 1);
            healthPowerupY = 0;
            healthPowerupX = 50;
        }
    }
}
void moveHealthPowerupVertically()
{
    eraseGeneric(healthPowerupX, healthPowerupY, 1, 1);
    healthPowerupY++;
    printHealthPowerup(healthPowerupX, healthPowerupY);
}
void moveHealthPowerupHorizontally()
{
    if (screen[healthPowerupY][healthPowerupX - 1] == m || screen[healthPowerupY + 1][healthPowerupX - 1] == m)
    {
        healthPowerUpMovement = true;
    }
    else if (screen[healthPowerupY][healthPowerupX + 1] == m || screen[healthPowerupY + 1][healthPowerupX + 1] == m)
    {
        healthPowerUpMovement = false;
    }
    if (healthPowerUpMovement)
    {
        eraseGeneric(healthPowerupX, healthPowerupY, 1, 1);
        healthPowerupX++;
        printHealthPowerup(healthPowerupX, healthPowerupY);
    }
    else
    {
        eraseGeneric(healthPowerupX, healthPowerupY, 1, 1);
        healthPowerupX--;
        printHealthPowerup(healthPowerupX, healthPowerupY);
    }
}
void printHealthPowerup(int x, int y)
{
    if (healthPowerupX % 2)
    {
        setColor(0x14);
    }
    else
    {
        setColor(0x16);
    }
    gotoxy(x, y);
    cout << (char)3;
    setColor(0x17);
}
bool checkCannonRocketBound(int i)
{
    if (cannonRocketY[i] < 29 && cannonRocketType[i] == 0 && getCharxy(cannonRocketX[i], cannonRocketY[i] + 1) == ' ')
    {
        return true;
    }
    else if (cannonRocketY[i] >= 0 && cannonRocketType[i] == 2 && getCharxy(cannonRocketX[i], cannonRocketY[i] - 1) == ' ')
    {
        return true;
    }
    else if (cannonRocketType[i] == 1 && getCharxy(cannonRocketX[i] + 1, cannonRocketY[i]) == ' ')
    {
        return true;
    }
    else if (cannonRocketType[i] == 3 && getCharxy(cannonRocketX[i] - 1, cannonRocketY[i]) == ' ')
    {
        return true;
    }
    return false;
}
void moveBattleShipHorizontally(int i)
{
    battleShipMovementTimer[i]++;
    if (battleShipMovementTimer[i] >= 3)
    {
        battleShipMovementTimer[i] = 0;
        eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
        if (screen[battleShipsY[i]][battleShipsX[i] - 4] == m)
        {
            battleShipsMovement[i] = 1;
        }
        else if (screen[battleShipsY[i]][battleShipsX[i] + 4] == m)
        {
            battleShipsMovement[i] = 0;
        }
        if (battleShipsMovement[i])
        {
            battleShipsX[i]++;
        }
        else
        {
            battleShipsX[i]--;
        }
        printBattleShip(battleShipsX[i], battleShipsY[i]);
    }
}
void moveHelicopterHorizontally(int i)
{
    helicoptersMovementTimer[i]++;
    if (helicoptersMovementTimer[i] >= 3)
    {
        helicoptersMovementTimer[i] = 0;
        eraseGeneric(helicoptersX[i], helicoptersY[i], 1, 1);
        if (screen[helicoptersY[i]][helicoptersX[i] - 1] == m)
        {
            helicoptersMovement[i] = true;
        }
        else if (screen[helicoptersY[i]][helicoptersX[i] + 1] == m)
        {
            helicoptersMovement[i] = false;
        }
        if (helicoptersMovement[i])
        {
            helicoptersX[i]++;
        }
        else
        {
            helicoptersX[i]--;
        }
        printHelicopter(helicoptersX[i], helicoptersY[i]);
    }
}
void moveBattleShipRocket(int i)
{
    gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
    cout << " ";
    battleShipRocketY[i]++;
    gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
    cout << "#";
}
void moveCannonRocket(int i)
{
    gotoxy(cannonRocketX[i], cannonRocketY[i]);
    cout << ' ';
    if (cannonRocketType[i] == 0)
    {
        cannonRocketY[i]++;
    }
    else if (cannonRocketType[i] == 1)
    {
        cannonRocketX[i]++;
    }
    else if (cannonRocketType[i] == 2)
    {
        cannonRocketY[i]--;
    }
    else if (cannonRocketType[i] == 3)
    {
        cannonRocketX[i]--;
    }
    gotoxy(cannonRocketX[i], cannonRocketY[i]);
    cout << '#';
}
void moveHelicopterBullet(int i)
{
    gotoxy(helicopterBulletsX[i], helicopterBulletsY[i]);
    cout << " ";
    helicopterBulletsY[i]++;
    gotoxy(helicopterBulletsX[i], helicopterBulletsY[i]);
    cout << ".";
}
void removeBattleShipRocket(int i)
{
    gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
    cout << " ";
    removeElementFromIntArray(battleShipRocketX, i, currentBattleShipRocketsCount);
    removeElementFromIntArray(battleShipRocketY, i, currentBattleShipRocketsCount);
    currentBattleShipRocketsCount--;
}
void removeHelicopterBullet(int i)
{
    gotoxy(helicopterBulletsX[i], helicopterBulletsY[i]);
    cout << " ";
    removeElementFromIntArray(helicopterBulletsX, i, currenthelicoptersBulletsCount);
    removeElementFromIntArray(helicopterBulletsY, i, currenthelicoptersBulletsCount);
    currenthelicoptersBulletsCount--;
}
void removeCannonRocket(int i)
{
    gotoxy(cannonRocketX[i], cannonRocketY[i]);
    cout << " ";
    removeElementFromIntArray(cannonRocketX, i, currentCannonRocketCount);
    removeElementFromIntArray(cannonRocketY, i, currentCannonRocketCount);
    removeElementFromIntArray(cannonRocketType, i, currentCannonRocketCount);
    currentCannonRocketCount--;
}
void drawPlayer(int x, int y)
{
    if (currentPlayer == 1)
    {
        printPlayer1(x, y);
    }
    else if (currentPlayer == 2)
    {
        printPlayer2(x, y);
    }
    else if (currentPlayer == 3)
    {
        printPlayer3(x, y);
    }
}
void printPlayer1(int x, int y)
{
    char s = 205;
    char t = 30;
    setColor(0x16);
    gotoxy(x, y - 1);
    cout << t;
    setColor(0x17);
    gotoxy(x - 2, y);
    setColor(0x16);
    cout << s << s;
    setColor(0x17);
    cout << m;
    setColor(0x16);
    cout << s << s;
    setColor(0x17);
    gotoxy(x, y + 1);
    cout << m;
    gotoxy(x - 1, y + 2);
    setColor(0x16);
    cout << s << m << s;
    setColor(0x17);
}
void printPlayer2(int x, int y)
{
    setColor(0x1e);
    gotoxy(x - 2, y - 1);
    cout << (char)205 << (char)202 << (char)206 << (char)202 << (char)205;
    gotoxy(x, y);
    cout << (char)186;
    gotoxy(x - 1, y + 1);
    cout << (char)205 << (char)202 << (char)205;
    setColor(0x17);
}
void printPlayer3(int x, int y)
{
    char s = 205;
    char t = 30;
    setColor(0x16);
    gotoxy(x, y - 1);
    cout << '^';
    setColor(0x17);
    gotoxy(x - 2, y);
    setColor(0x16);
    cout << '/' << '/';
    setColor(0x17);
    cout << '|';
    setColor(0x16);
    cout << '\\' << '\\';
    setColor(0x17);
    gotoxy(x, y + 1);
    cout << '|';
    gotoxy(x - 1, y + 2);
    setColor(0x16);
    cout << '/' << '|' << '\\';
    setColor(0x17);
}
void erasePlayer(int x, int y)
{
    if (currentPlayer == 2)
    {
        gotoxy(x - 2, y - 1);
        cout << "     ";
        gotoxy(x, y);
        cout << " ";
        gotoxy(x - 1, y + 1);
        cout << "   ";
    }
    else
    {
        gotoxy(x, y - 1);
        cout << " ";
        gotoxy(x - 2, y);
        cout << "     ";
        gotoxy(x, y + 1);
        cout << " ";
        gotoxy(x - 1, y + 2);
        cout << "   ";
    }
}
void eraseGeneric(int x, int y, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        gotoxy(x, y);
        for (int j = 0; j < rows; j++)
        {
            cout << " ";
        }
        y++;
    }
}
void destroyGeneric(int x, int y, int rows, int cols, int duration)
{
    int initialY = y;
    setColor(0x17);
    for (int i = 0; i < cols; i++)
    {
        gotoxy(x, y);
        for (int j = 0; j < rows; j++)
        {
            cout << '*';
        }
        y++;
    }
    y = initialY;
    Sleep(duration / 2);
    setColor(0x18);
    for (int i = 0; i < cols; i++)
    {
        gotoxy(x, y);
        for (int j = 0; j < rows; j++)
        {
            cout << 'x';
        }
        y++;
    }
    y = initialY;
    Sleep(duration / 2);
}
void movePlayerUp()
{
    if (playerY > 2)
    {

        if (screen[playerY - 1][playerX - 2] == m)
        {
            movePlayerRight();
        }
        else if (screen[playerY - 1][playerX + 2] == m)
        {
            movePlayerLeft();
        }
        erasePlayer(playerX, playerY);
        playerY--;
        drawPlayer(playerX, playerY);
    }
}
void movePlayerDown()
{
    if ((playerY <= 27 && currentPlayer == 2) || (playerY <= 26))
    {
        if (screen[playerY + 1][playerX - 2] == m || screen[playerY + 3][playerX - 1] == m)
        {
            movePlayerRight();
        }
        else if (screen[playerY + 1][playerX + 2] == m || screen[playerY + 3][playerX + 1] == m)
        {
            movePlayerLeft();
        }
        erasePlayer(playerX, playerY);
        playerY++;
        drawPlayer(playerX, playerY);
    }
}
void movePlayerLeft()
{
    if (currentPlayer == 2)
    {
        if (screen[playerY - 1][playerX - 3] != m && screen[playerY][playerX - 3] != m)
        {
            erasePlayer(playerX, playerY);
            playerX--;
            drawPlayer(playerX, playerY);
        }
    }
    else
    {
        if (screen[playerY][playerX - 3] != m && screen[playerY + 2][playerX - 2] != m)
        {
            erasePlayer(playerX, playerY);
            playerX--;
            drawPlayer(playerX, playerY);
        }
    }
}
void movePlayerRight()
{
    if (currentPlayer == 2)
    {
        if (screen[playerY - 1][playerX + 3] != m && screen[playerY][playerX + 3] != m)
        {
            erasePlayer(playerX, playerY);
            playerX++;
            drawPlayer(playerX, playerY);
        }
    }
    else
    {
        if (screen[playerY][playerX + 3] != m && screen[playerY + 2][playerX + 2] != m)
        {
            erasePlayer(playerX, playerY);
            playerX++;
            drawPlayer(playerX, playerY);
        }
    }
}
void handleRocketLasorBulletCollision()
{
    for (int i = currentLaserBulletsCount - 1; i >= 0; i--)
    {
        for (int j = currentCannonRocketCount - 1; j >= 0; j--)
        {
            if ((playerLaserY[i] == cannonRocketY[j] + 1) && (playerLaserX[i] == cannonRocketX[j]))
            {
                removeLaserBullet(i);
                removeCannonRocket(j);
            }
        }
        for (int j = currentBattleShipRocketsCount - 1; j >= 0; j--)
        {
            if ((playerLaserY[i] == battleShipRocketY[j] + 1) && (playerLaserX[i] == battleShipRocketX[j]))
            {
                removeLaserBullet(i);
                removeBattleShipRocket(j);
            }
        }
    }
}
void clearUnprocessedKeys()
{
    cin.sync();
    while (kbhit())
    {
        getch();
    }
}
void pauseMenu()
{
    int choice;
    setColor(0);
    while (1)
    {
        printLogo();
        printMenuItems(16, pauseMenuItems, 0, 4);
        clearUnprocessedKeys();
        choice = takeChoice(16, 4, 0x3);
        if (choice == 0)
        {
            // Drawing for smooth resume of game
            drawMaze();
            drawPlayer(playerX, playerY);
            drawStatsWindow();
            printStats();
            return;
        }
        else if (choice == 1)
        {
            saveGame();
        }
        else if (choice == 2)
        {
            clearUnprocessedKeys();
            gameRunning = false;
            return;
        }
        else if (choice == 3)
        {
            exit(0); // Terminate the game
        }
    }
}
void render()
{
    clearUnprocessedKeys();
    drawPlayer(playerX, playerY);
    while (gameRunning)
    {
        startTime = clock();
        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerUp();
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            if (currentPlayer == 1)
            {
                createLaserBullet(playerX - 1, playerY);
                createLaserBullet(playerX + 1, playerY);
            }
            else if (currentPlayer == 2)
            {
                createLaserBullet(playerX - 1, playerY);
                createLaserBullet(playerX, playerY);
                createLaserBullet(playerX + 1, playerY);
            }
            else
            {
                createLaserBullet(playerX, playerY);
            }
            Beep(1700, 5);
        }
        handleEdges();
        moveMazeAndGameElements();
        handleRandomEnemySpawn();
        helicopterHandler();
        battleShipHandler();
        healthPowerupHandler();
        cannonHandler();
        handleRocketLasorBulletCollision();
        moveLaserBullets();
        handleRocketLasorBulletCollision();
        if (statsUpdateFlag)
        {
            printStats();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            pauseMenu();
        }
        stopTime = clock();
        timeElapsed = double(stopTime - startTime);
        if (timeElapsed < 60)
            Sleep(60 - timeElapsed);
    }
    if (currentHealth <= 0)
    {
        showAfterGameScreen();
    }
    setColor(0x7);
}
void showAfterGameScreen()
{
    clearUnprocessedKeys();
    Sleep(100);
    printGameOver();
    printScore(52, 18);
    halt();
}

void printScore(int x, int y)
{
    gotoxy(x, y);
    setColor(0x5);
    cout << "Your Score: ";
    setColor(0x6);
    cout << score;
}
void handleEdges()
{
    if (currentPlayer == 2)
    {
        if (screen[playerY - 2][playerX + 2] == m)
        {
            movePlayerLeft();
        }
        if (screen[playerY - 2][playerX - 2] == m)
        {
            movePlayerRight();
        }
    }
    else
    {
        if (screen[playerY - 1][playerX + 2] == m)
        {
            movePlayerLeft();
        }
        if (screen[playerY - 1][playerX - 2] == m)
        {
            movePlayerRight();
        }
    }
}
void printMenuItems(int offset, string items[], int startingIndex, int endingIndex)
{
    setColor(0x3);
    gotoxy(45, offset);
    for (int i = startingIndex; i < endingIndex; i++)
    {
        gotoxy(45, offset + i);
        cout << "  " << i + 1 - startingIndex << ".\t" << items[i];
    }
    setColor(0x7);
}
int takeChoice(int offset, int size, short color)
{
    int pointerPos = 0;
    int previousPos = 0;
    int key = -1;
    if (size != 0)
    {
        movePointer(previousPos, pointerPos, offset, color);
    }
    else
    {
        getch();
        return key;
    }
    while (1)
    {
        key = getch();
        if (key == 224) // getch() function two values for arrow keys,so discarding first one
        {
            key = getch();
        }
        if (key == 72 && pointerPos == 0)
        {
            previousPos = pointerPos;
            pointerPos = size - 1;
            movePointer(previousPos, pointerPos, offset, color);
        }
        else if (key == 80 && pointerPos == size - 1)
        {
            previousPos = pointerPos;
            pointerPos = 0;
            movePointer(previousPos, pointerPos, offset, color);
        }
        else if (key == 72 && pointerPos > 0)
        {
            previousPos = pointerPos;
            pointerPos--;
            movePointer(previousPos, pointerPos, offset, color);
        }
        else if (key == 80 && pointerPos < size - 1)
        {
            previousPos = pointerPos;
            pointerPos++;
            movePointer(previousPos, pointerPos, offset, color);
        }
        if (key > '0' && key <= '9')
        {
            key -= '0';
            if (key <= size)
            {
                key = key - 1;
                break;
            }
        }
        else if (key == VK_ESCAPE)
        {
            key = -1;
            break;
        }
        else if (key == VK_RETURN)
        {
            key = pointerPos;
            break;
        }
    }
    setColor(0x7);
    return key;
}
void movePointer(int previousPos, int pointerPos, int offset, short color)
{
    previousPos += offset;
    pointerPos += offset;
    string temp = getStringAtxy(45, previousPos);
    setColor(color);
    gotoxy(45, previousPos);
    cout << temp;
    temp = getStringAtxy(45, pointerPos);
    setColor(0x30);
    gotoxy(45, pointerPos);
    cout << temp;
}
string getStringAtxy(short int x, short int y)
{
    char buffer[31];
    COORD position{x, y};
    DWORD dwChars;
    ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 31, position, &dwChars);
    buffer[31] = '\0';
    string temp = buffer;
    return temp;
}
void consoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}
void halt()
{
    int key;
    gotoxy((120 - 24) / 2, 24);
    setColor(0x2);
    cout << "Press ENTER to Continue";
    do
    {
        key = getch();
    } while (key != VK_RETURN);
}
void printLogo()
{
    system("cls");
    setColor(0x3);
    for (int y = 0; y < 16; y++)
    {
        gotoxy(38, y);
        cout << logo[y];
    }
    setColor(0x7);
}
void printGameOver()
{
    setColor(0x3);
    system("cls");
    for (int y = 0; y < 16; y++)
    {
        gotoxy(38, y);
        cout << gameOverLogo[y];
    }
    setColor(0x7);
}
void setColor(short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int digitCount(int number)
{
    int count = 0;
    while (number != 0)
    {
        number /= 10;
        count++;
    }
    return count;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharxy(short x, short y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : '\0';
}

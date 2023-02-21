#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;

// globals
#define numOfLaserBullets 20
#define numOfBattleShips 10
#define numOfHelicopters 10
#define numOfCannons 10
int playerLaserX[numOfLaserBullets];
int playerLaserY[numOfLaserBullets];
int currentLaserBulletsCount = 0;
int mazeMoveCount = 0;
int score = 0;
int currentHealth = 100;
bool gameRunning = false;
int randomEnemy=0;
int mazeEnemyCount=0;
int mazeEnemyRandomCount=30;

int mazePos = 0;
int mazeNumber = 0;

// mazes
char maze1[25][61] = {
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******"};
char maze2[25][61] = {
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "*******                                              *******",
    "********                                            ********",
    "*********                                          *********",
    "**********                                        **********",
    "**********                                        **********",
    "*********                                          *********",
    "*******                                              *******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******"};
char maze3[25][61] = {
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "********                                             *******",
    "*********                                           ********",
    "**********                                        **********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "*********                                          *********",
    "********                                            ********",
    "*******                                              *******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******",
    "******                                                ******"};
char maze4[25][61] = {
    "*******                                              *******",
    "********                                            ********",
    "*********                                          *********",
    "**********                                        **********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "***********                                      ***********",
    "**********                                        **********",
    "*********                                          *********",
    "********                                            ********",
    "*******                                              *******"};

string emptyLine = "                                                                                ";

char screen[25][60];
char screenSingleLine[60];
char c254 = 254;
char c219 = 219;

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

string menuItems[] = {"start game", "options", "exit"};
int playerX = 20, playerY = 15;

// function prototypes
void printLogo();
char getCharxy(short x, short y);
char getCharxy(short x, short y);
void halt();
void gotoxy(int x, int y);
void setColor(short color);
void consoleCursor(bool visibility);
int takeChoice(int offset, int size, short color);
string getStringAtxy(short int x, short int y);
void printMenuItems(int offset, string items[], int arraySize);
void movePointer(int previousPos, int pointerPos, int offset, short color);
void copyCharArray(char arr1[], char arr2[], int size);

void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();
void drawPlayer(int x, int y);
void erasePlayer(int x, int y);
void createLaserBullet(int x, int y);
void moveLaserBullets();
bool checkCollisionWithPlayer(int x, int y);

void eraseGeneric(int x, int y, int rows, int cols);

void removeElementFromIntArray(int arr[], int elementIndex, int arraySize);
void removeElementFromBoolArray(bool arr[], int elementIndex, int arraySize);
void removeLaserBullet(int i);
int findElementIndex(int xVal, int yVal, int arr1[], int arr2[], int arrSize);
void collisionHandling(int x, int y, char next);

void moveMazeAndGameElements();
void moveMaze();
void startGame();
void init();
void printStats();

void printBattleShip(int x, int y);
void createBattleShip();
void battleShipHandler();
void battleShipRocketCreate(int x, int y);
void moveBattleShipHorizontally(int i);
void moveBattleShipRocket(int i);
void removeBattleShip(int i);
void removeBattleShipRocket(int i);
bool checkCollisionWithBattleShip(int i);

void printHelicopter(int x, int y);
void createHelicopter();
void helicopterHandler();
void helicopterBulletCreate(int x, int y);
void moveHelicopterHorizontally(int i);
void moveHelicopterBullet(int i);
void removeHelicopter(int i);
void removeHelicopterBullet(int i);
bool checkCollisionWithHelicopter(int i);

void printCannon(int x, int y);
void createCannon();
void cannonHandler();
void cannonRocketCreate(int x, int y);
void moveCannonRocket(int i);
bool checkCannonRocketBound(int i);
void removeCannon(int i);
void removeCannonRocket(int i);
bool checkCollisionWithCannon(int i);

void addScore(int value);
void decreasePlayerHealth(int value);

void printDebugInfo()
{
    gotoxy(61, 0);
    //   cout << "No of bullets:" << currentCannonBulletsCount << endl;
    //  cout << "No of battleShips" << currentBattleShipsCount<<endl;
    cout << "Health: " << currentHealth << endl;
    gotoxy(61, 1);
    cout << "Score: " << score;
    gotoxy(61, 2);
    cout << "helicopters:" << currenthelicoptersCount;
    gotoxy(61, 3);
    cout << "Bullets: " << currentLaserBulletsCount;
}
void printStats()
{
    gotoxy(62, 0);
    if (currentHealth == 100)
    {
        cout << "Health: " << currentHealth << endl;
    }
    else
    {
        cout << "Health:  " << currentHealth << endl;
    }
    gotoxy(62, 1);
    cout << "Score: " << score;
}
int main()
{
    int choice = 0;
    consoleCursor(false);
    while (choice != 2)
    {
        system("cls");
        printLogo();
        printMenuItems(12, menuItems, 3);
        choice = takeChoice(12, 3, 0x3);
        if (choice == 0)
        {
            cin.sync();
            init();
            startGame();
        }
    }
}
void init()
{
    gameRunning = true;
    system("cls");
    currentBattleShipRocketsCount = 0;
    currentBattleShipsCount = 0;
    currenthelicoptersBulletsCount = 0;
    currenthelicoptersCount = 0;
    currentCannonCount = 0;
    currentCannonRocketCount = 0;
    currentLaserBulletsCount = 0;
    currentHealth = 100;
    mazePos = 0;
    mazeNumber = 0;
    score = 0;
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            screen[i][j] = maze1[i][j];
        }
    }
    char c254 = 254;
    for (int i = 0; i < 25; i++)
    {
        gotoxy(60, i);
        cout << c254;
        gotoxy(61, i);
        cout << c254;
    }
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
    cout << '|';
    playerLaserX[currentLaserBulletsCount] = x;
    playerLaserY[currentLaserBulletsCount] = y;
    currentLaserBulletsCount++;
}
int findElementIndex(int xVal, int yVal, int arr1[], int arr2[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        // gotoxy(0, 0);
        // cout << emptyLine;
        // gotoxy(0, 0);
        // cout << "debug: " << arr1[i] << " " << arr2[i] << " " << xVal << " " << yVal << endl;
        // system("pause");
        if (arr1[i] == xVal && arr2[i] == yVal)
        {
            return i;
        }
    }
    // system("pause");
    return -1;
}
void addScore(int value)
{
    score += value;
}
void decreasePlayerHealth(int value)
{
    currentHealth -= value;
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
        if (playerLaserY[i] - 1 <= 0 || checkCollisionWithBattleShip(i) || checkCollisionWithHelicopter(i) || checkCollisionWithCannon(i))
        {
            removeLaserBullet(i);
            continue;
        }
        char next = getCharxy(playerLaserX[i], playerLaserY[i] - 1);
        if (next == ' ' || next == '.')
        {

            gotoxy(playerLaserX[i], playerLaserY[i]);
            cout << ' ';
            playerLaserY[i]--;
            gotoxy(playerLaserX[i], playerLaserY[i]);
            cout << '|';
        }
        else
        {
            removeLaserBullet(i);
        }
    }
}
void moveMaze()
{
    char c = 219;
    if (mazeMoveCount == 2)
    {
        mazePos++;
        if (mazePos == 25)
        {
            mazeNumber = rand() % 4;
            mazePos = 0;
        }
        if (mazeNumber == 0)
        {
            copyCharArray(screenSingleLine, maze1[mazePos], 60);
        }
        else if (mazeNumber == 2)
        {
            copyCharArray(screenSingleLine, maze2[mazePos], 60);
        }
        else if (mazeNumber == 3)
        {

            copyCharArray(screenSingleLine, maze3[mazePos], 60);
        }
        else
        {
            copyCharArray(screenSingleLine, maze4[mazePos], 60);
        }
    }
    copyCharArray(screen[0], screenSingleLine, 60);
    if (mazeMoveCount == 4)
    {
        for (int i = 25 - 1; i > 0; i--)
        {
            copyCharArray(screen[i], screen[i - 1], 60);
        }
        for (int y = 0; y < 25; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                if (getCharxy(x, y) == '*' && screen[y][x] == ' ')
                {
                    gotoxy(x, y);
                    cout << ' ';
                }
                else if (screen[y][x] == '*' && getCharxy(x, y) == ' ')
                {
                    gotoxy(x, y);
                    cout << '*';
                }
            }
            for (int x = 60 - 12; x < 60; x++)
            {
                if (getCharxy(x, y) == '*' && screen[y][x] == ' ')
                {
                    gotoxy(x, y);
                    cout << ' ';
                }
                else if (screen[y][x] == '*' && getCharxy(x, y) == ' ')
                {
                    gotoxy(x, y);
                    cout << '*';
                }
            }
        }
    }
}
void moveMazeAndGameElements()
{
    mazeMoveCount++;
    mazeEnemyCount++;
    if(mazeEnemyCount==mazeEnemyRandomCount)
    {
        int randomEnemy =rand()%3;
        if(randomEnemy==0)
        {
            createBattleShip();
        }
        else if(randomEnemy==1)
        {
            createHelicopter();
        }
        else if(randomEnemy==2)
        {
            createCannon();
        }
        mazeEnemyCount=0;
        mazeEnemyRandomCount=rand()%50+10;
    }
    moveMaze();
    if (mazeMoveCount == 4)
    {
        for (int i = currentBattleShipsCount - 1; i >= 0; i--)
        {
            if (battleShipsY[i] < 24)
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
        for (int i = currenthelicoptersCount - 1; i >= 0; i--)
        {
            if (helicoptersY[i] < 24)
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
        for (int i = currentCannonCount - 1; i >= 0; i--)
        {
            if (cannonY[i] < 24)
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
        mazeMoveCount = 0;
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
}
void HelicopterBulletCreate(int x, int y)
{
    y++;
    gotoxy(x, y);
    cout << ".";
    helicopterBulletsX[currenthelicoptersBulletsCount] = x;
    helicopterBulletsY[currenthelicoptersBulletsCount] = y;
    currenthelicoptersBulletsCount++;
}
void createBattleShip()
{
    int x = (rand() % 20) + 20;
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
    int x = (rand() % 20) + 20;
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
    int x = 30;
    int y = 1;
    cannonX[currentCannonCount] = x;
    cannonY[currentCannonCount] = y;
    cannonRocketsReady[currentCannonCount] = 0;
    printCannon(cannonX[currentCannonCount], cannonY[currentCannonCount]);
    currentCannonCount++;
}
void removeBattleShip(int i)
{
    eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
    removeElementFromIntArray(battleShipsX, i, currentBattleShipsCount);
    removeElementFromIntArray(battleShipsY, i, currentBattleShipsCount);
    removeElementFromIntArray(battleShipRocketReady, i, currentBattleShipsCount);
    removeElementFromBoolArray(battleShipsMovement, i, currentBattleShipsCount);
    currentBattleShipsCount--;
}
void removeHelicopter(int i)
{
    eraseGeneric(helicoptersX[i], helicoptersY[i], 1, 1);
    removeElementFromIntArray(helicoptersX, i, currenthelicoptersCount);
    removeElementFromIntArray(helicoptersY, i, currenthelicoptersCount);
    removeElementFromIntArray(helicoptersBulletsReady, i, currenthelicoptersCount);
    removeElementFromBoolArray(helicoptersMovement, i, currenthelicoptersCount);
    currenthelicoptersCount--;
}
void removeCannon(int i)
{
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
    cout << "<" << b << c << b << ">";
}
void printHelicopter(int x, int y)
{
    gotoxy(x, y);
    cout << '%';
}
void printCannon(int x, int y)
{
    char c16 = 16;
    char c17 = 17;
    char c30 = 30;
    char c31 = 31;
    gotoxy(x, y - 1);
    cout << c30;
    gotoxy(x - 1, y);
    cout << c17 << 'o' << c16;
    gotoxy(x, y + 1);
    cout << c31;
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

        eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
        if (getCharxy(battleShipsX[i] - 4, battleShipsY[i]) == '*' || getCharxy(battleShipsX[i] + 4, battleShipsY[i]) == '*')
        {
            battleShipsMovement[i] = !battleShipsMovement[i];
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

        if (battleShipRocketReady[i] >= 15)
        {
            battleShipRocketCreate(battleShipsX[i], battleShipsY[i]);
            battleShipRocketReady[i] = 0;
        }
    }
    for (int i = currentBattleShipRocketsCount - 1; i >= 0; i--)
    {
        char next = getCharxy(battleShipRocketX[i], battleShipRocketY[i] + 1);
        if (checkCollisionWithPlayer(battleShipRocketX[i], battleShipRocketY[i]))
        {
            removeBattleShipRocket(i);
            decreasePlayerHealth(25);
        }
        else if (battleShipRocketY[i] < 24 && next == ' ')
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
        char next = getCharxy(helicopterBulletsX[i], helicopterBulletsY[i] + 1);
        if (checkCollisionWithPlayer(helicopterBulletsX[i], helicopterBulletsY[i]))
        {
            removeHelicopterBullet(i);
            decreasePlayerHealth(1);
        }
        else if (helicopterBulletsY[i] < 24 && next == ' ')
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
bool checkCannonRocketBound(int i)
{
    if (cannonRocketY[i] <= 25 && cannonRocketType[i] == 0 && getCharxy(cannonRocketX[i], cannonRocketY[i] + 1) == ' ')
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
        if (screen[battleShipsY[i]][battleShipsX[i] - 4] == '*')
        {
            battleShipsMovement[i] = 1;
        }
        else if (screen[battleShipsY[i]][battleShipsX[i] + 4] == '*')
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
        if (screen[helicoptersY[i]][helicoptersX[i] - 1] == '*')
        {
            helicoptersMovement[i] = true;
        }
        else if (screen[helicoptersY[i]][helicoptersX[i] + 1] == '*')
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
    char b = 254;
    char s = 205;
    char t = 30;
    gotoxy(x, y - 1);
    cout << t;
    gotoxy(x - 2, y);
    cout << s << s << b << s << s;
    gotoxy(x, y + 1);
    cout << b;
    gotoxy(x - 1, y + 2);
    cout << s << b << s;
}
void removeCannonRocket(int i)
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
void movePlayerUp()
{
    if (playerY > 2)
    {
        if (getCharxy(playerX - 2, playerY - 1) == '*')
        {
            movePlayerRight();
        }
        else if (getCharxy(playerX + 2, playerY - 1) == '*')
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
    if (playerY <= 21)
    {
        if (getCharxy(playerX - 2, playerY + 1) == '*')
        {
            movePlayerRight();
        }
        else if (getCharxy(playerX + 2, playerY + 1) == '*')
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
    if (getCharxy(playerX - 3, playerY) != '*')
    {
        erasePlayer(playerX, playerY);
        playerX--;
        drawPlayer(playerX, playerY);
    }
}
void movePlayerRight()
{
    if (getCharxy(playerX + 3, playerY) != '*')
    {
        erasePlayer(playerX, playerY);
        playerX++;
        drawPlayer(playerX, playerY);
    }
}
void startGame()
{
    init();
    drawPlayer(playerX, playerY);
    while (gameRunning)
    {
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
            createLaserBullet(playerX, playerY);
        }
        if (screen[playerY - 1][playerX + 2] == '*')
        {
            movePlayerLeft();
        }
        if (screen[playerY - 1][playerX - 2] == '*')
        {
            movePlayerRight();
        }
        helicopterHandler();
        battleShipHandler();
        cannonHandler();
        moveMazeAndGameElements();
        Sleep(75);
    }
}
void printMenuItems(int offset, string items[], int arraySize)
{
    setColor(0x3);
    gotoxy(0, offset);
    for (int i = 1; i <= arraySize; i++)
    {
        cout << "  " << i << ".\t" << items[i - 1] << endl;
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
        if (GetAsyncKeyState(VK_UP) && pointerPos > 0)
        {
            previousPos = pointerPos;
            pointerPos--;
            movePointer(previousPos, pointerPos, offset, color);
        }
        else if (GetAsyncKeyState(VK_DOWN) && pointerPos < size - 1)
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
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            key = -1;
            break;
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            key = pointerPos;
            break;
        }
        Sleep(100);
    }
    setColor(0x7);
    return key;
}
void movePointer(int previousPos, int pointerPos, int offset, short color)
{
    previousPos += offset;
    pointerPos += offset;
    string temp = getStringAtxy(0, previousPos);
    setColor(color);
    gotoxy(0, previousPos);
    cout << temp;
    temp = getStringAtxy(0, pointerPos);
    setColor(0x30);
    gotoxy(0, pointerPos);
    cout << temp;
}
string getStringAtxy(short int x, short int y)
{
    char buffer[81];
    COORD position{x, y};
    DWORD dwChars;
    ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 80, position, &dwChars);
    buffer[80] = '\0';
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
    cout << "Press any key to continue..." << endl;
    getch();
}
void printLogo()
{
    setColor(0x3);
    cout << " 00000   0   0        0   000000   00000    " << endl;
    cout << " 0   0   0    0      0    0        0   0    " << endl;
    cout << " 00000   0     0    0     000000   00000    " << endl;
    cout << " 0   0   0      0  0      0        0   0    " << endl;
    cout << " 0    0  0       00       000000   0    0   " << endl;
    cout << "                                            " << endl;
    cout << "    00000     00000     0     0000          " << endl;
    cout << "    0   0     0   0     0     0   0         " << endl;
    cout << "    00000     00000     0     0   0         " << endl;
    cout << "    0   0     0   0     0     0   0         " << endl;
    cout << "    0    0    0   0     0     0000          " << endl;
    setColor(0x7);
}
void setColor(short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
using namespace std;

// globals
#define numOfCannonBullets 100
#define numOfBattleShips 100
int playerCannonX[numOfCannonBullets];
int playerCannonY[numOfCannonBullets];
int currentCannonBulletsCount = 0;
int mazeMoveCount = 0;
int mazeBattleShipCreate = 0;

// mazes
string maze1[] = {
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******"};
string maze2[] = {
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    " ******                                                                  ****** ",
    "  ******                                                                ******  ",
    "   ******                                                              ******   ",
    "    ******                                                            ******    ",
    "    ******                                                            ******    ",
    "   ******                                                              ******   ",
    " ******                                                                  ****** ",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******",
    "******                                                                    ******"};
string emptyLine = "                                                                                ";
string screen[20];

int battleShipsX[numOfBattleShips];
int battleShipsY[numOfBattleShips];
bool battleShipsMovement[numOfBattleShips];
int battleShipRocketX[numOfBattleShips];
int battleShipRocketY[numOfBattleShips];
int battleShipRocketReady[numOfBattleShips];
int currentBattleShipRocketsCount = 0;
int currentBattleShipsCount = 0;

string menuItems[] = {"start game", "options", "exit"};
int playerX = 20, playerY = 15;

// function prototypes
void printLogo();
char getCharxy(short x, short y);
void halt();
void gotoxy(int x, int y);
void setColor(short color);
void consoleCursor(bool visibility);
int takeChoice(int offset, int size, short color);
string getStringAtxy(short int x, short int y);
void printMenuItems(int offset, string items[], int arraySize);
void movePointer(int previousPos, int pointerPos, int offset, short color);
// void setPixel(int x,int y);
void movePlayerUp();
void movePlayerDown();
void movePlayerLeft();
void movePlayerRight();
void drawPlayer(int x, int y);
void erasePlayer(int x, int y);
void eraseGeneric(int x, int y, int rows, int cols);
void createBattleShip();
void createCannonBullet(int x, int y);
void cannonBulletsMovement();
void battleShipHandler();
void printBattleShip(int x, int y);
void moveMaze();
void battleShipRocketCreate(int x, int y);
void removeElementFromArray(int arr1[], int arr2[], int elementIndex, int arraySize);
void init();
void moveMazeAndGameElements();
void startGame();

int main()
{
    consoleCursor(false);
    system("cls");
    printLogo();
    // halt();
    printMenuItems(12, menuItems, 3);
    int choice = takeChoice(12, 3, 0x3);
    if (choice == 0)
    {
        startGame();
    }
}
void init()
{
    for (int i = 0; i < numOfBattleShips; i++)
    {
        battleShipRocketReady[i] = 0;
    }
}
void removeElementFromArray(int arr1[], int arr2[], int elementIndex, int arraySize)
{
    for (int i = elementIndex; i < arraySize; i++)
    {
        arr1[i] = arr1[i + 1];
        arr2[i] = arr2[i + 1];
    }
}
void createCannonBullet(int x, int y)
{
    // x += 3;
    y -= 3;
    gotoxy(x, y);
    cout << "|";
    playerCannonX[currentCannonBulletsCount] = x;
    playerCannonY[currentCannonBulletsCount] = y;
    currentCannonBulletsCount++;
}
void cannonBulletsMovement()
{
    for (int i = currentCannonBulletsCount - 1; i >= 0; i--)
    {
        if (playerCannonY[i] - 1 >= 0)
        {
            gotoxy(playerCannonX[i], playerCannonY[i]);
            cout << " ";
            gotoxy(playerCannonX[i], --playerCannonY[i]);
            cout << "|";
        }
        else
        {
            gotoxy(playerCannonX[i], 0);
            removeElementFromArray(playerCannonX, playerCannonY, i, currentCannonBulletsCount);
            cout << " ";
            currentCannonBulletsCount--;
        }
    }
}
int countIter = 0;
bool l = false;
void moveMaze()
{
    char c = 219;

    countIter++;
    if (countIter == 20)
    {
        l = rand() % 2;
        countIter = 0;
    }
    string temp;
    if (l)
    {
        temp = maze1[countIter];
    }
    else
    {
        temp = maze2[countIter];
    }

    screen[0] = temp;
    for (int i = 20 - 1; i > 0; i--)
    {
        screen[i] = screen[i - 1];
    }
    for (int y = 0; y < 20; y++)
    {
        // gotoxy(0, i - 1);

        for (int x = 0; x < 80; x++)
        {
            if (getCharxy(x, y) == '*' && screen[y][x] == ' ')
            {
                gotoxy(x, y);
                cout << ' ';
            }
            else if (screen[y][x] == '*')
            {
                gotoxy(x, y);
                cout << screen[y][x];
            }
        }
    }
}
void moveMazeAndGameElements()
{
    mazeMoveCount++;
    mazeBattleShipCreate++;
    if (mazeBattleShipCreate == 40)
    {
        createBattleShip();
        mazeBattleShipCreate = 0;
    }
    if (mazeMoveCount == 4)
    {
        moveMaze();
        for (int i = currentBattleShipsCount - 1; i >= 0; i--)
        {
            if (battleShipsY[i] < 20)
            {
                eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
                battleShipsY[i]++;
                printBattleShip(battleShipsX[i], battleShipsY[i]);
            }
            else
            {
                gotoxy(battleShipsX[i], 20);
                eraseGeneric(battleShipsX[i] - 2, battleShipsY[i], 5, 1);
                removeElementFromArray(battleShipsX, battleShipsY, i, currentBattleShipsCount);
                currentBattleShipsCount--;
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
void createBattleShip()
{
    int x = (rand() % 20) + 30;
    int y = 0;
    printBattleShip(x, y);
    currentBattleShipsCount++;
}
void printBattleShip(int x, int y)
{
    char b = 219;
    char c = 254;
    gotoxy(x - 2, y);
    cout << "<" << b << c << b << ">";
    battleShipsX[currentBattleShipsCount] = x;
    battleShipsY[currentBattleShipsCount] = y;
}
void battleShipHandler()
{
    for (int i = currentBattleShipsCount - 1; i >= 0; i--)
    {
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
        if (battleShipRocketY[i] < 20 && getCharxy(battleShipRocketX[i] - 3, battleShipRocketY[i]) != '*' && getCharxy(battleShipRocketX[i] + 3, battleShipRocketY[i]) != '*')
        {
            gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
            cout << " ";
            battleShipRocketY[i]++;
            gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
            cout << "#";
        }
        else
        {
            gotoxy(battleShipRocketX[i], battleShipRocketY[i]);
            cout << " ";
            //  gotoxy(battleShipRocketX[i], 21);
            //  cout << " ";
            removeElementFromArray(battleShipRocketX, battleShipRocketY, i, currentBattleShipRocketsCount);
            currentBattleShipRocketsCount--;
        }
    }
}
void drawPlayer(int x, int y)
{
    char b = 219;
    char s = 254;
    gotoxy(x, y - 2);
    cout << b;
    gotoxy(x - 1, y - 1);
    cout << b << b << b;
    gotoxy(x - 3, y);
    cout << s << s << b << b << b << s << s;
    gotoxy(x, y + 1);
    cout << b;
}
void erasePlayer(int x, int y)
{
    gotoxy(x, y - 2);
    cout << " ";
    gotoxy(x - 1, y - 1);
    cout << "   ";
    gotoxy(x - 3, y);
    cout << "       ";
    gotoxy(x, y + 1);
    cout << " ";
    /* for (int i = 0; i < 4; i++)
     {
         gotoxy(x - 4, y + i - 2);
         cout << "         ";
     }*/
}
void eraseGeneric(int x, int y, int rows, int cols)
{
    for (int i = 0; i < cols; i++)
    {
        gotoxy(x, y++);
        for (int j = 0; j < rows; j++)
        {
            cout << " ";
        }
    }
}

void movePlayerUp()
{
    if (getCharxy(playerX - 3, playerY - 1) == '*')
    {
        movePlayerRight();
    }
    else if (getCharxy(playerX + 3, playerY - 1) == '*')
    {
        movePlayerLeft();
    }
    erasePlayer(playerX, playerY);
    playerY--;
    drawPlayer(playerX, playerY);
}
void movePlayerDown()
{
    if (getCharxy(playerX - 3, playerY + 1) == '*')
    {
        movePlayerRight();
    }
    else if (getCharxy(playerX + 3, playerY + 1) == '*')
    {
        movePlayerLeft();
    }
    erasePlayer(playerX, playerY);
    playerY++;
    drawPlayer(playerX, playerY);
}
void movePlayerLeft()
{
    if (getCharxy(playerX - 4, playerY) != '*')
    {
        erasePlayer(playerX, playerY);
        playerX--;
        drawPlayer(playerX, playerY);
    }
}
void movePlayerRight()
{
    if (getCharxy(playerX + 4, playerY) != '*')
    {
        erasePlayer(playerX, playerY);
        playerX++;
        drawPlayer(playerX, playerY);
    }
}
void startGame()
{
    // init();
    bool running = true;
    /*    char char0;
    for(int  i=0;i<256;i++)
    {
    char0=i;
    cout<<i<<" "<<char0<<endl;
    }*/
    system("cls");
    drawPlayer(20, 15);
    // createBattleShip();
    //  createBattleShip();
    while (running)
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
            createCannonBullet(playerX, playerY);
        }
        if (getCharxy(playerX + 3, playerY - 1) == '*')
        {
            movePlayerLeft();
        }
        if (getCharxy(playerX - 3, playerY - 1) == '*')
        {
            movePlayerRight();
        }
        battleShipHandler();
        cannonBulletsMovement();
        moveMazeAndGameElements();
        Sleep(75);
    }
    halt();
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
        if (key == VK_ESCAPE)
        {
            key = -1;
            break;
        }
        else if (key == VK_RETURN)
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
    char buffer[80];
    COORD position{x, y};
    DWORD dwChars;
    ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 80, position, &dwChars);
    buffer[dwChars] = '\0';
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
/*void setPixel(int x,int y)
{
    HWND console = GetConsoleWindow();
    HDC deviceHandle =GetDC(console);
    COLORREF color = RGB(255,255,255);
    SetPixel(deviceHandle,x,x,color);
    ReleaseDC(console,deviceHandle);
}*/
char getCharxy(short x, short y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

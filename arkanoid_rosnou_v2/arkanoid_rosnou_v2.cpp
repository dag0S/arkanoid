#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <windows.h>
#include <cassert> 
#include <math.h> 

#define WIDTH 60
#define HEIGHT 30

#define BRICK (char)176
#define BRICK_WIDTH 3

using namespace std;

char mas[HEIGHT][WIDTH + 1];
char lvlMap[HEIGHT][WIDTH];

// Ракетка
typedef struct {
    int x, y;
    int widthRacket;
} TRacket;

typedef struct {
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

TRacket racket;
TBall ball;
int hitCount = 0;
int maxHitCount = 0;
int lvl = 1;
bool run = false;
bool skip = false;
string hp = "\3\3\3";

void moveBall(float x, float y);
void setCursor(short x, short y);

void initBall() {
    moveBall(2, 2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

void putBall() {
    mas[ball.iy][ball.ix] = '\1';
}

void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void autoMoveBall() {
    if (ball.alfa < 0) {
        ball.alfa += M_PI * 2;
    }

    if (ball.alfa > M_PI * 2) {
        ball.alfa -= M_PI * 2;
    }

    TBall b1 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed, ball.y + sin(ball.alfa) * ball.speed);

    switch (mas[ball.iy][ball.ix]) {
    case '3':
        lvlMap[ball.iy][ball.ix] = '2';
        break;
    case '2':
        lvlMap[ball.iy][ball.ix] = '1';
        break;
    case '1':
        lvlMap[ball.iy][ball.ix] = ' ';
        break;
    }

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '"') || (mas[ball.iy][ball.ix] == BRICK) || ((mas[ball.iy][ball.ix] == '1')
        || (mas[ball.iy][ball.ix] == '2') || (mas[ball.iy][ball.ix] == '3'))) {
        
        if (mas[ball.iy][ball.ix] == BRICK) {
            int brickNom = (ball.ix - 1) / BRICK_WIDTH;
            int dx = 1 + brickNom * BRICK_WIDTH;
            for (int i = 0; i < BRICK_WIDTH; i++) {
                static char* c;
                c = &lvlMap[ball.iy][i + dx];
                if (*c == BRICK) {
                    *c = ' ';
                }
            }
        }

        if (mas[ball.iy][ball.ix] == '"') {
            hitCount++;
            float pos = ball.x - racket.x;
            float psi = pos / racket.widthRacket * 2;
            psi = (psi - 1) * M_PI_2 * 0.9;
            assert((psi < M_PI_2) && (psi > -M_PI_2));
            b1.alfa = -M_PI_2 + psi;
        }
        else if ((ball.ix != b1.ix) && (ball.iy != b1.iy)) {

            if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix]) {
                b1.alfa = b1.alfa + M_PI;
            }
            else {

                if (mas[b1.iy][ball.ix] == '#') {
                    b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
                }
                else {
                    b1.alfa = (2 * M_PI - b1.alfa);
                }
            }
        }
        else if (ball.iy == b1.iy) {
            b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
        } 
        else {
            b1.alfa = (2 * M_PI - b1.alfa);
        }

        ball = b1;
    }
}

// инициализация ракетка
void initRacket() {
    racket.widthRacket = 7;
    racket.x = (WIDTH - racket.widthRacket) / 2;
    racket.y = HEIGHT - 1;
}

// показ ракетки
void putRacket() {
    for (int i = racket.x; i < racket.x + racket.widthRacket; i++) {
        mas[racket.y][i] = '"';
    }
}

void drawBrick(int x, int y) {
    for (int i = 0; i < 3; i++) {
        lvlMap[x][y + i] = BRICK;
    }
}

// инициализация карты
void lvlMapPuzzile() {
    if (lvl == 1) {
       /*
        int step = 0;
        for (int i = 4; i < WIDTH - 4; i++) {
            step++;
            if ((step == 4) || (step == 5) || (step == 6)) {
                if (step == 6) {
                    step = 0;
                }
                continue;
            }
            lvlMap[5][i] = lvlMap[7][i] = lvlMap[9][i] = lvlMap[11][i] = lvlMap[13][i] = lvlMap[15][i] = BRICK;
        }
        for (int i = 1; i < WIDTH - 3; i = i + 2) {
            lvlMap[17][i] = '3';
        }
        */
        
        // Р
        for (int i = 3; i <= 8; i++)
            drawBrick(i, 1);
        for (int i = 3; i <= 6; i++)
            drawBrick(i, 7);
        drawBrick(3, 4);
        drawBrick(6, 4);

        // О
        for (int i = 3; i <= 8; i++)
            drawBrick(i, 13);
        drawBrick(3, 16);
        drawBrick(8, 16);
        for (int i = 3; i <= 8; i++)
            drawBrick(i, 19);

        // С 
        for (int i = 3; i <= 8; i++)
            drawBrick(i, 25);
        drawBrick(3, 28);
        drawBrick(8, 28);
        drawBrick(3, 31);
        drawBrick(4, 31);
        drawBrick(7, 31);
        drawBrick(8, 31);

        // Н
        for (int i = 11; i <= 16; i++)
            drawBrick(i, 25);
        for (int i = 11; i <= 16; i++)
            drawBrick(i, 31);
        drawBrick(13, 28);
        drawBrick(14, 28);

        // О
        for (int i = 11; i <= 16; i++)
            drawBrick(i, 37);
        drawBrick(11, 40);
        drawBrick(16, 40);
        for (int i = 11; i <= 16; i++)
            drawBrick(i, 43);

        // У
        for (int i = 11; i <= 14; i++)
            drawBrick(i, 49);
        for (int i = 11; i <= 16; i++)
            drawBrick(i, 55);
        drawBrick(16, 49);
        drawBrick(16, 52);
        drawBrick(14, 52);
    }

    if (lvl == 2) {
        for (int i = 19; i <= 48; i++) {
            lvlMap[1][i] = lvlMap[2][i] = BRICK;
            lvlMap[8][i] = lvlMap[9][i] = BRICK;
            lvlMap[10][i] = '#';
        }
    }

    if (lvl == 3) {
        for (int j = 1; j < 10; j++) {
            for (int i = 1; i < 62; i += 6) {
                lvlMap[j][i] = lvlMap[j][i + 1] = lvlMap[j][i + 2] = BRICK;
            }
        }
    }
}

void lvlMapInit(int lvl) {
    memset(lvlMap, ' ', sizeof(lvlMap));

    lvlMapPuzzile();

    for (int i = 0; i < WIDTH; i++) {
        lvlMap[0][i] = '#';
    }
    for (int j = 0; j < HEIGHT; j++) {
        lvlMap[j][0] = lvlMap[j][WIDTH - 1] = '#';
    }
}

void lvlMapPut() {
    memset(mas, 0, sizeof(mas));

    for (int j = 0; j < HEIGHT; j++) {
        memcpy(mas[j], lvlMap[j], sizeof(**lvlMap) * WIDTH);
    }
}

// показ карты
void show() {
    setCursor(0, 0);

    cout << endl;
    cout << "+--------------+----------------------+--------------------+" << endl;
    cout << "|    hp " << hp;

    if (hp.length() == 3)
        cout << "";
    else if (hp.length() == 2)
        cout << " ";
    else
        cout << "  ";

    cout << "    |         lvl " << lvl << "        |   hit " << hitCount;

    if (hitCount < 10)
        cout << "  ";
    else if ((hitCount >= 10) && (hitCount < 100))
        cout << " ";
    else
        cout << "";

    cout << " max " << maxHitCount;

    if (maxHitCount < 10)
        cout << "  ";
    else if ((maxHitCount >= 10) && (hitCount < 100))
        cout << " ";
    else
        cout << "";
    cout << "  |" << endl << "+--------------+----------------------+--------------------+" << endl << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << mas[i];
        
        if (i == 2) {
            cout << "\t\tControl ";
        }
        if (i == 3) {
            cout << "\tW - running the ball";
        }
        if (i == 4) {
            cout << "\tA - movement to the left";
        }
        if (i == 5) {
            cout << "\tD - movement to the right";
        }
        if (i == 6) {
            cout << "\tK - skip level";
        }
        
        if (i < HEIGHT) {
            cout << endl;
        }
    }
}

// движение ракетки, x задает левый угол ракетки
void moveRacket(int x) {
    racket.x = x;

    if (racket.x < 1) {
        racket.x = 1;
    }

    if (racket.x + racket.widthRacket >= WIDTH) {
        racket.x = WIDTH - 1 - racket.widthRacket;
    }
}

void setCursor(short x, short y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showPreview() {
    system("cls");
    cout << endl
        << endl
        << endl
        << endl
        << endl
        << endl
        << "\t\t\t\tLVL " << lvl;
    Sleep(1000);
    system("cls");
}

void checkFaild() {
    if (ball.y >= HEIGHT - 1) {
        run = false;
        hp.pop_back();
        if (hitCount > maxHitCount) {
            maxHitCount = hitCount;
        }
        if (hp == "") {
            lvlMapInit(lvl);
            hp = "\3\3\3";
            maxHitCount = 0;
        }
        hitCount = 0;
        system("cls");
    }
}

int lvlMapBrickCount() {
    int count = 0;
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (lvlMap[j][i] == BRICK) {
                count++;
            }
        }
    }
    return count;
}

void checkWin() {
    if ((lvlMapBrickCount() == 0) || skip) {
        lvl++;
        hp = "\3\3\3";
        if (lvl > 3) {
            lvl = 1;
        }
        lvlMapInit(lvl);
        run = false;
        skip = false;
        maxHitCount = 0;
        hitCount = 0;
        system("cls");
        showPreview();
    }
}

void ballWork() {
    if (run) {
        autoMoveBall();
    }
    else {
        moveBall(racket.x + racket.widthRacket / 2, racket.y - 1);
    }
}

int main()
{
    system("mode con cols=90 lines=36");

    initRacket();

    initBall();

    lvlMapInit(lvl);

    showPreview();

    do {
        ballWork();

        checkFaild();

        checkWin();

        lvlMapPut();

        putRacket();

        putBall();

        show(); // вызов show

        if (GetKeyState('A') < 0) {
            moveRacket(racket.x - 1);
        }

        if (GetKeyState('D') < 0) {
            moveRacket(racket.x + 1);
        }

        if (GetKeyState('W') < 0) {
            run = true;
        }

        if (GetKeyState('K') < 0) {
            Sleep(100);
            skip = true;
            checkWin();
        }
      
        Sleep(10);

    } while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
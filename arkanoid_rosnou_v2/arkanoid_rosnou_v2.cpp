#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#define WIDTH 60
#define HEIGHT 30
#define Pi 3.14

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

void moveBall(float x, float y);
void setCursor(short x, short y);

void initBall() {
    moveBall(2, 2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

void putBall() {
    mas[ball.iy][ball.ix] = 'o';
}

void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void autoMoveBall() {
    if (ball.alfa < 0) {
        ball.alfa += Pi * 2;
    }
    if (ball.alfa > Pi * 2) {
        ball.alfa -= Pi * 2;
    }

    TBall b1 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed, ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '"') || (mas[ball.iy][ball.ix] == BRICK)) {
        if (mas[ball.iy][ball.ix] == '"') {
            hitCount++;
        }
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
        if ((ball.ix != b1.ix) && (ball.iy != b1.iy)) {
            if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix]) {
                b1.alfa = b1.alfa + Pi;
            }
            else {
                if (mas[b1.iy][ball.ix] == '#') {
                    b1.alfa = (2 * Pi - b1.alfa) + Pi;
                }
                else {
                    b1.alfa = (2 * Pi - b1.alfa);
                }
            }
        }
        else if (ball.iy == b1.iy) {
            b1.alfa = (2 * Pi - b1.alfa) + Pi;
        } 
        else {
            b1.alfa = (2 * Pi - b1.alfa);
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

// инициализация карты
void lvlMapPuzzile() {
    if (lvl == 1) {
        for (int i = 7; i < WIDTH - 7; i++) {
            lvlMap[5][i] = lvlMap[6][i] = BRICK;
        }   
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
    for (int i = 0; i < HEIGHT; i++) {
        cout << mas[i];
        if (i == 2) {
            cout << "   lvl " << lvl;
        }
        if (i == 3) {
            cout << "   hit " << hitCount;
        }
        if (i == 4) {
            cout << "   max " << maxHitCount;
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
        if (hitCount > maxHitCount) {
            maxHitCount = hitCount;
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
    if (lvlMapBrickCount() == 0) {
        lvl++;
        if (lvl > 3) {
            lvl = 1;
        }
        lvlMapInit(lvl);
        run = false;
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
    system("mode con cols=70 lines=31");

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
      
        Sleep(10);

    } while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <windows.h>
#include <cassert> 
#include <math.h> 
#include <ctime> 

#define WIDTH 60
#define HEIGHT 30

#define BRICK (char)176
#define BRICK_WIDTH 3

using namespace std;

char mas[HEIGHT][WIDTH + 1];
char lvlMap[HEIGHT][WIDTH];

// Ракетка
struct TRacket {
    int x, y;
    int widthRacket;
    int fireMode;
} ;

// Шарик
typedef struct {
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
    char type;
    char del;
} TBall, TObj;

TRacket racket;
TBall ball;
int hitCount = 0;
int maxHitCount = 0;
int lvl = 1;
bool run = false;
bool skip = false;
string hp = "\3\3\3";

// Максимально возможное кол-во объектов
#define OBJ_ARR_SIZE 1000
TObj objArr[OBJ_ARR_SIZE];
int objArrCnt = 0;

#define WIDE 'W'
#define THIN 'T'
#define FIRE 'F'
#define BULLET '.'
#define OBJ_UPGRADE_TYPES_RAND_MAX 18
char objUpgradeTypes[] = { WIDE, THIN, FIRE };
int objUpgradeTypesCnt = sizeof(objUpgradeTypes) / sizeof(objUpgradeTypes[0]);

void moveBall(float x, float y);
void setCursor(short x, short y);
char objHitBrick(TObj ball);

// Создаем объект
TObj objCreate(float x, float y, float a, float spd, char chr) {
    return {x, y, (int)x, (int)y, a, spd, chr};
}

// Кладем объект на карту
void objPut(TObj obj) {
    if (mas[obj.iy][obj.ix] == ' ')
        mas[obj.iy][obj.ix] = obj.type;
}

// Коректировка угла движения
void correctAngle(float* a) {
    if (*a < 0)
        *a += M_PI * 2;
    if (*a > M_PI * 2)
        *a -= M_PI * 2;
}

// Перемещение объекта
void objMove(TObj *obj) {
    correctAngle(&obj->alfa);
    obj->x += cos(obj->alfa) * obj->speed;
    obj->y += sin(obj->alfa) * obj->speed;
    obj->ix = (int)obj->x;
    obj->iy = (int)obj->y;
}

void objWorkUpgrade(TObj* obj) {
    if (mas[obj->iy][obj->ix] != '"')
        return;
    if (obj->type == WIDE)
        racket.widthRacket = min(racket.widthRacket + 1, 15), obj->del = 1;
    if (obj->type == THIN)
        racket.widthRacket = max(racket.widthRacket - 1, 5), obj->del = 1;
    if (obj->type == FIRE) {
        if (racket.fireMode < 1)
            racket.fireMode = 1;
        obj->del = 1;
    }
}

// Обработчик пуль
void objWorkBullet(TObj* obj) {
    if (obj->type != BULLET)
        return;
    if (objHitBrick(*obj) || mas[obj->iy][obj->ix] == '#')
        obj->del = 1;
}

// Ф-ция работы объкта
void objWork(TObj* obj) {
    objMove(obj);
    objWorkUpgrade(obj);
    objWorkBullet(obj);
}

// Добавляет объект в массив
void objArrAdd(TObj obj) {
    assert(objArrCnt + 1 < OBJ_ARR_SIZE);
    objArr[objArrCnt] = obj;
    objArrCnt++;
}

// Удаляет объкт из массива
void objArrDelPos(int pos) {
    if (pos < 0 || pos >= objArrCnt)
        return;
    objArr[pos] = objArr[objArrCnt - 1];
    objArrCnt--;
}

// Обрабатывает все объекты в массиве
void objArrWork() {
    int i = 0;
    while (i < objArrCnt) {
        objWork(objArr + i);
        if (objArr[i].y < 0 || objArr[i].y > HEIGHT || objArr[i].del)
            objArrDelPos(i);
        else
            i++;
    }
}

// Кладет на карту все объекты
void objArrPut() {
    for (int i = 0; i < objArrCnt; i++)
        objPut(objArr[i]);
}

// Очистка массива с объектами
void objArrClear() {
    objArrCnt = 0;
}

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

// Генерация случайного числа
void objChanceCreateRandomUpgradeObj(float x, float y) {
    int i = rand() % OBJ_UPGRADE_TYPES_RAND_MAX;
    if (i < objUpgradeTypesCnt)
        objArrAdd(objCreate(x, y, M_PI_2, 0.2, objUpgradeTypes[i]));
}

// Разрушение кирпичика
char objHitBrick(TObj ball) {
    if (mas[ball.iy][ball.ix] == BRICK) {
        if (lvlMap[ball.iy][ball.ix] == BRICK)
            objChanceCreateRandomUpgradeObj(ball.x, ball.y);
        int brickNom = (ball.ix - 1) / BRICK_WIDTH;
        int dx = 1 + brickNom * BRICK_WIDTH;
        for (int i = 0; i < BRICK_WIDTH; i++) {
            static char* c;
            c = &lvlMap[ball.iy][i + dx];
            if (*c == BRICK) {
                *c = ' ';
            }
        }
        return 1;
    }
    return 0;
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
        
        objHitBrick(ball);

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
    racket.fireMode = 0;
}

// помещение ракетки в локацию
void putRacket() {
    for (int i = racket.x; i < racket.x + racket.widthRacket; i++) {
        mas[racket.y][i] = '"';
    }
    if (racket.fireMode > 0)
        mas[racket.y - 1][racket.x + racket.widthRacket / 2] = '|';
}

void drawBrick(int x, int y) {
    for (int i = 0; i < 3; i++) {
        lvlMap[x][y + i] = BRICK;
    }
}

// инициализация карты
void lvlMapPuzzile() {
    if (lvl == 1) {
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
        for (int i = 9; i <= 49; i++)
            lvlMap[15][i] = '3';
        for (int i = 1; i <= 14; i++) {
            lvlMap[i][9] = '3';
            lvlMap[i][49] = '3';
        }
        for (int i = 1; i <= 5; i++) {
            drawBrick(i, 10);
            drawBrick(i + 9, 10);
            drawBrick(i, 46);
            drawBrick(i + 9, 46);
        }
        for (int i = 1; i <= 4; i++) {
            drawBrick(i, 13);
            drawBrick(i + 10, 13);
            drawBrick(i, 43);
            drawBrick(i + 10, 43);
        }
        for (int i = 1; i <= 3; i++) {
            drawBrick(i, 16);
            drawBrick(i +11, 16);
            drawBrick(i, 40);
            drawBrick(i + 11, 40);
        }
        for (int i = 1; i <= 2; i++) {
            drawBrick(i, 19);
            drawBrick(i + 12, 19);
            drawBrick(i, 37);
            drawBrick(i + 12, 37);
        }

        drawBrick(1, 22);
        drawBrick(14, 22);
        drawBrick(1, 34);
        drawBrick(14, 34);
            
        for (int i = 6; i <= 9; i++)
            drawBrick(i, 28);
        for (int i = 5; i <= 10; i++) {
            lvlMap[i][27] = '1';
            lvlMap[i][31] = '1';
        }
        for (int i = 28; i <= 30; i++) {
            lvlMap[5][i] = '1';
            lvlMap[10][i] = '1';
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

// переводит курсор в верхний левый угол
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
            initRacket();
            objArrClear();
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
        initRacket();
        objArrClear();
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

// Стреляба с ракетки
void racketShout() {
    if (racket.fireMode != 1)
        return;
    objArrAdd(objCreate(racket.x + racket.widthRacket / 2, racket.y - 2, -M_PI_2, 0.5, BULLET));
    racket.fireMode += 10;
}

int flag = 0; // костыли
time_t start = 0;

// Засекает 10 сек после чего отключает fire mode
void timerFireMod() {
    flag++;
    if (flag == 1)
        start = time(NULL);
    if ((time(NULL) - start) < 8)
        return;
    else {
        start = 0;
        flag = 0;
    }
    racket.fireMode = 0;
}

void racketWork() {
    if (racket.fireMode > 1)
        racket.fireMode--;
    timerFireMod();
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

        objArrWork();

        racketWork();

        checkFaild();

        checkWin();

        lvlMapPut();

        putRacket();

        putBall();

        objArrPut();

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

        if (GetKeyState(VK_SPACE) < 0) {
            racketShout();
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
#define WIDTH 60
#define HEIGHT 25

#define BALL 'o'
#define RACKET '"'
#define BORDER '#'
#define GUN '|'
#define BULLET '.'
#define BRICK 'X'
#define BRICK_WIDTH 3

#define WIDE 'W'
#define THIN 'T'
#define FIRE 'F'
#define QUICKLY 'Q'
#define SLOW 'S'

#define OBJ_UPGRADE_TYPES_RAND_MAX 18 // Ўанс выподени€ улучшени€

using namespace std;

// массив игрового пол€
vector<vector<char>> mas( 
    HEIGHT,
    vector<char>(WIDTH));

// массив уровн€
vector<vector<char>> lvlMap(
    HEIGHT,
    vector<char>(WIDTH));

// –акетка
struct TRacket {
    int x, y;         // координаты ракетки по x и y
    int widthRacket;  // ширина ракетки
    int fireMode;     // режим стрельбы
};

// Ўарик и ќбъекты
typedef struct {
    float x, y;        // координаты м€ча по x и y
    int ix, iy;        // координаты м€ча по x и y округленные до целого числа
    float alfa;        // угол направлени€ м€ча
    float speed;       // скорость м€ча
    char type;         // тип объекта 
    char del;          // метка удаленного объекта
} TBall, TObj;

TRacket racket;        // объ€вление ракетки
TBall ball;            // объ€вление м€чика

int hitCount = 0;      // текущее кол-во ударов м€ча о ракетку
int maxHitCount = 0;   // общее кол-во ударов м€ча о ракетку
int lvl = 1;           // текущий уровень
int speed = 10;        // скорость игры
bool run = false;      // запуск м€ч
bool skip = false;     // скип уровн€
bool pause = false;    // пауза
string hp = "\3\3\3";  // жизни ракетки

// переменные дл€ ф-ции rimerDireMode
int flag = 0;
int timeForFire = 5;
time_t start = 0;

char menu;   // выбор пункта меню

vector <TObj> objArr;  // массив объектов
vector <char> objUpgradeTypes = { WIDE, THIN, FIRE, QUICKLY, SLOW };   // массив бонусных улучшений
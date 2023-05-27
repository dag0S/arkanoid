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

#define OBJ_UPGRADE_TYPES_RAND_MAX 18 // ���� ��������� ���������

using namespace std;

// ������ �������� ����
vector<vector<char>> mas( 
    HEIGHT,
    vector<char>(WIDTH));

// ������ ������
vector<vector<char>> lvlMap(
    HEIGHT,
    vector<char>(WIDTH));

// �������
struct TRacket {
    int x, y;         // ���������� ������� �� x � y
    int widthRacket;  // ������ �������
    int fireMode;     // ����� ��������
};

// ����� � �������
typedef struct {
    float x, y;        // ���������� ���� �� x � y
    int ix, iy;        // ���������� ���� �� x � y ����������� �� ������ �����
    float alfa;        // ���� ����������� ����
    float speed;       // �������� ����
    char type;         // ��� ������� 
    char del;          // ����� ���������� �������
} TBall, TObj;

TRacket racket;        // ���������� �������
TBall ball;            // ���������� ������

int hitCount = 0;      // ������� ���-�� ������ ���� � �������
int maxHitCount = 0;   // ����� ���-�� ������ ���� � �������
int lvl = 1;           // ������� �������
int speed = 10;        // �������� ����
bool run = false;      // ������ ���
bool skip = false;     // ���� ������
bool pause = false;    // �����
string hp = "\3\3\3";  // ����� �������

// ���������� ��� �-��� rimerDireMode
int flag = 0;
int timeForFire = 5;
time_t start = 0;

char menu;   // ����� ������ ����

vector <TObj> objArr;  // ������ ��������
vector <char> objUpgradeTypes = { WIDE, THIN, FIRE, QUICKLY, SLOW };   // ������ �������� ���������
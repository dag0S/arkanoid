#define _USE_MATH_DEFINES

// Библиотеки
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cmath> 
#include <ctime> 

// Заголовки с кодом
#include "Variables.h"
#include "Headers.h"
#include "Ball.h"
#include "Racket.h"
#include "Object.h"
#include "Map.h"
#include "Menu.h"
#include "Utilis.h"

int main()
{
    srand(time(NULL));

    initRacket();
    initBall();
    lvlMapInit();
    showMenu();
    showPreview();

    do {
        ballWork();
        objArrWork( checkFaild() );
        racketWork();
        checkWin();
        lvlMapPut();
        putRacket();
        putBall();
        objArrPut();
        show();

        if (GetKeyState('A') < 0)
            moveRacket(racket.x - 1);

        if (GetKeyState('D') < 0)
            moveRacket(racket.x + 1);

        if (GetKeyState('W') < 0)
            run = true;

        bool pause = false;

        if ((GetKeyState('P') < 0) && (pause == false)) {
            system("cls");
            pause = true;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   P A U S E" << endl;
            Sleep(500);
            while ((GetKeyState('P')) >= 0) {
                Sleep(1);
            }
            pause = false;
            Sleep(500);
            system("cls");
        }

        if (GetKeyState(VK_SPACE) < 0)
            racketShout();

        if (GetKeyState('K') < 0) {
            Sleep(100);
            skip = true;
            checkWin();
        }
      
        Sleep(speed);

    } while ((GetKeyState(VK_ESCAPE) >= 0) && (menu == '1'));

    return 0;
}
#define _USE_MATH_DEFINES

// Библиотеки
#include <iostream>
#include <conio.h>
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

void main()
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

        if ((GetKeyState('P') < 0) && (pause == false)) {
            showPause();
        }

        if (GetKeyState(VK_SPACE) < 0)
            racketShout();

        if (GetKeyState('K') < 0) {
            Sleep(100);
            skip = true;
            checkWin();
        }
      
        Sleep(speed);
    } while (GetKeyState(VK_ESCAPE) >= 0);
}
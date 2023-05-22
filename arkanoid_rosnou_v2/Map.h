// рисует кирпич в указанных координатах
void drawBrick(int x, int y) {
    for (int i = 0; i < 3; i++)
        lvlMap[x][y + i] = BRICK;
}

// инициализация карты
void lvlMapPuzzile() {
    // lvl 1
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

    // lvl 2
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
            drawBrick(i + 11, 16);
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

    // lvl 3
    if (lvl == 3) {
        for (int i = 16; i <= 42; i = i + 6)
            drawBrick(1, i);
        for (int i = 2; i <= 4; i++) {
            drawBrick(i, 19);
            drawBrick(i, 37);
        }
        drawBrick(2, 25);
        drawBrick(2, 31);
        for (int i = 25; i <= 31; i = i + 3)
            drawBrick(4, i);
        for (int j = 5; j <= 8; j++)
            for (int i = 22; i <= 34; i = i + 3)
                drawBrick(j, i);
        drawBrick(9, 28);
        for (int i = 13; i <= 14; i++) {
            drawBrick(i, 7);
            drawBrick(i, 49);
        }
        for (int i = 9; i <= 14; i++) {
            drawBrick(i, 19);
            drawBrick(i, 37);
        }
        drawBrick(12, 22);
        drawBrick(14, 22);
        drawBrick(12, 34);
        drawBrick(14, 34);
        for (int i = 9; i <= 14; i++)
            lvlMap[i][18] = lvlMap[i][40] = '3';
        for (int i = 19; i <= 25; i++)
            lvlMap[15][i] = lvlMap[15][i + 14] = '3';
        for (int i = 22; i <= 25; i++)
            lvlMap[13][i] = lvlMap[13][i + 11] = '3';
        for (int i = 25; i <= 33; i++)
            lvlMap[18][i] = '#';
        lvlMap[14][25] = lvlMap[14][33] = '3';
        for (int i = 19; i <= 20; i++) {
            drawBrick(i, 13);
            drawBrick(i, 43);
        }
        for (int i = 5; i <= 6; i++) {
            drawBrick(i, 4);
            drawBrick(i, 52);
        }
        for (int i = 25; i <= 27; i++)
            lvlMap[9][i] = lvlMap[9][i + 6] = '2';
    }

    // lvl 4
    if (lvl == 4) {
        int k = 0;
        int d = 1;
        for (int i = 2; i <= 19; i++) {
            drawBrick(i, 1);
            k = i;
            while (k > 2) {
                drawBrick(i, d + 3);
                d += 3;
                k--;
            }
            d = 1;
        }
        for (int i = 1; i <= 54; i++)
            lvlMap[20][i] = '3';
        drawBrick(20, 55);
        lvlMap[20][58] = '3';
    }
}

// Заполняет уровень пробелами и рисует стенки
void lvlMapInit() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            lvlMap[i][j] = ' ';
    }
    
    lvlMapPuzzile();

    for (int i = 0; i < WIDTH; i++)
        lvlMap[0][i] = BORDER;
    for (int j = 0; j < HEIGHT; j++)
        lvlMap[j][0] = lvlMap[j][WIDTH - 1] = BORDER;
}

// копирует карту уровня в буффер вывода
void lvlMapPut() {
    mas = lvlMap;
}

// показ карты и худа
void show() {
    setCursor(0, 0);

    // HUD
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

        string str(mas[i].begin(), mas[i].end());

        cout << str;

        // Инструкция управления
        if (i == 4)
            cout << "\t\t\t\tControl ";
        if (i == 6)
            cout << "\t\t\tW - running the ball";
        if (i == 7)
            cout << "\t\t\tA - movement to the left";
        if (i == 8)
            cout << "\t\t\tD - movement to the right";
        if (i == 9)
            cout << "\t\t\tK - skip level";
        if (i == 10)
            cout << "\t\t\tP - pause";
        if (i == 11)
            cout << "\t\t\tESC - exit";
        if (i == 12)
            cout << "\t\t\tSPACE - shoot";

        // Бонусные улучшения
        if (i == 14)
            cout << "\t\t\t\tUpgrades ";
        if (i == 16)
            cout << "\t\t\tW - wide";
        if (i == 17)
            cout << "\t\t\tT - thin";
        if (i == 18)
            cout << "\t\t\tF - fire mode";
        if (i == 19)
            cout << "\t\t\tQ - quickly";
        if (i == 20)
            cout << "\t\t\tS - slow";

        if (i < HEIGHT)
            cout << endl;
    }
}

// переводит курсор в верхний левый угол
void setCursor(short x, short y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

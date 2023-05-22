// Засекает 5 сек после чего отключает fire mode
void timerFireMod() {
    flag++;
    if (flag == 1)
        start = time(NULL);
    if ((time(NULL) - start) < timeForFire)
        return;
    start = 0;
    flag = 0;
    timeForFire = 5;
    racket.fireMode = 0;
}

// Показ превью уровня
void showPreview() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tLVL " << lvl << endl;
    Sleep(1000);
    system("cls");
}

// Проверяет вылетел ли мяч за нижнюю границу
bool checkFaild() {
    if (ball.y >= HEIGHT - 1) {
        speed = 10;
        run = false;
        hp.pop_back();
        if (hitCount > maxHitCount)
            maxHitCount = hitCount;
        if (hp == "") {
            lvlMapInit();
            hp = "\3\3\3";
            maxHitCount = 0;
            objArrClear();
        }
        hitCount = 0;
        system("cls");
        initRacket();
        return true;
    }
    return false;
}

int lvlMapBrickCount() {
    int count = 0;
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (lvlMap[j][i] == BRICK)
                count++;
        }
    }
    return count;
}

// Проверяет пройден ли уровень
void checkWin() {
    if ((lvlMapBrickCount() == 0) || skip) {
        speed = 10;
        lvl++;
        hp = "\3\3\3";
        if (lvl > 4)
            lvl = 1;
        lvlMapInit();
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

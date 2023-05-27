// ������������� �������
void initRacket() {
    racket.widthRacket = 7;
    racket.x = (WIDTH - racket.widthRacket) / 2;
    racket.y = HEIGHT - 1;
    racket.fireMode = 0;
}

// ��������� ������� � �������
void putRacket() {
    for (int i = racket.x; i < racket.x + racket.widthRacket; i++)
        mas[racket.y][i] = RACKET;
    if (racket.fireMode > 0) {
        mas[racket.y - 1][racket.x + racket.widthRacket / 2] = GUN;
        timerFireMod();
    }
}

// �������� �������, x ������ ����� ���� �������
void moveRacket(int x) {
    racket.x = x;

    if (racket.x < 1)
        racket.x = 1;

    if (racket.x + racket.widthRacket >= WIDTH)
        racket.x = WIDTH - 1 - racket.widthRacket;
}

// �������� � �������
void racketShout() {
    if (racket.fireMode != 1)
        return;
    objArrAdd( objCreate(racket.x + racket.widthRacket / 2, racket.y - 2, -M_PI_2, 0.5, BULLET) );
    racket.fireMode += 10;
}

// ��������� fireMode �� 1 ������ ��������
void racketWork() {
    if (racket.fireMode > 1)
        racket.fireMode--;
}
// »нициализачи€ позиции шарика
void initBall() {
    moveBall(2, 2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

//  ладет шарик на карту
void putBall() {
    mas[ball.iy][ball.ix] = BALL;
}

// ƒвигает шарик по карте
void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

// автоматическое движение м€чика
void autoMoveBall() {
    if (ball.alfa < 0)
        ball.alfa += M_PI * 2;

    if (ball.alfa > M_PI * 2)
        ball.alfa -= M_PI * 2;

    TBall b1 = ball;

    moveBall(ball.x + cos(ball.alfa) * ball.speed, ball.y + sin(ball.alfa) * ball.speed);

    objHitDigit(ball);

    if ((mas[ball.iy][ball.ix] == BORDER) || (mas[ball.iy][ball.ix] == RACKET) || (mas[ball.iy][ball.ix] == BRICK) || ((mas[ball.iy][ball.ix] == '1')
        || (mas[ball.iy][ball.ix] == '2') || (mas[ball.iy][ball.ix] == '3'))) {

        objHitBrick(ball);

        if (mas[ball.iy][ball.ix] == RACKET) {
            hitCount++;
            float pos = ball.x - racket.x;
            float psi = pos / racket.widthRacket * 2;
            psi = (psi - 1) * M_PI_2 * 0.5;
            b1.alfa = -M_PI_2 + psi;
        }
        else if ((ball.ix != b1.ix) && (ball.iy != b1.iy)) {

            if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix])
                b1.alfa = b1.alfa + M_PI;
            else {

                if (mas[b1.iy][ball.ix] == BORDER)
                    b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
                else
                    b1.alfa = (2 * M_PI - b1.alfa);
            }
        }
        else if (ball.iy == b1.iy)
            b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
        else
            b1.alfa = (2 * M_PI - b1.alfa);

        ball = b1;
    }
}

void ballWork() {
    if (run)
        autoMoveBall();
    else {
        moveBall(racket.x + racket.widthRacket / 2, racket.y - 1);
        ball.alfa = -M_PI_2 - 0.5;
    }
}

// ������� ������
TObj objCreate(float x, float y, float a, float spd, char chr) {
    return { x, y, (int)x, (int)y, a, spd, chr };
}

// ������ ������ �� �����
void objPut(TObj obj) {
    if (mas[obj.iy][obj.ix] == ' ')
        mas[obj.iy][obj.ix] = obj.type;
}

// ������������ ���� ��������
void correctAngle(float* a) {
    if (*a < 0)
        *a += M_PI * 2;
    if (*a > M_PI * 2)
        *a -= M_PI * 2;
}

// ����������� �������
void objMove(TObj* obj) {
    correctAngle(&obj->alfa);
    obj->x += cos(obj->alfa) * obj->speed;
    obj->y += sin(obj->alfa) * obj->speed;
    obj->ix = (int)obj->x;
    obj->iy = (int)obj->y;
}

// ������������ �������� ��������� ��� �� ������ ��������
void objWorkUpgrade(TObj* obj) {
    if (mas[obj->iy][obj->ix] != RACKET)
        return;
    if (obj->type == WIDE)
        racket.widthRacket = min(racket.widthRacket + 1, 15), obj->del = 1;
    if (obj->type == THIN)
        racket.widthRacket = max(racket.widthRacket - 1, 5), obj->del = 1;
    if (obj->type == FIRE) {
        if (racket.fireMode > 0)
            timeForFire += 5;
        if (racket.fireMode < 1)
            racket.fireMode = 1;
        obj->del = 1;
    }
    if (obj->type == SLOW) {
        if (speed < 16)
            speed += 1, obj->del = 1;
    }
    if (obj->type == QUICKLY) {
        if (speed > 7)
            speed -= 1, obj->del = 1;
    }
}

// ���������� ����
void objWorkBullet(TObj* obj) {
    if (obj->type != BULLET)
        return;
    if ((objHitBrick(*obj)) || (objHitDigit(*obj)) || (mas[obj->iy][obj->ix] == BORDER))
        obj->del = 1;
}

// �-��� ������ ������
void objWork(TObj* obj) {
    objMove(obj);
    objWorkUpgrade(obj);
    objWorkBullet(obj);
}

// ��������� ������ � ������
void objArrAdd(TObj obj) {
    objArr.push_back(obj);
}

// ������� ����� �� �������
void objArrDelPos(int pos) {
    objArr[pos] = objArr[objArr.size() - 1];
    objArr.pop_back();
}

// ������������ ��� ������� � �������
void objArrWork(bool ballFaild) {
    int i = 0;
    while (i < objArr.size()) {
        objWork(&objArr[i]);
        if (objArr[i].y < 0 || objArr[i].y >= (HEIGHT - 1) || objArr[i].del || ballFaild)
            objArrDelPos(i);
        else
            i++;
    }
}

// ������ �� ����� ��� �������
void objArrPut() {
    for (int i = 0; i < objArr.size(); i++)
        objPut(objArr[i]);
}

// ������� ������� � ���������
void objArrClear() {
    objArr.clear();
}

// ��������� ���������� �������
void objChanceCreateRandomUpgradeObj(float x, float y) {
    int i = rand() % OBJ_UPGRADE_TYPES_RAND_MAX;
    if (i < objUpgradeTypes.size())
        objArrAdd( objCreate(x, y, M_PI_2, 0.2, objUpgradeTypes[i]) );
}

// ���������� ���������
int objHitBrick(TObj ball) {
    if (mas[ball.iy][ball.ix] == BRICK) {
        objChanceCreateRandomUpgradeObj(ball.x, ball.y);
        int brickNom = (ball.ix - 1) / BRICK_WIDTH;
        int dx = 1 + brickNom * BRICK_WIDTH;
        for (int i = 0; i < BRICK_WIDTH; i++) {
            char* c;
            c = &lvlMap[ball.iy][i + dx];
            if (*c == BRICK)
                *c = ' ';
        }
        return 1;
    }
    return 0;
}

// ���������� ����
int objHitDigit(TObj ball) {
    switch (mas[ball.iy][ball.ix]) {
    case '3':
        lvlMap[ball.iy][ball.ix] = '2';
        return 1;
    case '2':
        lvlMap[ball.iy][ball.ix] = '1';
        return 1;
    case '1':
        lvlMap[ball.iy][ball.ix] = ' ';
        return 1;
    }
    return 0;
}

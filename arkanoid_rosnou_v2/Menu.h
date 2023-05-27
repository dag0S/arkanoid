// пунки меню - Инструкция
void showInstruction() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\t\t\t\tI N S T R U C T I O N \n\n"
        << "\t\t\tControl\n\n"
        << "\t\t\tW - running the ball\n"
        << "\t\t\tA - movement to the left\n"
        << "\t\t\tD - movement to the right\n"
        << "\t\t\tK - skip level\n"
        << "\t\t\tP - pause\n"
        << "\t\t\tSPACE - shoot\n"
        << "\t\t\tESC - exit\n\n"
        << "\t\t\tUpgrades\n\n"
        << "\t\t\tW - wide\n"
        << "\t\t\tT - thin\n"
        << "\t\t\tF - fire mode\n"
        << "\t\t\tQ - quickly\n"
        << "\t\t\tS - slow\n\n";
    cout << "\t\t\tgo back - 4\n";
    menu = _getch();
    if (menu == '4') {
        menu = ' ';
        showMenu();
    }
    else {
        menu = ' ';
        showInstruction();
    }
}

// пунки меню - Информация
void showInfo() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\t\t\t\t\tI N F O \n\n\n\n\n\n\n\n\n\n\n\n"
        << "\tauthor: Gosudarev Danila\n"
        << "\temail:  danidagosudarev@gmail.com\n"
        << "\tgitHub: https://github.com/dag0S/arkanoid.git \n\n";

    cout << "\tgo back - 4\n";
    menu = _getch();
    if (menu == '4') {
        menu = ' ';
        showMenu();
    }
    else {
        menu = ' ';
        showInfo();
    }
}

// меню
void showMenu() {
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tA R K A N O I D \n\n"
        << "\t\t\t\t1 Start      \n"
        << "\t\t\t\t2 Instruction\n"
        << "\t\t\t\t3 Info       \n\n";
    menu = _getch();
    if (menu == '1')
        return;
    else if (menu == '2') {
        menu = ' ';
        showInstruction();
    }
    else if (menu == '3') {
        menu = ' ';
        showInfo();
    }
    else {
        menu = ' ';
        showMenu();
    }
}

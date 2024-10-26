// Snake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

using namespace std;
#include <iostream>
#include <conio.h>
#include <windows.h>

struct Snake {
    int x, y;
    Snake* next;
};

void input();
void generateFood(Snake* head);
void drawField(Snake* head);
bool gameOver(Snake* head);
void moveSnake(Snake*& head, Snake*& tail);
bool foodTaken(Snake* head);

const int width = 20;
const int height = 20;

int foodX;
int foodY;
int score;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

int main() {
    Snake* head = new Snake();
    head->x = width / 2;
    head->y = height / 2;
    head->next = nullptr;
    Snake* tail = head;

    score = 0;
    dir = RIGHT;
    generateFood(head);

    while (dir != STOP) {
        drawField(head);
        input();
        moveSnake(head, tail);
        if (gameOver(head)) {
            cout << "Game over!" << endl;
            Sleep(10000);
            break;
        }
        Sleep(250);
    }

    return 0;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case '0': dir = STOP; break;
        }
    }
}

void generateFood(Snake* head) {
    bool foodOnSnake;
    do {
        foodX = rand() % width;
        foodY = rand() % height;
        foodOnSnake = false;
        Snake* temp = head;
        while (temp != nullptr) {
            if (temp->x == foodX && temp->y == foodY) {
                foodOnSnake = true;
                break;
            }
            temp = temp->next;
        }
    } while (foodOnSnake);
}

void drawField(Snake* head) {
    system("cls");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            bool isBodyPart = false;
            Snake* temp = head;

            while (temp != nullptr) {
                if (temp->x == j && temp->y == i) {
                    cout << "O";
                    isBodyPart = true;
                }
                temp = temp->next;
            }

            if (!isBodyPart) {
                if (foodX == j && foodY == i) cout << "F";
                else cout << " ";
            }

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

bool gameOver(Snake* head) {
    if (head->x < 0 || head->x >= width || head->y < 0 || head->y >= height)
        return true;

    Snake* temp = head->next;
    while (temp != nullptr) {
        if (temp->x == head->x && temp->y == head->y)
            return true;
        temp = temp->next;
    }

    return false;
}

void moveSnake(Snake*& head, Snake*& tail) {
    int prevX = head->x;
    int prevY = head->y;
    int tempX, tempY;

    switch (dir) {
    case LEFT: head->x--; break;
    case RIGHT: head->x++; break;
    case UP: head->y--; break;
    case DOWN: head->y++; break;
    default: break;
    }

    if (foodTaken(head)) {
        Snake* newSnake = new Snake();
        newSnake->x = prevX;
        newSnake->y = prevY;
        newSnake->next = nullptr;
        tail->next = newSnake;
        tail = newSnake;
        generateFood(head);
    }
    else {
        Snake* temp = head->next;
        while (temp != nullptr) {
            tempX = temp->x;
            tempY = temp->y;

            temp->x = prevX;
            temp->y = prevY;

            prevX = tempX;
            prevY = tempY;
            temp = temp->next;
        }
    }
}

bool foodTaken(Snake* head) {
    if (head->x == foodX && head->y == foodY) {
        score += 10;
        return true;
    }
    return false;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
using namespace std;

int i = 3,      //Порядок кривой Гильберта 
    l = 50,     //Длина основания
    x = 150,    //Нач. позиция по 'x'
    y = 150;    //Нач. позиция по 'y'
    
sf::RenderWindow Window(sf::VideoMode(666, 666), "Hilbert's Curve");    //Создание объекта окна

void A(int i);  //  ]
void B(int i);  //  [
void C(int i);  //  П
void D(int i);  //  U
void DrawLine(unsigned X, unsigned Y);

void A(int i) {              //  ]
    if (i > 0) {
        D(i-1);
        DrawLine(l, 0);     //Вправо
        A(i-1);
        DrawLine(0, l);     //Вниз
        A(i-1);
        DrawLine(-l, 0);    //Влево
        C(i-1);
    }
}
void B(int i) {              //  [
    if (i > 0) {
        C(i - 1);
        DrawLine(-l, 0);    //Влево
        B(i - 1);
        DrawLine(0, -l);    //Вверх
        B(i - 1);
        DrawLine(l, 0);     //Вправо
        D(i - 1);  
    }
}
void C(int i) {             //  П
    if (i > 0) {
        B(i - 1);
        DrawLine(0, -l);    //Вверх
        C(i - 1);
        DrawLine(-l, 0);    //Влево
        C(i - 1);
        DrawLine(0, l);     //Вниз
        A(i - 1);
    }
}
void D(int i) {             //  U
    if (i > 0) {
        A(i - 1);
        DrawLine(0, l);     //Вниз
        D(i - 1);
        DrawLine(l, 0);     //Вправо
        D(i - 1);
        DrawLine(0, -l);    //Вверх
        B(i - 1);
    }
}
void DrawLine(unsigned X, unsigned Y) {
    sf::Vertex Line[] =                         //Массив двух точек
    {
        sf::Vertex(sf::Vector2f(x, y)),
        sf::Vertex(sf::Vector2f(x + X, y + Y))
    };
    Window.draw(Line, 2, sf::Lines);            //Нарисовать соединение двух точек
    x += X;                                     //Сдвигаем координаты "карандаша"
    y += Y;                                     //
}

int main()
{
    Window.setVisible(false);                   //Прячем окно OpenGL
    setlocale(LC_ALL, "");
    
    HWND windowHandle = GetConsoleWindow();     //Перехватываем консоль
    ShowWindow(windowHandle, SW_SHOW);          //Показываем консоль для ввода
    char Answer = 'Y';
    cout << "Использовать параметры по умолчанию? (Y/n)\n>";
    cin >> Answer;
    if (Answer == 'n') {
        cout << "Введите порядок кривой Гильберта: ";
        cin >> i;
        cout << "Введите длину основания кривой: ";
        cin >> l;
        cout << "Введите начальную позицию:\nx=";
        cin >> x;
        cout << "y=";
        cin >> y;
    }
    
    ShowWindow(windowHandle, SW_HIDE);          //Прячем консоль
    
    Window.clear();                             //Очищаем кадр
    
    A(i);                                       //Вызываем рисование кривой Гильберта
    
    Window.setVisible(true);                    //Показываем окно OpenGL
    
    Window.display();                           //Отображаем кадр

    while (Window.isOpen())                     //Цикл ожидания выхода
    {
        sf::Event event;
        while (Window.pollEvent(event))
            if (event.type == sf::Event::Closed)//Если нажата кнопка выхода (крестик)
                Window.close();                 //Закрыть окно
    }

    return 0;
}
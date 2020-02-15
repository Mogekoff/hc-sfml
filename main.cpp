#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
using namespace std;

int i = 3,      //������� ������ ��������� 
    l = 50,     //����� ���������
    x = 150,    //���. ������� �� 'x'
    y = 150;    //���. ������� �� 'y'
    
sf::RenderWindow Window(sf::VideoMode(666, 666), "Hilbert's Curve");    //�������� ������� ����

void A(int i);  //  ]
void B(int i);  //  [
void C(int i);  //  �
void D(int i);  //  U
void DrawLine(unsigned X, unsigned Y);

void A(int i) {              //  ]
    if (i > 0) {
        D(i-1);
        DrawLine(l, 0);     //������
        A(i-1);
        DrawLine(0, l);     //����
        A(i-1);
        DrawLine(-l, 0);    //�����
        C(i-1);
    }
}
void B(int i) {              //  [
    if (i > 0) {
        C(i - 1);
        DrawLine(-l, 0);    //�����
        B(i - 1);
        DrawLine(0, -l);    //�����
        B(i - 1);
        DrawLine(l, 0);     //������
        D(i - 1);  
    }
}
void C(int i) {             //  �
    if (i > 0) {
        B(i - 1);
        DrawLine(0, -l);    //�����
        C(i - 1);
        DrawLine(-l, 0);    //�����
        C(i - 1);
        DrawLine(0, l);     //����
        A(i - 1);
    }
}
void D(int i) {             //  U
    if (i > 0) {
        A(i - 1);
        DrawLine(0, l);     //����
        D(i - 1);
        DrawLine(l, 0);     //������
        D(i - 1);
        DrawLine(0, -l);    //�����
        B(i - 1);
    }
}
void DrawLine(unsigned X, unsigned Y) {
    sf::Vertex Line[] =                         //������ ���� �����
    {
        sf::Vertex(sf::Vector2f(x, y)),
        sf::Vertex(sf::Vector2f(x + X, y + Y))
    };
    Window.draw(Line, 2, sf::Lines);            //���������� ���������� ���� �����
    x += X;                                     //�������� ���������� "���������"
    y += Y;                                     //
}

int main()
{
    Window.setVisible(false);                   //������ ���� OpenGL
    setlocale(LC_ALL, "");
    
    HWND windowHandle = GetConsoleWindow();     //������������� �������
    ShowWindow(windowHandle, SW_SHOW);          //���������� ������� ��� �����
    char Answer = 'Y';
    cout << "������������ ��������� �� ���������? (Y/n)\n>";
    cin >> Answer;
    if (Answer == 'n') {
        cout << "������� ������� ������ ���������: ";
        cin >> i;
        cout << "������� ����� ��������� ������: ";
        cin >> l;
        cout << "������� ��������� �������:\nx=";
        cin >> x;
        cout << "y=";
        cin >> y;
    }
    
    ShowWindow(windowHandle, SW_HIDE);          //������ �������
    
    Window.clear();                             //������� ����
    
    A(i);                                       //�������� ��������� ������ ���������
    
    Window.setVisible(true);                    //���������� ���� OpenGL
    
    Window.display();                           //���������� ����

    while (Window.isOpen())                     //���� �������� ������
    {
        sf::Event event;
        while (Window.pollEvent(event))
            if (event.type == sf::Event::Closed)//���� ������ ������ ������ (�������)
                Window.close();                 //������� ����
    }

    return 0;
}
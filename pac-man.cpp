#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;


void search(int x, int y, int number);


//инициализация змеи
struct Snake
{
    int duration = 1;
    char direction = 0;
    int x = 10;
    int y = 13;
};
Snake python;

struct Ghosts
{
    int duration = 1;
    char previous_step = 0;
    char next_step = 0;
    int x = 1;
    int y = 6;
    int purposex = 29;
    int purposey = 27;
};
Ghosts blinky;

//старое расположение змеи
int x1 = python.x;
int y_1 = python.y;


//инициализация поля
int arr[30][29];
const unsigned short int arr_planet[30][28] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                               1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                               1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
                                               1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
                                               1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
                                               1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
                                               1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
                                               1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                                               1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                                               1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                              };

int main()
{
    vector<int> go, go1;


    Texture texture1;
    if (!texture1.loadFromFile("1.png"))
    {
        cout << "No file" << endl;

        system("pause");
    }
    Sprite start;
    start.setTexture(texture1);
    start.setOrigin(8.f, 8.f);
    start.rotate(180.f);


    bool flag = false, repeatability = false;
    int x2 = 0;
    int y2 = 0;
    int score = 0;
    int spritex = 0, spritey = 0;
    short int pause = 60, ijkn = 10;


    //инициализация поля
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 29; ++j)
        {
            arr[i][j] = 0;
        }
    }


    arr[python.x][python.y] = 1;

    //физика призрака
    switch (blinky.next_step)
    {
//вниз
    case 0:
    {

        if (arr_planet[blinky.x][blinky.y] == 0)
        {
            if (arr_planet[blinky.x + 1][blinky.y] == 0)
            {
                go.push_back(0);
                go1.push_back(sqrt(pow(blinky.y - (blinky.x + 1), 2) + pow(blinky.purposey - blinky.purposex, 2)));
            }
            if (arr_planet[blinky.x][blinky.y - 1] == 0)
            {
                go.push_back(1);
                go1.push_back(sqrt(pow((blinky.y - 1) - blinky.x, 2) + pow(blinky.purposey - blinky.purposex, 2)));
            }
            if (arr_planet[blinky.x - 1][blinky.y] == 0)
            {
                go.push_back(2);
                go1.push_back(sqrt(pow(blinky.y - (blinky.x - 1), 2) + pow(blinky.purposey - blinky.purposex, 2)));
            }
            if (arr_planet[blinky.x][blinky.y + 1] == 0)
            {
                go.push_back(3);
                go1.push_back(sqrt(pow((blinky.y + 1) - blinky.x, 2) + pow(blinky.purposey - blinky.purposex, 2)));
            }
        }
    }


//влево
    case 1:
    {
    }



//вверх
    case 2:
    {
    }


//вправо
    case 3:
    {
    }
    }
    for (int i = 0; i < 3; i++)
    {
        cout << go[i] << "\t";
        cout << go1[i] << endl;
    }


    RenderWindow window(VideoMode(448, 480), "SNAKE ");/*
    while (!Keyboard::isKeyPressed(sf::Keyboard::Space)) {;}*/

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        RectangleShape rectangle(Vector2f(16.f, 16.f));
        rectangle.setFillColor(Color::Blue);

        window.clear(Color::Black);



        for (int k = 0; k < ijkn; k++)
        {
            if ((score % 10) == 0 && score > 1 && repeatability == false)
            {
                if (pause == 20)
                {
                    pause = 100;
                    ijkn--;
                    repeatability = true;
                }
                else
                {
                    pause -= 20;
                    repeatability = false;
                }
                sleep(milliseconds(pause));
            }
            else {
                sleep(milliseconds(pause));
            }


            if (Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (python.direction == 1)
                {
                    start.rotate(-90.f);
                    python.direction = 0;
                }
                else if (python.direction == 3)
                {
                    start.rotate(90.f);
                    python.direction = 0;
                }
                if ((python.y + 1) < 30 && arr_planet[python.x][python.y + 1] == 0) {
                    python.y++;
                    arr[python.x][python.y] = 1;
                    x1 = python.x;
                    y_1 = python.y;
                    for (int i = 1; i <= python.duration; ++i)
                    {
                        search(x1, y_1, i);
                        if (i < python.duration)  {
                            arr[x1][y_1] = i + 1;
                        }
                        else
                        {
                            arr[x1][y_1] = 0;
                        }
                    }
                    break;
                }
                else if (arr_planet[python.x][python.y + 1] == 1 && (python.y + 1) < 30)
                {
                    break;
                }
                else {
                    return 0;
                }
                flag = true;
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (python.direction == 2)
                {
                    start.rotate(-90.f);
                    python.direction = 1;
                }
                else if (python.direction == 0)
                {
                    start.rotate(90.f);
                    python.direction = 1;
                }
                flag = true;

                if ((python.x + 1) < 29 && arr_planet[python.x + 1][python.y] == 0)
                {
                    python.x++;
                    arr[python.x][python.y] = 1;
                    x1 = python.x;
                    y_1 = python.y;
                    for (int i = 1; i <= python.duration; ++i)
                    {
                        search(x1, y_1, i);

                        if (i < python.duration)  {
                            arr[x1][y_1] = i + 1;
                        }
                        else
                        {
                            arr[x1][y_1] = 0;
                        }
                    }
                    break;
                }
                else if (arr_planet[python.x + 1][python.y] == 1 && (python.x + 1) < 30)
                {
                    break;
                }
                else {
                    return 1;
                }
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (python.direction == 1)
                {
                    start.rotate(90.f);
                    python.direction = 2;
                }
                else if (python.direction == 3)
                {
                    start.rotate(-90.f);
                    python.direction = 2;
                }
                flag = true;

                if ((python.y - 1) > ((-1)) && arr_planet[python.x][python.y - 1] == 0)
                {
                    python.y--;
                    arr[python.x][python.y] = 1;
                    x1 = python.x;
                    y_1 = python.y;
                    for (int i = 1; i <= python.duration; ++i)
                    {
                        search(x1, y_1, i);
                        if (i < python.duration)  {
                            arr[x1][y_1] = i + 1;
                        }
                        else
                        {
                            arr[x1][y_1] = 0;
                        }
                    }
                    break;
                }
                else if (arr_planet[python.x][python.y - 1] == 1 && (python.y - 1) > ((-1)))
                {
                    break;
                }
                else {
                    return 2;
                }
            }
            else if (Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (python.direction == 2)
                {
                    start.rotate(90.f);
                    python.direction = 3;
                }
                else if (python.direction == 0)
                {
                    start.rotate(-90.f);
                    python.direction = 3;
                }
                flag = true;
                if ((python.x - 1) > ((-1)) && arr_planet[python.x - 1][python.y] == 0)
                {
                    python.x--;
                    arr[python.x][python.y] = 1;
                    x1 = python.x;
                    y_1 = python.y;
                    for (int i = 1; i <= python.duration; ++i)
                    {
                        search(x1, y_1, i);
                        if (i < python.duration)  {
                            arr[x1][y_1] = i + 1;
                        }
                        else
                        {
                            arr[x1][y_1] = 0;
                        }
                    }
                    break;
                }
                else if (arr_planet[python.x - 1][python.y] == 1 && (python.x - 1) > ((-1)))
                {
                    break;
                }
                else {
                    return 3;
                }
            }
            if (flag == true)
            {
                break;
            }
        }
        flag = false;



        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j < 29; ++j)
            {
                if (arr_planet[i][j] == 1)
                {
                    rectangle.setPosition(spritex, spritey);
                    window.draw(rectangle);
                }
                if (arr[i][j] == 1)
                {
                    start.setPosition(spritex + 8, spritey + 8);
                    window.draw(start);
                }
                spritex += 16;
            }
            spritex = 0;
            spritey += 16;
        }
        spritex = 0;
        spritey = 0;



        window.display();
    }

    return 0;
}

void search(int x, int y, int number)
{
    if (arr[(x + 1)][y] == number && (x + 1) < 29)
    {
        x1 = x + 1;
        y_1 = y;
    }
    else if (arr[(x - 1)][y] == number && (x - 1) > -1)
    {
        x1 = x - 1;
        y_1 = y;
    }
    else if (arr[x][(y + 1)] == number && (y + 1) < 30)
    {
        x1 = x;
        y_1 = y + 1;
    }
    else if (arr[x][(y - 1)] == number && (y - 1) > -1)
    {
        x1 = x;
        y_1 = y - 1;
    }
};
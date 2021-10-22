#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

int n;
int m;
Font font;

class Game
{
public:
            Game();
    void    run();
private:
    void    processEvents();
    void    update(Time);
    void    render();
    void    handlePlayerInput(Keyboard::Key, bool);
private:

    RenderWindow    Window;
    Time            timePerFrame;
    int c1;
    int c2;
    bool IsNextCross;
    bool IsPress;
    vector<vector<int>> Field;

    bool IsMovingUp;
    bool IsMovingDown;
    bool IsMovingRight;
    bool IsMovingLeft;

    int framesSinceUpdate;
    int WaitFrames;

    Color color;
    Text text;

    vector<vector<RectangleShape>> field;

    int PlayerWin;
};

Game::Game()
:Window(VideoMode(800,600),"TIC-TAC-TOE")
{
    timePerFrame = seconds(1.f / 60.f);

    c1 = 1;
    c2 = 1;
    IsNextCross = 1;
    IsPress = 0;

    Field.resize(n);
    for (int i=0; i<n; i++) Field[i].resize(n);

     for (int i=0; i<n; i++)
     for (int j=0; j<n; j++)
       {
           Field[i][j] = 0;
       }

    field.resize(n);
    for (int i=0; i<n; i++) field[i].resize(n);

    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            field[i][j].setSize(Vector2f(600.f / (float(n) + 0.5), 600.f / (float(n) + 0.5) ));
            field[i][j].setPosition(Vector2f(100 + 600.f / float(n) * float(i) + (600.f / float(n) - 600.f / (float(n) + 0.5)) / 2 ,
                                                   600.f / float(n) * float(j) + (600.f / float(n) - 600.f / (float(n) + 0.5)) / 2));
            field[i][j].setFillColor(Color::White);
        }

     framesSinceUpdate = 0;
     WaitFrames = 5;

     PlayerWin = 0;
     text.setFont(font);
     text.setFillColor(Color::White);
     text.setString("");
}

void Game::run()
{
    Clock clock;
    Time timeSinceLastUpdate = Time::Zero;

    while (Window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }
}

void Game::processEvents()
{
    Event event;
    while (Window.pollEvent(event))

        switch (event.type) {
            case Event::Closed: {
                Window.close();
                break;
            }
            case Event::KeyPressed: {
                handlePlayerInput(event.key.code, 1);
                break;
            }
            case Event::KeyReleased: {
                handlePlayerInput(event.key.code, 0);
                break;
            }
    }
}

void Game::update(Time timePerFrame)
{
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            field[i][j].setFillColor(Color::White);
        }

    framesSinceUpdate++;
    if (framesSinceUpdate > WaitFrames) {
    if (IsMovingLeft  && c1 > 0  ) {c1--;}
    if (IsMovingRight && c1 < n-1) {c1++;}
    if (IsMovingUp    && c2 > 0)   {c2--;}
    if (IsMovingDown  && c2 < n-1) {c2++;}
    framesSinceUpdate = 0;
    }
    if (IsPress && PlayerWin == 0)
    {
        if (Field[c1][c2] == 0) {
            if (IsNextCross == 1) { Field[c1][c2] = 1; }
            if (IsNextCross == 0) { Field[c1][c2] = 2; }
            if (IsNextCross == 0) {IsNextCross = 1;} else {IsNextCross = 0;}
        }
        IsPress = 0;
    }

    field[c1][c2].setFillColor( {127, 127, 127, 255} );
    //text.setString(to_string(c1) + " " + to_string(c2));
    if (PlayerWin == 0) {
        for (int i = 0; i < n - m + 1; i++)
            for (int j = 0; j < n; j++) {

                bool w1 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i + l][j] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i + l][j] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n - m + 1; j++) {

                bool w1 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i][j+l] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i][j+l] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = 0; i < n - m + 1; i++)
            for (int j = 0; j < n - m + 1; j++) {

                bool w1 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i+l][j+l] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i+l][j+l] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }

        for (int i = m-1; i < n; i++)
            for (int j = 0; j < n - m + 1; j++) {

                bool w1 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i-l][j+l] != 1) { w1 = 1; }
                if (w1 == 0) {PlayerWin = 1;}

                bool w2 = 0;
                for (int l = 0; l < m; l++)
                    if (Field[i-l][j+l] != 2) { w2 = 1; }
                if (w2 == 0) {PlayerWin = 2;}
            }
    }
}

void Game::render()
{
    Window.clear();
    //Рисуем поле и т.п.
    Window.draw(text);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            Window.draw(field[i][j]);
        }
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
        {
            if (Field[i][j] == 1)
            {
                RectangleShape Cross;
                Cross.setSize    (Vector2f(600.f / (float(n) + 1.5), 600.f / (float(n) + 1.5) ));
                Cross.setPosition(Vector2f(100 + 600.f / float(n) * float(i) + (600.f / float(n) - 600.f / (float(n) + 1.5)) / 2 ,
                                                 600.f / float(n) * float(j) + (600.f / float(n) - 600.f / (float(n) + 1.5)) / 2));
                Cross.setFillColor(Color::Red);
                Window.draw(Cross);
            }
            if (Field[i][j] == 2)
            {
                RectangleShape Zero;
                Zero.setSize    (Vector2f(600.f / (float(n) + 1.5), 600.f / (float(n) + 1.5) ));
                Zero.setPosition(Vector2f(100 + 600.f / float(n) * float(i) + (600.f / float(n) - 600.f / (float(n) + 1.5)) / 2 ,
                                                600.f / float(n) * float(j) + (600.f / float(n) - 600.f / (float(n) + 1.5)) / 2));
                Zero.setFillColor(Color::Blue);
                Window.draw(Zero);
            }
        }

    if (PlayerWin != 0)
    {
        RectangleShape Shade;
        Shade.setSize(Vector2f(800 , 600));
        Shade.setPosition(0,0);
        Shade.setFillColor({0, 0, 0, 127});
        Window.draw(Shade);
    }

    if (PlayerWin == 1)
    {
        text.setFillColor({255, 63, 63, 255});
        text.setString("RED WON!");
        text.setPosition(400 - text.getLocalBounds().width/2, 300 - text.getLocalBounds().height/2);
        Window.draw(text);
    }

    if (PlayerWin == 2)
    {
        text.setFillColor({63, 63, 255, 255});
        text.setString("BLUE WON!");
        text.setPosition(400 - text.getLocalBounds().width/2, 300 - text.getLocalBounds().height/2);
        Window.draw(text);
    }

    Window.display();
}

void Game::handlePlayerInput(Keyboard::Key key, bool IsPressed)
{
    switch (key)
    {
        case Keyboard::Key::Up: {
            IsMovingUp = IsPressed;
            break;
        }
        case Keyboard::Key::Down: {
            IsMovingDown = IsPressed;
            break;
        }
        case Keyboard::Key::Left: {
            IsMovingLeft = IsPressed;
            break;
        }
        case Keyboard::Key::Right: {
            IsMovingRight = IsPressed;
            break;
        }
        case Keyboard::Key::Enter: {
            IsPress = 1;
            break;
        }
    }
}

int main()
{
    n = 3;
    m = 3;
    if (!font.loadFromFile("../ArialBlack.ttf")) {cout << "Can't load font.\n";}
    Game game;
    game.run();
    return 0;
}

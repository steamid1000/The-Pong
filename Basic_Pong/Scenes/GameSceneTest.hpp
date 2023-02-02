#pragma once
#include "Scene.hpp"
#include <math.h> // required by the sin and cos functions

//^ Logic functions for this Scene
template <typename t>
void logData(t data) // logs input to the console
{
    std::cout << data << '\n';
}

void setSound(sf::SoundBuffer &buffer, sf::Sound &src, const std::string filePath)
{

    if (!buffer.loadFromFile(filePath))
    {
        logData("file cannot be loaded\n");
    }
    src.setBuffer(buffer);
}

//& Remove this function and call the once from the GUI file
void setText(sf::Font &fontObject, sf::Text &textObject, std::string filepath, short characterSize, std::string data = "null")
{
    if (!fontObject.loadFromFile(filepath))
    {
        logData("Font file for text was not found\n");
        return;
    }
    textObject.setFont(fontObject);
    textObject.setCharacterSize(characterSize);
    textObject.setString(data);
}

// This stops the rendering of items and show the last position of them before calling the function
// I dont think the pause is a problem as the game will be reset anyway.
bool keyWasPressed(sf::Keyboard::Key key)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
    {
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
        {
            continue;
        }

        return true;
    }

    return false;
}

/*bool TimerEnded(short allowedTime, short timer)
{
    return allowedTime - timer < 1;
}*/

void endScreen(sf::Font &font, sf::RenderWindow &window)
{
    sf::Text endText("Game-Has-Ended", font, 20);
    endText.setPosition((600 / 3.1) - endText.getPosition().x, 400 / 2);
    window.clear();
    window.draw(endText);
    window.display();
}

//^ Paddle Class

class paddels
{
    int speed = 180;
    // 0 is the left side and 1 is the right side

public:
    sf::RectangleShape paddel;
    paddels(sf::Vector2f sizes, bool side)
    {
        paddel.setSize(sizes);
        paddel.setFillColor(sf::Color(std::rand() + 208 % 255, std::rand() + 20 % 255, std::rand() + 10 % 255));

        if (side == 0)
        {
            paddel.setPosition(0, 40);
        }
        else
        {
            paddel.setPosition(600 - sizes.x, 400 - sizes.y);
        }
    }

    void displace(paddels &pad, sf::Time &dt, bool side, const short &vertical_height, bool part) // the inline might or might not helo at all
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and side == 0 and within_bounds(pad, vertical_height, part))
        {
            pad.paddel.move(0, speed * dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and side == 0 and within_bounds(pad, vertical_height, part))
        {
            pad.paddel.move(0, -(speed * dt.asSeconds()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and side == 1 and within_bounds(pad, vertical_height, part))
        {
            pad.paddel.move(0, -(speed * dt.asSeconds()));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and side == 1 and within_bounds(pad, vertical_height, part))
        {
            pad.paddel.move(0, (speed * dt.asSeconds()));
        }
    }

    bool within_bounds(paddels &pad, const short &window_height, bool side)
    {
        if ((side == false and pad.paddel.getPosition().y < 0.f))
        {
            pad.paddel.setPosition(pad.paddel.getPosition().x, 1.f); // setting the y to 0 will relieve the shaking but let it be for some feel right now
            return false;
        }
        if (side == false and (pad.paddel.getPosition().y + pad.paddel.getGlobalBounds().height) > window_height)
        {
            pad.paddel.setPosition(0.f, window_height - pad.paddel.getGlobalBounds().height);
            return false;
        }
        if (side == true and pad.paddel.getPosition().y < 0.f)
        {
            pad.paddel.setPosition(pad.paddel.getPosition().x, 1.f);
            return false;
        }
        if (side == true and (pad.paddel.getPosition().y + pad.paddel.getGlobalBounds().height) > window_height)
        {
            pad.paddel.setPosition(pad.paddel.getPosition().x, window_height - pad.paddel.getGlobalBounds().height);
            return false;
        }

        return true;
    }
};

//^ End of paddle class

//^ Ball Class
float pi = 3.1415;
extern const short height, width;

class Sphere
{
public:
    float size;
    sf::CircleShape ball;

    Sphere(float radius)
    {
        size = radius;

        ball.setRadius(radius);
        ball.setFillColor(sf::Color::White);
        ball.setPosition(width / 2, height / 2);
    }
};

void logCollision(paddels pad, Sphere gameball) // Just logs the collision information on the console
{
    std::cout << "ball has collided\n";
    std::cout << "X-Position of Ball: " << gameball.ball.getPosition().x << "\n";
    std::cout << "Y-Position of collided paddel: " << pad.paddel.getPosition().y << "\n";
}

bool onCollision(paddels &pad, Sphere &gameball, sf::Sound &collision) // return true and calls the log function
{
    // left pad collision
    if (gameball.ball.getPosition().x - gameball.ball.getRadius() < pad.paddel.getPosition().x + pad.paddel.getSize().x and
        gameball.ball.getPosition().x - gameball.ball.getRadius() > pad.paddel.getPosition().x and
        gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y and
        gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y)
    {
        logCollision(pad, gameball);
        collision.play();
        return true;
    }
    // right pad collision
    if (gameball.ball.getPosition().x + gameball.ball.getRadius() > pad.paddel.getPosition().x - pad.paddel.getSize().x and
        gameball.ball.getPosition().x + gameball.ball.getRadius() < pad.paddel.getPosition().x and
        gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y and
        gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y)
    {
        logCollision(pad, gameball);
        collision.play();
        return true;
    }

    return false;
}

void checkCollision(float &dt, Sphere &gameball, paddels &leftpad, paddels &rightpad, float &Angle, short &leftscore, short &rightscore, sf::Sound &collisionSound)
{
    float factor = 260.f * dt;

    if (!onCollision(leftpad, gameball, collisionSound) and !onCollision(rightpad, gameball, collisionSound) and gameball.ball.getPosition().y + gameball.ball.getRadius() > height) // Bottom Collision
    {
        gameball.ball.setPosition(gameball.ball.getPosition().x, height - gameball.ball.getRadius() - 0.1f);
        Angle = -Angle;
    }
    else if (!onCollision(leftpad, gameball, collisionSound) and !onCollision(rightpad, gameball, collisionSound) and gameball.ball.getPosition().y < 0) // Top Collision
    {
        gameball.ball.setPosition(gameball.ball.getPosition().x, 0.1f);
        Angle = -Angle;
    }
    else if (onCollision(leftpad, gameball, collisionSound) or onCollision(rightpad, gameball, collisionSound))
    {
        std::cout << "Value of angle: " << Angle << "\n";

        if (onCollision(leftpad, gameball, collisionSound)) // This has to be changed in the future
        {
            Angle = pi - Angle;
            gameball.ball.setPosition(gameball.ball.getPosition().x + gameball.ball.getRadius() / 3 + 0.1f, gameball.ball.getPosition().y);
            leftscore += 5;
        }
        else
        {
            Angle = pi - Angle;
            gameball.ball.setPosition(gameball.ball.getPosition().x - gameball.ball.getRadius() / 3 - 0.1, gameball.ball.getPosition().y);
            rightscore += 5;
        }
    }

    gameball.ball.move(std::cos(Angle) * factor, std::sin(Angle) * factor);
}

void collidedWithWall(Sphere &gameball, short &numberOfHeartsOnLeft, short &scoreLeft, short &numberOfHeartsOnRight, short &scoreRight, sf::Sound &sound) // This function is a early version of the life system, which will be added in future commits
{
    if (gameball.ball.getPosition().x + gameball.ball.getRadius() > width)
    {
        gameball.ball.setPosition(width / 2, height / 2);
        --numberOfHeartsOnRight; // this will reduce the rendered hearts by 1 same is below
        scoreRight -= 10;
        sound.play();
    }
    else if (gameball.ball.getPosition().x < 0)
    {
        gameball.ball.setPosition(width / 2, height / 2);
        --numberOfHeartsOnLeft;
        scoreLeft -= 10;
        sound.play();
    }
}
//^ End of Ball Class

//^ Lives CLass (hearts)

class hearts
{
private:
    bool side;
    sf::Texture heartImg;
    sf::Font font;
    sf::Text text;
    sf::Sprite lives[5]; // needs initilization

public:
    short numberOfLivesLeft;
    short score;
    short width, height;
    hearts(bool side, short width, short height)
    {
        // Setting up the files used
        heartImg.loadFromFile("res\\heart.png");
        font.loadFromFile("res\\VeraBd.ttf");
        text.setFont(font);
        text.setCharacterSize(35);

        // Initializing the variables.
        this->side = side;
        this->width = width;
        this->height = height;
        numberOfLivesLeft = 5;
        score = 0;
        initiateHearts(); // ! Warning ! ,Dont call this function from outside
    }

    void initiateHearts()
    {
        sf::Vector2f size(0.19, 0.19);
        text.setString(std::to_string(score));
        float x_position;

        if (side == false) // for hearts on the left side
        {
            // setting the first heart size and position as all the other hearts
            // will have a offset according to the first hearts position
            lives[0].setTexture(heartImg);
            lives[0].setScale(size);
            lives[0].setPosition(80.f, 10.f);

            x_position = 80.f;
            text.setPosition(width / 4, height - 60);
        }
        else // for hearts on the right side
        {
            lives[0].setTexture(heartImg);
            lives[0].setScale(size);
            lives[0].setPosition(375.f, 10.f);

            x_position = 375.f;
            text.setPosition(width / 1.4f, height - 60);
        }

        // drawing the remaning hearts
        for (short i = 1; i < 5; i++)
        {
            lives[i].setTexture(heartImg);
            lives[i].setScale(size);
            lives[i].setPosition(x_position + 30.f * i, 10.f); // offsetting the position accodring to the 1st position
        }
    }

    void drawHearts(sf::RenderWindow &window) // Drawn the hearts on the screen
    {
        for (short i = 0; i < numberOfLivesLeft; i++)
        {
            window.draw(lives[i]);
        }
        text.setString(std::to_string(score));
        window.draw(text);
    }
};
//^ End of lives class

// The function is for development only, so that I dont have to restart the game again and again
void reset(float &Angle, Sphere &gameBall, short &leftHearts, short &rightHearts, short &leftScore, short &rightScore, short width, short height)
{
    gameBall.ball.setPosition(width / 2, height / 2);
    Angle = std::rand() + 1 % 20;
    leftHearts = 5;
    rightHearts = 5;
    leftScore = 0;
    rightScore = 0;
}

extern short sceneIndex;
extern sf::Font font;

class GameScene : public Scene
{
private:
    // GUI::Button* gameMode;
    sf::RenderWindow *internalwindow;
    sf::Texture middleline;
    sf::Sprite middleLine;

public:
    // Useful variables
    float Angle;
    float seconds;
    short timerCount;
    short allowedTime = 10;

    // Timers
    sf::Clock deltaclock;
    sf::Time dt;
    sf::Text timerText;

    Sphere *gameBall;
    paddels *right;
    paddels *left;

    // lives code here
    hearts *leftHearts;
    hearts *rightHearts;

    // sounds
    const std::string wallCollisionfile = "res\\collision.wav";
    const std::string paddleCollisionfile = "res\\paddel_hit.wav";

    sf::SoundBuffer wallCollision;
    sf::SoundBuffer paddleCollision;
    sf::Sound wallSound;
    sf::Sound paddleHitSound;

    GameScene(sf::RenderWindow &);
    ~GameScene();

    void setup();
    void render();
};

GameScene::GameScene(sf::RenderWindow &window)
{
    internalwindow = &window;
    setup();
}

GameScene::~GameScene()
{
    // delete internalwindow; //! Could be problamatic if
    //! it deletes the original window oject
}

void GameScene::setup()
{
    // gameMode->SetInnerText("Game is on!",50);
    // gameMode->SetPosition(sf::Vector2f(width/2-gameMode->getBounds().width/2,height/2));

    Angle = std::rand() % 10;

    middleline.loadFromFile("res\\middle-Line.png");
    middleLine.setTexture(middleline);
    middleLine.setScale(0.8, 1.1);
    middleLine.setPosition(width / 2, 0);

    left = new paddels(sf::Vector2f(20, 60), 0);
    right = new paddels(sf::Vector2f(20, 60), 1);
    gameBall = new Sphere(11.f);

    // setting font for timer ( //^ Not in use )
    setText(font, timerText, "res\\times.ttf", 20);

    // lives code here
    leftHearts = new hearts(0, width, height);
    rightHearts = new hearts(1, width, height);

    //^ Setting the sounds
    setSound(wallCollision, wallSound, wallCollisionfile);
    setSound(paddleCollision, paddleHitSound, paddleCollisionfile);

    printf("The game scene has loaded succesfully\n");
}

void GameScene::render()
{
    while (internalwindow->isOpen() or sceneIndex == 1)
    {

        sf::Event poll;
        while (internalwindow->pollEvent(poll))
        {
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            printf("The game Scene has been closed\n");
            sceneIndex--;
            return;
        }

        dt = deltaclock.restart();
        seconds = dt.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            left->displace(*left, dt, false, height, 0);
            // False means the paddle is on the left and vice versa
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            right->displace(*right, dt, true, height, 1);
        }

        checkCollision(seconds, *gameBall, *left, *right, Angle, leftHearts->score, rightHearts->score, paddleHitSound); // More precision required in collision
        collidedWithWall(*gameBall, leftHearts->numberOfLivesLeft, leftHearts->score, rightHearts->numberOfLivesLeft, rightHearts->score, wallSound);

        if (leftHearts->numberOfLivesLeft > 0 and rightHearts->numberOfLivesLeft > 0)
        {
            internalwindow->clear(sf::Color(45, 90, 120));
            internalwindow->draw(middleLine);
            internalwindow->draw(left->paddel);
            internalwindow->draw(right->paddel);
            internalwindow->draw(gameBall->ball);
            leftHearts->drawHearts(*internalwindow);
            rightHearts->drawHearts(*internalwindow);
            internalwindow->display();
        }

        if (leftHearts->numberOfLivesLeft <= 0 or rightHearts->numberOfLivesLeft <= 0)
        {
            endScreen(font, *internalwindow);
        }

        // Resets the required game objects like the ball,lives and the heart counters
        if (keyWasPressed(sf::Keyboard::Key::R))
        {
            reset(Angle, *gameBall, leftHearts->numberOfLivesLeft, rightHearts->numberOfLivesLeft, leftHearts->score, rightHearts->score, width, height);
        }
    }
}

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "character.hpp"
#include <iostream>
int main()
{
    //Loading and setting up textures
    sf::Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);
    sf::Texture guy_texture;
    if(!guy_texture.loadFromFile("guy.png")) {return 1;}
    sf::Sprite guy;
    guy.setTexture(guy_texture);
    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setScale(1, 1);
    grass.setTextureRect(sf::IntRect(0, 0, 800, 600));
    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("wall.png")) { return 1; }
    texture_wall.setRepeated(true);
    //Clock
    float dt;
    sf::Clock dt_clock;
    //  Walls
    std::vector<sf::RectangleShape> walls;
    sf::RectangleShape wall;
    wall.setTexture(&texture_wall);
    wall.setSize(sf::Vector2f(100,300));
    wall.setPosition(100,0);

    sf::RectangleShape wall1;
    wall.setTexture(&texture_wall);
    wall.setSize(sf::Vector2f(100,300));
    wall.setPosition(300,0);


    walls.push_back(wall);
    walls.push_back(wall1);

    sf::FloatRect nextPos;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(120);
    sf::RectangleShape player;
    player.setTexture(&guy_texture);
    player.setSize(sf::Vector2f(43,69));


    const float movementSpeed = 400.f;
    sf::Vector2f velocity;
  // Start the game loop
    while (window.isOpen())
    {
        dt = dt_clock.restart().asSeconds();
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            //handle input
            velocity.x = 0.f;
            velocity.y = 0.f;
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Up))
            {
                velocity.y += -movementSpeed * dt ;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Down))
            {
                velocity.y += movementSpeed * dt ;

            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Left))
            {
                velocity.x += -movementSpeed * dt ;

            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Right))
            {
                velocity.x += movementSpeed * dt ;
            }

            //colisions



            for (auto &wall : walls)
            {
                sf::FloatRect playerBounds = player.getGlobalBounds();
                sf::FloatRect wallBounds = wall.getGlobalBounds();

                nextPos = playerBounds;
                nextPos.left +=  velocity.x;
                nextPos.top  +=  velocity.y;

                if(wallBounds.intersects(nextPos))
                {
                    //Bottom collision
                    if(playerBounds.top < wallBounds.top &&
                            playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                            playerBounds.left < wallBounds.left + wallBounds.width
                            && playerBounds.left + playerBounds.width > wallBounds.left
                            )
                    {
                        velocity.y =0.f;
                        player.setPosition(wallBounds.left, wallBounds.top - playerBounds.height );

                    }
                    //Topcollision
                    if(playerBounds.top > wallBounds.top &&
                            playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                            playerBounds.left < wallBounds.left + wallBounds.width
                            && playerBounds.left + playerBounds.width > wallBounds.left
                            )
                    {
                        velocity.y =0.f;
                        player.setPosition(playerBounds.left, wallBounds.top + wallBounds.height );

                    }
                    //Right collision
                    if(playerBounds.left < wallBounds.left &&
                            playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
                            playerBounds.top < wallBounds.top + wallBounds.height
                            && playerBounds.top + playerBounds.height > wallBounds.top
                            )
                    {
                        velocity.x =0.f;
                        player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);

                    }
                    //Left collision
                    if(playerBounds.left > wallBounds.left &&
                            playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                            playerBounds.top < wallBounds.top + wallBounds.height
                            && playerBounds.top + playerBounds.height > wallBounds.top
                            )
                    {
                        velocity.x =0.f;
                        player.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);

                    }
                }


            }
            player.move(velocity);
            //Collision screen
            //left collision
            if(player.getPosition().x < 0.f)
                player.setPosition(0.f, player.getPosition().y);
            //Top collision
            if(player.getPosition().y < 0.f)
                player.setPosition(player.getPosition().x, 0.f);
            //Right collision
            if(player.getPosition().x + player.getGlobalBounds().width > 800)
                player.setPosition(800 - player.getGlobalBounds().width, player.getPosition().y);
            //bottom collision
            if(player.getPosition().y + player.getGlobalBounds().height > 600)
                player.setPosition(player.getPosition().x, 600 - player.getGlobalBounds().height);





        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(grass);

        for (auto&i : walls)
        {
            window.draw(i);
        }

        window.draw(player);


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "character.hpp"
class Character
{
public:
    Character(const sf::Vector2f& pos) : pos(pos)
    {
        texture.loadFromFile("guy.png");
        sprite = sf::Sprite( texture );
    }
    void  Draw( sf::RenderTarget& rt)
    {
        rt.draw(sprite);
    }
    void SetDirection( const sf::Vector2f& dir )
    {
        vel = dir * speed;
    }
    void Update( float dt)
    {
       pos += vel*dt;
         sprite.setPosition(pos);
    }
private:
    static constexpr float speed = 1.0f;
    sf::Vector2f pos;
    sf::Vector2f vel = {0.0f,0.0f};
    sf::Texture texture;
    sf::Sprite sprite;
};

int main()
{
    sf::Texture texture_grass;
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    texture_grass.setRepeated(true);

    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setScale(1, 1);
    grass.setTextureRect(sf::IntRect(0, 0, 800, 600));
    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("wall.png")) { return 1; }
    texture_wall.setRepeated(true);

    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setTextureRect(sf::IntRect(0, 0, 400, 100));
    wall.setPosition(0,100);
    sf::Sprite wall1;
    wall1.setTexture(texture_wall);
    wall1.setScale(0.6, 0.6);
    wall1.setTextureRect(sf::IntRect(0, 0, 100, 400));
    wall1.setPosition(200,100);
    sf::Sprite wall2;
    wall2.setTexture(texture_wall);
    wall2.setScale(0.6, 0.6);
    wall2.setTextureRect(sf::IntRect(0, 0, 100, 900));
    wall2.setPosition(400,0);
    sf::Sprite wall3;
    wall3.setTexture(texture_wall);
    wall3.setScale(0.6, 0.6);
    wall3.setTextureRect(sf::IntRect(0, 0, 100, 400));
    wall3.setPosition(200,100);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    Character guy( { 100.0f,100.0f } );

  // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            // get dt

            //handle input
            sf::Vector2f dir = {0.0f,0.0f};
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Up))
            {
                dir.y -= 1.0f;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Down))
            {
                dir.y += 1.0f;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Left))
            {
                dir.x -= 1.0f;
            }
            if(sf::Keyboard::isKeyPressed( sf::Keyboard::Right))
            {
                dir.x += 1.0f;
            }
            guy.SetDirection(dir);

        }
        //Update model
        guy.Update(1.0f/60.0f);
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(grass);
        window.draw(wall);
       window.draw(wall1);
           window.draw(wall2);
               window.draw(wall3);
        guy.Draw( window);
        // Draw the string
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

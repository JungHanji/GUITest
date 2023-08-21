#include <SFML/Graphics.hpp>
#include <GUIlib/Elems/RichText.hpp>
#include <MathLib/VectorFuncs.hpp>
using namespace std;
#include <AdtClasses/AdtClasses.hpp>


class TXT{
    sf::Font font;
    public:
    sfe::RichText text;

    TXT(string f, vec2 pos, int chsize){
        font.loadFromFile(f);
        text.setFont(font);
        text.setCharacterSize(chsize);
        text.setPosition({pos.x, pos.y});
    }

    sfe::RichText &getText(){
        return text;
    }

    void draw(sf::RenderWindow &wind){
        //text.setOrigin({text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f});
        wind.draw(text);
    }

    void init(string f){
        font.loadFromFile(f);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "sfe::RichText");
    window.setFramerateLimit(30);

    TXT txt("res/arial.ttf", {400, 300}, 25);

    
    txt.getText() << sf::Text::Bold       << sf::Color::Cyan  << L"Это "
                  << sf::Text::Italic     << sf::Color::White << L"тот самый\n"
                  << sf::Text::Regular    << sf::Color::Green << L"пример"
                  << sf::Color::White     << L".\n"
                  << sf::Text::Underlined << L"Выглядит" << sf::Color::Blue <<L" хорошо!";

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        txt.draw(window);
        window.display();
    }
}
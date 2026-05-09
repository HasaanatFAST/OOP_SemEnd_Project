#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

// Manual int/float to string helper functions
string iToS(int val);
string fToS(float val);

// =============================================
// Button class - clickable GUI button
// =============================================
class Button {
private:
    sf::RectangleShape rect;
    sf::Text* text;
    bool visible;
    sf::Color normalColor, hoverColor;

public:
    Button();
    Button(const Button& o);
    Button& operator=(const Button& o);
    ~Button();

    void create(float x, float y, float w, float h,
                const string& label, sf::Font& font, unsigned int sz = 18);
    void setColors(sf::Color n, sf::Color h);
    bool handleClick(sf::RenderWindow& win);
    void updateHover(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);
    void setVisible(bool v);
};

// =============================================
// TextBox class - text input field
// =============================================
class TextBox {
private:
    sf::RectangleShape rect;
    sf::Text* text;
    string input;
    bool selected, visible;

public:
    TextBox();
    TextBox(const TextBox& o);
    TextBox& operator=(const TextBox& o);
    ~TextBox();

    void create(float x, float y, float w, float h,
                sf::Font& font, unsigned int sz = 18);
    void handleMouseClick(sf::RenderWindow& win);
    void handleTextInput(unsigned int code);
    void draw(sf::RenderWindow& win);
    const string& getText() const;
    void clear();
    void setVisible(bool v);
    int toInt() const;
    float toFloat() const;
};

// Helper function to draw a colored panel
void drawPanel(sf::RenderWindow& win, float x, float y, float w, float h, sf::Color col);

#endif

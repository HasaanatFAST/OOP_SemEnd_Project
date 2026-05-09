#include "GUI.h"

// =============================================
// Helper functions to convert int/float to string
// (no built-in to_string used)
// =============================================

string iToS(int val) {
    if (val == 0) return "0";
    string r;
    bool neg = val < 0;
    if (neg) val = -val;
    while (val > 0) {
        r = char('0' + val % 10) + r;
        val /= 10;
    }
    if (neg) r = "-" + r;
    return r;
}

string fToS(float val) {
    int ip = (int)val;
    int fp = (int)((val - ip) * 100 + 0.5f);
    string r = iToS(ip) + ".";
    if (fp < 10) r += "0";
    r += iToS(fp);
    return r;
}

// =============================================
// Button class implementation
// =============================================

Button::Button()
    : text(nullptr), visible(true),
      normalColor(70, 90, 180), hoverColor(100, 120, 220) {
}

Button::Button(const Button& o)
    : text(nullptr), visible(o.visible),
      normalColor(o.normalColor), hoverColor(o.hoverColor) {
    rect = o.rect;
    if (o.text) text = new sf::Text(*o.text);
}

Button& Button::operator=(const Button& o) {
    if (this != &o) {
        delete text;
        text = nullptr;
        rect = o.rect;
        visible = o.visible;
        normalColor = o.normalColor;
        hoverColor = o.hoverColor;
        if (o.text) text = new sf::Text(*o.text);
    }
    return *this;
}

Button::~Button() {
    delete text;
}

void Button::create(float x, float y, float w, float h,
                    const string& label, sf::Font& font, unsigned int sz) {
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(normalColor);
    rect.setOutlineColor(sf::Color(40, 50, 120));
    rect.setOutlineThickness(1.5f);

    delete text;
    text = new sf::Text(font, label, sz);
    text->setFillColor(sf::Color::White);

    sf::FloatRect tb = text->getLocalBounds();
    text->setOrigin(sf::Vector2f(tb.position.x + tb.size.x / 2.f,
                                 tb.position.y + tb.size.y / 2.f));
    text->setPosition(sf::Vector2f(x + w / 2.f, y + h / 2.f));
}

void Button::setColors(sf::Color n, sf::Color h) {
    normalColor = n;
    hoverColor = h;
}

bool Button::handleClick(sf::RenderWindow& win) {
    if (!visible) return false;
    sf::Vector2i mp = sf::Mouse::getPosition(win);
    return rect.getGlobalBounds().contains(sf::Vector2f((float)mp.x, (float)mp.y));
}

void Button::updateHover(sf::RenderWindow& win) {
    if (!visible) return;
    sf::Vector2i mp = sf::Mouse::getPosition(win);
    if (rect.getGlobalBounds().contains(sf::Vector2f((float)mp.x, (float)mp.y))) {
        rect.setFillColor(hoverColor);
    }
    else {
        rect.setFillColor(normalColor);
    }
}

void Button::draw(sf::RenderWindow& win) {
    if (!visible) return;
    win.draw(rect);
    if (text) win.draw(*text);
}

void Button::setVisible(bool v) {
    visible = v;
}

// =============================================
// TextBox class implementation
// =============================================

TextBox::TextBox() : text(nullptr), selected(false), visible(true) {
}

TextBox::TextBox(const TextBox& o)
    : text(nullptr), input(o.input), selected(o.selected), visible(o.visible) {
    rect = o.rect;
    if (o.text) text = new sf::Text(*o.text);
}

TextBox& TextBox::operator=(const TextBox& o) {
    if (this != &o) {
        delete text;
        text = nullptr;
        rect = o.rect;
        input = o.input;
        selected = o.selected;
        visible = o.visible;
        if (o.text) text = new sf::Text(*o.text);
    }
    return *this;
}

TextBox::~TextBox() {
    delete text;
}

void TextBox::create(float x, float y, float w, float h,
                     sf::Font& font, unsigned int sz) {
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(sf::Color::White);
    rect.setOutlineColor(sf::Color(150, 150, 150));
    rect.setOutlineThickness(1.5f);

    delete text;
    text = new sf::Text(font, "", sz);
    text->setFillColor(sf::Color::Black);
    text->setPosition(sf::Vector2f(x + 5, y + (h - sz) / 2.f));
}

void TextBox::handleMouseClick(sf::RenderWindow& win) {
    if (!visible) return;
    sf::Vector2i mp = sf::Mouse::getPosition(win);
    selected = rect.getGlobalBounds().contains(sf::Vector2f((float)mp.x, (float)mp.y));

    if (selected)
        rect.setOutlineColor(sf::Color(70, 90, 180));
    else
        rect.setOutlineColor(sf::Color(150, 150, 150));
}

void TextBox::handleTextInput(unsigned int code) {
    if (!selected || !visible) return;

    if (code == 8) {
        if (input.size() > 0) input.pop_back();
    }
    else if (code < 128 && code > 31 && input.size() < 98) {
        input += (char)code;
    }

    if (text) text->setString(input);
}

void TextBox::draw(sf::RenderWindow& win) {
    if (!visible) return;
    win.draw(rect);
    if (text) win.draw(*text);
}

const string& TextBox::getText() const {
    return input;
}

void TextBox::clear() {
    input = "";
    if (text) text->setString("");
}

void TextBox::setVisible(bool v) {
    visible = v;
}

int TextBox::toInt() const {
    int r = 0;
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            r = r * 10 + (input[i] - '0');
        }
    }
    return r;
}

float TextBox::toFloat() const {
    float r = 0, frac = 0, div = 10;
    bool dot = false;
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i] == '.') {
            dot = true;
        }
        else if (input[i] >= '0' && input[i] <= '9') {
            if (!dot)
                r = r * 10 + (input[i] - '0');
            else {
                frac += (input[i] - '0') / div;
                div *= 10;
            }
        }
    }
    return r + frac;
}

// =============================================
// drawPanel helper function
// =============================================

void drawPanel(sf::RenderWindow& win, float x, float y, float w, float h, sf::Color col) {
    sf::RectangleShape r(sf::Vector2f(w, h));
    r.setPosition(sf::Vector2f(x, y));
    r.setFillColor(col);
    win.draw(r);
}

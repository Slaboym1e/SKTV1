#include "GravityModel.h"
#include "SFML/Graphics.hpp"
#include <memory>

struct Button {
   sf::RectangleShape rect;
   sf::Text text;

   bool isClicked(sf::Vector2f mousePos) {
      return rect.getGlobalBounds().contains(mousePos);
   }

   void draw(sf::RenderWindow& window) {
      window.draw(rect);
      window.draw(text);
   }
};

class MainWindow 
{
 private:
   sf::Font _font;
   const int _windowWidth = 1400;
   const int _windowHeight = 900;
   Button _forwardButton;
   Button _inverseButton;
   std::unique_ptr<GravityModel> _model;
   std::vector<Cell> cells;

 public:
   void Initialization();
   void RunMainWindow();

};
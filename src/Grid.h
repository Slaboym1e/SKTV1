#pragma once
#include"SFML/Graphics.hpp"
#include"Cell.h"
#include <vector>

class DrawebelCell
{
   sf::Font _font;
   sf::Text _text;
   sf::RectangleShape _rect;
public:
   DrawebelCell();
   void draw(sf::RenderWindow &window);
   void setRho(double rho);
   void setPosition(double x, double y);
   void setColor(int color);

};

class Grid
{
 private:
   sf::VertexArray _xAxis;
   sf::VertexArray _zAxis;
   std::vector<sf::Text> _xValues;
   std::vector<sf::Text> _zValues;
   sf::Font font;
   std::vector<DrawebelCell> _cells;
   bool _kindProblem = false;
 public:
   Grid();
   void draw(sf::RenderWindow &window);
   void setCells(std::vector<Cell> cells);
   void kindProblem(const bool &kindProblem);
};
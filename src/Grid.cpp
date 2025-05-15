#include "Grid.h"

Grid::Grid()
{
   _xAxis.setPrimitiveType(sf::Lines);
   _zAxis.setPrimitiveType(sf::Lines);
   _xAxis.resize(2);
   _zAxis.resize(2);
   _xAxis[0].color = sf::Color::Red;
   _xAxis[1].color = sf::Color::Red;
   _xAxis[0].position = sf::Vector2f(100, 100);
   _xAxis[1].position = sf::Vector2f(600, 100);
   _zAxis[0].color = sf::Color::Red;
   _zAxis[1].color = sf::Color::Red;
   _zAxis[0].position = sf::Vector2f(100, 100);
   _zAxis[1].position = sf::Vector2f(100, 300);
   _xValues.resize(6);
   _zValues.resize(3);
   font.loadFromFile("resources/ttt.otf");
   for (int i = 0; i < 6; i++)
   {

      _xValues[i].setFont(font);
      _xValues[i].setPosition(100 + i * 100, 75);
      _xValues[i].setString(std::to_string(i * 1000));
      _xValues[i].setCharacterSize(20);
      _xValues[i].setFillColor(sf::Color::Red);
   }
   for (int i = 0; i < 3; i++)
   {
      _zValues[i].setFont(font);
      _zValues[i].setPosition(40, 85 + (i+1) * 50);
      _zValues[i].setString(std::to_string(-(i + 1) * 500));
      _zValues[i].setCharacterSize(20);
      _zValues[i].setFillColor(sf::Color::Red);
   }
}

void Grid::draw(sf::RenderWindow& window)
{
   for(const auto &text : _xValues)
      window.draw(text);
   for (const auto& text : _zValues)
      window.draw(text);
   window.draw(_xAxis);
   window.draw(_zAxis);
   for(auto & cell : _cells)
      cell.draw(window);

}

void Grid::setCells(std::vector<Cell> cells)
{
   int i = 0;
   _cells.resize(cells.size());
   for (const auto& cell : cells)
   {
      _cells[i].setRho(cell.rho);
      _cells[i].setPosition(100 + cell.x / 10, 100 + (-cell.z) / 10);
      if (_kindProblem)
         _cells[i].setColor(std::min(255, std::max(0, int(128 + cell.rho * 127))));

      i++;
   }
}

void Grid::kindProblem(const bool& kindProblem)
{
   _kindProblem = kindProblem;
   for (auto& cell : _cells)
      cell.setColor(-1);
   
}



DrawebelCell::DrawebelCell()
{
   _font.loadFromFile("resources/ttt.otf");
   _text.setFont(_font);
   _text.setCharacterSize(12);
   _text.setFillColor(sf::Color::Black);
   _rect.setSize(sf::Vector2f(50,25));
   _rect.setOutlineThickness(1);
   _rect.setOutlineColor(sf::Color::Black);
   _rect.setFillColor(sf::Color(200, 200, 200));
}

void DrawebelCell::draw(sf::RenderWindow& window)
{
   window.draw(_rect);
   window.draw(_text);
}

void DrawebelCell::setRho(double rho)
{
   char buffer[16];
   snprintf(buffer, sizeof(buffer), "%.2f", rho);
   _text.setString(buffer);
}

void DrawebelCell::setPosition(double x, double y)
{
   _rect.setPosition(x, y);
   _text.setPosition(x + _rect.getSize().x / 4, y + _rect.getSize().y / 4);
}

void DrawebelCell::setColor(int color)
{
   _rect.setFillColor(sf::Color(color, 100, 255 - color));
   if(color == -1)
      _rect.setFillColor(sf::Color(200, 200, 200));
}




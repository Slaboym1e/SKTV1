#include "GProfile.h"

void GProfileDraw::calcProf()
{
   for (int i = 0; i < _xProfile.size(); i++) 
   {
      double gx = 100 + (_xProfile[i] + 2000) / 10;
      double gy = 800 - (_gProfile[i] / maxG * 400);
      gPlot[i].position = sf::Vector2f(gx, gy);
      gPlot[i].color = sf::Color::Blue;
   }
}

void GProfileDraw::setXProfile(std::vector<double>& xProfile)
{
   _xProfile = xProfile;
   gPlot.resize(_xProfile.size());
   maxX = *std::max_element(begin(_xProfile), end(_xProfile));

}

void GProfileDraw::setGProfile(std::vector<double> gProfile)
{
   _gProfile = gProfile;
   if(gProfile.size() > 0)
   {
     
      maxG = *std::max_element(begin(_gProfile), end(_gProfile));

      char buffer[16];
      snprintf(buffer, sizeof(buffer), "%.2f", maxG);
      _gValues[_gValues.size() - 1].setString(buffer);
      _gValues[_gValues.size() - 1].setFont(_font);
      _gValues[_gValues.size() - 1].setPosition(50, 400);
      _gValues[_gValues.size() - 1].setCharacterSize(20);
      _gValues[_gValues.size() - 1].setFillColor(sf::Color::Black);
   }
}

GProfileDraw::GProfileDraw()
{
   gPlot.setPrimitiveType(sf::LinesStrip);
   _xAxis.setPrimitiveType(sf::Lines);
   _gAxis.setPrimitiveType(sf::Lines);
   _xAxis.resize(2);
   _xAxis[0].position = sf::Vector2f(100, 800);
   _xAxis[1].position = sf::Vector2f(900, 800);
   _xAxis[0].color = sf::Color::Black;
   _xAxis[1].color = sf::Color::Black;

   _gAxis.resize(2);
   _gAxis[0].position = sf::Vector2f(100, 400);
   _gAxis[1].position = sf::Vector2f(100, 800);
   _gAxis[0].color = sf::Color::Black;
   _gAxis[1].color = sf::Color::Black;

   _xValues.resize(5);
   _font.loadFromFile("resources/ttt.otf");
   for (int i = 0; i < _xValues.size(); i++)
   {
      _xValues[i].setFont(_font);
      _xValues[i].setPosition(100 + i * 200, 800);
      _xValues[i].setString(std::to_string(-2000 + i * 2000));
      _xValues[i].setCharacterSize(20);
      _xValues[i].setFillColor(sf::Color::Black);
   }
   _gValues.resize(5);
   for (int i = 0; i < _gValues.size()-1; i++)
   {
      _gValues[i].setFont(_font);
      _gValues[i].setPosition(50, 780 - i * 100);
      char buffer[16];
      snprintf(buffer, sizeof(buffer), "%.2f", i * 0.01);
      _gValues[i].setString(buffer);
      _gValues[i].setCharacterSize(20);
      _gValues[i].setFillColor(sf::Color::Black);
   }
}

void GProfileDraw::draw(sf::RenderWindow& window)
{
   if(_xProfile.size() && _gProfile.size())
   {
      calcProf();
      window.draw(gPlot);
   }
   window.draw(_xAxis);
   window.draw(_gAxis);
   for(const auto& text : _xValues)
      window.draw(text);
   for (const auto& text : _gValues)
      window.draw(text);
}

#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include<algorithm>

class GProfileDraw
{
private:
   int _countSource = 0;
   std::vector<double> _gProfile;
   std::vector<double> _xProfile;
   sf::VertexArray gPlot;
   sf::VertexArray _xAxis;
   sf::VertexArray _gAxis;
   std::vector<sf::Text> _xValues;
   std::vector<sf::Text> _gValues;
   sf::Font _font;
   double maxG = 0;
   double maxX = 0;
   void calcProf();
public:
   void setXProfile(std::vector<double> &xProfile);
   void setGProfile(std::vector<double> gProfile);
   GProfileDraw();
   void draw(sf::RenderWindow &window);
};
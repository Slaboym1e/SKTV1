#pragma once
#include "GravityModel.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Grid.h"
#include "GProfile.h"
#include <functional>


class GuiHandler
{
 private:
   bool _inverse = false;
   double _alpha = 0;
   std::unique_ptr<Grid> _grid;
   std::vector<Cell> _cells;
 public:
   void setAlpha(double alpha);
   double getAlpha();
   void changeProblem(bool problem);
   bool getProblem();
   void setCells(std::vector<Cell> &cells);
   std::vector<Cell> getCells();
   std::unique_ptr<GravityModel> _model;
   ~GuiHandler();

};

extern GuiHandler GUIHandler;

struct Button 
{
   sf::RectangleShape rect;
   sf::Text text;
   std::function<void()> onClick;
   bool isContain(sf::Vector2f mousePos) 
   {
      return rect.getGlobalBounds().contains(mousePos);
   }
   
   void draw(sf::RenderWindow& window) 
   {
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
   Button _solveButton;
   Button _test1Button;
   Button _test2Button;
   Button _test3Button;
   Button _test4Button;
   Button _test5Button;
   Button _test6Button;
   std::vector<Cell> cells;
   Grid _grid;
   GProfileDraw gPlot;

 public:
   void Initialization();
   void RunMainWindow();
   ~MainWindow();

};


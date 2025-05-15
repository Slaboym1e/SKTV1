#include "Render.h"

GuiHandler GUIHandler;


void forwardButton_onClick()
{
   GUIHandler.changeProblem(false);
   GUIHandler._model->setCells(GUIHandler.getCells());
}

void inverseButton_onClick()
{
   GUIHandler.changeProblem(true);

   auto cells = GUIHandler._model->getCells();
   GUIHandler.setCells(cells);
   for(auto & cell: cells)
      cell.rho = 0;
   GUIHandler._model->setCells(cells);

}

void solveButton_onClick()
{
   if (GUIHandler.getProblem())
   {
      GUIHandler._model->solveInverseProblem(0.0, GUIHandler.getAlpha());
      auto tmp = GUIHandler._model->getCells();
      GUIHandler.setCells(tmp);
   }
   else
      GUIHandler._model->comcomputeGravityProfile(0.0);
}

void test1Button_onClick()
{  
   GUIHandler.setAlpha(0.0);
   std::vector<Cell> test1;
   test1.push_back({ 2000, -500, 1 });
   test1.push_back({ 2500, -500, 1 });
   test1.push_back({ 2000, -750, 1 });
   test1.push_back({ 2500, -750, 1 });
   GUIHandler._model->setCells(test1);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(test1);
}
void test2Button_onClick()
{
   GUIHandler.setAlpha(0.0);
   std::vector<Cell> test2;
   test2.push_back({ 2000, -500, 1 });
   test2.push_back({ 2500, -500, 1 });
   test2.push_back({ 2000, -750, 1 });
   test2.push_back({ 2500, -750, 1 });

   test2.push_back({ 1500, -250, 0 });
   test2.push_back({ 2000, -250, 0 });
   test2.push_back({ 2500, -250, 0 });
   test2.push_back({ 3000, -250, 0 });

   test2.push_back({ 1500, -500, 0 });
   test2.push_back({ 3000, -500, 0 });

   test2.push_back({ 1500, -750, 0 });
   test2.push_back({ 3000, -750, 0 });

   test2.push_back({ 1500, -1000, 0 });
   test2.push_back({ 2000, -1000, 0 });
   test2.push_back({ 2500, -1000, 0 });
   test2.push_back({ 3000, -1000, 0 });
   GUIHandler._model->setCells(test2);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(test2);
}
void test3Button_onClick()
{
   GUIHandler.setAlpha(0.0);
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;
   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix) 
      for (int iz = 0; iz < Nz; ++iz) 
      {
         double cx = x_start + ix * dx;
         double cz = z_start + iz * dz;
         gridCells.push_back({ cx, cz, 0  }); // начальная плотность 0
      }
   gridCells[5].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;

   GUIHandler._model->setCells(gridCells);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(gridCells);
}


void test4Button_onClick()
{
   GUIHandler.setAlpha(1e-5);
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;
   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix)
      for (int iz = 0; iz < Nz; ++iz)
      {
         double cx = x_start + ix * dx;
         double cz = z_start + iz * dz;
         gridCells.push_back({ cx, cz, 0 }); // начальная плотность 0
      }
   gridCells[5].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;

   GUIHandler._model->setCells(gridCells);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(gridCells);
}

void test5Button_onClick()
{
   GUIHandler.setAlpha(1e-7);
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;
   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix)
      for (int iz = 0; iz < Nz; ++iz)
      {
         double cx = x_start + ix * dx;
         double cz = z_start + iz * dz;
         gridCells.push_back({ cx, cz, 0 }); // начальная плотность 0
      }
   gridCells[5].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;

   GUIHandler._model->setCells(gridCells);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(gridCells);
}

void test6Button_onClick()
{
   GUIHandler.setAlpha(1e-14);
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;
   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix)
      for (int iz = 0; iz < Nz; ++iz)
      {
         double cx = x_start + ix * dx;
         double cz = z_start + iz * dz;
         gridCells.push_back({ cx, cz, 0 }); // начальная плотность 0
      }
   gridCells[5].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;

   GUIHandler._model->setCells(gridCells);
   GUIHandler.changeProblem(false);
   GUIHandler.setCells(gridCells);
}

void MainWindow::Initialization()
{

   if (!_font.loadFromFile("resources/ttt.otf")) 
      return;
   _forwardButton.rect.setSize(sf::Vector2f(200, 50));
   _forwardButton.rect.setPosition(50, 20);
   _forwardButton.rect.setFillColor(sf::Color(200, 200, 250));
   _forwardButton.rect.setOutlineColor(sf::Color::Black);
   _forwardButton.rect.setOutlineThickness(2);
   _forwardButton.text.setFont(_font);
   _forwardButton.text.setString("forward");
   _forwardButton.text.setCharacterSize(20);
   _forwardButton.text.setFillColor(sf::Color::Black);
   _forwardButton.text.setPosition(60, 30);
   _forwardButton.onClick = forwardButton_onClick;

   _inverseButton.rect.setSize(sf::Vector2f(200, 50));
   _inverseButton.rect.setPosition(300, 20);
   _inverseButton.rect.setFillColor(sf::Color(250, 200, 200));
   _inverseButton.rect.setOutlineColor(sf::Color::Black);
   _inverseButton.rect.setOutlineThickness(2);
   _inverseButton.text.setFont(_font);
   _inverseButton.text.setString("inverse");
   _inverseButton.text.setCharacterSize(20);
   _inverseButton.text.setFillColor(sf::Color::Black);
   _inverseButton.text.setPosition(310, 30);
   _inverseButton.onClick = inverseButton_onClick;

   _solveButton.rect.setSize(sf::Vector2f(200, 50));
   _solveButton.rect.setPosition(550, 20);
   _solveButton.rect.setFillColor(sf::Color(200, 200, 250));
   _solveButton.rect.setOutlineColor(sf::Color::Black);
   _solveButton.rect.setOutlineThickness(2);
   _solveButton.text.setFont(_font);
   _solveButton.text.setString("solve");
   _solveButton.text.setCharacterSize(20);
   _solveButton.text.setFillColor(sf::Color::Black);
   _solveButton.text.setPosition(560, 30);
   _solveButton.onClick = solveButton_onClick;

   _test1Button.rect.setSize(sf::Vector2f(200, 50));
   _test1Button.rect.setPosition(800, 20);
   _test1Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test1Button.rect.setOutlineColor(sf::Color::Black);
   _test1Button.rect.setOutlineThickness(2);
   _test1Button.text.setFont(_font);
   _test1Button.text.setString("test1");
   _test1Button.text.setCharacterSize(20);
   _test1Button.text.setFillColor(sf::Color::Black);
   _test1Button.text.setPosition(810, 30);
   _test1Button.onClick = test1Button_onClick;

   _test2Button.rect.setSize(sf::Vector2f(200, 50));
   _test2Button.rect.setPosition(1050, 20);
   _test2Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test2Button.rect.setOutlineColor(sf::Color::Black);
   _test2Button.rect.setOutlineThickness(2);
   _test2Button.text.setFont(_font);
   _test2Button.text.setString("test2");
   _test2Button.text.setCharacterSize(20);
   _test2Button.text.setFillColor(sf::Color::Black);
   _test2Button.text.setPosition(1060, 30);
   _test2Button.onClick = test2Button_onClick;

   _test3Button.rect.setSize(sf::Vector2f(200, 50));
   _test3Button.rect.setPosition(1050, 120);
   _test3Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test3Button.rect.setOutlineColor(sf::Color::Black);
   _test3Button.rect.setOutlineThickness(2);
   _test3Button.text.setFont(_font);
   _test3Button.text.setString("test3");
   _test3Button.text.setCharacterSize(20);
   _test3Button.text.setFillColor(sf::Color::Black);
   _test3Button.text.setPosition(1060, 130);
   _test3Button.onClick = test3Button_onClick;

   _test4Button.rect.setSize(sf::Vector2f(200, 50));
   _test4Button.rect.setPosition(1050, 220);
   _test4Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test4Button.rect.setOutlineColor(sf::Color::Black);
   _test4Button.rect.setOutlineThickness(2);
   _test4Button.text.setFont(_font);
   _test4Button.text.setString("test4");
   _test4Button.text.setCharacterSize(20);
   _test4Button.text.setFillColor(sf::Color::Black);
   _test4Button.text.setPosition(1060, 230);
   _test4Button.onClick = test4Button_onClick;

   _test5Button.rect.setSize(sf::Vector2f(200, 50));
   _test5Button.rect.setPosition(1050, 320);
   _test5Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test5Button.rect.setOutlineColor(sf::Color::Black);
   _test5Button.rect.setOutlineThickness(2);
   _test5Button.text.setFont(_font);
   _test5Button.text.setString("test5");
   _test5Button.text.setCharacterSize(20);
   _test5Button.text.setFillColor(sf::Color::Black);
   _test5Button.text.setPosition(1060, 330);
   _test5Button.onClick = test5Button_onClick;

   _test6Button.rect.setSize(sf::Vector2f(200, 50));
   _test6Button.rect.setPosition(1050, 420);
   _test6Button.rect.setFillColor(sf::Color(200, 200, 250));
   _test6Button.rect.setOutlineColor(sf::Color::Black);
   _test6Button.rect.setOutlineThickness(2);
   _test6Button.text.setFont(_font);
   _test6Button.text.setString("test6");
   _test6Button.text.setCharacterSize(20);
   _test6Button.text.setFillColor(sf::Color::Black);
   _test6Button.text.setPosition(1060, 430);
   _test6Button.onClick = test6Button_onClick;
}

void MainWindow::RunMainWindow()
{
   sf::RenderWindow window(sf::VideoMode(_windowWidth, _windowHeight), "Gravity Modeling - Regular Grid");
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;

   GravityModel model(abs(dx * dz)); // объем ячейки
   
   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix) {
      for (int iz = 0; iz < Nz; ++iz) {
         double cx = x_start + ix  * dx;
         double cz = z_start + iz * dz;
         gridCells.push_back({ cx, cz, 0 /*dis(gen)*/ }); // начальная плотность 0
      }
   }





   gridCells[5].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;



   std::vector<Cell> test1;
   test1.push_back({ 2000, -500, 1 });
   test1.push_back({ 2500, -500, 1 });
   test1.push_back({ 2000, -750, 1 });
   test1.push_back({ 2500, -750, 1 });

   std::vector<Cell> test2;
   test2.push_back({ 2000, -500, 1 });
   test2.push_back({ 2500, -500, 1 });
   test2.push_back({ 2000, -750, 1 });
   test2.push_back({ 2500, -750, 1 });

   test2.push_back({ 1500, -250, 0 });
   test2.push_back({ 2000, -250, 0 });
   test2.push_back({ 2500, -250, 0 });
   test2.push_back({ 3000, -250, 0 });

   test2.push_back({ 1500, -500, 0 });
   test2.push_back({ 3000, -500, 0 });

   test2.push_back({ 1500, -750, 0 });
   test2.push_back({ 3000, -750, 0 });

   test2.push_back({ 1500, -1000, 0 });
   test2.push_back({ 2000, -1000, 0 });
   test2.push_back({ 2500, -1000, 0 });
   test2.push_back({ 3000, -1000, 0 });

   model.setCells(gridCells);
   _grid.setCells(gridCells);
   GUIHandler.setCells(gridCells);
   std::vector<double> xProfile(800);
   for (int i = 0; i < 800; ++i)
      xProfile[i] = -2000 + i * 10;
   gPlot.setXProfile(xProfile);
   model.setXProfile(xProfile);
   GUIHandler._model.reset(&model);
   std::vector<double> gProfile;
   bool gComputed = false;
   bool solvedInverse = false;

   while (window.isOpen()) 
   {
      model = *GUIHandler._model.get();
      _grid.setCells(model.getCells());
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed)
            window.close();
         if (event.type == sf::Event::MouseButtonPressed) 
         {
            if (event.mouseButton.button == sf::Mouse::Left) 
            {
               sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

               if (_forwardButton.isContain(mousePos)) 
               {
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.onClick();
                  _grid.kindProblem(GUIHandler.getProblem());
               }
               if (_inverseButton.isContain(mousePos) && gComputed)
               {
                  gComputed = false;
                  std::vector<double> zeros(0);
                  gPlot.setGProfile(zeros);
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 255));
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 50));
                  _inverseButton.onClick();
                  
                  _grid.kindProblem(GUIHandler.getProblem());

               }
               if (_solveButton.isContain(mousePos))
               {
                  _solveButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                
                  _solveButton.onClick();
                  if (!GUIHandler.getProblem())
                  {
                     gComputed = true;
                     gPlot.setGProfile(GUIHandler._model->getGProfile());
                  }
                  _grid.kindProblem(GUIHandler.getProblem());

               }
               if (_test1Button.isContain(mousePos))
               {
                  _test1Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test1Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
               if (_test2Button.isContain(mousePos))
               {
                  _test2Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test2Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
               if (_test3Button.isContain(mousePos))
               {
                  _test3Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test3Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
               if (_test4Button.isContain(mousePos))
               {
                  _test4Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test4Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
               if (_test5Button.isContain(mousePos))
               {
                  _test5Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test5Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
               if (_test6Button.isContain(mousePos))
               {
                  _test6Button.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _test6Button.onClick();
                  _inverseButton.rect.setFillColor(sf::Color(250, 200, 200, 255));
                  _forwardButton.rect.setFillColor(sf::Color(200, 200, 250, 50));
                  _grid.kindProblem(GUIHandler.getProblem());
                  gComputed = false;
               }
            }
         }
         else if (event.type == sf::Event::MouseButtonReleased)
         {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
               _solveButton.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test1Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test2Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test3Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test4Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test5Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
               _test6Button.rect.setFillColor(sf::Color(200, 200, 250, 255));
            }
            
         }
      }

      window.clear(sf::Color::White);

      // Кнопки
      _test1Button.draw(window);
      _forwardButton.draw(window);
      _inverseButton.draw(window);
      _solveButton.draw(window);
      _test2Button.draw(window);
      _test3Button.draw(window);
      _test4Button.draw(window);
      _test5Button.draw(window);
      _test6Button.draw(window);
      // Нарисовать ?g профиль
      if (gComputed) {

      }
      gPlot.draw(window);
      _grid.draw(window);

      window.display();
   }
}

MainWindow::~MainWindow()
{
   GUIHandler.~GuiHandler();
}

void GuiHandler::setAlpha(double alpha)
{
   _alpha = alpha;
}

double GuiHandler::getAlpha()
{
   return _alpha;
}

void GuiHandler::changeProblem(bool problem)
{
   _inverse = problem;
}

bool GuiHandler::getProblem()
{
   return _inverse;
}

void GuiHandler::setCells(std::vector<Cell>& cells)
{
   _cells = cells;
}

std::vector<Cell> GuiHandler::getCells()
{
   return _cells;
}

GuiHandler::~GuiHandler()
{
   _model.release();
}



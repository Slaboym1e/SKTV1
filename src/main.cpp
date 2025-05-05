

#include <SFML/Graphics.hpp>
#include "GravityModel.h"
#include <vector>
#include <iostream>

#include <random>

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

int main() {
   const int windowWidth = 1400;
   const int windowHeight = 900;
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0.0, 0.1);
   sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Gravity Modeling - Regular Grid");

   sf::Font font;
   if (!font.loadFromFile("resources/ttt.otf")) {
      std::cerr << "Font loading failed!" << std::endl;
      return -1;
   }

   // Кнопки
   Button forwardButton;
   forwardButton.rect.setSize(sf::Vector2f(200, 50));
   forwardButton.rect.setPosition(50, 20);
   forwardButton.rect.setFillColor(sf::Color(200, 200, 250));
   forwardButton.rect.setOutlineColor(sf::Color::Black);
   forwardButton.rect.setOutlineThickness(2);
   forwardButton.text.setFont(font);
   forwardButton.text.setString("forward");
   forwardButton.text.setCharacterSize(20);
   forwardButton.text.setFillColor(sf::Color::Black);
   forwardButton.text.setPosition(60, 30);

   Button inverseButton;
   inverseButton.rect.setSize(sf::Vector2f(200, 50));
   inverseButton.rect.setPosition(300, 20);
   inverseButton.rect.setFillColor(sf::Color(250, 200, 200));
   inverseButton.rect.setOutlineColor(sf::Color::Black);
   inverseButton.rect.setOutlineThickness(2);
   inverseButton.text.setFont(font);
   inverseButton.text.setString("inverse");
   inverseButton.text.setCharacterSize(20);
   inverseButton.text.setFillColor(sf::Color::Black);
   inverseButton.text.setPosition(310, 30);

   // Построение регулярной сетки
  // Построение сетки маленького размера
   const int Nx = 9;
   const int Nz = 6;
   const double x_start = 0.0;
   const double x_end = 4500;
   const double z_start = 0.0;
   const double z_end = -1500.0;
   const double dx = (x_end - x_start) / Nx;
   const double dz = (z_end - z_start) / Nz;

   GravityModel model(dx * dz * 1000.0); // объем ячейки

   std::vector<Cell> gridCells;

   for (int ix = 0; ix < Nx; ++ix) {
      for (int iz = 0; iz < Nz; ++iz) {
         double cx = x_start + (ix + 0.5) * dx;
         double cz = z_start + (iz + 0.5) * dz;
         gridCells.push_back({ cx, cz, dis(gen)}); // начальная плотность 0
      }
   }

   //// ЗАДАЁМ аномалию в центре
   //for (auto& cell : gridCells) {
   //   if (cell.x >= 1500 && cell.x <= 3000 && cell.z >= -1500 && cell.z <= -1000) {
   //      cell.rho = 1.0;
   //   }
   //   else {
   //      cell.rho = 0.0;
   //   }
   //}


   gridCells[4].rho = 1;
   gridCells[5].rho = 1;
   gridCells[9].rho = 1;
   gridCells[10].rho = 1;
   gridCells[14].rho = 1;
   gridCells[15].rho = 1;
   gridCells[20].rho = 1;
   gridCells[21].rho = 1;
   gridCells[26].rho = 1;
   gridCells[27].rho = 1;
   gridCells[28].rho = 1;
   gridCells[29].rho = 1;
   gridCells[32].rho = 1;
   gridCells[33].rho = 1;
   gridCells[31].rho = 1;
   gridCells[30].rho = 1;

   
   std::vector<Cell> test1;
   test1.push_back({ 2000, -500, 2});
   test1.push_back({ 2500, -500, 1 });
   test1.push_back({ 2000, -1000, 4 });
   test1.push_back({ 2500, -1000, 1 });

   std::vector<Cell> test2;
   test2.push_back({ 2000, -500, 1 });
   test2.push_back({ 2500, -500, 1 });
   test2.push_back({ 2000, -1000, 1 });
   test2.push_back({ 2500, -1000, 1 });

   test2.push_back({ 1500, -150, 0 });
   test2.push_back({ 2000, -150, 0 });
   test2.push_back({ 2500, -150, 0 });
   test2.push_back({ 3000, -150, 0 });

   test2.push_back({ 1500, -500, 0 });
   test2.push_back({ 3000, -500, 0 });

   test2.push_back({ 1500, -1000, 0 });
   test2.push_back({ 3000, -1000, 0 });

   test2.push_back({ 1500, -1500, 0 });
   test2.push_back({ 2000, -1500, 0 });
   test2.push_back({ 2500, -1500, 0 });
   test2.push_back({ 3000, -1500, 0 });

   model.setCells(test2);

   std::vector<double> xProfile(800);
   for (int i = 0; i < 800; ++i)
      xProfile[i] = -2000 + i * 10;

   std::vector<double> gProfile;
   bool gComputed = false;
   bool solvedInverse = false;

   while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed)
            window.close();
         if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
               sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

               if (forwardButton.isClicked(mousePos)) {
                  gProfile = model.comcomputeGravityProfile(xProfile, 0.0);
                  gComputed = true;
                  solvedInverse = false;
               }
               if (inverseButton.isClicked(mousePos) && gComputed) 
               {
                  auto tmp = model.getCells();
                  for(auto &cell : tmp)
                     cell.rho = 0;
                  model.setCells(tmp);
                  model.solveInverseProblem(gProfile, xProfile, 0.0, 1e-28 );
                  solvedInverse = true;
               }
            }
         }
      }

      window.clear(sf::Color::White);

      // Кнопки
      forwardButton.draw(window);
      inverseButton.draw(window);

      // Нарисовать Δg профиль
      if (gComputed) {
         sf::VertexArray gPlot(sf::LinesStrip, xProfile.size());
         for (size_t i = 0; i < xProfile.size(); ++i) {
            double gx = 100 + (xProfile[i] + 2000) * 0.1;
            double gy = 400 + gProfile[i] * 2e10;
            gPlot[i].position = sf::Vector2f(gx, gy);
            gPlot[i].color = sf::Color::Blue;
         }
         window.draw(gPlot);
      }

      // Нарисовать сетку ячеек
      for (const auto& cell : model.getCells()) {
         sf::RectangleShape rect(sf::Vector2f(dx * 0.1, -dz * 0.1));
         rect.setPosition(100 + (cell.x - dx / 2 - x_start) * 0.1, 600 + (-cell.z + dz / 2 + z_end) * 0.1);

         if (solvedInverse) {
            int color = std::min(255, std::max(0, int(128 + cell.rho * 127)));
            rect.setFillColor(sf::Color(color, 100, 255 - color));
         }
         else {
            rect.setFillColor(sf::Color(200, 200, 200));
         }
         rect.setOutlineColor(sf::Color::Black);
         rect.setOutlineThickness(1);
         window.draw(rect);

         // ПОДПИСЬ ПЛОТНОСТИ в центре ячейки
         sf::Text densityText;
         densityText.setFont(font);
         char buffer[16];
         snprintf(buffer, sizeof(buffer), "%.2f", cell.rho); // две цифры после запятой
         densityText.setString(buffer);
         densityText.setCharacterSize(12);
         densityText.setFillColor(sf::Color::Black);
         // Центрировать текст в ячейке
         densityText.setPosition(
            rect.getPosition().x + rect.getSize().x / 4,
            rect.getPosition().y + rect.getSize().y / 4
         );
         window.draw(densityText);
      }
      window.display();
   }

   return 0;
}
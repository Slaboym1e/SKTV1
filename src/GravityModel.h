#pragma once

#include<vector>
#include"Cell.h"

class GravityModel
{
 public:
   GravityModel();
   GravityModel(double cellVolume);
   void setXProfile(std::vector<double>& xProfile);
   void setGProfile(std::vector<double> &gProfile);
   void setCells(const std::vector<Cell>&cells);
   std::vector<double> comcomputeGravityProfile(const double &zObs);
   std::vector<double> solveInverseProblem(double zObs, double alpha);
   
   double computeFunctionalValue(const std::vector<double>& gObserved, const std::vector<double>& xProfile, double zObs, const std::vector<std::vector<double>>& C, double alpha);
   
   const std::vector<Cell>& getCells() const {return _cells;}
   const std::vector<double> &getGProfile() const {return _gProfile; }
   void setCellVolume(const double &cellVolume);



private:
   double _G;
   double _cellVolume;
   std::vector<Cell> _cells;
   std::vector<double> _xProfile;
   std::vector<double> _gProfile;





   std::vector<std::vector<double>> buildRegularizationMatrixC(int Nx, int Nz) 
   {
      Nx = 9;
      Nz = 6;
      int nCells = Nx * Nz;

      // C будет sparse-матрицей, но для простоты делаем её полной
      std::vector<std::vector<double>> C;

      // Разности по X (горизонтали)
      for (int iz = 0; iz < Nz; ++iz) {
         for (int ix = 0; ix < Nx - 1; ++ix) {
            std::vector<double> row(nCells, 0.0);
            int current = iz * Nx + ix;
            int neighbor = iz * Nx + (ix + 1);
            row[current] = 1.0;
            row[neighbor] = -1.0;
            C.push_back(row);
         }
      }

      // Разности по Z (глубине)
      for (int iz = 0; iz < Nz - 1; ++iz) {
         for (int ix = 0; ix < Nx; ++ix) {
            std::vector<double> row(nCells, 0.0);
            int current = iz * Nx + ix;
            int neighbor = (iz + 1) * Nx + ix;
            row[current] = 1.0;
            row[neighbor] = -1.0;
            C.push_back(row);
         }
      }

      return C;
   }
   std::vector<std::vector<double>> computeCtC(const std::vector<std::vector<double>>& C, int nCells) {
      std::vector<std::vector<double>> CtC(nCells, std::vector<double>(nCells, 0.0));

      for (const auto& row : C) {
         for (int i = 0; i < nCells; ++i) {
            if (row[i] == 0.0) continue;
            for (int j = 0; j < nCells; ++j) {
               if (row[j] == 0.0) continue;
               CtC[i][j] += row[i] * row[j];
            }
         }
      }

      return CtC;
   }
};
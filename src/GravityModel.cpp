#include "GravityModel.h"

GravityModel::GravityModel()
{
}

GravityModel::GravityModel(double cellVolume)
   : _G(6.67430e-11), _cellVolume(cellVolume) {}

void GravityModel::setCells(const std::vector<Cell>& cells)
{
   _cells = cells;
}

std::vector<double> GravityModel::comcomputeGravityProfile(const std::vector<double>& xProfile, const double& zObs)
{
   std::vector<double> gProfile(xProfile.size(), 0.0);
   for(const auto & cell: _cells)
      for (size_t i = 0; i < xProfile.size(); i++)
      {
         double dx = xProfile[i] - cell.x;
         double dz = zObs - cell.z;
         double r = sqrt(dx * dx + dz* dz);
         if(r > 0.0)
            gProfile[i] += _G * cell.rho * _cellVolume * dz / (4 * 3.1415692 * r * r *r) ;
      }
   return gProfile;
}

std::vector<double> GravityModel::solveInverseProblem(const std::vector<double>& gObserved, const std::vector<double>& xProfile, double zObs, double alpha)
{
   size_t nObs = xProfile.size();   // количество наблюдений
   size_t nCells = _cells.size();   // количество €чеек

   // —троим матрицу G (nObs ? nCells)
   std::vector<std::vector<double>> Gmat(nObs, std::vector<double>(nCells, 0.0));

   for (size_t q = 0; q < nCells; ++q) {
      for (size_t i = 0; i < nObs; ++i) {
         double dx = xProfile[i] - _cells[q].x;
         double dz = zObs - _cells[q].z;
         double r =sqrt(dx * dx + dz * dz);
         if (r > 0.0)
            Gmat[i][q] = _G * _cellVolume * dz / (4 * 3.1415692 * r * r * r); // пересчЄт в м√ал
      }
   }

   // ‘ормируем матрицу A = G^T G + alpha * I и вектор b = G^T d
   std::vector<std::vector<double>> A(nCells, std::vector<double>(nCells, 0.0));
   std::vector<double> b(nCells, 0.0);

   for (size_t q = 0; q < nCells; ++q) {
      for (size_t s = 0; s < nCells; ++s) {
         for (size_t i = 0; i < nObs; ++i) {
            A[q][s] += Gmat[i][q] * Gmat[i][s];
         }
      }
      A[q][q] += alpha; // регул€ризаци€
      for (size_t i = 0; i < nObs; ++i) {
         b[q] += Gmat[i][q] * gObserved[i];
      }
   }


   std::vector<double> rho(nCells, 0.0);

   // ѕр€мой ход
   for (size_t i = 0; i < nCells; ++i) {
      double pivot = A[i][i];
      if (std::abs(pivot) < 1e-20) {
         continue;
      }
      for (size_t j = i; j < nCells; ++j)
         A[i][j] /= pivot;
      b[i] /= pivot;

      for (size_t k = i + 1; k < nCells; ++k) {
         double factor = A[k][i];
         for (size_t j = i; j < nCells; ++j)
            A[k][j] -= factor * A[i][j];
         b[k] -= factor * b[i];
      }
   }

   // ќбратный ход
   for (int i = nCells - 1; i >= 0; --i) {
      rho[i] = b[i];
      for (size_t j = i + 1; j < nCells; ++j)
         rho[i] -= A[i][j] * rho[j];
   }

   for (size_t k = 0; k < nCells; ++k) {
      _cells[k].rho = rho[k];
   }

   return rho;
}

void GravityModel::setCellVolume(const double& cellVolume)
{
   _cellVolume = cellVolume;
}


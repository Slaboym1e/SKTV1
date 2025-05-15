#include "GravityModel.h"

GravityModel::GravityModel()
{
}

GravityModel::GravityModel(double cellVolume)
   : _G(6.67430), _cellVolume(cellVolume) {}

void GravityModel::setXProfile(std::vector<double>& xProfile)
{
   _xProfile = xProfile;
}

void GravityModel::setGProfile(std::vector<double>& gProfile)
{
   _gProfile = gProfile;
}

void GravityModel::setCells(const std::vector<Cell>& cells)
{
   _cells = cells;
}

std::vector<double> GravityModel::comcomputeGravityProfile(const double& zObs)
{
   std::vector<double> gProfile(_xProfile.size(), 0.0);
   _gProfile.clear();
   _gProfile.resize(_xProfile.size(), 0.0);
   for(const auto & cell: _cells)
      for (size_t i = 0; i < _xProfile.size(); i++)
      {
         double dx = _xProfile[i] - cell.x;
         double dz = zObs - cell.z;
         double r = sqrt(dx * dx + dz * dz);
         if(r > 0)
         {
            gProfile[i] += cell.rho * _cellVolume * dz / (4 * 3.1415926535 * r * r * r);
            _gProfile[i] += cell.rho * _cellVolume * dz / (4 * 3.1415926535 * r * r * r);
         }
      }
   return gProfile;
}

std::vector<double> GravityModel::solveInverseProblem(double zObs, double alpha)
{
   size_t nObs = _xProfile.size();   // количество наблюдений
   size_t nCells = _cells.size();   // количество ячеек

   std::vector<std::vector<double>> Gmat(nObs, std::vector<double>(nCells, 0.0));

   for (size_t q = 0; q < nCells; ++q) {
      for (size_t i = 0; i < nObs; ++i) {
         double dx = _xProfile[i] - _cells[q].x;
         double dz = zObs - _cells[q].z;
         double r =sqrt(dx * dx + dz * dz);
         if (r > 0.0)
            Gmat[i][q] = _cellVolume * dz / (4 * 3.1415926535 * r * r * r); 
      }
   }


   std::vector<std::vector<double>> A(nCells, std::vector<double>(nCells, 0.0));
   std::vector<double> b(nCells, 0.0);
   auto C = buildRegularizationMatrixC(9,6);
   auto CtC = computeCtC(C, nCells);
   for (size_t q = 0; q < nCells; ++q) 
   {
      for (size_t s = 0; s < nCells; ++s) 
      {
         for (size_t i = 0; i < nObs; ++i) 
            A[q][s] += Gmat[i][q] * Gmat[i][s];
         
      }
      A[q][q] += alpha; // регуляризация
      for (size_t i = 0; i < nObs; ++i) {
         b[q] += Gmat[i][q] * _gProfile[i];
      }
   }
   for(int i = 0; i < nCells; i++)
      for(int j = 0; j < nCells; j++)
         A[i][j] += alpha * CtC[i][j];


   std::vector<double> rho(nCells, 0.0);

   // Прямой ход
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

   // Обратный ход
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



double GravityModel::computeFunctionalValue(const std::vector<double>& gObserved, const std::vector<double>& xProfile, double zObs, const std::vector<std::vector<double>>& C, double alpha)
{
   size_t nObs = xProfile.size();
   size_t nCells = _cells.size();

   // 1. Считаем G * rho
   std::vector<double> gCalculated(nObs, 0.0);
   for (size_t i = 0; i < nObs; ++i) {
      for (size_t k = 0; k < nCells; ++k) {
         double dx = xProfile[i] - _cells[k].x;
         double dz = zObs - _cells[k].z;
         double r = sqrt(dx * dx + dz * dz);
         if (r > 0.0)
            gCalculated[i] += _cells[k].rho * _cellVolume * dz / (4 * 3.141569 * r * r * r) ; 
      }
   }

   // 2. Вычисляем невязку: ||G*rho - d||^2
   double misfit = 0.0;
   double sumTrue = 0;
   double sumCalc = 0;
   for (size_t i = 0; i < nObs; ++i) 
   {
      sumTrue += gObserved[i];
      sumCalc += gCalculated[i];
   }
   misfit = (sumTrue - sumCalc) * (sumTrue - sumCalc);
   //// 3. Вычисляем регуляризационное слагаемое: ||C*rho||^2
   //double regularization = 0.0;
   //for (const auto& row : C) {
   //   double sum = 0.0;
   //   for (size_t k = 0; k < nCells; ++k) {
   //      sum += row[k] * _cells[k].rho;
   //   }
   //   regularization += sum * sum;
   //}

   // 4. Полное значение функционала
   double functionalValue = misfit /*+ alpha * regularization*/;

   return functionalValue;
}




void GravityModel::setCellVolume(const double& cellVolume)
{
   _cellVolume = cellVolume;
}


#pragma once

#include<vector>

struct Cell 
{
   double x = 0, z = 0;
   double rho = 0;
};

class GravityModel
{
 public:
   GravityModel();
   GravityModel(double cellVolume);
   void setCells(const std::vector<Cell>&cells);
   std::vector<double> comcomputeGravityProfile(const std::vector<double> & xProfile, const double &zObs);
   std::vector<double> solveInverseProblem(const std::vector<double>& gObserved, const std::vector<double> &xProfile, double zObs, double alpha);
   
   const std::vector<Cell>& getCells() const {return _cells;}
   void setCellVolume(const double &cellVolume);
 private:
   double _G;
   double _cellVolume;
   std::vector<Cell> _cells;
};
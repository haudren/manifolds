#ifndef _PGS_SOLVER_OPTIONS_H_
#define _PGS_SOLVER_OPTIONS_H_

#include <pgsolver/solver/Filter.h>

namespace pgs
{
  enum eHessianUpdate { EXACT, BFGS, SR1 };
  enum eGlobalization { NONE, LINESEARCH, TRUSTREGION };
  enum eLineSearchType { FILTER };
  enum eTrustRegionType { };
  struct SolverOptions
  {
    int maxIter = 1000;
    double epsilon_P = 1e-6;
    double epsilon_D = 1e-6;
    double gammaFilter = 1e-6;
    Filter::eOption filterOpt = Filter::EXISTING;

    eHessianUpdate hessianUpdateMethod = BFGS; 
    eGlobalization globalizationMethod = LINESEARCH;
    eLineSearchType lineSearchMethod = FILTER;
  };
}
#endif //_PGS_SOLVER_OPTIONS_H_

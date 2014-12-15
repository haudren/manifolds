#include <iostream>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Core>

#include <pgsolver/manifolds/pgs_assert.h>
#include <pgsolver/manifolds/RealSpace.h>
#include <pgsolver/manifolds/SO3.h>
#include <pgsolver/manifolds/CartesianProduct.h>
#include <pgsolver/manifolds/Point.h>
#include <pgsolver/manifolds/ExpMapMatrix.h>
#include <pgsolver/manifolds/ReusableTemporaryMap.h>

#include <pgsolver/solver/Problem.h>
#include <pgsolver/solver/ExampleGeometricProblem.h>

using namespace pgs;

int main()
{
  std::cout << "Using: Eigen" << EIGEN_WORLD_VERSION << "." << EIGEN_MAJOR_VERSION <<"." << EIGEN_MINOR_VERSION<< std::endl;
  RealSpace R2(2);
  RealSpace R3(3);
  SO3<ExpMapMatrix> RotSpace;
  CartesianProduct R2R3R2(R2, R3);
  R2R3R2.multiply(R2);
  CartesianProduct SO3R2R3R2(RotSpace, R2R3R2);
  CartesianProduct SO3R2R3R2SO3(SO3R2R3R2, RotSpace);
  CartesianProduct R3SO3(R3, RotSpace);
  CartesianProduct R3SO3R3SO3(R3, RotSpace);
  R3SO3R3SO3.multiply(R3);
  R3SO3R3SO3.multiply(RotSpace);
  {
    ExampleGeometricProblem myProb;
    Eigen::VectorXd x0(3);
    x0 << 1,2,3;
    Eigen::VectorXd z0(3);
    z0 << 3,4,5;
    myProb.setX(myProb.M().createPoint(x0));
    myProb.setZ(z0);

    double obj = 0.0;
    Eigen::Matrix<double,1,3> objGrad;
    Eigen::Vector3d tangentLB;
    Eigen::Vector3d tangentUB;

    Eigen::VectorXd linCstr(1);
    Eigen::Matrix<double,1,3> linCstrDiff;
    Eigen::VectorXd linCstrLB(1);
    Eigen::VectorXd linCstrUB(1);

    Eigen::VectorXd NonLinCstr(1);
    Eigen::Matrix<double,1,3> NonLinCstrDiff;
    Eigen::VectorXd NonLinCstrLB(1);
    Eigen::VectorXd NonLinCstrUB(1);

    std::cout << "Evaluation of the problem" << std::endl;
    std::cout << "Given x=" << myProb.x() << std::endl;
    std::cout << "And z=" << myProb.z().transpose() << std::endl;
    std::cout << "x + z = " << myProb.x()+myProb.z() << std::endl;

    std::cout << std::endl << "Objective Function:" << std::endl;
    myProb.evalObj(obj);
    myProb.evalObjGrad(objGrad);
    std::cout << "f(phi_x(z))=" << obj << std::endl;
    std::cout << "grad_z(f(phi_x(z))=" << objGrad << std::endl;

    std::cout << std::endl << "Bounds:" << std::endl;
    myProb.getTangentLB(tangentLB);
    myProb.getTangentUB(tangentUB);
    std::cout << "[" << tangentLB.transpose() << "] < z < [" << tangentUB.transpose() << "]" << std::endl;

    std::cout << std::endl << "Linear Constraints:" << std::endl;
    myProb.evalLinCstr(linCstr, 0);
    myProb.evalLinCstrGrad(linCstrDiff, 0);
    myProb.getLinCstrLB(linCstrLB, 0);
    myProb.getLinCstrUB(linCstrUB, 0);
    std::cout << linCstrLB << " < linCstr = " << linCstr << " < " << linCstrUB << std::endl;
    std::cout << "gradlinCstr = " << linCstrDiff << std::endl;

    std::cout << std::endl << "NonLinear Constraints:" << std::endl;
    myProb.evalNonLinCstr(NonLinCstr, 0);
    myProb.evalNonLinCstrGrad(NonLinCstrDiff, 0);
    myProb.getNonLinCstrLB(NonLinCstrLB, 0);
    myProb.getNonLinCstrUB(NonLinCstrUB, 0);
    std::cout << NonLinCstrLB << " < NonLinCstr = " << NonLinCstr << " < " << NonLinCstrUB << std::endl;
    std::cout << "gradNonLinCstr = " << NonLinCstrDiff << std::endl;
  }
#ifdef _WIN32
  system("pause");
#endif
  return 0;
}


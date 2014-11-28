#include <iostream>
#include <stdexcept>
#include "RealSpace.h"
#include "SO3.h"
#include "CartesianProduct.h"
#include "Point.h"

using namespace pgs;
int main()
{
  RealSpace R3(3);
  RealSpace R2(2);
  SO3 RotSpace;
  //Point x = R3.createPoint();
  //Point y = R3.getIdentity();
  //std::cout << x[0].transpose() << std::endl;
  //std::cout << y[0].transpose() << std::endl;
  //x[0] = Eigen::Vector3d(3, 2, 1);
  //Point z = x(0);
  //Eigen::Vector3d p(1, 2, 3);
  //x.increment(p);
  //std::cout << x[0].transpose() << std::endl;
  //std::cout << z[0].transpose() << std::endl;

  CartesianProduct P(R2, R3);
  P.multiply(R2);
  CartesianProduct Q(P, RotSpace);
  Eigen::VectorXd val = Eigen::VectorXd::Ones(7);
  Eigen::VectorXd p = Eigen::VectorXd::LinSpaced(7, 0, 6);
  Point x = P.createPoint();
  Point y = P.getIdentity();
  Point R = Q.getIdentity();
  try
  {
    P.multiply(R3);
  }
  catch (std::runtime_error e)
  {
    std::cout << e.what() << std::endl;
  }
  Point z = P.createPoint(val);
  x[0] = Eigen::Vector2d(7, 6);
  x[1] = Eigen::Vector3d(5, 4, 3);
  x[2] = Eigen::Vector2d(2, 1);
  x.increment(p);
  std::cout << "x = \n" << x << std::endl;
  std::cout << "y = \n" << y << std::endl;
  std::cout << "y+p = \n" << y+p << std::endl;
  std::cout << "R = \n" << R << std::endl;
  std::cout << x.value().transpose() << std::endl;
  std::cout << y.value().transpose() << std::endl;
  std::cout << (y + p).value().transpose() << std::endl;
  return 0;
}

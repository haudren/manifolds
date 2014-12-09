#include <iostream>
#include <stdexcept>

#include <pgsolver/pgs_assert.h>
#include <pgsolver/RealSpace.h>
#include <pgsolver/Point.h>

#ifndef _WIN32
#define BOOST_TEST_MODULE PGSolver 
#endif

#include <boost/test/unit_test.hpp>

using namespace pgs;

BOOST_AUTO_TEST_CASE(RealSpaceConstructor)
{
  RealSpace R5(5);
  BOOST_CHECK_EQUAL(R5.dim(), 5);
  BOOST_CHECK_EQUAL(R5.representationDim(), 5);
  BOOST_CHECK_EQUAL(R5.numberOfSubmanifolds(), 1);
}

BOOST_AUTO_TEST_CASE(RealPointConstructor)
{
  RealSpace R3(3);
  Point x = R3.createPoint();
  Eigen::Vector3d vy;
  vy << 1,2,3;
  Point y = R3.createPoint(vy);
  BOOST_CHECK_EQUAL(x.value().size(), 3);
  BOOST_CHECK_EQUAL(y.value().size(), 3);
  BOOST_CHECK_EQUAL(y.value()[0], 1);
  BOOST_CHECK_EQUAL(y.value()[1], 2);
  BOOST_CHECK_EQUAL(y.value()[2], 3);
}

BOOST_AUTO_TEST_CASE(RealSpaceIdentity)
{
  RealSpace R3(3);
  Point x = R3.getIdentity();
  for(long i = 0; i < x.value().size(); ++i)
  {
    BOOST_CHECK_EQUAL(x.value()[i], 0);
  }
}

BOOST_AUTO_TEST_CASE(RealPointIncrement)
{
  //[XXX] shouldn't this test be in PointTest? Here we want to test plus(z,x,y);
  RealSpace R3(3);
  Point x = R3.getIdentity();
  Eigen::Vector3d vy;
  vy << 1,2,3;
  x.increment(vy);
  x.increment(vy);
  BOOST_CHECK_EQUAL(x.value().size(), 3);
  BOOST_CHECK_EQUAL(x.value()[0], 2);
  BOOST_CHECK_EQUAL(x.value()[1], 4);
  BOOST_CHECK_EQUAL(x.value()[2], 6);
}

BOOST_AUTO_TEST_CASE(RealPointAddition)
{
  //[XXX] shouldn't this test be in PointTest?
  RealSpace R3(3);
  Point y = R3.getIdentity();
  Eigen::Vector3d vy;
  vy << 1,2,3;
  y=y+vy+vy;
  BOOST_CHECK_EQUAL(y.value().size(), 3);
  BOOST_CHECK_EQUAL(y.value()[0], 2);
  BOOST_CHECK_EQUAL(y.value()[1], 4);
  BOOST_CHECK_EQUAL(y.value()[2], 6);
}

BOOST_AUTO_TEST_CASE(RealPointSubstraction)
{
  //[XXX] shouldn't this test be in PointTest? Here we want to test plus(z,x,y);
  RealSpace R3(3);
  Point x = R3.getIdentity();
  Eigen::Vector3d vy;
  vy << 1,2,3;
  x = x + vy;
  Point y = x + vy + vy;
  Eigen::Vector3d z = y-x; 
  BOOST_CHECK_EQUAL(z[0], 2);
  BOOST_CHECK_EQUAL(z[1], 4);
  BOOST_CHECK_EQUAL(z[2], 6);
}

BOOST_AUTO_TEST_CASE(RealPointInvMap)
{
  RealSpace Space(7);
  Point x = Space.getIdentity();
  Eigen::VectorXd vy = Eigen::VectorXd::Random(Space.dim());;
  x = x + vy;
  Eigen::VectorXd z(Space.dim());
  Space.invMap(z, x.value()); 
  BOOST_CHECK(z.isApprox(vy));
}

BOOST_AUTO_TEST_CASE(RealPointDiff)
{
  RealSpace R7(7);
  Eigen::MatrixXd J;
  Point x = R7.createPoint();
  J = R7.diffMap(x.value());
  BOOST_CHECK(J.isIdentity());
}

BOOST_AUTO_TEST_CASE(RealApplyDiff)
{
  int c = 5;
  RealSpace Space(7);
  Index dim = Space.dim();
  Index repDim = Space.representationDim();
  Eigen::MatrixXd Jf = Eigen::MatrixXd::Random(c,repDim);
  Point x = Space.getIdentity();
  x.increment(Eigen::VectorXd::Random(dim));
  Eigen::MatrixXd expectedRes;
  expectedRes = Jf*Space.diffMap(x.value());
  Eigen::MatrixXd J(c,dim);
  Space.applyDiffMap(J, Jf, x.value());
  BOOST_CHECK(expectedRes.isApprox(J));
}

//BOOST_AUTO_TEST_CASE(RealApplyDiffGuaranteedResultTest)
//{
//  Index c = 3;
//  RealSpace Space(7);
//  Index dim = Space.dim();
//  Index repDim = Space.representationDim();
//  Eigen::MatrixXd Jf = Eigen::MatrixXd::Random(c,repDim);
//  Eigen::MatrixXd Jres = Eigen::MatrixXd::Random(c,dim);
//  Point x = Space.getIdentity();
//  Space.applyDiffMap(Jres, Jf, x.value());
//
//  for (int i = 0; i<dim+1; ++i)
//  {
//    Eigen::MatrixXd G = Eigen::MatrixXd::Zero(c,repDim+dim);
//    G.middleCols(dim,repDim) = Jf;
//    Eigen::Map<Eigen::MatrixXd> Gf(G.data()+dim*c,c,repDim);
//    Eigen::Map<Eigen::MatrixXd> Gres(G.data()+i*c,c,dim);
//    Space.applyDiffMap(Gres,Gf,x.value());
//    BOOST_CHECK(Jres.isApprox(Gres));
//  }
//}

BOOST_AUTO_TEST_CASE(RealApplyInvDiff)
{
  int c = 5;
  RealSpace Space(7);
  Index dim = Space.dim();
  Index repDim = Space.representationDim();
  Eigen::MatrixXd Jf = Eigen::MatrixXd::Random(c,dim);
  Point x = Space.getIdentity();
  x.increment(Eigen::VectorXd::Random(dim));
  Eigen::MatrixXd expectedRes;
  expectedRes = Jf*Space.diffInvMap(x.value());
  Eigen::MatrixXd J(c,repDim);
  Space.applyDiffInvMap(J, Jf, x.value());
  BOOST_CHECK(expectedRes.isApprox(J));
}

BOOST_AUTO_TEST_CASE(RealNoAllocation)
{
  //We only test here that the operations on the manifold do not create
  //temporary. Passing arguments that are not recognize by the Eigen::Ref will
  //create temporaries, but this is the user's fault.
  RealSpace R(4);
  Eigen::VectorXd x = Eigen::VectorXd::Random(4);
  Eigen::VectorXd y = Eigen::VectorXd::Random(4);
  Eigen::VectorXd z(4);
  Eigen::MatrixXd J0 = Eigen::MatrixXd::Random(3, 4);
  Eigen::MatrixXd J1(3, 4);
  Eigen::MatrixXd J2(3, 4);

  Eigen::internal::set_is_malloc_allowed(false);
  {
    R.plus(z, x, y);
    R.minus(z, x, y);
    R.invMap(z, x);
    R.applyDiffMap(J1, J0, x);
    R.applyDiffInvMap(J2, J0, x);
  }
  Eigen::internal::set_is_malloc_allowed(true);
}

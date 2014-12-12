#ifndef _PGS_PROBLEM_H_
#define _PGS_PROBLEM_H_

#include <iostream>
#include <Eigen/Core>

#include <pgsolver/manifolds/defs.h>
#include <pgsolver/manifolds/Point.h>
#include <pgsolver/manifolds/Manifold.h>

namespace pgs
{
  class Problem
  {
    public:
      /// \brief Default Constructor
      Problem(Manifold& manifold);
      /// \brief Constructor that sets x
      Problem(Manifold& manifold, const Point& x);
      
      /// \brief Sets new value for x_
      void setX(const Point& x);
      /// \brief Sets new value for z_
      void setZ(const ConstRefVec& z);

      /// \brief Gets current x_ value
      const Point& x() const;
      /// \brief Gets current z_ value
      const Eigen::VectorXd& z() const;
      
      /// \brief Get Upper Bounds on the variable
      virtual void getUB(RefVec out) const = 0;
      /// \brief Get Lower Bounds on the variable
      virtual void getLB(RefVec out) const = 0;

      /// \brief Get Constraints Lower Bounds
      virtual void getCstrLB(RefVec out, size_t i) const = 0;
      /// \brief Get Constraints Upper Bounds
      virtual void getCstrUB(RefVec out, size_t i) const = 0;

      /// \brief Evaluate Objective Function at point
      //\f$\phi_x^{\mathcal{M}}(z)\f$
      virtual void evalObj(RefVec out) const = 0;
      /// \brief Evaluate Gradient of Objective Function at point
      //\f$x\f$
      virtual void evalObjGrad(RefVec out) const = 0;

      /// \brief Evaluate Linear Constraints Index i at point
      //\f$\phi_x^{\mathcal{M}}(z)\f$
      virtual void evalLinCstr(RefVec out, size_t i) const = 0;
      /// \brief Evaluate Gradient of Linear Constraints Index i\n
      /// They are constants
      virtual void evalLinCstrGrad(RefVec out, size_t i) const = 0;

      /// \brief Evaluate NonLinear Constraints Index i at point
      //\f$\phi_x^{\mathcal{M}}(z)\f$
      virtual void evalNonLinCstr(RefVec out, size_t i) const = 0;
      /// \brief Evaluate Gradient of NonLinear Constraints Index i at point
      //\f$x\f$
      virtual void evalNonLinCstrGrad(RefVec out, size_t i) const = 0;

    protected:
      /// \brief Updates the problem for a new value of X
      virtual void broadcastXIsNew();
      /// \brief Updates the problem for a new value of Z
      virtual void broadcastZIsNew();

    protected:
      /// \brief Manifold on which the problem is defined
      Manifold& M_;

    private:
      /// \brief Current zero point of the map
      Point x_;
      /// \brief Current tangent vector \f$ z \in T_x\mathcal{M}\f$
      Eigen::VectorXd z_;
  };
}

#endif //_PGS_PROBLEM_H_

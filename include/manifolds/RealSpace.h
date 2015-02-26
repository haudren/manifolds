#ifndef _MANIFOLDS_REAL_SPACE_H_
#define _MANIFOLDS_REAL_SPACE_H_

#include <iostream>
#include <manifolds/defs.h>
#include <manifolds/Manifold.h>

namespace pgs
{
  /// \brief Manifold representing the space of real numbers of dimension n
  /// \f$\mathbb{R}^n\f$
  class MANIFOLDS_API RealSpace: public Manifold
  {
  public:
    /// \brief Constructor
    /// \param n the dimension of the realspace \f$\mathbb{R}^n\f$
    RealSpace(Index n);

    virtual size_t numberOfSubmanifolds() const;
    virtual const Manifold& operator()(size_t i) const;

    virtual std::string toString(const ConstRefVec& val, const std::string& prefix = "") const;

  protected:
    //map operations
    virtual bool isValidInit_(const Eigen::VectorXd& ) const;
    virtual void plus_(RefVec out, const ConstRefVec& x, const ConstRefVec& v) const;
    virtual void minus_(RefVec out, const ConstRefVec& x, const ConstRefVec& y) const;
    virtual void invMap_(RefVec out, const ConstRefVec& x) const;
    virtual void setIdentity_(RefVec out) const;
    virtual Eigen::MatrixXd diffMap_(const ConstRefVec& x) const;
    virtual void applyDiffMap_(RefMat out, const ConstRefMat& in, const ConstRefVec& x) const;
    virtual Eigen::MatrixXd diffInvMap_(const ConstRefVec& x) const;
    virtual void applyDiffInvMap_(RefMat out, const ConstRefMat& in, const ConstRefVec& x) const;
    virtual void applyTransport_(RefMat out, const ConstRefMat& in, const ConstRefVec& x, const ConstRefVec& v) const;
    virtual void applyInvTransport_(RefMat out, const ConstRefMat& in, const ConstRefVec& x, const ConstRefVec& v) const;
  
    virtual void tangentConstraint_(RefMat out, const ConstRefVec& x) const;
    virtual bool isInTxM_(const ConstRefVec& x, const ConstRefVec& v) const;
    virtual void forceOnTxM_(RefVec out, const ConstRefVec& in, const ConstRefVec&x) const;

  };
}

#endif //_MANIFOLDS_REAL_SPACE_H_


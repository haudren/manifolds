#include <stdexcept>
#include <manifolds/Manifold.h>
#include <manifolds/pgs_assert.h>

namespace pgs
{
  Manifold::Manifold(Index dimension, Index tangentDimension, Index representationDimension)
    : dimension_(dimension)
    , tangentDim_(tangentDimension)
    , representationDim_(representationDimension)
    , lock_(false)
  {
    pgs_assert(0 <= dimension && "Negative dimension not accepted");
    pgs_assert(dimension <= tangentDimension);
    pgs_assert(tangentDimension <= representationDimension);
  }
  
  Manifold::~Manifold()
  {
  }

  Point Manifold::createPoint() const
  {
    pgs_assert(isValid() || seeMessageAbove());
    lock();
    return Point(*this);
  }

  Point Manifold::createPoint(const ConstRefVec& val) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    if (isInM(val))
    {
      lock();
      return Point(*this, val);
    }
    else
    {
      throw std::runtime_error("Bad Point Initialization");
    }
  }

  bool Manifold::isInM(const Eigen::VectorXd& val) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(val.size() == representationDim());
    return isInM_(val);
  }

  Point Manifold::getZero() const
  {
    pgs_assert(isValid() || seeMessageAbove());
    lock();
    Eigen::VectorXd id(representationDim_);
    setZero(id);
    return Point(*this, id);
  }

  Index Manifold::dim() const
  {
    pgs_assert(isValid() || seeMessageAbove());
    return dimension_;
  }

  Index Manifold::tangentDim() const
  {
    pgs_assert(isValid() || seeMessageAbove());
    return tangentDim_;
  }

  Index Manifold::representationDim() const
  {
    pgs_assert(isValid() || seeMessageAbove());
    return representationDim_;
  }

  void Manifold::plus(RefVec out, const ConstRefVec& x, const ConstRefVec& v) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.size() == representationDim_);
    pgs_assert(x.size() == representationDim_);
    pgs_assert(v.size() == tangentDim_);
    pgs_assert(isInTxM(x, v));
    plus_(out, x, v);
  }

  void Manifold::minus(RefVec out, const ConstRefVec& x, const ConstRefVec& y) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.size() == tangentDim_);
    pgs_assert(x.size() == representationDim_);
    pgs_assert(y.size() == representationDim_);
    minus_(out, x, y);
  }

  void Manifold::invMap(RefVec out, const ConstRefVec& x) const
  {
    pgs_assert(out.size() == tangentDim_);
    pgs_assert(x.size() == representationDim_);
    invMap_(out, x);
  }

  Eigen::MatrixXd Manifold::diffMap(const ConstRefVec& x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(x.size() == representationDim_);
    return diffMap_(x);
  }

  void Manifold::applyDiffMap(
      RefMat out, const ConstRefMat& in, const ConstRefVec& x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(in.cols() == representationDim_);
    pgs_assert(out.cols() == tangentDim_);
    pgs_assert(in.rows() == out.rows());
    pgs_assert(x.size() == representationDim_);
    applyDiffMap_(out, in, x);
  }

  Eigen::MatrixXd Manifold::diffInvMap(const ConstRefVec& x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(x.size() == representationDim_);
    return diffInvMap_(x);
  }

  void Manifold::applyDiffInvMap(
      RefMat out, const ConstRefMat& in, const ConstRefVec& x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.cols() == representationDim_);
    pgs_assert(in.cols() == tangentDim_);
    pgs_assert(in.rows() == out.rows());
    pgs_assert(x.size() == representationDim_);
    applyDiffInvMap_(out, in, x);
  }

  void Manifold::applyTransport(
      RefMat out, const ConstRefMat& in, const ConstRefVec& x, const ConstRefVec& v) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(in.rows() == tangentDim_);
    pgs_assert(out.rows() == tangentDim_);
    pgs_assert(in.cols() == out.cols());
    pgs_assert(x.size() == representationDim());
    pgs_assert(v.size() == dim());
    pgs_assert(isInTxM(x, v));
    applyTransport_(out, in, x, v);
  }

  void Manifold::applyInvTransport(
      RefMat out, const ConstRefMat& in, const ConstRefVec& x, const ConstRefVec& v) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(in.cols() == tangentDim_);
    pgs_assert(out.cols() == tangentDim_);
    pgs_assert(in.rows() == out.rows());
    pgs_assert(x.size() == representationDim());
    pgs_assert(v.size() == dim());
    pgs_assert(isInTxM(x, v));
    applyInvTransport_(out, in, x, v);
  }

  void Manifold::setDimension(Index d)
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(d>=0 && "Negative dimension not accepted");
    testLock();
    dimension_ = d;
  }

  void Manifold::setTangentDimension(Index td)
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(td >= 0 && "Negative dimension not accepted");
    testLock();
    tangentDim_ = td;
  }

  void Manifold::setRepresentationDimension(Index rd)
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(rd>=0 && "Negative dimension not accepted");
    testLock();
    representationDim_ = rd;
  }


  void Manifold::setZero(RefVec out) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.size() == representationDim_);
    setZero_(out);
  }

  void Manifold::tangentConstraint(RefMat out, const ConstRefVec& x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.rows() == tangentDim_ - dimension_);
    pgs_assert(out.cols() == tangentDim_);
    pgs_assert(x.size() == representationDim());
    tangentConstraint_(out, x);
  }

  bool Manifold::isInTxM(const ConstRefVec& x, const ConstRefVec& v) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(v.size() == tangentDim_);
    pgs_assert(x.size() == representationDim());
    return isInTxM_(x, v);
  }

  void Manifold::forceOnTxM(RefVec out, const ConstRefVec& in, const ConstRefVec&x) const
  {
    pgs_assert(isValid() || seeMessageAbove());
    pgs_assert(out.size() == tangentDim_);
    pgs_assert(x.size() == representationDim());
    pgs_assert(in.size() == tangentDim_);
    forceOnTxM_(out, in, x);
  }



  void Manifold::lock() const
  {
    lock_ = true;
  }

  void Manifold::testLock() const
  {
    if (lock_)
      throw std::runtime_error("Either a point or a compound manifold is relying on this manifold, you can't modify it anymore.");
  }
}

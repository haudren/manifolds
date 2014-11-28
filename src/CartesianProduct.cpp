#include "CartesianProduct.h"

namespace pgs
{
  CartesianProduct::CartesianProduct()
    : Manifold(0,0)
  {
    startIndexT_.push_back(0);
    startIndexR_.push_back(0);
  }

  CartesianProduct::CartesianProduct(const Manifold& m1, const Manifold& m2)
    : Manifold(0,0)
  {
    startIndexT_.push_back(0);
    startIndexR_.push_back(0);
    multiply(m1);
    multiply(m2);
  }

  CartesianProduct& CartesianProduct::multiply(const Manifold& m)
  {
    m.lock();
    setDimension(dim() + m.dim());
    setRepresentationDimension(representationDim() + m.representationDim());
    submanifolds_.push_back(&m);
    startIndexT_.push_back(startIndexT_.back() + m.dim());
    startIndexR_.push_back(startIndexR_.back() + m.representationDim());
    return *this;
  }

  size_t CartesianProduct::numberOfSubmanifolds() const
  {
    return submanifolds_.size();
  }

  const Manifold& CartesianProduct::operator()(size_t i) const
  {
    assert(i < submanifolds_.size() && "invalid index");
    return *submanifolds_[i];
  }

  Segment CartesianProduct::getValue(Eigen::Ref<Eigen::VectorXd> val, size_t i) const
  {
    assert(i < submanifolds_.size() && "invalid index");
    return val.segment(static_cast<long> (startIndexR_[i]),static_cast<long> (submanifolds_[i]->representationDim()));
  }

  ConstSegment CartesianProduct::getValueConst(const Eigen::Ref<const Eigen::VectorXd>& val, size_t i) const
  {
    assert(i < submanifolds_.size() && "invalid index");
    return val.segment(static_cast<long> (startIndexR_[i]), static_cast<long> (submanifolds_[i]->representationDim()));
  }

  void CartesianProduct::plus_(Eigen::Ref<Eigen::VectorXd> out, const Eigen::Ref<const Eigen::VectorXd>& x, const Eigen::Ref<const Eigen::VectorXd>& v) const
  {
    for (size_t i = 0; i < submanifolds_.size(); ++i)
    {
      submanifolds_[i]->plus(getValue(out, i), 
                              getValueConst(x, i), 
                              v.segment(static_cast<long> (startIndexT_[i]),static_cast<long> ( submanifolds_[i]->dim())));
    }
  }

  void CartesianProduct::setIdentity_(Eigen::Ref<Eigen::VectorXd> out) const
  {
    for (size_t i = 0; i < submanifolds_.size(); ++i)
      submanifolds_[i]->setIdentity(getValue(out, i));
  }
}


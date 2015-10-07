// Copyright (c) 2015 CNRS
// Authors: Stanislas Brossette, Adrien Escande

// This file is part of manifolds
// manifolds is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.

// manifolds is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// manifolds. If not, see
// <http://www.gnu.org/licenses/>.

#include <limits>
#define _USE_MATH_DEFINES
#include <math.h>

#include <manifolds/utils.h>
#include <manifolds/S2.h>
#include <manifolds/S2_Base.h>
#include <manifolds/mnf_assert.h>

namespace mnf
{
S2::S2(std::shared_ptr<internal::S2_Base> p)
    : Manifold(std::static_pointer_cast<internal::Manifold_Base>(p))
{
}

S2::S2() : Manifold(std::shared_ptr<internal::Manifold_Base>(new internal::S2_Base())) {}

S2::S2(double magnitude)
    : Manifold(std::shared_ptr<internal::Manifold_Base>(new internal::S2_Base(magnitude)))
{
}

S2::S2(const ConstRefVec& magnitude)
    : Manifold(std::shared_ptr<internal::Manifold_Base>(new internal::S2_Base(magnitude)))
{
}

//Manifold S2::shallowCopy()
//{
  //std::cout << "S2::shallowCopy()" << std::endl;
  //return (S2(ptr_));
//}

//Manifold S2::deepCopy() const
//{
  //std::cout << "S2::deepCopy()" << std::endl;
  //return (S2(ptr_->clone()));
//}

S2 S2::copy() const
{
  return S2(std::make_shared<internal::S2_Base>(
      std::static_pointer_cast<internal::S2_Base>(ptr_)->copy()));
}

void S2::logarithm(RefVec out, const ConstRefVec& x, const ConstRefVec& y) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->logarithm(out, x, y);
}

double S2::distance(const ConstRefVec& x, const ConstRefVec& y) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->distance(x, y);
}

void S2::projRows(RefMat out, const ConstRefMat& in, const ConstRefVec& x) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->projRows(out, in, x);
}
void S2::projCols(RefMat out, const ConstRefMat& in, const ConstRefVec& x) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->projCols(out, in, x);
}
void S2::projVec(RefVec out, const ConstRefVec& in, const ConstRefVec& x) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->projVec(out, in, x);
}

void S2::rand(RefVec out) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->rand(out);
}

void S2::randVec(RefVec out, const ConstRefVec& x) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->randVec(out, x);
}
Eigen::Vector3d S2::randVec(const ConstRefVec& x) const
{
  return std::static_pointer_cast<internal::S2_Base>(ptr_)->randVec(x);
}
}

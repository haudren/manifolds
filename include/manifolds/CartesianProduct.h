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

#pragma once

#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <memory>

#include <manifolds/defs.h>
#include <manifolds/Manifold.h>
#include <manifolds/utils.h>

namespace mnf
{
  /// \brief Manifold representing the cartesian product of several submanifolds
  class MANIFOLDS_API CartesianProduct : public Manifold
  {
  public:
    /// \brief Default constructor
    CartesianProduct();

    ///brief Constructor of the manifold from a list of manifolds
    CartesianProduct(const std::initializer_list<Manifold*> m);

    /// \brief Constructor of the manifold composed of \f$ m1\times m2\f$
    CartesianProduct(const Manifold& m1, const Manifold& m2);

    /// \brief Adds manifold m to the current composed manifold\n
    /// This method cannot be executed if the manifold is locked
    CartesianProduct& multiply(const Manifold& m);
  };
}


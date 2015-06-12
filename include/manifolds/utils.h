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

#ifndef _MANIFOLDS_UTILS_H_
#define _MANIFOLDS_UTILS_H_

#include <manifolds/defs.h>

namespace mnf
{

namespace utils
{
  bool MANIFOLDS_API set_is_malloc_allowed(bool allow);

  namespace hash {
    constexpr uint assembleBytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
    {
      return uint(b0) | uint(b1 << 8) | uint(b2 << 16) | uint(b3 << 24);
    }

    constexpr static uint c1 = 0xcc9e2d51;
    constexpr static uint c2 = 0x1b873593;
    constexpr static uint r1 = 15;
    constexpr static uint r2 = 12;
    constexpr static uint m = 5;
    constexpr static uint n = 0xe6546b64;
    constexpr static uint seed = 39;

    constexpr uint computeK_1(uint k)
    {
      return k * c1;
    }
    constexpr uint computeK_2(uint k)
    {
      return (k << r1) | (k >> (32 - r1));
    }
    constexpr uint computeK_3(uint k)
    {
      return k * c2;
    }
    constexpr uint computeRound_1(uint hash, uint k)
    {
      return hash ^ k;
    }
    constexpr uint computeRound_2(uint hash)
    {
      return (hash << r2) | (hash >> (32 - r2));
    }
    constexpr uint computeRound_3(uint hash)
    {
      return hash * m + n;
    }

    constexpr uint computeK(uint fourBytes)
    {
      return computeK_3(computeK_2(computeK_1(fourBytes)));
    }
    constexpr uint computeRound(uint hash, uint k)
    {
      return computeRound_3(computeRound_2(computeRound_1(hash, k)));
    }

    constexpr uint finalize_1(uint hash)
    {
      return hash ^ (hash >> 16);
    }
    constexpr uint finalize_2(uint hash)
    {
      return hash * 0x85ebca6b;
    }
    constexpr uint finalize_3(uint hash)
    {
      return hash ^ (hash >> 13);
    }
    constexpr uint finalize_4(uint hash)
    {
      return hash * 0xc2b2ae35;
    }

    constexpr uint finalize(uint hash)
    {
      return finalize_1(finalize_4(finalize_3(finalize_2(finalize_1(hash)))));
    }

    template<int N>
      constexpr uint computeHash_recurse(const char (&str)[N], int index = 0, uint hash = 0)
      {
	return (index > N+3?
		hash:
		computeHash_recurse(str,
				    index+4,
				    computeRound(hash,
						 assembleBytes(static_cast<uint8_t>(index<N?str[index]:0),
							       static_cast<uint8_t>(index+1<N?str[index+1]:0),
							       static_cast<uint8_t>(index+2<N?str[index+2]:0),
							       static_cast<uint8_t>(index+3<N?str[index+3]:0)))));
      }

    template<int N>
      constexpr uint computeHash(const char (&str)[N])
      {
	return finalize(computeHash_recurse(str, 0, 0));
      }

    template<int N, int M>
      constexpr uint computeHash(const char (&str)[N], const char (&str2)[M])
    {
      return finalize(computeHash_recurse(str2, 0, computeHash_recurse(str, 0, 0)));
    }

  }
}

}

#endif //_MANIFOLDS_UTILS_H_

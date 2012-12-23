// Copyright (C) 2012 by Antonio El Khoury, CNRS.
//
// This file is part of the kite-fcl-bridge.
//
// kite-fcl-bridge is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// kite-fcl-bridge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with kite-fcl-bridge.  If not, see
// <http://www.gnu.org/licenses/>.

/// \brief Declaration of utility functions.

#ifndef KWS_FCL_BRIDGE_UTIL_HH
# define KWS_FCL_BRIDGE_UTIL_HH

# include <kws/fcl/types.hh>

namespace kws
{
  namespace fcl
  {
    inline void toMatFromKitMat (matrix4_t& dst, const CkitMat4& src)
    {
      matrix3_t rotation;
      point_t translation;
      
      for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j)
	  rotation(i,j) = src(i,j);
      for (int j = 0; j < 3; ++j)
	translation[j] = src(3,j);

      dst.setTransform (rotation, translation);
    }
    
    inline void toPointFromKitPoint (point_t& dst, const CkitPoint3& src)
    {
      dst[0] = src[0];
      dst[1] = src[1];
      dst[2] = src[2];
    }

  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KWS_FCL_BRIDGE_UTIL_HH

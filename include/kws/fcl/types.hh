// Copyright (C) 2012 by Antonio El Khoury, CNRS.
//
// This file is part of the kws-fcl-bridge.
//
// kws-fcl-bridge is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// kws-fcl-bridge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with kws-fcl-bridge.  If not, see
// <http://www.gnu.org/licenses/>.

/// \brief Declaration of types.

#ifndef KWS_FCL_BRIDGE_TYPES_HH
# define KWS_FCL_BRIDGE_TYPES_HH

# include <fcl/collision_object.h>

namespace kws
{
  namespace fcl
  {
    /// \brief Import types from fcl.
    typedef ::fcl::CollisionGeometry geometry_t;
    typedef ::fcl::CollisionObject object_t;
    typedef ::fcl::FCL_REAL value_type;
    typedef ::fcl::Vec3f point_t;
    typedef ::fcl::Transform3f matrix4_t;
  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KWS_FCL_BRIDGE_TYPES_HH

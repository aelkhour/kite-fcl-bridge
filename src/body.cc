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

/// \file src/body.cc 
///
/// \brief Implementation of Body.

#ifndef KWS_FCL_BRIDGE_BODY_CC
# define KWS_FCL_BRIDGE_BODY_CC

# include <kws/fcl/body.hh>

namespace kws
{
  namespace fcl
  {
    Body::
    Body ()
      : CkwsBody ()
    {
    }

    Body::
    ~Body ()
    {
    }

  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KWS_FCL_BRIDGE_BODY_CC

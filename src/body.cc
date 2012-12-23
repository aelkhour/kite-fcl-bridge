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
    ~Body ()
    {
    }

    BodyShPtr
    Body::create ()
    {
      Body* ptr = new Body ();
      BodyShPtr shPtr (ptr);

      if (KD_OK != ptr->init(shPtr))
	shPtr.reset();

      return shPtr;
    }

    BodyShPtr
    Body::createCopy (const BodyConstShPtr &body)
    {
      BodyShPtr shPtr;

      if (body)
	{
	  shPtr.reset(new Body(*body));

	  if (KD_OK != shPtr->init (shPtr))
	    shPtr.reset();
	}

      return shPtr;
    }

    CkwsBodyShPtr
    Body::clone () const
    {
      return Body::createCopy (wkPtr_.lock ());
    }

    double
    Body::getBoundingSphereRadius (const CkitPoint3& center) const
    {
      // FIXME
      return 0;
    }

    bool
    Body::isColliding (const CCollisionAnalysisParameters& analysisParameters,
		       double& distance)
    {
      return distance <= 0.;
    }

    Body::
    Body ()
      : CkwsBody (true)
    {
    }

    Body::
    Body (const Body& body)
    {
      // FIXME.
    }

    ktStatus Body::
    init (const BodyWkPtr& wkPtr)
    {
      ktStatus result = CkwsBody::init (wkPtr);

      if (KD_OK == result)
	wkPtr_ = wkPtr;

      return result;
    }

    void
    Body::placeBody (const CkitMat4& pos)
    {
      // FIXME
    }

  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KWS_FCL_BRIDGE_BODY_CC

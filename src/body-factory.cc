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

/// \file src/body-factory.cc
///
/// \brief Implementation of BodyFactory.

#ifndef KITE_FCL_BRIDGE_BODYFACTORY_CC
# define KITE_FCL_BRIDGE_BODYFACTORY_CC

# include "kite-fcl-bridge/body-factory.hh"

namespace kite_fcl_bridge
{
  BodyFactory::BodyFactory ()
    : CkppFactory<BodyShPtr> (),
      weakPtr_ ()
  {
  }

  BodyFactory::~BodyFactory ()
  {
  }

  BodyFactoryShPtr BodyFactory::
  create ()
  {
    BodyFactory* bodyFactory = new BodyFactory ();
    BodyFactoryShPtr bodyFactoryShPtr (bodyFactory);
    BodyFactoryWkPtr bodyFactoryWkPtr = bodyFactoryShPtr;

    if (bodyFactory->init(bodyFactoryWkPtr) != KD_OK)
      {
	bodyFactoryShPtr.reset();
      }
    return bodyFactoryShPtr;
  }

  ktStatus BodyFactory::
  init (const BodyFactoryWkPtr weakPtr)
  {
    weakPtr_ = weakPtr;
    return KD_OK;
  }

  BodyShPtr BodyFactory::
  make () const
  {
    return Body::create ();
  }

} // end of namespace kite_fcl_bridge.

#endif //! KITE_FCL_BRIDGE_BODYFACTORY_CC

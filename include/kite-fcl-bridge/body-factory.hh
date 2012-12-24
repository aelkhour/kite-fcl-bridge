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

/// \brief Declaration of BodyFactory class that builds bodies.

#ifndef KITE_FCL_BRIDGE_BODYFACTORY_HH
# define KITE_FCL_BRIDGE_BODYFACTORY_HH

# include <KineoModel/kppFactory.h>

# include <kite-fcl-bridge/fwd.hh>
# include <kite-fcl-bridge/body.hh>

namespace kite_fcl_bridge
{
  class BodyFactory
    : public CkppFactory<BodyShPtr>
  {
  public:
    /// \brief Destructor.
    virtual ~BodyFactory ();

    /// \brief Create body factory.
    static BodyFactoryShPtr create ();

    /// \brief Create a new body.
    virtual BodyShPtr make () const;

  protected:
    /// \brief Constructor.
    BodyFactory ();

    /// \brief Initialize body factory.
    ktStatus init (const BodyFactoryWkPtr weakPtr);

  private:
    BodyFactoryWkPtr weakPtr_;
  };

} // end of namespace kite_fcl_bridge

#endif // KITE_FCL_BRIDGE_BODYFACTORY_HH

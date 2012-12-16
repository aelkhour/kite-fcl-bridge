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

/// \brief Declaration of Body class that wraps FCL.

#ifndef KWS_FCL_BRIDGE_BODY_HH
# define KWS_FCL_BRIDGE_BODY_HH

# include <KineoWorks2/kwsBody.h>

# include <kws/fcl/fwd.hh>
# include <kws/fcl/types.hh>

namespace kws
{
  namespace fcl
  {
    /// \brief KineoWorks FCL Body.
    ///
    /// This class wraps the flexible collision library (FCL) to allow
    /// collision detection in the KineoWorks motion planning
    /// algorithms.
    class Body
      : public CkwsBody
    {
    public:
      /// \brief Destructor.
      ~Body ();

      /// \brief Create.
      static BodyShPtr create ();

      /// \brief Create copy.
      static BodyShPtr createCopy (const BodyConstShPtr &body);

      /// \brief Clone.
      CkwsBodyShPtr clone () const;

      /// \brief Compute bounding sphere radius.
      double getBoundingSphereRadius (const CkitPoint3& center) const;

      /// \brief Collision checking.
      bool isColliding (const CCollisionAnalysisParameters& analysisParameters,
			double& distance);

    protected:
      /// \brief Constructor.
      explicit Body ();

      /// \brief Copy constructor.
      explicit Body (const Body& body);

      /// \brief Initialize.
      ktStatus init (const BodyWkPtr& wkPtr);

      /// \brief Update body absolute position.
      void placeBody (const CkitMat4& pos);

    private:
      BodyWkPtr wkPtr_;
    };

  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KWS_FCL_BRIDGE_BODY_HH

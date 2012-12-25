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

/// \brief Declaration of Body class that wraps FCL.

#ifndef KITE_FCL_BRIDGE_BODY_HH
# define KITE_FCL_BRIDGE_BODY_HH

# include <kwsKcd2/kwsKCDBody.h>

# include <kite-fcl-bridge/fwd.hh>
# include <kite-fcl-bridge/types.hh>

namespace kite_fcl_bridge
{
    /// \brief KineoWorks FCL Body.
    ///
    /// This class wraps the flexible collision library (FCL) to allow
    /// collision detection in the KineoWorks motion planning
    /// algorithms.
    class Body
      : public CkwsKCDBody
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

      /// \brief Set inner objects.
      void innerFclObjects (const objectShPtrs_t innerObjects);

      /// \brief Get inner objects.
      const objectShPtrs_t innerFclObjects () const;

      /// \brief Set outer objects.
      void outerFclObjects (const objectShPtrs_t outerObjects);

      /// \brief Get outer objects.
      const objectShPtrs_t outerFclObjects () const;

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
      BodyWkPtr weakPtr_;
      objectShPtrs_t innerObjects_;
      objectShPtrs_t outerObjects_;

      mutable matrix4_t transform_;
      mutable collisionRequest_t collisionRequest_;
      mutable collisionResult_t collisionResult_;
      mutable distanceRequest_t distanceRequest_;
      mutable distanceResult_t distanceResult_;
    };

} // end of namespace kite_fcl_bridge.

#endif //! KITE_FCL_BRIDGE_BODY_HH

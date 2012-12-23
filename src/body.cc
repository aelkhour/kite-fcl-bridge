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

#ifndef KITE_FCL_BRIDGE_BODY_CC
# define KITE_FCL_BRIDGE_BODY_CC

# include <boost/foreach.hpp>

# include <fcl/BVH/BV_fitter.h>
# include <fcl/BVH/BVH_model.h>
# include <fcl/collision.h>
# include <fcl/distance.h>

# include <kws/fcl/body.hh>
# include <kws/fcl/util.hh>

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
      unsigned int numVertices = 0;

      // Retrieve total number of vertices.
      BOOST_FOREACH (objectShPtr_t object, innerObjects_)
	{
	  if (object->getObjectType () == ::fcl::OT_BVH)
	    {
	      geometryConstShPtr_t geometry (object->getCollisionGeometry ());
	      numVertices +=
		KIT_DYNAMIC_PTR_CAST (const ::fcl::BVHModel< ::fcl::OBB>,
				      geometry)->num_vertices;
	    }
	}

      point_t vertices[numVertices];
      unsigned int indices[numVertices];
      unsigned int k = 0;

      // Retrieve all vertices.
      BOOST_FOREACH (objectShPtr_t object, innerObjects_)
	{
	  if (object->getObjectType () == ::fcl::OT_BVH)
	    {
	      geometryConstShPtr_t geometry (object->getCollisionGeometry ());
	      boost::shared_ptr<const ::fcl::BVHModel< ::fcl::OBB> > bvh =
		KIT_DYNAMIC_PTR_CAST (const ::fcl::BVHModel< ::fcl::OBB>,
				      geometry);
	      for (unsigned i = 0; i < bvh->num_vertices; ++i)
		{
		  vertices[k] = bvh->vertices[i];
		  indices[k] = k;
		  ++k;
		}
	    }
	  else
	    {
	      std::cout
		<< "Object not taken into account in bounding sphere computation."
		<< std::endl;
	    }
	}

      // Fit sphere over vertices.
      ::fcl::BVFitter< ::fcl::kIOS> fitter;
      fitter.clear ();
      fitter.set (vertices, NULL, ::fcl::BVH_MODEL_POINTCLOUD);
      ::fcl::kIOS kios = fitter.fit (indices, numVertices);

      // Find sphere radius.
      point_t center1;
      toPointFromKitPoint (center1, center);
      point_t center2 = kios.spheres[0].o;
      value_type radius = (center2 - center1).length () + kios.spheres[0].r;

      return radius;
    }

    bool
    Body::isColliding (const CCollisionAnalysisParameters& analysisParameters,
		       double& distance)
    {
      if (analysisParameters.fieldsToUse()
	  & CkwsBody::CCollisionAnalysisParameters::POSITION)
	{
	  // Use given position instead of absolute position.
	  placeBody (analysisParameters.bodyPosition ());
	}

      if (analysisParameters.distanceComputationMethod ()
	  == CkwsBody::CCollisionAnalysisParameters::NO_DISTANCE)
	{
	  // Fast collision detection.
	  BOOST_FOREACH (objectShPtr_t innerObject, innerObjects_)
	    BOOST_FOREACH (objectShPtr_t outerObject, outerObjects_)
	    {
	      ::fcl::collide (innerObject.get (),
			      outerObject.get (),
			      collisionRequest_,
			      collisionResult_);

	      if (collisionResult_.isCollision ())
		return true;
	    }

	  return false;
	}
      else if (analysisParameters.distanceComputationMethod ()
	       == CkwsBody::CCollisionAnalysisParameters::ESTIMATED_DISTANCE)
	{
	  // Return estimated distance.
	  // FIXME.
	  std::cout << "Estimated distance computation not supported yet."
		    << std::endl;
	  return false;
	}
      else if (analysisParameters.distanceComputationMethod ()
	       == CkwsBody::CCollisionAnalysisParameters::EXACT_DISTANCE)
	{
	  distance = std::numeric_limits<value_type>::max ();

	  // Compute exact distance.
	  BOOST_FOREACH (objectShPtr_t innerObject, innerObjects_)
	    BOOST_FOREACH (objectShPtr_t outerObject, outerObjects_)
	    {
	      ::fcl::distance (innerObject.get (),
			       outerObject.get (),
			       distanceRequest_,
			       distanceResult_);

	      if (distanceResult_.min_distance < distance)
		distance = distanceResult_.min_distance;

	      if (distance <= 0)
		{
		  distance = 0.;
		  return true;
		}
	    }

	  return false;
	}
      else if (analysisParameters.distanceComputationMethod ()
	       == CkwsBody::CCollisionAnalysisParameters::
	       DISTANCE_WITH_TOLERANCE)
	{
	  // Return distance with tolerance.
	  // FIXME.
	  std::cout << "Distance with tolerance computation not supported yet."
		    << std::endl;
	  return false;
	}
    }

    void
    Body::innerObjects (const objectShPtrs_t innerObjects)
    {
      innerObjects_ = innerObjects;
    }

    const objectShPtrs_t
    Body::innerObjects () const
    {
      return innerObjects_;
    }

    void
    Body::outerObjects (const objectShPtrs_t outerObjects)
    {
      outerObjects_ = outerObjects;
    }

    const objectShPtrs_t
    Body::outerObjects () const
    {
      return outerObjects_;
    }

    Body::
    Body ()
      : CkwsBody (true),
	wkPtr_ (),
	innerObjects_ (),
	outerObjects_ (),
	transform_ (),
	collisionRequest_ (),
	collisionResult_ (),
	distanceRequest_ (),
	distanceResult_ ()
    {
    }

    Body::
    Body (const Body& body)
    {
      innerObjects_ = body.innerObjects ();
      outerObjects_ = body.outerObjects ();
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
      toMatFromKitMat (transform_, pos);
      BOOST_FOREACH(objectShPtr_t object, innerObjects_)
	object->setTransform (transform_);
    }

  } // end of namespace fcl.
} // end of namespace kws.

#endif //! KITE_FCL_BRIDGE_BODY_CC

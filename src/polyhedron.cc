// Copyright (C) 2012 by Antonio El Khoury.
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

/// \file src/polyhedron.cc
///
/// \brief Implementation of Polyhedron component.

#include <kite-fcl-bridge/polyhedron.hh>
#include <kite-fcl-bridge/util.hh>

namespace kite_fcl_bridge
{
  Polyhedron::
  ~Polyhedron ()
  {
  }

  CkppComponentShPtr Polyhedron::
  cloneComponent () const
  {
    CkppComponentShPtr shPtr = CkppComponent::create ("");
    return shPtr;
  }

  bool Polyhedron::
  isComponentClonable () const
  {
    return false;
  }

  void Polyhedron::
  setAbsolutePosition (const CkitMat4& matrix)
  {
    absTransform_ = matrix;

    CkppSolidComponentShPtr solidComponent
      = KIT_DYNAMIC_PTR_CAST (CkppSolidComponent, parent ());

    if (solidComponent)
      {
	CkitMat4 parentAbsTransform;
	solidComponent->getAbsolutePosition (parentAbsTransform);
	relTransform_ = parentAbsTransform.inverse () * matrix;
      }
    else
      relTransform_ = matrix;
  }

  void Polyhedron::
  getAbsolutePosition (CkitMat4& matrix) const
  {
    matrix = absTransform_;
  }

  void Polyhedron::
  getAbsolutePosition (CkcdMat4& matrix) const
  {
    matrix = absTransform_;
  }

  void Polyhedron::
  setRelativePosition (const CkitMat4& matrix)
  {
    relTransform_ = matrix;

    CkppSolidComponentShPtr solidComponent
      = KIT_DYNAMIC_PTR_CAST (CkppSolidComponent, parent ());

    if (solidComponent)
      {
	CkitMat4 parentAbsTransform;
	solidComponent->getAbsolutePosition (parentAbsTransform);
	absTransform_ = parentAbsTransform * matrix;
      }
    else
      absTransform_ = matrix;
  }

  void Polyhedron::
  getRelativePosition (CkitMat4& matrix) const
  {
    matrix = relTransform_;
  }

  ktStatus Polyhedron::
  getBBMatrixOrientation (CkitMat4& matrix) const
  {
    // FIXME?
    std::cout << "FIXME" << std::endl;
    matrix = absTransform_;
    return KD_OK;
  }

  ktStatus Polyhedron::
  getBBHalfLengths (float &x, float &y, float &z) const
  {
    // FIXME?
    std::cout << "FIXME" << std::endl;
    return KD_OK;
  }

  CkitMat4 Polyhedron::
  computeDefaultFrame () const
  {
    // FIXME.
    std::cout << "FIXME" << std::endl;
    return absTransform_;
  }

  ktStatus Polyhedron::
  addPoint (const CkitPoint3& point)
  {
    point_t fclPoint;
    toPointFromKitPoint (fclPoint, point);
    points_.push_back (fclPoint);
  }

  ktStatus Polyhedron::
  addTriangle (unsigned int i_p1,
	       unsigned int i_p2,
	       unsigned int i_p3)
  {
    polyhedron_->addTriangle (polyhedron_->vertices[i_p1],
			      polyhedron_->vertices[i_p2],
			      polyhedron_->vertices[i_p3]);
  }

  void Polyhedron::
  addPolygon (const std::vector< int > &i_verticesVector)
  {
    // FIXME.
    std::cout << "FIXME" << std::endl;
  }

  unsigned int Polyhedron::
  countPoints () const
  {
    return polyhedron_->num_vertices;
  }

  unsigned int Polyhedron::
  countTriangles () const
  {
    return polyhedron_->num_tris;
  }

  void Polyhedron::
  getTriangle (const unsigned int i_rank,
	       unsigned int &o_p1,
	       unsigned int &o_p2,
	       unsigned int &o_p3) const
  {
    triangle_t triangle = polyhedron_->tri_indices[i_rank];
    o_p1 = triangle[0];
    o_p2 = triangle[1];
    o_p3 = triangle[2];
  }

  void Polyhedron::
  getPoint (const unsigned int i_rank,
	    float &o_x, float &o_y, float &o_z) const
  {
    point_t point = polyhedron_->vertices[i_rank];
    o_x = point[0];
    o_y = point[1];
    o_z = point[2];
  }

  void Polyhedron::
  getPoint (const unsigned int i_rank,
	    CkitPoint3 &o_point) const
  {
    point_t point = polyhedron_->vertices[i_rank];
    toKitPointFromPoint (o_point, point);
  }

  CkppAssemblyComponentShPtr Polyhedron::
  explode (const CkitProgressDelegateShPtr &i_delegate)
  {
    // FIXME.
    std::cout << "FIXME" << std::endl;
    CkppAssemblyComponentShPtr assemblyComponent;
    return assemblyComponent;
  }

  PolyhedronShPtr Polyhedron::
  create (const std::string& name)
  {
    Polyhedron* ptr = new Polyhedron ();
    PolyhedronShPtr ptrShPtr (ptr);

    if (ptr->init (ptrShPtr, name) != KD_OK)
      {
	ptrShPtr.reset ();
      }

    return ptrShPtr;
  }

  Polyhedron::
  Polyhedron ()
    : CkppPolyhedron (),
      polyhedron_ (),
      absTransform_ (),
      relTransform_ (),
      points_ ()
  {
  }

  ktStatus Polyhedron::
  init (const PolyhedronWkPtr weakPtr,
	const std::string& name)
  {
    ktStatus success = CkppPolyhedron::init (weakPtr, name);

    if (KD_OK == success)
      {
	weakPtr_ = weakPtr;
	polyhedronPtr_t ptr = new polyhedron_t ();
	polyhedron_ = polyhedronShPtr_t (ptr);

	return KD_OK;
      }
    else
      return KD_ERROR;
  }

  CkppPolyhedronShPtr Polyhedron::
  createPolyhedronFromPolyExpandingData
  (const CkppPolyExpandingDataShPtr& i_polyExpandingData,
   unsigned int i_offset)
  {
    // FIXME.
    std::cout << "FIXME" << std::endl;
    PolyhedronShPtr polyhedron = Polyhedron::create ("");
    return polyhedron;
  }

} // end of namespace kite_fcl_bridge.

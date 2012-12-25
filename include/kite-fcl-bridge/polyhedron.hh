// Copyright (C) 2012 by Antonio El Khoury.
//
// This file is part of the kpp-fcl-bridge.
//
// kpp-fcl-bridge is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// kpp-fcl-bridge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with kpp-fcl-bridge.  If not, see
// <http://www.gnu.org/licenses/>.

/// \brief Declaration of Polyhedron component that wraps FCL.

#ifndef KITE_FCL_BRIDGE_POLYHEDRON_HH
# define KITE_FCL_BRIDGE_POLYHEDRON_HH

# include <KineoModel/KineoModel.h>

# include <fcl/BVH/BVH_model.h>

# include <kite-fcl-bridge/fwd.hh>
# include <kite-fcl-bridge/types.hh>

namespace kite_fcl_bridge
{
  class Polyhedron
    : public CkppPolyhedron,
      public polyhedron_t
  {
  public:
    /// \brief Destructor
    virtual ~Polyhedron ();

    /// \brief Create polyhedron.
    static PolyhedronShPtr create (const std::string& name);

    /// \brief Create a copy of the component.
    virtual CkppComponentShPtr cloneComponent () const;

    /// \brief Tell whether the component can be cloned using
    /// cloneComponent().
    virtual bool isComponentClonable () const;

    /// \brief Set the absolute position of the component.
    virtual void setAbsolutePosition (const CkitMat4 &i_matrix);

    /// \brief Retrieve the absolute position of the component.
    virtual void getAbsolutePosition (CkitMat4 &o_matrix) const;

    /// \brief Retrieve the absolute position of the component.
    virtual void getAbsolutePosition (CkcdMat4 &o_matrix) const;

    /// \brief Set the relative position of the component.
    virtual void setRelativePosition (const CkitMat4 &i_matrix);

    /// \brief Retrieve the relative position of the component.
    virtual void getRelativePosition (CkitMat4 &o_matrix) const;

    /// \brief Retrieve the orientation of the bounding box
    /// around the component.
    virtual ktStatus getBBMatrixOrientation (CkitMat4 &o_matrix) const;

    /// \brief Retrieve the half-lengths of the bounding box
    /// around the component.
    virtual ktStatus getBBHalfLengths (float &x, float &y, float &z) const;

    /// \brief Compute and returns the default motion frame.
    virtual CkitMat4 computeDefaultFrame () const;

    /// \brief Add a point to the polyhedron.
    virtual ktStatus addPoint (const CkitPoint3 &i_point);

    /// \brief Add a triangle to the polyhedron.
    virtual ktStatus addTriangle (unsigned int i_p1,
				  unsigned int i_p2,
				  unsigned int i_p3);

    /// \brief Add a polygon to the polyhedron.
    virtual void addPolygon (const std::vector< int > &i_verticesVector);

    /// \brief Return the number of points in the polyhedron.
    virtual unsigned int countPoints () const;

    /// \brief Return the number of triangles in the polyhedron.
    virtual unsigned int countTriangles () const;

    /// \brief Get the triangle corresponding to the given rank.
    virtual void getTriangle (const unsigned int i_rank,
			      unsigned int &o_p1,
			      unsigned int &o_p2,
			      unsigned int &o_p3) const;

    /// \brief Get the point corresponding to the given rank.
    virtual void getPoint (const unsigned int i_rank,
			   float &o_x, float &o_y, float &o_z) const;

    /// \brief Get the point corresponding to the given rank.
    virtual void getPoint (const unsigned int i_rank,
			   CkitPoint3 &o_point) const;

    /// \brief Explode the polyhedron, transforming it into an
    /// assembly.
    virtual CkppAssemblyComponentShPtr
    explode (const CkitProgressDelegateShPtr &i_delegate
	     =CkitProgressDelegateShPtr());

  protected:
    /// \brief Constructor.
    Polyhedron ();

    /// \brief Initialize polyhedron.
    ktStatus init (const PolyhedronWkPtr weakPtr,
		   const std::string& name);

    virtual CkppPolyhedronShPtr createPolyhedronFromPolyExpandingData
    (const CkppPolyExpandingDataShPtr& i_polyExpandingData,
     unsigned int i_offset);

  private:
    PolyhedronWkPtr weakPtr_;

    CkitMat4 absTransform_;
    CkitMat4 relTransform_;
    std::vector<point_t> points_;
  };

} // end of namespace kite_fcl_bridge.

#endif //! KITE_FCL_BRIDGE_POLYHEDRON_HH

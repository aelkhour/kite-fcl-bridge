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

/// \brief Declaration of macros.

#ifndef KITE_FCL_BRIDGE_MACROS_HH
# define KITE_FCL_BRIDGE_MACROS_HH

/// \def KITE_FCL_DEFINE_TYPES(T, NAME)
///
/// Create typedefs from class.
///
/// This macro defines new pointer and vector types from \a T and
/// prefixes them with \a NAME.
///
/// \param T class name
/// \param Name desired name
# define KITE_FCL_DEFINE_TYPES(T, NAME)				\
  typedef T NAME##_t;						\
  typedef T* NAME##Ptr_t;					\
  typedef boost::shared_ptr<T> NAME##ShPtr_t;			\
  typedef boost::shared_ptr<const T> NAME##ConstShPtr_t;	\
  typedef boost::weak_ptr<T> NAME##WkPtr_t;			\
  typedef std::vector<T> NAME##s_t;				\
  typedef std::vector<T*> NAME##Ptrs_t;				\
  typedef std::vector<boost::shared_ptr<T> > NAME##ShPtrs_t;	\
  typedef std::vector<boost::weak_ptr<T> > NAME##WkPtrs_t

#endif //! KITE_FCL_BRIDGE_MACROS_HH

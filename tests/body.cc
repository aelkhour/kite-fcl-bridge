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

#define BOOST_TEST_MODULE body

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <kite-fcl-bridge/body.hh>

using boost::test_tools::output_test_stream;

BOOST_AUTO_TEST_CASE (body)
{
  kite_fcl_bridge::BodyShPtr body = kite_fcl_bridge::Body::create ();
}

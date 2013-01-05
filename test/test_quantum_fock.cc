// -*- mode: c++; fill-column: 80; c-basic-offset: 2; indent-tabs-mode: nil -*-
/*
    Copyright (c) 2010 Juan Jose Garcia Ripoll

    Tensor is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published
    by the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <tensor/io.h>
#include <mps/quantum.h>
#include <gtest/gtest.h>

using namespace mps;

TEST(Fock, Number) {
  {
    RSparse n0 = number_operator(0);
    RTensor n0_manual(igen << 1 << 1,
                      rgen << 0.0);
    EXPECT_EQ(n0, n0_manual);
  }
  {
    RSparse n1 = number_operator(1);
    RTensor n1_manual(igen << 2 << 2,
                      rgen << 0.0 << 0.0
                           << 0.0 << 1.0);
    EXPECT_EQ(n1, n1_manual);
  }
  {
    RSparse n2 = number_operator(2);
    RTensor n2_manual(igen << 3 << 3,
                      rgen << 0.0 << 0.0 << 0.0
                           << 0.0 << 1.0 << 0.0
                           << 0.0 << 0.0 << 2.0);
    EXPECT_EQ(n2, n2_manual);
  }
}

TEST(Fock, Creation) {
  {
    RSparse a0 = creation_operator(0);
    RTensor a0_manual(igen << 1 << 1,
                      rgen << 0.0);
    EXPECT_EQ(a0, a0_manual);
  }
  {
    RSparse a1 = creation_operator(1);
    RTensor a1_manual(igen << 2 << 2,
                      rgen << 0.0 << 1.0
                           << 0.0 << 0.0);
    EXPECT_EQ(a1, a1_manual);
  }
  {
    RSparse a2 = creation_operator(2);
    RTensor a2_manual(igen << 3 << 3,
                      rgen << 0.0 << 1.0 << 0.0
                           << 0.0 << 0.0 << sqrt(2.0)
                           << 0.0 << 0.0 << 0.0);
    EXPECT_EQ(a2, a2_manual);
  }
}

TEST(Fock, Destruction) {
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(creation_operator(i), transpose(full(destruction_operator(i))));
  }
}
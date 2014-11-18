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

#include <tensor/tensor.h>
#include <tensor/tensor_lapack.h>
#include <tensor/linalg.h>
#include <tensor/io.h>

namespace linalg {

  using namespace tensor;

  template<typename elt_t>
  elt_t eig_power_loop(const Map<Tensor<elt_t> > *A, size_t dims, Tensor<elt_t> *vector,
                       size_t iter, double tol)
  {
    if (tol <= 0) {
      tol = 1e-11;
    }
    assert(vector);
    Tensor<elt_t> &v = *vector;
    if (v.size() != dims) {
      v = 0.5 - Tensor<elt_t>::random(dims);
    }
    if (iter == 0) {
      iter = std::max<size_t>(20, v.size());
    }
    v /= norm2(v);
    elt_t eig, old_eig;
    for (size_t i = 0; i <= iter; i++) {
      Tensor<elt_t> v_new = (*A)(v);
      eig = scprod(v_new, v);
      v_new /= norm2(v_new);
      if (i) {
        double eig_change = std::abs(eig - old_eig);
        if (eig_change < tol * std::abs(eig)) {
          double error = norm0(v_new - v);
          if (error < tol) {
            v = v_new;
            break;
          }
        }
      }
      old_eig = eig;
      v = v_new;
    }
    delete A;
    return eig;
  }

} // namespace linalg

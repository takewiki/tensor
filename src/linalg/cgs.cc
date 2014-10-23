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
#include <tensor/linalg.h>

namespace linalg {

  using namespace tensor;

  template<class Tensor>
  static const Tensor
  solve(const Tensor &A, const Tensor &b, const Tensor *x_start,
	int maxiter, double tol)
  {
    typedef typename Tensor::elt_t number;
    if (maxiter == 0) {
      maxiter = sqrt(b.size())*b.size();
    }
    if (tol == 0) {
      tol = 1e-7;
    }
    if (!x_start) {
      x_start = &b;
    }
    Tensor x = *x_start;
    Tensor r = b - mmult(A, x);
    Tensor p = r;
    number rsold = real(scprod(r,r));
    while (maxiter-- >= 0) {
      Tensor Ap = mmult(A, p);
      number alpha = rsold / scprod(p, Ap);
      x += alpha * p;
      r -= alpha * Ap;
      number rsnew = scprod(r, r);
      if (sqrt(abs(rsnew)) < tol)
	break;
      p = r + (rsnew / rsold) * p;
      rsold = rsnew;
    }
    return x;
  }

}

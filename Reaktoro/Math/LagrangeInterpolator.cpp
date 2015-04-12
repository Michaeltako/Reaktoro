// Reaktoro is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "LagrangeInterpolator.hpp"

namespace Reaktoro {
namespace {

auto interpolate(double x, const double* xi, const double* yi, unsigned npoints) -> double
{
    double y = 0.0;

    for(unsigned i = 0; i < npoints; ++i)
    {
        double li = 1.0;

        for(unsigned j = 0; j < npoints; ++j)
            li *= (i == j) ? 1.0 : (x - xi[j])/(xi[i] - xi[j]);

        y += yi[i] * li;
    }

    return y;
}

} // namespace

LagrangeInterpolator::LagrangeInterpolator()
{}

LagrangeInterpolator::LagrangeInterpolator(const std::vector<double>& xi, const std::vector<double>& yi, unsigned order)
: xi(xi), yi(yi), order(order)
{}

auto LagrangeInterpolator::operator()(double x) const -> double
{
	// The number of interpolation points
	const unsigned size = xi.size();

	// Check if x is less than the smallest interpolation x-point
	if(x <= xi.front()) return yi.front();

	// Check if x is larger than the largest interpolation x-point
	if(x >= xi.back()) return yi.back();

	// Otherwise, find the interval where x lives
	unsigned i = 0; while(xi[i] < x) ++i;

	// The number of points to be used in the interpolation
	unsigned npoints = (i + order + 1 > size) ? size - i : order + 1;

	return interpolate(x, &xi[i], &yi[i], npoints);
}

} // namespace Reaktoro
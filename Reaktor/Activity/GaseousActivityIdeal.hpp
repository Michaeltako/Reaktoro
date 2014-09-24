// Reaktor is a C++ library for computational reaction modelling.
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

#pragma once

// C++ includes
#include <string>

// Reaktor includes
#include <Reaktor/Activity/GaseousActivity.hpp>

namespace Reaktor {

/// Create the gaseous activity function of a gaseous species based on the ideal model
///
/// @param species The name of the gaseous species
/// @param mixture The gaseous mixture instance containing the gaseous species
/// @return The gaseous activity function of the gaseous species
/// @see GaseousMixture, GaseousActivity
auto gaseousActivityIdeal(const std::string& species, const GaseousMixture& mixture) -> GaseousActivity;

} // namespace Reaktor
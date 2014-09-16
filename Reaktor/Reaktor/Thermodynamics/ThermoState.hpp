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

// Reaktor includes
#include <Reaktor/Common/ThermoProperty.hpp>

namespace Reaktor {

/// Describe the thermodynamic state of a species
struct ThermoState
{
	/// The standard molar volume @f$ V^{\circ}@f$ of the species (in units of m3/mol)
	ThermoProperty V;

	/// The standard molar entropy @f$ S^{\circ}@f$ of the species (in units of J/K)
	ThermoProperty S;

	/// The apparent standard molar Helmholtz free energy @f$\Delta A_{f}^{\circ}@f$ of the species (in units of J/mol)
	ThermoProperty A;

	/// The apparent standard molar internal energy @f$\Delta U_{f}^{\circ}@f$ of the species (in units of J/mol)
	ThermoProperty U;

	/// The apparent standard molar enthalpy @f$\Delta H_{f}^{\circ}@f$ of the species (in units of J/mol)
	ThermoProperty H;

	/// The apparent standard molar Gibbs free energy @f$\Delta G_{f}^{\circ}@f$ of the species (in units of J/mol)
	ThermoProperty G;

	/// The standard molar isobaric heat capacity @f$ C_{p}^{\circ}@f$ of the species (in units of J/(mol K))
	ThermoProperty Cp;
};

} // namespace Reaktor
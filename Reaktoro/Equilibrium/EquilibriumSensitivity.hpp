// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2015 Allan Leal
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

// Reaktoro includes
#include <Reaktoro/Math/Matrix.hpp>

namespace Reaktoro {

/// A type that contains the sensitivity data of the equilibrium state.
/// The sensitivity of the equilibrium state contains derivatives of the
/// species molar amounts with respect to temperature, pressure, and
/// molar amounts of the elements. It is an important information for
/// implicit numerical methods, since these derivatives allow the calculation
/// to converge faster to the solution.
struct EquilibriumSensitivity
{
    /// The partial derivatives @f$\left.\frac{\partial n_e}{\partial T}\right|_{P,b_e}@f$ (in units of mol/K).
    /// These derivatives provide a measure of how much the equilibrium molar amounts of the equilibrium species,
    /// @f$n_e@f$, change with an infinitesimal change in temperature, @f$T@f$. They are useful when solving
    /// non-linear problems that involve equilibrium calculations and derivatives with respect to temperature.
    Vector dnedT;

    /// The partial derivatives @f$\left.\frac{\partial n_e}{\partial P}\right|_{T,b_e}@f$ (in units of mol/Pa).
    /// These derivatives provide a measure of how much the equilibrium molar amounts of the equilibrium species,
    /// @f$n_e@f$, change with an infinitesimal change in pressure, @f$P@f$. They are useful when solving
    /// non-linear problems that involve equilibrium calculations and derivatives with respect to pressure.
    Vector dnedP;

    /// The partial derivatives @f$\left.\frac{\partial n_e}{\partial b_e}\right|_{T,P}@f$ (in units of mol/mol).
    /// These derivatives provide a measure of how much the equilibrium molar amounts of the equilibrium species,
    /// @f$n_e@f$, change with an infinitesimal change in the amounts of equilibrium elements, @f$b_e@f$. They are
    /// useful when solving non-linear problems that involve equilibrium calculations and derivatives with respect
    /// to the amounts of equilibrium elements.
    Matrix dnedbe;
};

} // namespace Reaktoro

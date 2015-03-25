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
#include <vector>

// Reaktor includes
#include <Reaktor/Common/ReactionEquation.hpp>
#include <Reaktor/Common/Optional.hpp>
#include <Reaktor/Math/BilinearInterpolator.hpp>

namespace Reaktor {

/// A type for storing thermodynamic properties of a species over a range of temperatures and pressures.
/// The thermodynamic properties are represented by BilinearInterpolator instances, where
/// the temperature points (in units of K) are along the x-coordinates, and the pressure points
/// (in units of Pa) are along the y-coordinates.
struct SpeciesThermoProperties
{
    /// The interpolator of the standard molar Gibbs free energy @f$\Delta G_{f}^{\circ}@f$ of the species (in units of J/mol)
    BilinearInterpolator gibbs_energy;

    /// The interpolator of the standard molar Helmholtz free energy @f$\Delta A_{f}^{\circ}@f$ of the species (in units of J/mol)
    BilinearInterpolator helmholtz_energy;

    /// The interpolator of the standard molar internal energy @f$\Delta U_{f}^{\circ}@f$ of the species (in units of J/mol)
    BilinearInterpolator internal_energy;

    /// The interpolator of the standard molar enthalpy @f$\Delta H_{f}^{\circ}@f$ of the species (in units of J/mol)
    BilinearInterpolator enthalpy;

    /// The interpolator of the standard molar entropy @f$ S^{\circ}@f$ of the species (in units of J/K)
    BilinearInterpolator entropy;

    /// The interpolator of the standard molar volume @f$ V^{\circ}@f$ of the species (in units of m3/mol)
    BilinearInterpolator volume;

    /// The interpolator of the standard molar isobaric heat capacity @f$ C_{p}^{\circ}@f$ of the species (in units of J/(mol*K))
    BilinearInterpolator heat_capacity;
};

/// A type for storing thermodynamic properties of a reaction over a range of temperatures and pressures.
/// The thermodynamic properties are represented by BilinearInterpolator instances, where
/// the temperature points (in units of K) are along the x-coordinates, and the pressure points
/// (in units of Pa) are along the y-coordinates.
struct ReactionThermoProperties
{
    /// The equation of the reaction as pairs `(reactant, stoichiometry)`
    ReactionEquation equation;

    /// The interpolator of the equilibrium constant @f$\ln k_{\mathrm{eq}}@f$ of the reaction
    BilinearInterpolator lnk;

    /// The interpolator of the standard molar Gibbs free energy @f$\Delta G_{r}^{\circ}@f$ of the reaction (in units of J/mol)
    BilinearInterpolator gibbs_energy;

    /// The interpolator of the standard molar Helmholtz free energy @f$\Delta A_{r}^{\circ}@f$ of the reaction (in units of J/mol)
    BilinearInterpolator helmholtz_energy;

    /// The interpolator of the standard molar internal energy @f$\Delta U_{r}^{\circ}@f$ of the reaction (in units of J/mol)
    BilinearInterpolator internal_energy;

    /// The interpolator of the standard molar enthalpy @f$\Delta H_{r}^{\circ}@f$ of the reaction (in units of J/mol)
    BilinearInterpolator enthalpy;

    /// The interpolator of the standard molar entropy @f$\Delta S_{r}^{\circ}@f$ of the reaction (in units of J/K)
    BilinearInterpolator entropy;

    /// The interpolator of the standard molar volume @f$\Delta V_{r}^{\circ}@f$ of the reaction (in units of m3/mol)
    BilinearInterpolator volume;

    /// The interpolator of the standard molar isobaric heat capacity @f$ \Delta C_{p}^{\circ}@f$ of the reaction (in units of J/(mol*K))
    BilinearInterpolator heat_capacity;
};

/// A type for storing the parameters of the HKF equation of state for a aqueous species
struct AqueousSpeciesThermoParamsHKF
{
    /// The apparent standard molal Gibbs free energy of formation of the species from its elements (in units of cal/mol)
    double Gf;

    /// The apparent standard molal enthalpy of formation of the species from its elements (in units of cal/mol)
    double Hf;

    /// The standard molal entropy of the species at reference temperature and pressure (in units of cal/(mol*K))
    double Sr;

    /// The coefficient a1 of the HKF equation of state of the aqueous species (in units of cal/(mol*bar))
    double a1;

    /// The coefficient a2 of the HKF equation of state of the aqueous species (in units of cal/mol)
    double a2;

    /// The coefficient a3 of the HKF equation of state of the aqueous species (in units of (cal*K)/(mol*bar))
    double a3;

    /// The coefficient a4 of the HKF equation of state of the aqueous species (in units of (cal*K)/mol)
    double a4;

    /// The coefficient c1 of the HKF equation of state of the aqueous species (in units of cal/(mol*K))
    double c1;

    /// The coefficient c2 of the HKF equation of state of the aqueous species (in units of (cal*K)/mol)
    double c2;

    /// The conventional Born coefficient of the aqueous species at reference temperature 298.15 K and pressure 1 bar (in units of cal/mol)
    double wref;
};

/// A type for storing the parameters of the HKF equation of state for a gaseous species
struct GaseousSpeciesThermoParamsHKF
{
    /// The apparent standard molal Gibbs free energy of formation of the species from its elements (in units of cal/mol)
    double Gf;

    /// The apparent standard molal enthalpy of formation of the species from its elements (in units of cal/mol)
    double Hf;

    /// The standard molal entropy of the species at reference temperature and pressure (in units of cal/(mol�K))
    double Sr;

    /// The coefficient a of the HKF equation of state of the gaseous species (in units of cal/(mol�K))
    double a;

    /// The coefficient b of the HKF equation of state of the gaseous species (in units of cal/(mol�K^2))
    double b;

    /// The coefficient c of the HKF equation of state of the gaseous species (in units of (cal�K)/mol)
    double c;

    /// The maximum temperature at which the HKF equation of state can be applied for the gaseous species (in units of K)
    double Tmax;
};

/// A type for storing the parameters of the HKF equation of state for a mineral species
struct MineralSpeciesThermoParamsHKF
{
    /// The apparent standard molal Gibbs free energy of formation of the species from its elements (in units of cal/mol)
    double Gf;

    /// The apparent standard molal enthalpy of formation of the species from its elements (in units of cal/mol)
    double Hf;

    /// The standard molal entropy of the species at reference temperature and pressure (in units of cal/(mol�K))
    double Sr;

    /// The standard molal volume of the mineral species at reference temperature and pressure (in units of cm^3/mol)
    double Vr;

    /// The number of phase transitions that the mineral may undergo
    int nptrans;

    /// The coefficients ai of the HKF equation of state of the mineral species for each phase region (in units of cal/(mol�K))
    std::vector<double> a;

    /// The coefficients bi of the HKF equation of state of the mineral species for each phase region (in units of cal/(mol�K^2))
    std::vector<double> b;

    /// The coefficients ci of the HKF equation of state of the mineral species for each phase region (in units of (cal�K)/mol)
    std::vector<double> c;

    /// The temperatures at which the mineral experiences phase transition along the line of reference pressure (in units of K)
    std::vector<double> Ttr;

    /// The change in the standard molal enthalpy of each mineral phase transition (in units of cal/mol)
    std::vector<double> Htr;

    /// The change in the standard molal volume of each mineral phase transition (in units of cm^3/mol)
    std::vector<double> Vtr;

    /// The Clapeyron slote at each mineral phase transition (in units of bar/K)
    std::vector<double> dPdTtr;

    /// The maximum temperature at which the HKF equation of state can be applied for the mineral (in units of K)
    double Tmax;
};

/// A type for storing the thermodynamic data of an aqueous species
struct AqueousSpeciesThermoData
{
    /// The thermodynamic properties of an aqueous species
    Optional<SpeciesThermoProperties> properties;

    /// The thermodynamic properties of an aqueous species given in terms of reaction
    Optional<ReactionThermoProperties> reaction;

    /// The thermodynamic parameters of the HKF model for an aqueous species
    Optional<AqueousSpeciesThermoParamsHKF> hkf;
};

/// A type for storing the thermodynamic data of a gaseous species
struct GaseousSpeciesThermoData
{
    /// The thermodynamic properties of a gaseous species
    Optional<SpeciesThermoProperties> properties;

    /// The thermodynamic properties of a gaseous species given in terms of reaction
    Optional<ReactionThermoProperties> reaction;

    /// The thermodynamic parameters of the HKF model for a gaseous species
    Optional<GaseousSpeciesThermoParamsHKF> hkf;
};

/// A type for storing the thermodynamic data of a mineral species
struct MineralSpeciesThermoData
{
    /// The thermodynamic properties of a mineral species
    Optional<SpeciesThermoProperties> properties;

    /// The thermodynamic properties of a mineral species given in terms of reaction
    Optional<ReactionThermoProperties> reaction;

    /// The thermodynamic parameters of the HKF model for a mineral species
    Optional<MineralSpeciesThermoParamsHKF> hkf;
};

} // namespace Reaktor


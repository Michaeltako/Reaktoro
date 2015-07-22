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

#include "AqueousActivityModelDuanSunCO2.hpp"

// Reaktoro includes
#include <Reaktoro/Common/ChemicalScalar.hpp>
#include <Reaktoro/Common/ThermoScalar.hpp>
#include <Reaktoro/Thermodynamics/Mixtures/AqueousMixture.hpp>

namespace Reaktoro {
namespace {

/// The lambda coefficients for the activity coefficient of CO2(aq)
const double lambda_coeffs[] =
{
    -0.411370585,
     6.07632013e-4,
     97.5347708,
     0.0,
     0.0,
     0.0,
     0.0,
    -0.0237622469,
     0.0170656236,
     0.0,
     1.41335834e-5
};

/// The zeta coefficients for the activity coefficient of CO2(aq)
const double zeta_coeffs[] =
{
     3.36389723e-4,
    -1.98298980e-5,
     0.0,
     0.0,
     0.0,
     0.0,
     0.0,
     2.12220830e-3,
    -5.24873303e-3,
     0.0,
     0.0
};

auto paramDuanSun(const ThermoScalar& T, const ThermoScalar& P, const double coeffs[]) -> ThermoScalar
{
    // Convert pressure from pascal to bar
    const ThermoScalar Pbar = 1e-5 * P;

    const double c1  = coeffs[0];
    const double c2  = coeffs[1];
    const double c3  = coeffs[2];
    const double c4  = coeffs[3];
    const double c5  = coeffs[4];
    const double c6  = coeffs[5];
    const double c7  = coeffs[6];
    const double c8  = coeffs[7];
    const double c9  = coeffs[8];
    const double c10 = coeffs[9];
    const double c11 = coeffs[10];

    return c1 + c2*T + c3/T + c4*T*T + c5/(630 - T) +
        c6*Pbar + c7*Pbar*log(T) + c8*Pbar/T + c9*Pbar/(630 - T) +
        c10*Pbar*Pbar/(630 - T)/(630 - T) + c11*T*log(Pbar);
}

} // namespace

auto aqueousActivityModelDuanSunCO2(const AqueousMixture& mixture) -> AqueousActivityModel
{
    // The number of speciesn and charged species
    const unsigned nspecies = mixture.numSpecies();
    const unsigned nions = mixture.numChargedSpecies();

    // The local indices of some charged species among all charged species
    const Index iNa  = mixture.indexChargedSpecies("Na+");
    const Index iK   = mixture.indexChargedSpecies("K+");
    const Index iCa  = mixture.indexChargedSpecies("Ca++");
    const Index iMg  = mixture.indexChargedSpecies("Mg++");
    const Index iCl  = mixture.indexChargedSpecies("Cl-");
    const Index iSO4 = mixture.indexChargedSpecies("SO4--");

    AqueousActivityModel f = [=](const AqueousMixtureState& state)
    {
        // Extract temperature and pressure values
        const ThermoScalar T = ThermoScalar::Temperature(state.T);
        const ThermoScalar P = ThermoScalar::Pressure(state.P);

        // The stoichiometric molalities of the ions in the aqueous mixture and their molar derivatives
        const auto& ms = state.ms;

        // The parameters lambda and zeta of activity coefficient model
        const ThermoScalar lambda = paramDuanSun(T, P, lambda_coeffs);
        const ThermoScalar zeta   = paramDuanSun(T, P, zeta_coeffs);

        // The stoichiometric molalities of the specific ions and their molar derivatives
        ChemicalScalar zero(nspecies);
        ChemicalScalar mNa  = (iNa  < nions) ? ms[iNa]  : zero;
        ChemicalScalar mK   = (iK   < nions) ? ms[iK]   : zero;
        ChemicalScalar mCa  = (iCa  < nions) ? ms[iCa]  : zero;
        ChemicalScalar mMg  = (iMg  < nions) ? ms[iMg]  : zero;
        ChemicalScalar mCl  = (iCl  < nions) ? ms[iCl]  : zero;
        ChemicalScalar mSO4 = (iSO4 < nions) ? ms[iSO4] : zero;

        // The ln activity coefficient of CO2(aq)
        ChemicalScalar ln_gCO2 = 2*lambda*(mNa + mK + 2*mCa + 2*mMg) +
            zeta*(mNa + mK + mCa + mMg)*mCl - 0.07*mSO4;

        return ln_gCO2;
    };

    return f;
}

} // namespace Reaktoro
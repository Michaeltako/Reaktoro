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

#include "WaterElectroStateUtils.hpp"

// C++ includes
#include <cmath>
using namespace std;

// Reaktor includes
#include <Reaktor/Thermodynamics/WaterElectroState.hpp>
#include <Reaktor/Thermodynamics/WaterThermoState.hpp>

namespace Reaktor {
namespace internal {

// Reference:
// 		- Johnson, J. W. and Norton, D., 1991, Critical phenomena in hydrothermal system: State,
// 		  thermodynamic, electrostatic, and transport properties of H2O in the critical region,
// 		  Amer. Jour. Sci., v. 291, pp. 541-648.

// The reference temperature (in K) and density (in kg/m3) for the calculation of
// the dielectric constant of water and its partial derivatives
const double kReferenceTemperature = 298.15;
const double kReferenceDensity = 1000.0;

const double a[] =
{
	 0.0000000000e+00,
	 0.1470333593e+02,
	 0.2128462733e+03,
	-0.1154445173e+03,
	 0.1955210915e+02,
	-0.8330347980e+02,
	 0.3213240048e+02,
	-0.6694098645e+01,
	-0.3786202045e+02,
	 0.6887359646e+02,
	-0.2729401652e+02
};

inline auto k0(double t)    -> double { return 1.0; }
inline auto k1(double t)    -> double { return a[1]/t; }
inline auto k2(double t)    -> double { return a[2]/t + a[3] + a[4]*t; }
inline auto k3(double t)    -> double { return a[5]/t + a[6]*t + a[7]*t*t; }
inline auto k4(double t)    -> double { return a[8]/t/t + a[9]/t + a[10]; }

inline auto k0_t(double t)  -> double { return 0.0; }
inline auto k1_t(double t)  -> double { return -a[1]/(t*t); }
inline auto k2_t(double t)  -> double { return -a[2]/(t*t) + a[4]; }
inline auto k3_t(double t)  -> double { return -a[5]/(t*t) + a[6] + 2*a[7]*t; }
inline auto k4_t(double t)  -> double { return -2*a[8]/(t*t*t) - a[9]/(t*t); }

inline auto k0_tt(double t) -> double { return 0.0; }
inline auto k1_tt(double t) -> double { return 2*a[1]/(t*t*t); }
inline auto k2_tt(double t) -> double { return 2*a[2]/(t*t*t); }
inline auto k3_tt(double t) -> double { return 2*a[5]/(t*t*t) + 2*a[7]; }
inline auto k4_tt(double t) -> double { return 6*a[8]/(t*t*t*t) + 2*a[9]/(t*t*t); }

double (*k[5])(double)    = {k0, k1, k2, k3, k4};
double (*k_t[5])(double)  = {k0_t, k1_t, k2_t, k3_t, k4_t};
double (*k_tt[5])(double) = {k0_tt, k1_tt, k2_tt, k3_tt, k4_tt};

} /* namespace internal */

using namespace internal;

auto waterElectroStateJohnsonNorton(double T, double P, const WaterThermoState& wt) -> WaterElectroState
{
	WaterElectroState we;

	const double alpha  = -wt.densityT/wt.density;
    const double beta   =  wt.densityP/wt.density;
    const double alphaT = -wt.densityTT/wt.density + alpha*alpha;
    const double betaT  =  wt.densityTP/wt.density + alpha*beta;
    const double betaP  =  wt.densityPP/wt.density - beta*beta;

    const double Tr = kReferenceTemperature;
    const double Dr = kReferenceDensity;

	const double t = T/Tr;
	const double r = wt.density/Dr;

	for(int i = 0; i <= 4; ++i)
	{
		const double ri    = pow(r, i);
		const double ki    = k[i](t);
		const double ki_t  = k_t[i](t)/Tr;
		const double ki_tt = k_tt[i](t)/Tr/Tr;

		we.epsilon   += ki*ri;
		we.epsilonT  += ri*(ki_t - i*alpha*ki);
		we.epsilonP  += ri*ki*i*beta;
		we.epsilonTT += ri*(ki_tt - i*(alpha*ki_t + ki*alphaT) - i*alpha*(ki_t - i*alpha*ki));
		we.epsilonTP += ri*ki*i*beta*(ki_t/ki - i*alpha + betaT/beta);
		we.epsilonPP += ri*ki*i*beta*(i*beta + betaP/beta);
	}

	const double epsilon2 = we.epsilon * we.epsilon;

	we.bornZ = -1.0/we.epsilon;
	we.bornY = we.epsilonT/epsilon2;
	we.bornQ = we.epsilonP/epsilon2;
	we.bornU = we.epsilonTP/epsilon2 - 2*we.bornY*we.bornQ*we.epsilon;
	we.bornN = we.epsilonPP/epsilon2 - 2*we.bornQ*we.bornQ*we.epsilon;
	we.bornX = we.epsilonTT/epsilon2 - 2*we.bornY*we.bornY*we.epsilon;

	return we;
}

} // namespace Reaktor
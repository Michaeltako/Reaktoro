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
#include "EquilibriumUtils.hpp"

// Reaktoro includes
#include <Reaktoro/Common/Exception.hpp>
#include <Reaktoro/Core/ChemicalSystem.hpp>
#include <Reaktoro/Core/Partition.hpp>
#include <Reaktoro/Equilibrium/EquilibriumInverseProblem.hpp>
#include <Reaktoro/Equilibrium/EquilibriumInverseSolver.hpp>
#include <Reaktoro/Equilibrium/EquilibriumOptions.hpp>
#include <Reaktoro/Equilibrium/EquilibriumProblem.hpp>
#include <Reaktoro/Equilibrium/EquilibriumResult.hpp>
#include <Reaktoro/Equilibrium/EquilibriumSensitivity.hpp>
#include <Reaktoro/Equilibrium/EquilibriumSolver.hpp>
#include <Reaktoro/Equilibrium/EquilibriumState.hpp>

namespace Reaktoro {
namespace {

auto equilibrateAux(EquilibriumState& state, const EquilibriumProblem& problem, EquilibriumOptions options) -> EquilibriumResult
{
    // Define auxiliary references to problem data
    const auto& system = problem.system();
    const auto& partition = problem.partition();
    const auto& iee = partition.indicesEquilibriumElements();
    const auto& T = problem.temperature();
    const auto& P = problem.pressure();
    const auto& b = problem.elementAmounts();
    const auto& be = rows(b, iee);

    // The result of the equilibrium calculation
    EquilibriumResult res;

    // Perform a direct equilibrium calculation
    EquilibriumSolver solver(system);
    solver.setPartition(partition);
    solver.setOptions(options);
    res = solver.solve(state, T, P, be);

    // Assert the calculation succeeded
    Assert(res.optimum.succeeded, "Could not calculate the equilibrium state of the system.",
        "Convergence could not be established with given equilibrium conditions, "
        "initial guess, and/or numerical parameters.");

    return res;
}

auto equilibrateAux(EquilibriumState& state, const EquilibriumInverseProblem& problem, EquilibriumOptions options) -> EquilibriumResult
{
    // Define auxiliary references to problem data
    const auto& system = problem.system();
    const auto& partition = problem.partition();

    // The result of the equilibrium calculation
    EquilibriumResult res;

    // Perform an inverse equilibrium calculation
    EquilibriumInverseSolver solver(system);
    solver.setPartition(partition);
    solver.setOptions(options);
    res = solver.solve(state, problem);

    // Assert the calculation succeeded
    Assert(res.optimum.succeeded, "Could not calculate the equilibrium state of the system.",
        "Convergence could not be established with given equilibrium conditions, "
        "initial guess, and/or numerical parameters.");

    return res;
}

} // namespace

auto equilibrate(EquilibriumState& state) -> EquilibriumResult
{
    EquilibriumOptions options;
    return equilibrate(state, options);
}

auto equilibrate(EquilibriumState& state, const Partition& partition) -> EquilibriumResult
{
    return equilibrate(state, partition, {});
}

auto equilibrate(EquilibriumState& state, const EquilibriumOptions& options) -> EquilibriumResult
{
    ChemicalSystem system = state.system();

    return equilibrate(state, Partition(system), options);
}

auto equilibrate(EquilibriumState& state, const Partition& partition, const EquilibriumOptions& options) -> EquilibriumResult
{
    ChemicalSystem system = state.system();

    EquilibriumProblem problem(system);
    problem.setPartition(partition);
    problem.setTemperature(state.temperature());
    problem.setPressure(state.pressure());
    problem.setElementAmounts(state.elementAmounts());

    return equilibrate(state, problem, options);
}

auto equilibrate(EquilibriumState& state, const EquilibriumProblem& problem) -> EquilibriumResult
{
    return equilibrate(state, problem, {});
}

auto equilibrate(EquilibriumState& state, const EquilibriumProblem& problem, const EquilibriumOptions& options) -> EquilibriumResult
{
    return equilibrateAux(state, problem, options);
}

auto equilibrate(const EquilibriumProblem& problem) -> EquilibriumState
{
    return equilibrate(problem, {});
}

auto equilibrate(const EquilibriumProblem& problem, const EquilibriumOptions& options) -> EquilibriumState
{
    EquilibriumState state(problem.system());
    equilibrate(state, problem, options);
    return state;
}

auto equilibrate(EquilibriumState& state, const EquilibriumInverseProblem& problem) -> EquilibriumResult
{
    return equilibrate(state, problem, {});
}

auto equilibrate(EquilibriumState& state, const EquilibriumInverseProblem& problem, const EquilibriumOptions& options) -> EquilibriumResult
{
    return equilibrateAux(state, problem, options);
}

auto equilibrate(const EquilibriumInverseProblem& problem) -> EquilibriumState
{
    return equilibrate(problem, {});
}

auto equilibrate(const EquilibriumInverseProblem& problem, const EquilibriumOptions& options) -> EquilibriumState
{
    EquilibriumState state(problem.system());
    equilibrate(state, problem, options);
    return state;
}

} // namespace Reaktoro

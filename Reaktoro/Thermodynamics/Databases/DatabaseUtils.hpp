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

// C++ includes
#include <string>
#include <vector>

namespace Reaktoro {

/// Return the contents of a built-in database as a string.
/// This method searches among all built-in databases and
/// return the database file as a string. If the given
/// database `name` is not found, an empty string is returned.
/// @param name The name of the database.
/// @see databases
auto database(std::string name) -> std::string;

/// Return the list of names of all built-in databases.
auto databases() -> std::vector<std::string>;

} // namespace Reaktoro

// This file is part of 4C multiphysics licensed under the
// GNU Lesser General Public License v3.0 or later.
//
// See the LICENSE.md file in the top-level for license information.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef FOUR_C_SOLID_PORO_3D_ELE_FACTORY_HPP
#define FOUR_C_SOLID_PORO_3D_ELE_FACTORY_HPP

#include "4C_config.hpp"

#include "4C_fem_general_cell_type_traits.hpp"
#include "4C_fem_general_element.hpp"
#include "4C_solid_3D_ele_factory_lib.hpp"
#include "4C_solid_poro_3D_ele_calc_pressure_based.hpp"
#include "4C_solid_poro_3D_ele_calc_pressure_velocity_based.hpp"

#include <memory>
#include <variant>

FOUR_C_NAMESPACE_OPEN

namespace Discret::Elements
{

  namespace Internal
  {
    using ImplementedSolidPoroCellTypes = Core::FE::CelltypeSequence<Core::FE::CellType::hex8,
        Core::FE::CellType::hex27, Core::FE::CellType::tet4, Core::FE::CellType::tet10>;

    using PoroPressureBasedEvaluators =
        Core::FE::apply_celltype_sequence<Discret::Elements::SolidPoroPressureBasedEleCalc,
            ImplementedSolidPoroCellTypes>;

    using SolidPoroPressureBasedEvaluators = Core::FE::Join<PoroPressureBasedEvaluators>;

    using ImplementedSolidPoroPressureVelocityBasedCellTypes =
        Core::FE::CelltypeSequence<Core::FE::CellType::hex8, Core::FE::CellType::hex27,
            Core::FE::CellType::tet4, Core::FE::CellType::tet10>;


    using PoroPressureVelocityBasedEvaluators =
        Core::FE::apply_celltype_sequence<Discret::Elements::SolidPoroPressureVelocityBasedEleCalc,
            ImplementedSolidPoroPressureVelocityBasedCellTypes>;


    using SolidPoroPressureVelocityBasedEvaluators =
        Core::FE::Join<PoroPressureVelocityBasedEvaluators>;


  }  // namespace Internal


  using SolidPoroPressureBasedCalcVariant =
      CreateVariantType<Internal::SolidPoroPressureBasedEvaluators>;

  SolidPoroPressureBasedCalcVariant create_solid_poro_pressure_based_calculation_interface(
      Core::FE::CellType celltype);

  template <Core::FE::CellType celltype>
  SolidPoroPressureBasedCalcVariant create_solid_poro_pressure_based_calculation_interface();

  using SolidPoroPressureVelocityBasedCalcVariant =
      CreateVariantType<Internal::SolidPoroPressureVelocityBasedEvaluators>;


  SolidPoroPressureVelocityBasedCalcVariant
  create_solid_poro_pressure_velocity_based_calculation_interface(Core::FE::CellType celltype);

  template <Core::FE::CellType celltype>
  SolidPoroPressureVelocityBasedCalcVariant
  create_solid_poro_pressure_velocity_based_calculation_interface();

}  // namespace Discret::Elements


FOUR_C_NAMESPACE_CLOSE

#endif
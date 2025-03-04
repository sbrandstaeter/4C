# This file is part of 4C multiphysics licensed under the
# GNU Lesser General Public License v3.0 or later.
#
# See the LICENSE.md file in the top-level for license information.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

# A function to search for and configure an external dependency
function(four_c_configure_dependency _package_name)
  set(options "")
  set(oneValueArgs DEFAULT)
  set(multiValueArgs "")
  cmake_parse_arguments(
    _parsed
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
    )

  if(DEFINED _parsed_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "There are unparsed arguments: ${_parsed_UNPARSED_ARGUMENTS}")
  endif()

  # Sanitize the package name: all upper case, no hyphens and dots.
  string(TOUPPER ${_package_name} _package_name_SANITIZED)
  string(REGEX REPLACE "[^A-Z0-9]" "_" _package_name_SANITIZED ${_package_name_SANITIZED})

  # Add a cache entry to turn the option ON or OFF.
  four_c_process_global_option(
    FOUR_C_WITH_${_package_name_SANITIZED} "Build 4C with ${_package_name}" ${_parsed_DEFAULT}
    )

  if(FOUR_C_WITH_${_package_name_SANITIZED})
    if(${_package_name}_ROOT)
      message(
        WARNING
          "A variable '${_package_name}_ROOT' is set. Prefer setting it via 'FOUR_C_${_package_name_SANITIZED}_ROOT'."
        )
    endif()

    if(FOUR_C_${_package_name_SANITIZED}_ROOT)
      # Translate the ROOT variable into the case style that fits to the package name.
      # This variable is automatically understood by CMake's find_XXX functions.
      set(${_package_name}_ROOT ${FOUR_C_${_package_name_SANITIZED}_ROOT})
    else()
      message(
        STATUS
          "No variable 'FOUR_C_${_package_name_SANITIZED}_ROOT' set. Trying to find ${_package_name} in default locations."
        )
    endif()

    # Hand over the actual configuration to a separate script.
    include(cmake/configure/configure_${_package_name}.cmake)
  endif()

  # Store the flag that was generated from the package name
  set_property(
    GLOBAL APPEND
    PROPERTY FOUR_C_FLAGS_EXTERNAL_DEPENDENCIES FOUR_C_WITH_${_package_name_SANITIZED}
    )

  message(STATUS "Processed dependency ${_package_name}.\n")
endfunction()

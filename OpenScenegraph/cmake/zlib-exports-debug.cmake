#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MINIZIP::aes" for configuration "Debug"
set_property(TARGET MINIZIP::aes APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::aes PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/aesd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS MINIZIP::aes )
list(APPEND _IMPORT_CHECK_FILES_FOR_MINIZIP::aes "${_IMPORT_PREFIX}/lib/aesd.lib" )

# Import target "MINIZIP::minizip" for configuration "Debug"
set_property(TARGET MINIZIP::minizip APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MINIZIP::minizip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "MINIZIP::aes"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/minizipd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS MINIZIP::minizip )
list(APPEND _IMPORT_CHECK_FILES_FOR_MINIZIP::minizip "${_IMPORT_PREFIX}/lib/minizipd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

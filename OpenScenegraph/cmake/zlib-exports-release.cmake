#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MINIZIP::aes" for configuration "Release"
set_property(TARGET MINIZIP::aes APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::aes PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/aes.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS MINIZIP::aes )
list(APPEND _IMPORT_CHECK_FILES_FOR_MINIZIP::aes "${_IMPORT_PREFIX}/lib/aes.lib" )

# Import target "MINIZIP::minizip" for configuration "Release"
set_property(TARGET MINIZIP::minizip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(MINIZIP::minizip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "MINIZIP::aes"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/minizip.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS MINIZIP::minizip )
list(APPEND _IMPORT_CHECK_FILES_FOR_MINIZIP::minizip "${_IMPORT_PREFIX}/lib/minizip.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

# - Find mpg123
# Find the mpg123 libraries
#  This module defines the following variables:
#     MPG123_FOUND       - True if MPG123_INCLUDE_DIR & MPG123_LIBRARY are found
#     MPG123_LIBRARIES   - Set when MPG123_LIBRARY is found
#     MPG123_INCLUDE_DIRS - Set when MPG123_INCLUDE_DIR is found
#
#     MPG123_INCLUDE_DIR - where to find asoundlib.h, etc.
#     MPG123_LIBRARY     - the asound library
#

#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

find_path(MPG123_INCLUDE_DIR NAMES mpg123.h
          DOC "The mpg123 include directory"
)

find_library(MPG123_LIBRARY NAMES mpg123
          DOC "The mpg123 library"
)

# handle the QUIETLY and REQUIRED arguments and set MPG123_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MPG123 DEFAULT_MSG MPG123_LIBRARY MPG123_INCLUDE_DIR)

if(MPG123_FOUND)
  set( MPG123_LIBRARIES ${MPG123_LIBRARY} )
  set( MPG123_INCLUDE_DIRS ${MPG123_INCLUDE_DIR} )
endif()

mark_as_advanced(MPG123_INCLUDE_DIR MPG123_LIBRARY)

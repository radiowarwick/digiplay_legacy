# - Find flac++
# Find the flac++ libraries
#  This module defines the following variables:
#     FLAC_FOUND       - True if FLAC_INCLUDE_DIR & FLAC_LIBRARY are found
#     FLAC_LIBRARIES   - Set when FLAC_LIBRARY is found
#     FLAC_INCLUDE_DIRS - Set when FLAC_INCLUDE_DIR is found
#
#     FLAC_INCLUDE_DIR - where to find asoundlib.h, etc.
#     FLAC_LIBRARY     - the asound library
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

find_path(FLAC_INCLUDE_DIR NAMES decoder.h
          PATH_SUFFIXES FLAC++
          DOC "The FLAC++ include directory"
)

find_library(FLAC_LIBRARY NAMES FLAC++
          DOC "The FLAC++ library"
)

# handle the QUIETLY and REQUIRED arguments and set FLAC_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FLAC DEFAULT_MSG FLAC_LIBRARY FLAC_INCLUDE_DIR)

if(FLAC_FOUND)
  set( FLAC_LIBRARIES ${FLAC_LIBRARY} )
  set( FLAC_INCLUDE_DIRS ${FLAC_INCLUDE_DIR} )
endif()

mark_as_advanced(FLAC_INCLUDE_DIR FLAC_LIBRARY)

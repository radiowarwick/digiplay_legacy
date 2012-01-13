# - Find jack
# Find the jack libraries
#  This module defines the following variables:
#     JACK_FOUND       - True if JACK_INCLUDE_DIR & JACK_LIBRARY are found
#     JACK_LIBRARIES   - Set when JACK_LIBRARY is found
#     JACK_INCLUDE_DIRS - Set when JACK_INCLUDE_DIR is found
#
#     JACK_INCLUDE_DIR - where to find asoundlib.h, etc.
#     JACK_LIBRARY     - the asound library
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

find_path(JACK_INCLUDE_DIR NAMES jack.h
          PATH_SUFFIXES jack
          DOC "The Jack include directory"
)

find_library(JACK_LIBRARY NAMES jack
          DOC "The Jack library"
)

# handle the QUIETLY and REQUIRED arguments and set JACK_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JACK DEFAULT_MSG JACK_LIBRARY JACK_INCLUDE_DIR)

if(JACK_FOUND)
  set( JACK_LIBRARIES ${JACK_LIBRARY} )
  set( JACK_INCLUDE_DIRS ${JACK_INCLUDE_DIR} )
endif()

mark_as_advanced(JACK_INCLUDE_DIR JACK_LIBRARY)

cmake_minimum_required(VERSION 2.6)

project(Digiplay)
set(VERSION 0.99)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/dist CACHE PATH "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/src ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "-Wall -O3 -D_THREAD_SAFE -D_FILE_OFFSET_BITS=64 -DDEBUG=4 -fPIC -DVERSION=\"${VERSION}\" -DDPSDIR=\"\\\"${CMAKE_INSTALL_PREFIX}/share/dps\\\"\"")

include_directories(${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/audiolib)

include(CMakeDependentOption)
option(BUILD_AUDIO_LIBRARY "Build audio library." ON)
option(BUILD_STUDIO_MANAGE "Build studio management application." ON)
option(BUILD_SUE_SCHED "Build sustainer scheduler application." ON)
option(BUILD_ADMIN "Build digiplay administration tool." ON)
CMAKE_DEPENDENT_OPTION(BUILD_STUDIO_PLAY "Build studio playout application." ON
                        "BUILD_AUDIO_LIBRARY" OFF)
CMAKE_DEPENDENT_OPTION(BUILD_SUE_PLAY "Build sustainer playout application." ON
                        "BUILD_AUDIO_LIBRARY" OFF)

CMAKE_DEPENDENT_OPTION(ENABLE_FLAC "Enable FLAC audio support." OFF
                        "BUILD_AUDIO_LIBRARY" OFF)
CMAKE_DEPENDENT_OPTION(ENABLE_MP3 "Enable MP3 audio support." OFF
                        "BUILD_AUDIO_LIBRARY" OFF)
CMAKE_DEPENDENT_OPTION(ENABLE_JACK "Enable JACK audio support." OFF
                        "BUILD_AUDIO_LIBRARY" OFF)
CMAKE_DEPENDENT_OPTION(ENABLE_ALSA "Enable ALSA audio support." ON
                        "BUILD_AUDIO_LIBRARY" OFF)
CMAKE_DEPENDENT_OPTION(ENABLE_OSS "Enable OSS audio support." ON
                        "BUILD_AUDIO_LIBRARY" OFF)

add_subdirectory(src)

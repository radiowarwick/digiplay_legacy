set(STUDIO_PLAY_SOURCES frmPlayout.cpp
                        AudioPlayer.cpp
                        AudioWall.cpp
                        AudioWallDriver.cpp
                        AudioWallItem.cpp
                        AudioWallManager.cpp
                        RemoteStartThread.cpp
                        ../Config.cpp
                        ../Logger.cpp
                        ../dps.cpp
                        ../DataAccess.cpp
                        ../Security.cpp
                        ../clockThread.cpp
                        ../Thread.cpp
                        ../DbTrigger.cpp
                        ../MessagingInterface.cpp
                        ../QtTrigger.cpp
                        main.cpp
    )

set(STUDIO_PLAY_HEADERS frmPlayout.h
                        AudioPlayer.h
                        AudioWall.h
                        AudioWallDriver.h
                        AudioWallItem.h
                        AudioWallManager.h
                        RemoteStartThread.h
                        ../QtTrigger.h
    )

set(STUDIO_PLAY_RCCS    ../DpsResources.qrc)

find_library(M_LIB m)
mark_as_advanced(M_LIB)
find_package(Threads)
find_package(Pqxx)
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)

include_directories(${Pqxx_INCLUDE_DIRS})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
QT4_ADD_RESOURCES(STUDIO_PLAY_RCC_SRCS ${STUDIO_PLAY_RCCS})
QT4_WRAP_CPP(STUDIO_PLAY_HEADERS_MOC ${STUDIO_PLAY_HEADERS})

add_executable(studio_play ${STUDIO_PLAY_SOURCES}
                           ${STUDIO_PLAY_HEADERS_MOC}
                           ${STUDIO_PLAY_RCC_SRCS})
target_link_libraries(studio_play dpsaudio)
target_link_libraries(studio_play ${QT_LIBRARIES})
target_link_libraries(studio_play ${Pqxx_LIBRARIES})
target_link_libraries(studio_play ${M_LIB})
target_link_libraries(studio_play ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(studio_play PROPERTIES VERSION ${VERSION})
add_dependencies(studio_play dpsaudio)

install(TARGETS studio_play
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )


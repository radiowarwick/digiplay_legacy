set(SUE_PLAY_SOURCES    sueplay.cpp
                        ../DataAccess.cpp
                        ../Config.cpp
                        ../Logger.cpp
                        ../Security.cpp
                        ../dps.cpp
                        ../DbTrigger.cpp
                        ../Thread.cpp
    )

set(SUESCHED_HEADERS    ../DataAccess.h
                        ../Config.h
                        ../Logger.h
                        ../Security.h
                        ../dps.h
                        ../DbTrigger.h
                        ../Thread.h
    )

find_library(M_LIB m)
find_package(Threads)
find_package(Pqxx)

add_executable(sueplay ${SUE_PLAY_SOURCES})
target_link_libraries(sueplay ${Pqxx_LIBRARIES})
target_link_libraries(sueplay ${M_LIB})
target_link_libraries(sueplay ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(sueplay dpsaudio)
set_target_properties(sueplay PROPERTIES VERSION ${VERSION})
install(TARGETS sueplay
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

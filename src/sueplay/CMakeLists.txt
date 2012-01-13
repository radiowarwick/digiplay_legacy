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

add_executable(sueplay ${SUE_PLAY_SOURCES})
target_link_libraries(sueplay pqxx)
target_link_libraries(sueplay m)
target_link_libraries(sueplay pthread)
target_link_libraries(sueplay dpsaudio)
set_target_properties(sueplay PROPERTIES VERSION ${VERSION})
install(TARGETS sueplay
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

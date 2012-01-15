SET(PLAYIN_SOURCES  main.cpp
                    md5.c
                    ../Config.cpp
                    ../dps.cpp
                    ../DbTrigger.cpp
                    ../Thread.cpp
                    ../DataAccess.cpp
                    ../Logger.cpp
                    ../Security.cpp
                    ../SystemManager.cpp
                    ../ArchiveManager.cpp
                    ../XmlDocument.cpp
                    ../XmlElement.cpp
)

find_package(Threads)
find_package(Pqxx)
find_package(Curses)

add_executable(playin ${PLAYIN_SOURCES})
target_link_libraries(playin ${CURSES_LIBRARIES})
target_link_libraries(playin ${Pqxx_LIBRARIES})
target_link_libraries(playin ${M_LIB})
target_link_libraries(playin ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(playin PROPERTIES VERSION ${VERSION})
install(TARGETS playin
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

set(ADMIN_SOURCES       dpsadmin.cpp
                        ../SystemManager.cpp
                        ../ArchiveManager.cpp
                        ../UserManager.cpp
                        ../GroupManager.cpp
                        ../MusicManager.cpp
                        ../LocationManager.cpp
                        ../XmlDocument.cpp
                        ../XmlElement.cpp
                        ../DataAccess.cpp
                        ../Config.cpp
                        ../Logger.cpp
                        ../Security.cpp
                        ../dps.cpp
                        ../DbTrigger.cpp
                        ../Thread.cpp
    )

set(ADMIN_HEADERS       ../SystemManager.h
                        ../ArchiveManager.h
                        ../UserManager.h
                        ../GroupManager.h
                        ../MusicManager.h
                        ../LocationManager.h
                        ../XmlDocument.h
                        ../XmlElement.h
                        ../DataAccess.h
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

add_executable(dpsadmin ${ADMIN_SOURCES})
target_link_libraries(dpsadmin ${Pqxx_LIBRARIES})
target_link_libraries(dpsadmin ${M_LIB})
target_link_libraries(dpsadmin ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(dpsadmin PROPERTIES VERSION ${VERSION})
install(TARGETS dpsadmin
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

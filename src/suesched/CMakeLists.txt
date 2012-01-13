set(SUESCHED_SOURCES    suesched.cpp
                        sched_bin.cpp
                        schedule.cpp
                        scheduler.cpp
                        ../DataAccess.cpp
                        ../Config.cpp
                        ../Logger.cpp
                        ../Security.cpp
                        ../dps.cpp
                        ../DbTrigger.cpp
                        ../Thread.cpp
    )

set(SUESCHED_HEADERS    sched_bin.h
                        schedule.h
                        scheduler.h
                        ../DataAccess.h
                        ../Config.h
                        ../Logger.h
                        ../Security.h
                        ../dps.h
                        ../DbTrigger.h
                        ../Thread.h
    )

add_executable(suesched ${SUESCHED_SOURCES})
target_link_libraries(suesched pqxx)
target_link_libraries(suesched m)
target_link_libraries(suesched pthread)
set_target_properties(suesched PROPERTIES VERSION ${VERSION})
install(TARGETS suesched
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

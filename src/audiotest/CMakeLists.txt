find_library(M_LIB m)
find_library(READLINE_LIBRARY readline)
find_package(Threads)
find_package(Pqxx)

add_executable(audiotest audiotest.cpp)
target_link_libraries(audiotest dpsaudio)
target_link_libraries(audiotest ${Pqxx_LIBRARIES})
target_link_libraries(audiotest ${READLINE_LIBRARY})
target_link_libraries(audiotest ${M_LIB})
target_link_libraries(audiotest ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(audiotest PROPERTIES VERSION ${VERSION})

install(TARGETS audiotest
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

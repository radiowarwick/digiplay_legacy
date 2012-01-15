find_library(M_LIB m)
find_library(READLINE_LIBRARY readline)
find_package(Threads)
find_package(Pqxx)

add_executable(audioflac audioflac.cpp)
target_link_libraries(audioflac dpsaudio)
target_link_libraries(audioflac ${Pqxx_LIBRARIES})
target_link_libraries(audioflac ${READLINE_LIBRARY})
target_link_libraries(audioflac ${M_LIB})
target_link_libraries(audioflac ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(audioflac PROPERTIES VERSION ${VERSION})

install(TARGETS audioflac
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

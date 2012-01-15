find_library(M_LIB m)
find_library(READLINE_LIBRARY readline)
find_package(Threads)
find_package(Pqxx)

add_executable(audioplay audioplay.cpp)
target_link_libraries(audioplay dpsaudio)
target_link_libraries(audioplay ${Pqxx_LIBRARIES})
target_link_libraries(audioplay ${READLINE_LIBRARY})
target_link_libraries(audioplay ${M_LIB})
target_link_libraries(audioplay ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS audioplay
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

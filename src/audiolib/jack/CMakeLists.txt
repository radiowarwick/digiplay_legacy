set(AUDIOLIB_JACK_SOURCES OutputDspJack.cpp)

find_package(Jack)

add_library(dpsaudio-jack SHARED ${AUDIOLIB_JACK_SOURCES})
target_link_libraries(dpsaudio-jack ${JACK_LIBRARY})
set_target_properties(dpsaudio-jack PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-jack
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

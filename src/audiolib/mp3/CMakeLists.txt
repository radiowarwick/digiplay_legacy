set(AUDIOLIB_MP3_SOURCES InputMp3.cpp)

find_package(MPG123)

add_library(dpsaudio-mp3 SHARED ${AUDIOLIB_MP3_SOURCES})
target_link_libraries(dpsaudio-mp3 ${MPG123_LIBRARY})
set_target_properties(dpsaudio-mp3 PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-mp3
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

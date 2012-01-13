set(AUDIOLIB_ALSA_SOURCES OutputDspAlsa.cpp)

find_package(ALSA)

add_library(dpsaudio-alsa SHARED ${AUDIOLIB_ALSA_SOURCES})
target_link_libraries(dpsaudio-alsa ${ALSA_LIBRARY})
set_target_properties(dpsaudio-alsa PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-alsa
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

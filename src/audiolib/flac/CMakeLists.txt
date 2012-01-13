set(AUDIOLIB_FLAC_SOURCES InputFlac.cpp)

find_package(FLAC++)

add_library(dpsaudio-flac SHARED ${AUDIOLIB_FLAC_SOURCES})
target_link_libraries(dpsaudio-flac ${FLAC_LIBRARY})
set_target_properties(dpsaudio-flac PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-flac
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

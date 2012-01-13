set(AUDIOLIB_OSS_SOURCES OutputDspOss.cpp)

add_library(dpsaudio-oss SHARED ${AUDIOLIB_OSS_SOURCES})
set_target_properties(dpsaudio-oss PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-oss
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

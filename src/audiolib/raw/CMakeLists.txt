set(AUDIOLIB_RAW_SOURCES InputFileRaw.cpp OutputFileRaw.cpp)

add_library(dpsaudio-raw SHARED ${AUDIOLIB_RAW_SOURCES})
set_target_properties(dpsaudio-raw PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio-raw
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )

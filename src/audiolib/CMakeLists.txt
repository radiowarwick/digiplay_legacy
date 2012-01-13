set(AUDIOLIB_SOURCES    AudioPacket.cpp
                        CircularCache.cpp
                        ComponentAudio.cpp
                        Component.cpp
                        ComponentMonitor.cpp
                        Counter.cpp
                        CounterTrigger.cpp
                        Input.cpp
                        InputFile.cpp
                        Output.cpp
                        OutputDsp.cpp
                        OutputFile.cpp
                        Process.cpp
                        ProcessFader.cpp
                        ProcessLink.cpp
                        ProcessMixer.cpp
    )

set(AUDIOLIB_HEADERS    AudioPacket.h
                        CircularCache.h
                        ComponentAudio.h
                        Component.h
                        ComponentMonitor.h
                        Counter.h
                        CounterTrigger.h
                        Input.h
                        InputFile.h
                        Output.h
                        OutputDsp.h
                        OutputFile.h
                        Process.h
                        ProcessFader.h
                        ProcessLink.h
                        ProcessMixer.h
    )

add_library(dpsaudio SHARED ${AUDIOLIB_SOURCES})
set_target_properties(dpsaudio PROPERTIES VERSION ${VERSION})
install(TARGETS dpsaudio
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )
install(FILES ${AUDIOLIB_HEADERS} DESTINATION include)

add_subdirectory(raw)
if (ENABLE_OSS)
    add_subdirectory(oss)
endif (ENABLE_OSS)
if (ENABLE_ALSA)
    add_subdirectory(alsa)
endif (ENABLE_ALSA)
if (ENABLE_FLAC)
    add_subdirectory(flac)
endif (ENABLE_FLAC)
if (ENABLE_JACK)
    add_subdirectory(jack)
endif (ENABLE_JACK)
if (ENABLE_MP3)
    add_subdirectory(mp3)
endif (ENABLE_MP3)

if (BUILD_AUDIO_LIBRARY)
    add_subdirectory(audiolib)
endif (BUILD_AUDIO_LIBRARY)

if (BUILD_STUDIO_PLAY)
    add_subdirectory(studio_play)
endif (BUILD_STUDIO_PLAY)

if (BUILD_STUDIO_MANAGE)
    add_subdirectory(studio_manage)
endif (BUILD_STUDIO_MANAGE)

if (BUILD_SUE_SCHED)
    add_subdirectory(suesched)
endif (BUILD_SUE_SCHED)

if (BUILD_SUE_PLAY)
    add_subdirectory(sueplay)
endif (BUILD_SUE_PLAY)

if (BUILD_ADMIN)
    add_subdirectory(dpsadmin)
endif (BUILD_ADMIN)

if (BUILD_EXTRA_TOOLS)
    add_subdirectory(audiotest)
    add_subdirectory(audioplay)
    add_subdirectory(audioflac)
endif (BUILD_EXTRA_TOOLS)

if (BUILD_PLAYIN)
    add_subdirectory(playin)
endif (BUILD_PLAYIN)

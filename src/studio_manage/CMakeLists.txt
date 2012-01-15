set(STUDIO_MANAGE_SOURCES frmStudioManage.cpp
                        dlgLogin.cpp
                        dlgWarn.cpp
                        TabPanel.cpp
                        TabPanelInfo.cpp
                        TabPanelEmail.cpp
                        TabPanelSearch.cpp
                        TabPanelPlaylist.cpp
                        TabPanelLogging.cpp
                        TabPanelScript.cpp
                        #TabPanelFileBrowser.cpp
                        #FileBrowser.cpp
                        ShowplanModel.cpp
                        ShowplanView.cpp
                        ShowplanDelegate.cpp
                        Showplan.cpp
                        Nownext.cpp
                        ../Config.cpp
                        ../DpsEmail.cpp
                        ../dps.cpp
                        ../clockThread.cpp
                        ../Auth.cpp
                        ../AuthLdap.cpp
                        ../AuthPsql.cpp
                        ../Logger.cpp
                        ../UserConfig.cpp
                        ../DataAccess.cpp
                        ../Security.cpp
                        ../Thread.cpp
                        ../DbTrigger.cpp
                        ../MessagingInterface.cpp
                        ../DpsMusicSearch.cpp
                        ../QtTrigger.cpp
                        ../dps/DpsObject.cpp
                        ../dps/DpsHash.cpp
                        ../dps/DpsTime.cpp
                        ../dps/DpsDate.cpp
                        ../dps/DpsUser.cpp
                        ../dps/DpsGroup.cpp
                        ../dps/DpsAudioItem.cpp
                        ../dps/DpsScriptItem.cpp
                        ../dps/DpsShowItem.cpp
                        ../dps/DpsShowPlan.cpp
                        main.cpp
    )

set(STUDIO_MANAGE_HEADERS frmStudioManage.h
                        dlgWarn.h
                        dlgLogin.h
                        TabPanel.h
                        TabPanelInfo.h
                        TabPanelEmail.h
                        TabPanelSearch.h
                        TabPanelPlaylist.h
                        TabPanelLogging.h
                        TabPanelScript.h
                        ShowplanModel.h
                        ShowplanView.h
                        ShowplanDelegate.h
                        Showplan.h
                        Nownext.h
                        ../QtTrigger.h
    )

set(STUDIO_MANAGE_RCCS  ../DpsResources.qrc)

find_library(M_LIB m)
mark_as_advanced(M_LIB)
find_package(Threads)
find_package(Pqxx REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)

include_directories(${Pqxx_INCLUDE_DIRS})
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
QT4_ADD_RESOURCES(STUDIO_MANAGE_RCC_SRCS ${STUDIO_MANAGE_RCCS})
QT4_WRAP_CPP(STUDIO_MANAGE_HEADERS_MOC ${STUDIO_MANAGE_HEADERS})

add_executable(studio_manage ${STUDIO_MANAGE_SOURCES}
                             ${STUDIO_MANAGE_HEADERS_MOC}
                             ${STUDIO_MANAGE_RCC_SRCS})
target_link_libraries(studio_manage ${QT_LIBRARIES})
target_link_libraries(studio_manage ${Pqxx_LIBRARIES})
target_link_libraries(studio_manage ${M_LIB})
target_link_libraries(studio_manage ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(studio_manage PROPERTIES VERSION ${VERSION})

install(TARGETS studio_manage
    RUNTIME DESTINATION bin OPTIONAL
    ARCHIVE DESTINATION lib OPTIONAL
    LIBRARY DESTINATION lib OPTIONAL
    )


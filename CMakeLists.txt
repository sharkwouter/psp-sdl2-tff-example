cmake_minimum_required(VERSION 3.10)

project(jewels)

add_executable(${PROJECT_NAME} main.c)

IF(PLATFORM_PSP)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2 m GL ${PSP_LIBRARIES})
        create_pbp_file(
                TARGET ${PROJECT_NAME}
                ICON_PATH ICON0.PNG
                BACKGROUND_PATH NULL
                PREVIEW_PATH NULL
                TITLE ${PROJECT_NAME}
        )
        file(COPY platform/psp/ICON0.PNG DESTINATION ${CMAKE_BINARY_DIR})
ELSEIF(VITA)
        set(VITA_TITLEID "JWLT00001")

        include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

        target_link_libraries(${PROJECT_NAME} PRIVATE
                SDL2
                vita2d
                z
                m
                SceAppMgr_stub
                SceAppUtil_stub
                SceAudio_stub
                SceCommonDialog_stub
                SceCtrl_stub
                SceDisplay_stub
                SceGxm_stub
                SceHid_stub
                SceSysmodule_stub
                SceTouch_stub
        )
        vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
        vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
                VERSION "01.00"
                NAME ${PROJECT_NAME}
                FILE platform/vita/sce_sys sce_sys
                FILE block.bmp block.bmp
        )
ELSE()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
ENDIF()

if(NOT DEFINED VITA)
        file(COPY block.bmp DESTINATION ${CMAKE_BINARY_DIR})
endif()
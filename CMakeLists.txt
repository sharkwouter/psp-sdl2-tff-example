cmake_minimum_required(VERSION 3.10)

project(jewels)

add_executable(${PROJECT_NAME} main.c)

IF(PLATFORM_PSP)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2 pspvram pspvalloc m GL ${PSP_LIBRARIES})
        create_pbp_file(
                TARGET ${PROJECT_NAME}
                ICON_PATH ICON0.PNG
                BACKGROUND_PATH NULL
                PREVIEW_PATH NULL
                TITLE ${PROJECT_NAME}
		BUILD_PRX
        )
        file(COPY platform/psp/ICON0.PNG DESTINATION ${CMAKE_BINARY_DIR})
ELSEIF(VITA)
        set(VITA_TITLEID "JWLT00001")

	include("$ENV{DOLCESDK}/share/dolce.cmake" REQUIRED)

        target_link_libraries(${PROJECT_NAME} PRIVATE
                SDL2
                vita2d
                z
                m
		pib
                SceAppMgr_stub
                SceAppUtil_stub
                SceAudio_stub
                SceCommonDialog_stub
                SceCtrl_stub
                SceDisplay_stub
		SceDisplayUser_stub
                SceGxm_stub
                SceHid_stub
                SceSysmodule_stub
                SceTouch_stub
		SceMotion_stub
		libScePiglet_stub
        )
        dolce_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
        dolce_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
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

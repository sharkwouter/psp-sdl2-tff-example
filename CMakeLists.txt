cmake_minimum_required(VERSION 3.10)

project(font-example)

add_executable(${PROJECT_NAME} main.c)

IF(PLATFORM_PSP)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2 SDL2_ttf png freetype z pspvram pspvalloc m GL ${PSP_LIBRARIES})
        create_pbp_file(
                TARGET ${PROJECT_NAME}
                ICON_PATH NULL
                BACKGROUND_PATH NULL
                PREVIEW_PATH NULL
                TITLE ${PROJECT_NAME}
		BUILD_PRX
        )
ELSE()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2 SDL2_ttf png freetype)
ENDIF()

file(COPY PressStart2P.ttf DESTINATION ${CMAKE_BINARY_DIR})
file(COPY square_sans_serif_7.ttf DESTINATION ${CMAKE_BINARY_DIR})

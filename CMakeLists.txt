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
ELSE()
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
ENDIF()

file(COPY block.bmp DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ICON0.PNG DESTINATION ${CMAKE_BINARY_DIR})

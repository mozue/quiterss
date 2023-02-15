target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

qt5_wrap_cpp(
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/qtlocalpeer.h
)

target_sources(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/qtsingleapplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/qtlocalpeer.cpp
)
target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

qt5_wrap_cpp(
    ${CMAKE_CURRENT_SOURCE_DIR}/qzregexp.h
)

target_sources(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/qzregexp.cpp
)
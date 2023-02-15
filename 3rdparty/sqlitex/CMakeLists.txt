target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

qt5_wrap_cpp(
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlcachedresult.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlitedriver.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sqliteextension.h
)

target_sources(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlcachedresult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlitedriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sqliteextension.cpp
)
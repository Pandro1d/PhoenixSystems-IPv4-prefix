file(GLOB SOURCES ./*.c)
add_executable(release ${SOURCES})
target_include_directories(release PUBLIC ../src)
# Include 
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(.)

# Header files
# Specified for IDEs like Visual Studio and Qt Creator
set(HEADERS
    HttpServer.h)

# Implementation code
set(SRC 
    Main.cpp 
    HttpServer.cpp) 

# Executable
add_executable(${PROJECT_NAME} ${SRC} ${HEADERS})

# Library linking
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

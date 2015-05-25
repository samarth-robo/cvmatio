# MatlabIO CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
project(cvmatio)

# include all warning types
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Werror -pedantic")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build. Options are: None, Debug, Release, RelWithDebInfo, MinSizeRel"
    FORCE)
endif()

# find the dependencies
find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)
include(FindZLIB)

# include the dependencies
include_directories(SYSTEM ${OPENCV_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS}
                           ${ZLIB_INCLUDE_DIR})
include_directories("include")

# build the project
add_executable(test_cvmatio src/MatlabIO.cpp src/main.cpp)
target_link_libraries(test_cvmatio ${Boost_LIBRARIES} ${OpenCV_LIBS} ${ZLIB_LIBRARIES})
add_library(${PROJECT_NAME} SHARED src/MatlabIO.cpp)

# install
install(TARGETS test_cvmatio RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib)

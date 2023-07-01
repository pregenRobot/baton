cmake_minimum_required(VERSION 3.26.4)

project(baton VERSION 0.0.1)

include(ExternalProject)

set(LIBTORCH_URL "https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip")
set(LIBTORCH_DOWNLOAD_PATH ${CMAKE_BINARY_DIR}/downloads/libtorch.zip)
set(EXTERNAL_LIB_DIR ${CMAKE_BINARY_DIR}/external)
set(LIBTORCH_PATH ${EXTERNAL_LIB_DIR}/libtorch)
set(FETCHCONTENT_QUIET FALSE)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

if(EXISTS "${LIBTORCH_DOWNLOAD_PATH}")
    message(STATUS "Libtorch has been downloaded. Moving on...")
else()
    message(STATUS "Libtorch dependency not found. downloading now...")
    file(DOWNLOAD ${LIBTORCH_URL} ${LIBTORCH_DOWNLOAD_PATH} STATUS LIBTORCH_DOWNLOAD_STATUS SHOW_PROGRESS)
    list(GET LIBHELLO_DOWNLOAD_STATUS 0 LIBHELLO_DOWNLOAD_STATUS_NO)

    if(LIBHELLO_DOWNLOAD_STATUS_NO)
        message(FATAL_ERROR "Download has failed!")
        file(REMOVE ${LIBHELLO_PATH})
    else()
        message(STATUS "Download complete. Moving on...")
    endif()
endif()

if(EXISTS "${LIBTORCH_PATH}")
    message(STATUS "Unpacked Libtorch exists! Moving on...")
else()
    message(STATUS "Libtorch has not been unpacked. Unpacking now...")
    execute_process(COMMAND mkdir -p ${LIBTORCH_PATH})
    execute_process(COMMAND unzip ${LIBTORCH_DOWNLOAD_PATH} -d ${EXTERNAL_LIB_DIR})
    message(STATUS "Complete")
endif()

set(CMAKE_PREFIX_PATH "${EXTERNAL_LIB_DIR}/libtorch/share/cmake")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")


add_executable(${PROJECT_NAME} server.cpp)
target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)




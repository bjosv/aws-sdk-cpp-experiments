cmake_minimum_required(VERSION 3.11)
project(examples)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/tmp/aws-sdk-install")
list(APPEND CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath -Wl,$ENV{HOME}/tmp/openssl-1.1.1w/lib")

# Find the AWS SDK for C++ package.
find_package(AWSSDK REQUIRED COMPONENTS s3)

add_executable(client client.cc)
target_link_libraries(client ${AWSSDK_LINK_LIBRARIES})

# add_executable(minio minio.cc)
# target_link_libraries(minio ${AWSSDK_LINK_LIBRARIES})

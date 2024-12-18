cmake_minimum_required(VERSION 3.11)
project(examples)

#set(install_dir /tmp/aws/)
#set(install_dir /tmp/aws-1.9.36/)
#set(install_dir /tmp/aws-1.11.98/)
#set(install_dir /tmp/aws-1.11.98-update/)
set(install_dir /tmp/aws-1.11.98-update-crt-http-client/)

list(APPEND CMAKE_PREFIX_PATH "${install_dir}")

# Find the AWS SDK for C++ package.
find_package(AWSSDK REQUIRED COMPONENTS s3)

add_executable(minio
  minio.cc)

target_link_libraries(minio
  ${AWSSDK_LINK_LIBRARIES})

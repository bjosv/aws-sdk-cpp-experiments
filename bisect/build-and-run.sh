#!/bin/bash
set -x
set -e

# Prepare to build and install current commit
git submodule update --init --recursive

rm -rf $HOME/tmp/aws-sdk-install
rm -rf build && mkdir build && cd build

CXX=g++-9 CC=gcc-9 \
          cmake -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_ONLY="s3" \
          -DENABLE_TESTING=OFF \
          -DAUTORUN_UNIT_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=$HOME/tmp/aws-sdk-install \
          -DOPENSSL_ROOT_DIR=$HOME/tmp/openssl-1.1.1w \
          ..


# exit code of 125 asks "git bisect" to "skip" the current commit
make -j8 || exit 125
make -j8 install || exit 125

# Clean-up repo for next iteration
cd ..
git clean -fdx
git co .

# Build example (which uses $HOME/tmp/aws-sdk-install)
cd $HOME/git/aws-sdk-cpp-experiments/examples/
rm -rf build
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..

CXX=g++-9 CC=gcc-9 make clean all || exit 125
cd -

# Run binary
LD_LIBRARY_PATH=$HOME/tmp/openssl-1.1.1w/lib/ $HOME/git/aws-sdk-cpp-experiments/examples/build/client

# aws-sdk-cpp-experiments

https://github.com/aws/aws-sdk-cpp

## Build and install

### HEAD
```
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/tmp/aws/ -DCMAKE_INSTALL_PREFIX=/tmp/aws/
make -j8
make -j8 install
```

### 1.9.36
```
sudo snap remove cmake
sudo snap install cmake --classic --channel 3.14/stable

CXX=g++-9 CC=gcc-9 cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/tmp/aws-1.9.36/ -DCMAKE_INSTALL_PREFIX=/tmp/aws-1.9.36/
make -j8
make install
```

### 1.11.98
```
CXX=g++-9 CC=gcc-9 cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=/tmp/aws-1.11.98/ -DCMAKE_INSTALL_PREFIX=/tmp/aws-1.11.98/
make -j8
make install
```


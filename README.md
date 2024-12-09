# Optimization for ORB-SLAM3
See more from [original README](/README-orig.md)

## Prerequisites
### oneAPI libs
Make sure Intel oneAPI basekit (version < 2025.0) installed.

### Pangolin
Run below commands
```bash
cd [work-space-dir]
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install pangolin
```
after built and installed, make sure ENV argument is also set:
```bash
export CMAKE_PREFIX_PATH=[work-space-dir]/vcpkg/installed/x64-linux
```
### C++ Compiler
We updated the source code to support C++17, in order to use the new thread and chrono functionalities, as well as align with the dependent libs(pangolin, palsigslot, etc).

## Build
See original README.
### Build ORB-Extractor lib
```bash
cd [work-space-dir]
git clone https://github.com/intel-innersource/applications.robotics.mobile.orb-extractor
git checkout sycl_debian
source opt/intel/oneapi/setvars.sh
cd applications.robotics.mobile.orb-extractor
cmake ..
make -j
sudo make install
```
NOTE: if there are some errors during cmake, you'd update CMakeLists.txt as below:
```c++
@@ -85,7 +85,7 @@ install(TARGETS ${APP} ${APP_CV} SyclUtils
   EXPORT orblzeTargets
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} )
 
-install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h*" )
+install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ TYPE INCLUDE DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h*" )
 
 target_link_libraries(${APP} ${CMAKE_DL_LIBS} SyclUtils)
 target_link_libraries(${APP} -lpthread -lstdc++fs)

```
### Build ORB-SLAM3
See more from the [original Readme](README-orig.md).
```bash
cd [work-space-dir]
source opt/intel/oneapi/setvars.sh
./build.sh
```
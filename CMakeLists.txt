#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(DarkGeant4)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


#---------------------------------------------------------------------------
#
# Simply finds LUA
#
find_package(Lua 5.2 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
message(${LUA_INCLUDE_DIR})


find_package(OpenMP)
if (OPENMP_FOUND)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenMP_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OpenMP_CXX_FLAGS}")
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/DetectorConstruction)
include_directories(${PROJECT_SOURCE_DIR}/include/LuaPlugin)
include_directories(${PROJECT_SOURCE_DIR}/include/Fields)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#
# Release and Debug Commands
#
# Use by -DCMAKE_BUILD_TYPE=Debug/Release
#

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fopenmp")

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(DarkGeant4 main.cxx ${sources} ${headers})
target_link_libraries(DarkGeant4 -lGLU -ldl ${Geant4_LIBRARIES} ${LUA_LIBRARIES})

add_custom_command(TARGET DarkGeant4 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${PROJECT_SOURCE_DIR}/config
                   ${PROJECT_BINARY_DIR}/config
)

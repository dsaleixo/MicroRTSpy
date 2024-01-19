cmake_minimum_required(VERSION 3.0)
project(MicroRTS_CPP)


add_subdirectory(external/pugixml-1.14 EXCLUDE_FROM_ALL)

add_library(MicroRTScpp  STATIC src/cpp/PhysicalGameState.cpp src/cpp/UnitTypeTable.cpp  src/cpp/UnitType.cpp src/cpp/Player.cpp src/cpp/Unit.cpp)
target_include_directories(MicroRTScpp   PUBLIC include/)
target_link_libraries(MicroRTScpp pugixml)


add_executable(exp2 "main2.cpp" )
target_link_libraries(exp2 MicroRTScpp)
target_include_directories(exp2 PUBLIC include/)


add_subdirectory(external/pybind11)


pybind11_add_module(MicroRTSpy src/brind_pybind11/PhysicalGameState_py.cpp  )
target_link_libraries(MicroRTSpy  PUBLIC  MicroRTScpp)
target_include_directories(MicroRTSpy  PUBLIC include/)
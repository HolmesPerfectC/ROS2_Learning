cmake_minimum_required(VERSION 3.8)
project(tensorrt_yolov5)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_auto REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(cv_bridge REQUIRED)

add_compile_options(-Wno-deprecated-declarations)

option(CUDA_VERBOSE "Verbose output of CUDA modules" ON)


# set flags for CUDA availability
option(CUDA_AVAIL "CUDA available" OFF)
find_package(CUDA)
if(CUDA_FOUND)
  find_library(CUBLAS_LIBRARIES cublas HINTS
    ${CUDA_TOOLKIT_ROOT_DIR}/lib64
    ${CUDA_TOOLKIT_ROOT_DIR}/lib
  )
  if(CUDA_VERBOSE)
    message(STATUS "CUDA is available!")
    message(STATUS "CUDA Libs: ${CUDA_LIBRARIES}")
    message(STATUS "CUDA Headers: ${CUDA_INCLUDE_DIRS}")
  endif()
  set(CUDA_AVAIL ON)
else()
  message("CUDA NOT FOUND")
  set(CUDA_AVAIL OFF)
endif()

# set flags for TensorRT availability
option(TRT_AVAIL "TensorRT available" OFF)
# try to find the tensorRT modules
find_library(NVINFER NAMES nvinfer)
find_library(NVONNXPARSER nvonnxparser)
find_library(NVINFER_PLUGIN NAMES nvinfer_plugin)
if(NVINFER AND NVONNXPARSER AND NVINFER_PLUGIN)
  if(CUDA_VERBOSE)
    message(STATUS "TensorRT is available!")
    message(STATUS "NVINFER: ${NVINFER}")
    message(STATUS "NVPARSERS: ${NVPARSERS}")
    message(STATUS "NVINFER_PLUGIN: ${NVINFER_PLUGIN}")
    message(STATUS "NVONNXPARSER: ${NVONNXPARSER}")
  endif()
  set(TRT_AVAIL ON)
else()
  message("TensorRT is NOT Available")
  set(TRT_AVAIL OFF)
endif()

# set flags for CUDNN availability
option(CUDNN_AVAIL "CUDNN available" OFF)
# try to find the CUDNN module
find_library(CUDNN_LIBRARY
NAMES libcudnn.so${__cudnn_ver_suffix} libcudnn${__cudnn_ver_suffix}.dylib ${__cudnn_lib_win_name}
PATHS $ENV{LD_LIBRARY_PATH} ${__libpath_cudart} ${CUDNN_ROOT_DIR} ${PC_CUDNN_LIBRARY_DIRS} ${CMAKE_INSTALL_PREFIX}
PATH_SUFFIXES lib lib64 bin
DOC "CUDNN library."
)
if(CUDNN_LIBRARY)
  if(CUDA_VERBOSE)
    message(STATUS "CUDNN is available!")
    message(STATUS "CUDNN_LIBRARY: ${CUDNN_LIBRARY}")
  endif()
  set(CUDNN_AVAIL ON)
else()
  message("CUDNN is NOT Available")
  set(CUDNN_AVAIL OFF)
endif()

# create calib image directory for int8 calibration
set(CALIB_IMAGE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/calib_image")
if(NOT EXISTS "${CALIB_IMAGE_PATH}")
  execute_process(COMMAND mkdir -p ${CALIB_IMAGE_PATH})
endif()

if(TRT_AVAIL AND CUDA_AVAIL AND CUDNN_AVAIL)
  include_directories(
    include
    lib/include
    ${OpenCV_INCLUDE_DIRS}
    ${CUDA_INCLUDE_DIRS}
  )

  ### yolo ###
  cuda_add_library(mish_plugin SHARED
    lib/src/plugins/mish.cu
    lib/src/plugins/mish_plugin.cpp
  )

  cuda_add_library(yolo_layer_plugin SHARED
    lib/src/plugins/yolo_layer.cu
    lib/src/plugins/yolo_layer_plugin.cpp
  )

  cuda_add_library(nms_plugin SHARED
    lib/src/plugins/nms.cu
    lib/src/plugins/nms_plugin.cpp
  )

  ament_auto_add_library(yolo SHARED
    lib/src/trt_yolo.cpp
  )

  target_include_directories(yolo PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
    )
  
  target_include_directories(yolo PUBLIC
    lib/include
    )

  target_link_libraries(yolo
    ${NVINFER}
    ${NVONNXPARSER}
    ${NVINFER_PLUGIN}
    ${CUDA_LIBRARIES}
    ${CUBLAS_LIBRARIES}
    ${CUDNN_LIBRARY}
    mish_plugin
    yolo_layer_plugin
    nms_plugin
  )

  ament_auto_add_library(yolov5_component SHARED
  src/yolov5_component.cpp
  )
  
  ament_target_dependencies(yolov5_component
  "rclcpp"
  "sensor_msgs"
  "vision_msgs"
  "image_transport"
  "rclcpp_components"
  "cv_bridge")

  target_link_libraries(yolov5_component
    ${OpenCV_LIBS}
    yolo
    mish_plugin
    yolo_layer_plugin
    nms_plugin
  )
 

  rclcpp_components_register_nodes(yolov5_component
    "MYYOLO::YoloComponent"
  )

  ament_auto_package(INSTALL_TO_SHARE
    config
    launch
  )

  install(
    TARGETS
    yolov5_component
    mish_plugin
    yolo_layer_plugin
    nms_plugin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
  )

else()
  message("TensorrtYolo won't be built, CUDA and/or TensorRT were not found.")
  ament_auto_package(INSTALL_TO_SHARE
    config
    launch
  )
endif()

# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

# ament_package()

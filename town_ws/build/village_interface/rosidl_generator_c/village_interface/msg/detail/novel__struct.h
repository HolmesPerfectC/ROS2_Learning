// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from village_interface:msg/Novel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__STRUCT_H_
#define VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/Novel in the package village_interface.
/**
  * original data type
 */
typedef struct village_interface__msg__Novel
{
  rosidl_runtime_c__String content;
  /// use existed data type
  sensor_msgs__msg__Image image;
} village_interface__msg__Novel;

// Struct for a sequence of village_interface__msg__Novel.
typedef struct village_interface__msg__Novel__Sequence
{
  village_interface__msg__Novel * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} village_interface__msg__Novel__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__STRUCT_H_

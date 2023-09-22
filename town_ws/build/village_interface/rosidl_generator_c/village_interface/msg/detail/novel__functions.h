// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from village_interface:msg/Novel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__FUNCTIONS_H_
#define VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "village_interface/msg/rosidl_generator_c__visibility_control.h"

#include "village_interface/msg/detail/novel__struct.h"

/// Initialize msg/Novel message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * village_interface__msg__Novel
 * )) before or use
 * village_interface__msg__Novel__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__init(village_interface__msg__Novel * msg);

/// Finalize msg/Novel message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__msg__Novel__fini(village_interface__msg__Novel * msg);

/// Create msg/Novel message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * village_interface__msg__Novel__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__msg__Novel *
village_interface__msg__Novel__create();

/// Destroy msg/Novel message.
/**
 * It calls
 * village_interface__msg__Novel__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__msg__Novel__destroy(village_interface__msg__Novel * msg);

/// Check for msg/Novel message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__are_equal(const village_interface__msg__Novel * lhs, const village_interface__msg__Novel * rhs);

/// Copy a msg/Novel message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__copy(
  const village_interface__msg__Novel * input,
  village_interface__msg__Novel * output);

/// Initialize array of msg/Novel messages.
/**
 * It allocates the memory for the number of elements and calls
 * village_interface__msg__Novel__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__Sequence__init(village_interface__msg__Novel__Sequence * array, size_t size);

/// Finalize array of msg/Novel messages.
/**
 * It calls
 * village_interface__msg__Novel__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__msg__Novel__Sequence__fini(village_interface__msg__Novel__Sequence * array);

/// Create array of msg/Novel messages.
/**
 * It allocates the memory for the array and calls
 * village_interface__msg__Novel__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__msg__Novel__Sequence *
village_interface__msg__Novel__Sequence__create(size_t size);

/// Destroy array of msg/Novel messages.
/**
 * It calls
 * village_interface__msg__Novel__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__msg__Novel__Sequence__destroy(village_interface__msg__Novel__Sequence * array);

/// Check for msg/Novel message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__Sequence__are_equal(const village_interface__msg__Novel__Sequence * lhs, const village_interface__msg__Novel__Sequence * rhs);

/// Copy an array of msg/Novel messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__msg__Novel__Sequence__copy(
  const village_interface__msg__Novel__Sequence * input,
  village_interface__msg__Novel__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACE__MSG__DETAIL__NOVEL__FUNCTIONS_H_

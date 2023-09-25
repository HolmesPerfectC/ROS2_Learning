// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from village_interface:srv/SellNovel.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__FUNCTIONS_H_
#define VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "village_interface/msg/rosidl_generator_c__visibility_control.h"

#include "village_interface/srv/detail/sell_novel__struct.h"

/// Initialize srv/SellNovel message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * village_interface__srv__SellNovel_Request
 * )) before or use
 * village_interface__srv__SellNovel_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Request__init(village_interface__srv__SellNovel_Request * msg);

/// Finalize srv/SellNovel message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Request__fini(village_interface__srv__SellNovel_Request * msg);

/// Create srv/SellNovel message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * village_interface__srv__SellNovel_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__srv__SellNovel_Request *
village_interface__srv__SellNovel_Request__create();

/// Destroy srv/SellNovel message.
/**
 * It calls
 * village_interface__srv__SellNovel_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Request__destroy(village_interface__srv__SellNovel_Request * msg);

/// Check for srv/SellNovel message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Request__are_equal(const village_interface__srv__SellNovel_Request * lhs, const village_interface__srv__SellNovel_Request * rhs);

/// Copy a srv/SellNovel message.
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
village_interface__srv__SellNovel_Request__copy(
  const village_interface__srv__SellNovel_Request * input,
  village_interface__srv__SellNovel_Request * output);

/// Initialize array of srv/SellNovel messages.
/**
 * It allocates the memory for the number of elements and calls
 * village_interface__srv__SellNovel_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Request__Sequence__init(village_interface__srv__SellNovel_Request__Sequence * array, size_t size);

/// Finalize array of srv/SellNovel messages.
/**
 * It calls
 * village_interface__srv__SellNovel_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Request__Sequence__fini(village_interface__srv__SellNovel_Request__Sequence * array);

/// Create array of srv/SellNovel messages.
/**
 * It allocates the memory for the array and calls
 * village_interface__srv__SellNovel_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__srv__SellNovel_Request__Sequence *
village_interface__srv__SellNovel_Request__Sequence__create(size_t size);

/// Destroy array of srv/SellNovel messages.
/**
 * It calls
 * village_interface__srv__SellNovel_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Request__Sequence__destroy(village_interface__srv__SellNovel_Request__Sequence * array);

/// Check for srv/SellNovel message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Request__Sequence__are_equal(const village_interface__srv__SellNovel_Request__Sequence * lhs, const village_interface__srv__SellNovel_Request__Sequence * rhs);

/// Copy an array of srv/SellNovel messages.
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
village_interface__srv__SellNovel_Request__Sequence__copy(
  const village_interface__srv__SellNovel_Request__Sequence * input,
  village_interface__srv__SellNovel_Request__Sequence * output);

/// Initialize srv/SellNovel message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * village_interface__srv__SellNovel_Response
 * )) before or use
 * village_interface__srv__SellNovel_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Response__init(village_interface__srv__SellNovel_Response * msg);

/// Finalize srv/SellNovel message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Response__fini(village_interface__srv__SellNovel_Response * msg);

/// Create srv/SellNovel message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * village_interface__srv__SellNovel_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__srv__SellNovel_Response *
village_interface__srv__SellNovel_Response__create();

/// Destroy srv/SellNovel message.
/**
 * It calls
 * village_interface__srv__SellNovel_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Response__destroy(village_interface__srv__SellNovel_Response * msg);

/// Check for srv/SellNovel message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Response__are_equal(const village_interface__srv__SellNovel_Response * lhs, const village_interface__srv__SellNovel_Response * rhs);

/// Copy a srv/SellNovel message.
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
village_interface__srv__SellNovel_Response__copy(
  const village_interface__srv__SellNovel_Response * input,
  village_interface__srv__SellNovel_Response * output);

/// Initialize array of srv/SellNovel messages.
/**
 * It allocates the memory for the number of elements and calls
 * village_interface__srv__SellNovel_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Response__Sequence__init(village_interface__srv__SellNovel_Response__Sequence * array, size_t size);

/// Finalize array of srv/SellNovel messages.
/**
 * It calls
 * village_interface__srv__SellNovel_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Response__Sequence__fini(village_interface__srv__SellNovel_Response__Sequence * array);

/// Create array of srv/SellNovel messages.
/**
 * It allocates the memory for the array and calls
 * village_interface__srv__SellNovel_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
village_interface__srv__SellNovel_Response__Sequence *
village_interface__srv__SellNovel_Response__Sequence__create(size_t size);

/// Destroy array of srv/SellNovel messages.
/**
 * It calls
 * village_interface__srv__SellNovel_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
void
village_interface__srv__SellNovel_Response__Sequence__destroy(village_interface__srv__SellNovel_Response__Sequence * array);

/// Check for srv/SellNovel message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_village_interface
bool
village_interface__srv__SellNovel_Response__Sequence__are_equal(const village_interface__srv__SellNovel_Response__Sequence * lhs, const village_interface__srv__SellNovel_Response__Sequence * rhs);

/// Copy an array of srv/SellNovel messages.
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
village_interface__srv__SellNovel_Response__Sequence__copy(
  const village_interface__srv__SellNovel_Response__Sequence * input,
  village_interface__srv__SellNovel_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACE__SRV__DETAIL__SELL_NOVEL__FUNCTIONS_H_

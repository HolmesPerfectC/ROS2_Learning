// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from village_interface:srv/BorrowMoney.idl
// generated code does not contain a copyright notice
#include "village_interface/srv/detail/borrow_money__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
village_interface__srv__BorrowMoney_Request__init(village_interface__srv__BorrowMoney_Request * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    village_interface__srv__BorrowMoney_Request__fini(msg);
    return false;
  }
  // money
  return true;
}

void
village_interface__srv__BorrowMoney_Request__fini(village_interface__srv__BorrowMoney_Request * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // money
}

bool
village_interface__srv__BorrowMoney_Request__are_equal(const village_interface__srv__BorrowMoney_Request * lhs, const village_interface__srv__BorrowMoney_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // money
  if (lhs->money != rhs->money) {
    return false;
  }
  return true;
}

bool
village_interface__srv__BorrowMoney_Request__copy(
  const village_interface__srv__BorrowMoney_Request * input,
  village_interface__srv__BorrowMoney_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // money
  output->money = input->money;
  return true;
}

village_interface__srv__BorrowMoney_Request *
village_interface__srv__BorrowMoney_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Request * msg = (village_interface__srv__BorrowMoney_Request *)allocator.allocate(sizeof(village_interface__srv__BorrowMoney_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interface__srv__BorrowMoney_Request));
  bool success = village_interface__srv__BorrowMoney_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interface__srv__BorrowMoney_Request__destroy(village_interface__srv__BorrowMoney_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interface__srv__BorrowMoney_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interface__srv__BorrowMoney_Request__Sequence__init(village_interface__srv__BorrowMoney_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Request * data = NULL;

  if (size) {
    data = (village_interface__srv__BorrowMoney_Request *)allocator.zero_allocate(size, sizeof(village_interface__srv__BorrowMoney_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interface__srv__BorrowMoney_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interface__srv__BorrowMoney_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
village_interface__srv__BorrowMoney_Request__Sequence__fini(village_interface__srv__BorrowMoney_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      village_interface__srv__BorrowMoney_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

village_interface__srv__BorrowMoney_Request__Sequence *
village_interface__srv__BorrowMoney_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Request__Sequence * array = (village_interface__srv__BorrowMoney_Request__Sequence *)allocator.allocate(sizeof(village_interface__srv__BorrowMoney_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interface__srv__BorrowMoney_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interface__srv__BorrowMoney_Request__Sequence__destroy(village_interface__srv__BorrowMoney_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interface__srv__BorrowMoney_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interface__srv__BorrowMoney_Request__Sequence__are_equal(const village_interface__srv__BorrowMoney_Request__Sequence * lhs, const village_interface__srv__BorrowMoney_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interface__srv__BorrowMoney_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interface__srv__BorrowMoney_Request__Sequence__copy(
  const village_interface__srv__BorrowMoney_Request__Sequence * input,
  village_interface__srv__BorrowMoney_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interface__srv__BorrowMoney_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    village_interface__srv__BorrowMoney_Request * data =
      (village_interface__srv__BorrowMoney_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interface__srv__BorrowMoney_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          village_interface__srv__BorrowMoney_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interface__srv__BorrowMoney_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
village_interface__srv__BorrowMoney_Response__init(village_interface__srv__BorrowMoney_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // money
  return true;
}

void
village_interface__srv__BorrowMoney_Response__fini(village_interface__srv__BorrowMoney_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // money
}

bool
village_interface__srv__BorrowMoney_Response__are_equal(const village_interface__srv__BorrowMoney_Response * lhs, const village_interface__srv__BorrowMoney_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // money
  if (lhs->money != rhs->money) {
    return false;
  }
  return true;
}

bool
village_interface__srv__BorrowMoney_Response__copy(
  const village_interface__srv__BorrowMoney_Response * input,
  village_interface__srv__BorrowMoney_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // money
  output->money = input->money;
  return true;
}

village_interface__srv__BorrowMoney_Response *
village_interface__srv__BorrowMoney_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Response * msg = (village_interface__srv__BorrowMoney_Response *)allocator.allocate(sizeof(village_interface__srv__BorrowMoney_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interface__srv__BorrowMoney_Response));
  bool success = village_interface__srv__BorrowMoney_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interface__srv__BorrowMoney_Response__destroy(village_interface__srv__BorrowMoney_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interface__srv__BorrowMoney_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interface__srv__BorrowMoney_Response__Sequence__init(village_interface__srv__BorrowMoney_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Response * data = NULL;

  if (size) {
    data = (village_interface__srv__BorrowMoney_Response *)allocator.zero_allocate(size, sizeof(village_interface__srv__BorrowMoney_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interface__srv__BorrowMoney_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interface__srv__BorrowMoney_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
village_interface__srv__BorrowMoney_Response__Sequence__fini(village_interface__srv__BorrowMoney_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      village_interface__srv__BorrowMoney_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

village_interface__srv__BorrowMoney_Response__Sequence *
village_interface__srv__BorrowMoney_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interface__srv__BorrowMoney_Response__Sequence * array = (village_interface__srv__BorrowMoney_Response__Sequence *)allocator.allocate(sizeof(village_interface__srv__BorrowMoney_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interface__srv__BorrowMoney_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interface__srv__BorrowMoney_Response__Sequence__destroy(village_interface__srv__BorrowMoney_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interface__srv__BorrowMoney_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interface__srv__BorrowMoney_Response__Sequence__are_equal(const village_interface__srv__BorrowMoney_Response__Sequence * lhs, const village_interface__srv__BorrowMoney_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interface__srv__BorrowMoney_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interface__srv__BorrowMoney_Response__Sequence__copy(
  const village_interface__srv__BorrowMoney_Response__Sequence * input,
  village_interface__srv__BorrowMoney_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interface__srv__BorrowMoney_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    village_interface__srv__BorrowMoney_Response * data =
      (village_interface__srv__BorrowMoney_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interface__srv__BorrowMoney_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          village_interface__srv__BorrowMoney_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interface__srv__BorrowMoney_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

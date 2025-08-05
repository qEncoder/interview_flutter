# Implementing a Dart FFI binding

In this role you will frequently link Dart code with compiled C/C++ libraries. To make the interview process more engaging, we prepared a small challenge that mimics the kind of FFI work you might encounter.

To save you setup time we have included a small, representative C function and the supporting files you will need:
* `src/` : C source code plus a CMake build script (a pre-compiled Windows binary is also included).
* `lib/bindings.dart` : contains the Dart FFI bindings to the C function.
* `lib/read_data.dart` :implement readData in this file.

More information about the function and expected functionality can be found below.

## Expected functionality

Your task is to implement and test the following Dart function:

```dart
List readData(DataType type, List<int> shape)
```

This function should:

1.  Call the `dataRead` C function using Dart's FFI.
2.  Handle the data types for `int32` and `int64`.
3.  Reconstruct the flat buffer returned by the C function into a nested `List` that matches the provided `shape`.
4.  Include error handling for potential issues, such as a negative return value from `dataRead`.
5.  Be accompanied by tests to verify its correctness.


## The function in C

### Function signature

```
int64_t dataRead(int32_t type, int32_t shape_size, int32_t* shape, void* buffer);
```

### Purpose
Reads an N-dimensional block of native data into a caller-supplied buffer.

### Parameters

| Name    | Dir. | Description |
|---------|------|-------------|
| `type`  | in   | Element type of the returned data.<br/>• `0` → 32-bit signed integers (`int32_t`)<br/>• `1` → 64-bit signed integers (`int64_t`) |
| `shape_size` | in | The number of dimensions in the `shape` array. |
| `shape` | in   | Pointer to an array of `int32_t` describing the extent of each dimension (e.g. `{rows, cols, …}`). The product of all extents **must not exceed 10 000 000**; otherwise the function returns an error. |
| `buffer`| out  | Pointer to a memory block large enough to hold `numElements * sizeof(elementType)` bytes. On success the function populates this buffer with the requested data. |

### Return value (`status`)

| Value | Meaning |
|-------|---------|
| `>= 0` | Number of elements written to `buffer`. |
| `< 0`  | Negative error code indicating invalid arguments, size overflow, or other failures. |

| Code | Meaning                               |
|------|---------------------------------------|
| -1   | `shape_size` ≤ 0                      |
| -2   | Product of `shape` exceeds 10 000 000 |
| -3   | Unsupported `type`                   |
| -4   | `buffer == NULL`                      |
| any other negative | Internal failure        |


#### Data Reconstruction

The `dataRead` function returns a flat list of data. This flat list needs to be reconstructed into a nested list structure based on the `shape` parameter.

For example:

**1D:**

```
shape = [4]
buffer = [0, 1, 2, 3]
reconstructed data = [0, 1, 2, 3]
```

**2D:**

```
shape = [2, 3]
buffer = [0, 1, 2, 3, 4, 5]
reconstructed data = [[0, 1, 2],
                      [3, 4, 5]]
```

**3D:**

```
shape = [2, 3, 4]
buffer = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23]
reconstructed data = [[[0, 1, 2, 3],
                       [4, 5, 6, 7],
                       [8, 9, 10, 11]],
                      [[12, 13, 14, 15],
                       [16, 17, 18, 19],
                       [20, 21, 22, 23]]]
```

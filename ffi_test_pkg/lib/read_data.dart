import 'dart:ffi';

import 'package:ffi/ffi.dart';
import 'bindings.dart';

enum DataType {
  int32,
  int64
}

List readData(DataType type, List<int> shape) {
  return [];
}
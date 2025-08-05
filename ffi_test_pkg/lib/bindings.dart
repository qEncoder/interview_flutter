import 'dart:ffi';
import 'dart:io';

import 'package:path/path.dart' as path;

typedef _DataReadC = Int64 Function(
  Int32 type,
  Int32 shape_size,
  Pointer<Int32> shape,
  Pointer<Void> buffer,
);

typedef DataRead = int Function(
  int type,
  int shape_size,
  Pointer<Int32> shape,
  Pointer<Void> buffer,
);


DynamicLibrary _loadLibrary() {
  var libraryPath;
    if (Platform.isMacOS) {
      libraryPath = path.join(Directory.current.path, 'src', 'libtest_lib.dylib');
    } else if (Platform.isWindows) {
      libraryPath = path.join(Directory.current.path, 'src', 'test_lib.dll');
    } else if (Platform.isLinux) {
      libraryPath = path.join(Directory.current.path, 'src', 'libtest_lib.so');
    }
    return DynamicLibrary.open(libraryPath);
}

class Bindings {
  static final _c_lib = _loadLibrary();
  final DataRead dataRead;

  static final Bindings _singleton = Bindings._internal();

  factory Bindings() {
    return _singleton;
  }

  Bindings._internal()
      : dataRead = _c_lib
            .lookup<NativeFunction<_DataReadC>>('dataRead')
            .asFunction<DataRead>();
}
import 'package:ffi_test_pkg/read_data.dart';

void main(List<String> arguments) {
  final shape = [2,4];  
  print('SHAPE: $shape');
  print('DATA: ${readData(DataType.int64, shape)}!');
}

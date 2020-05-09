cmake_minimum_required (VERSION 3.8)

project(col)

add_subdirectory(src/col_base)
add_subdirectory(src/col_stream)
add_subdirectory(src/col_type_traits)
add_subdirectory(src/funct)
add_subdirectory(src/stringt)
add_subdirectory(src/tvalue)

enable_testing()

add_test(NAME col_base COMMAND src/col_base/col_base)
add_test(NAME col_stream COMMAND src/col_stream/col_stream)
add_test(NAME bstream COMMAND src/col_stream/bstream)
add_test(NAME col_type_traits COMMAND src/col_type_traits/col_type_traits)
add_test(NAME funct COMMAND src/funct/funct)
add_test(NAME stringt COMMAND src/stringt/stringt)
add_test(NAME tvalue COMMAND src/tvalue/tvalue)

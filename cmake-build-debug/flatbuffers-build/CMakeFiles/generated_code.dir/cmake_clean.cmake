file(REMOVE_RECURSE
  "CMakeFiles/generated_code"
  "samples/monster.bfbs"
  "samples/monster_generated.h"
  "tests/arrays_test.bfbs"
  "tests/arrays_test_generated.h"
  "tests/monster_extra_generated.h"
  "tests/monster_test.bfbs"
  "tests/monster_test_bfbs_generated.h"
  "tests/monster_test_generated.h"
  "tests/namespace_test/namespace_test1_generated.h"
  "tests/namespace_test/namespace_test2_generated.h"
  "tests/native_type_test_generated.h"
  "tests/union_vector/union_vector_generated.h"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/generated_code.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

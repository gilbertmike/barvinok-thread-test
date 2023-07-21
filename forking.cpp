#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

#include "barvinok/isl.h"
#include "isl/map.h"

#define CALL_BARVINOK_ROUTINE

std::mutex g_cout_mutex;

void foo()
{
  auto p_ctx = isl_ctx_alloc();
  auto p_map1 = isl_map_read_from_str(
    p_ctx,
    "{ [a, b, c] -> [a + b, c] : 0 < a < 5 and 0 < b < 6 and 0 < c < 3 }"
  );
  auto p_map2 = isl_map_read_from_str(
    p_ctx,
    "{ [x, y] -> [y, x - y] }"
  );
  auto p_map3 = isl_map_apply_range(p_map1, p_map2);

  std::cout << std::this_thread::get_id()
            << ": "
            << isl_map_to_str(p_map3)
            << std::endl;

  #ifdef CALL_BARVINOK_ROUTINE

  auto p_map3_card = isl_map_card(p_map3);

  std::cout << std::this_thread::get_id()
            << ": "
            << isl_pw_qpolynomial_to_str(p_map3_card)
            << std::endl;

  isl_pw_qpolynomial_free(p_map3_card);

  #else

  isl_map_free(p_map3);

  #endif
}

int main(int argc, char* argv[])
{
  fork();
  foo();
  return 0;
}

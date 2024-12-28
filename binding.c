#include "bare_zig_example.h"
#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

static js_value_t *
bare_zig_example_add(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);
  assert(argc == 2);

  double n1;
  err = js_get_value_double(env, argv[0], &n1);
  assert(err == 0);

  printf("from bare c binding: n1, %f\n", n1);

  double n2;
  err = js_get_value_double(env, argv[1], &n2);
  assert(err == 0);

  printf("from bare c binding: n2, %f\n", n2);

  double sum = bare_zig_add(n1, n2);
  printf("from bare c binding: sum %f\n", sum);

  js_value_t *result = NULL;
  printf("before js_create_double, result pointer: %p\n", (void *) result);

  err = js_create_double(env, sum, &result);
  assert(err == 0);

  printf("after js_create_double, result pointer: %p\n", (void *) result);

  printf("from bare c binding: sum %f\n", sum);

  err = js_create_double(env, sum, &result);
  printf("js_create_double error code: %d\n", err);
  assert(err == 0);

  double sumdoubletrouble;
  err = js_get_value_double(env, result, &sumdoubletrouble);
  assert(err == 0);

  printf("sumdoubletrouble: %f\n", sumdoubletrouble);

  return result;
}

static js_value_t *
bare_zig_example_addc(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);
  assert(argc == 2);

  double n1;
  err = js_get_value_double(env, argv[0], &n1);
  assert(err == 0);

  printf("from bare c binding: n1, %f\n", n1);

  double n2;
  err = js_get_value_double(env, argv[1], &n2);
  assert(err == 0);

  printf("from bare c binding: n2, %f\n", n2);

  double sum = n1 + n2;

  printf("from bare c binding: sum %f\n", sum);

  js_value_t *result;
  err = js_create_double(env, sum, &result);
  assert(err == 0);

  printf("the result: %f\n", result);

  return result;
}

static js_value_t *
bare_addon_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("add", bare_zig_example_add)
  V("addc", bare_zig_example_addc)
#undef V

  return exports;
}

BARE_MODULE(bare_addon, bare_addon_exports)

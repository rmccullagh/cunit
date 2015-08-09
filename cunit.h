#ifndef __MY_C_UNIT_H___
#define __MY_C_UNIT_H___

typedef int(*unit_test_function_t)(void);

typedef struct _UNIT_TEST {
	const char* function_name;
	unit_test_function_t function;
} UnitTest;

typedef struct _UNIT_TEST_STORE {
	struct _UNIT_TEST* 				test;
	struct _UNIT_TEST_STORE* 	next;
} UnitTestStore;

void unit_test_push(struct _UNIT_TEST_STORE**, struct _UNIT_TEST*);
void unit_test_run_all(const struct _UNIT_TEST_STORE*);

struct _UNIT_TEST* unit_test_create(const char*, unit_test_function_t);

#endif

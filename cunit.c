#include <stdlib.h>
#include <stdio.h>

#include "cunit.h"

#define RUNTIME_ASSERT(truth) do { \
	if(!truth) { \
		fprintf(stderr, "%s(): argument passed cannot be a NULL pointer\n", __func__); \
		exit(1); \
	} \
} while(0)

#define ASSERTION_FAILURE_MESSAGE(test) do { \
	fprintf(stderr, "%s(): Assertion failed\n", (test)->function_name); \
}	while(0)

void unit_test_push(struct _UNIT_TEST_STORE** list, struct _UNIT_TEST* test)
{
	struct _UNIT_TEST_STORE* _list = *list;
	if(_list == NULL) {
		_list = calloc(1, sizeof(struct _UNIT_TEST_STORE));
		RUNTIME_ASSERT(_list);
		_list->next = NULL;
		_list->test = test;
		*list = _list;
	} else {
		struct _UNIT_TEST_STORE* _prev = *list;
		struct _UNIT_TEST_STORE* _next;
		_next = calloc(1, sizeof(struct _UNIT_TEST_STORE));
		RUNTIME_ASSERT(_next);
		_next->next = _prev;
		_next->test = test;
		*list = _next;
	}
}


void unit_test_run_all(const struct _UNIT_TEST_STORE* list)
{
	while(list) {
		if(! list->test->function()) {
			ASSERTION_FAILURE_MESSAGE(list->test);
		}
		list = list->next;
	}
}

struct _UNIT_TEST* unit_test_create(const char* function_name, unit_test_function_t function)
{
	RUNTIME_ASSERT(function_name);
	struct _UNIT_TEST* test = calloc(1, sizeof(struct _UNIT_TEST));
	RUNTIME_ASSERT(test);
	test->function_name = function_name;
	test->function = function;
	return test;
}

int fn()
{
	return 0;
}

int main()
{
	UnitTestStore* unit;
	
	unit_test_push(&unit, unit_test_create("fn", fn));

	unit_test_run_all(unit);

	return 0;
}







#ifndef UNITY_FRAMEWORK_H
#define UNITY_FRAMEWORK_H

#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "unity_internals.h"

void UnityBegin(const char* filename);
int  UnityEnd(void);
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum);

#define TEST_PROTECT() (setjmp(Unity.AbortFrame) == 0)
#define TEST_ABORT() longjmp(Unity.AbortFrame, 1)

#define UNITY_BEGIN() UnityBegin(__FILE__)
#define UNITY_END() UnityEnd()

#define RUN_TEST(func) UnityDefaultTestRun(func, #func, __LINE__)

#define TEST_ASSERT(condition) do { if (!(condition)) { TEST_FAIL(); } } while(0)
#define TEST_ASSERT_TRUE(condition) TEST_ASSERT(condition)
#define TEST_ASSERT_FALSE(condition) TEST_ASSERT(!(condition))
#define TEST_ASSERT_NULL(pointer) TEST_ASSERT(pointer == NULL)
#define TEST_ASSERT_NOT_NULL(pointer) TEST_ASSERT(pointer != NULL)
#define TEST_ASSERT_EQUAL_INT(expected, actual) TEST_ASSERT((expected) == (actual))
#define TEST_ASSERT_EQUAL_UINT(expected, actual) TEST_ASSERT((expected) == (actual))
#define TEST_ASSERT_EQUAL_HEX8(expected, actual) TEST_ASSERT((expected) == (actual))
#define TEST_ASSERT_EQUAL_HEX16(expected, actual) TEST_ASSERT((expected) == (actual))
#define TEST_ASSERT_EQUAL_HEX32(expected, actual) TEST_ASSERT((expected) == (actual))

#define TEST_FAIL() do { Unity.CurrentTestFailed = 1; TEST_ABORT(); } while(0)

#endif // UNITY_FRAMEWORK_H


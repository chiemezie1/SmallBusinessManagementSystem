#ifndef UNITY_FRAMEWORK_H
#define UNITY_FRAMEWORK_H

#include <setjmp.h>
#include <math.h>

#define UNITY_FLOAT_PRECISION 0.00001f

typedef void (*UnityTestFunction)(void);

typedef enum {
    UNITY_DISPLAY_STYLE_INT,
    UNITY_DISPLAY_STYLE_UINT,
    UNITY_DISPLAY_STYLE_HEX8,
    UNITY_DISPLAY_STYLE_HEX16,
    UNITY_DISPLAY_STYLE_HEX32,
    UNITY_DISPLAY_STYLE_FLOAT
} UNITY_DISPLAY_STYLE_T;

typedef unsigned char UNITY_UINT8;
typedef unsigned short UNITY_UINT16;
typedef unsigned int UNITY_UINT32;
typedef signed char UNITY_INT8;
typedef signed short UNITY_INT16;
typedef signed int UNITY_INT32;
typedef float UNITY_FLOAT;

typedef UNITY_UINT32 UNITY_UINT;
typedef UNITY_INT32 UNITY_INT;

typedef enum {
    UNITY_EQUALITY_WITHIN = 0,
    UNITY_EQUALITY_ABSOLUTE,
} UNITY_EQUALITY_TYPE;

struct UNITY_STORAGE_T {
    const char* TestFile;
    const char* CurrentTestName;
    UNITY_UINT CurrentTestLineNumber;
    UNITY_UINT NumberOfTests;
    UNITY_UINT TestFailures;
    UNITY_UINT TestIgnores;
    UNITY_UINT CurrentTestFailed;
    UNITY_UINT CurrentTestIgnored;
    jmp_buf AbortFrame;
};

extern struct UNITY_STORAGE_T Unity;

void setUp(void);
void tearDown(void);

void UnityBegin(const char* filename);
int UnityEnd(void);
void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum);

void UnityPrintChar(const char ch);
void UnityPrint(const char* string);
void UnityPrintLen(const char* string, const UNITY_UINT32 length);
void UnityPrintNumberByStyle(const UNITY_INT number, const UNITY_DISPLAY_STYLE_T style);
void UnityPrintNumber(const UNITY_INT number);
void UnityPrintNumberUnsigned(const UNITY_UINT number);
void UnityPrintNumberHex(const UNITY_INT number, const char nibbles);
void UnityPrintFloat(const UNITY_FLOAT number);

void UnityPrintOk(void);
void UnityPrintFail(void);
void UnityConcludeTest(void);

#define TEST_PROTECT() (setjmp(Unity.AbortFrame) == 0)
#define TEST_ABORT() longjmp(Unity.AbortFrame, 1)

#define TEST_ASSERT(condition) if (!(condition)) { Unity.CurrentTestFailed = 1; TEST_ABORT(); }
#define TEST_ASSERT_TRUE(condition) TEST_ASSERT(condition)
#define TEST_ASSERT_FALSE(condition) TEST_ASSERT(!(condition))
#define TEST_ASSERT_NULL(pointer) TEST_ASSERT((pointer) == NULL)
#define TEST_ASSERT_NOT_NULL(pointer) TEST_ASSERT((pointer) != NULL)
#define TEST_ASSERT_EQUAL_INT(expected, actual) TEST_ASSERT((expected) == (actual))
#define TEST_ASSERT_EQUAL_STRING(expected, actual) TEST_ASSERT(strcmp((expected), (actual)) == 0)
#define TEST_ASSERT_EQUAL_FLOAT(expected, actual) TEST_ASSERT(fabs((expected) - (actual)) < UNITY_FLOAT_PRECISION)

#define UNITY_BEGIN() UnityBegin(__FILE__)
#define UNITY_END() UnityEnd()

#define RUN_TEST(func) UnityDefaultTestRun(func, #func, __LINE__)

#endif /* UNITY_FRAMEWORK_H */


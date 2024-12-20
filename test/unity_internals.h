#ifndef UNITY_INTERNALS_H
#define UNITY_INTERNALS_H

#include <stdint.h>

typedef void (*UnityTestFunction)(void);

typedef unsigned char UNITY_UINT8;
typedef unsigned short UNITY_UINT16;
typedef unsigned int UNITY_UINT32;
typedef signed char UNITY_INT8;
typedef signed short UNITY_INT16;
typedef signed int UNITY_INT32;

#if defined(UNITY_EXCLUDE_FLOAT) || defined(UNITY_EXCLUDE_DOUBLE)
typedef void UNITY_FLOAT_TYPE;
#else
typedef float UNITY_FLOAT_TYPE;
#endif

typedef UNITY_FLOAT_TYPE UNITY_DOUBLE;

typedef uintptr_t UNITY_INTERNAL_PTR;

#define UNITY_DISPLAY_RANGE_INT  UNITY_DISPLAY_STYLE_INT
#define UNITY_DISPLAY_RANGE_UINT UNITY_DISPLAY_STYLE_UINT
#define UNITY_DISPLAY_RANGE_HEX  UNITY_DISPLAY_STYLE_HEX

typedef enum {
    UNITY_DISPLAY_STYLE_INT = 1,
    UNITY_DISPLAY_STYLE_UINT,
    UNITY_DISPLAY_STYLE_HEX8,
    UNITY_DISPLAY_STYLE_HEX16,
    UNITY_DISPLAY_STYLE_HEX32
} UNITY_DISPLAY_STYLE_T;

typedef enum {
    UNITY_EQUAL_TO         = 1,
    UNITY_GREATER_THAN     = 2,
    UNITY_GREATER_OR_EQUAL = 2 + UNITY_EQUAL_TO,
    UNITY_SMALLER_THAN     = 4,
    UNITY_SMALLER_OR_EQUAL = 4 + UNITY_EQUAL_TO
} UNITY_COMPARISON_T;

typedef enum {
    UNITY_ARRAY_TO_VAL = 0,
    UNITY_ARRAY_TO_ARRAY
} UNITY_FLAGS_T;

struct UNITY_STORAGE_T {
    const char* TestFile;
    const char* CurrentTestName;
    unsigned char CurrentTestFailed;
    unsigned char CurrentTestIgnored;
    unsigned char NumberOfTests;
    unsigned char TestFailures;
    unsigned char TestIgnores;
    unsigned int CurrentTestLineNumber;
    jmp_buf AbortFrame;
};

extern struct UNITY_STORAGE_T Unity;

#define UNITY_OUTPUT_CHAR(a) putchar(a)
#define UNITY_OUTPUT_FLUSH() fflush(stdout)

#define UNITY_PRINT_EOL() do { UNITY_OUTPUT_CHAR('\n'); UNITY_OUTPUT_FLUSH(); } while(0)
#define UNITY_FLUSH_CALL() UNITY_OUTPUT_FLUSH()

#define UNITY_FAIL_AND_BAIL do { Unity.CurrentTestFailed = 1; TEST_ABORT(); } while(0)
#define UNITY_IGNORE_AND_BAIL do { Unity.CurrentTestIgnored = 1; TEST_ABORT(); } while(0)

#define UNITY_TEST_ASSERT(condition, line, message) do { if (!(condition)) { TEST_FAIL(); } } while(0)
#define UNITY_TEST_ASSERT_NULL(pointer, line, message) UNITY_TEST_ASSERT(((pointer) == NULL), line, message)
#define UNITY_TEST_ASSERT_NOT_NULL(pointer, line, message) UNITY_TEST_ASSERT(((pointer) != NULL), line, message)
#define UNITY_TEST_ASSERT_EQUAL_INT(expected, actual, line, message) UNITY_TEST_ASSERT(((expected) == (actual)), line, message)
#define UNITY_TEST_ASSERT_EQUAL_UINT(expected, actual, line, message) UNITY_TEST_ASSERT(((expected) == (actual)), line, message)

void UnityPrintNumber(const UNITY_INT number);
void UnityPrintNumberUnsigned(const UNITY_UINT number);
void UnityPrintNumberHex(const UNITY_UINT number, const char nibbles);

#endif // UNITY_INTERNALS_H


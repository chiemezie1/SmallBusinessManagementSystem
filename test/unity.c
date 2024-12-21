#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UNITY_STORAGE_T Unity;

void UnityPrintChar(const char ch)
{
    putchar(ch);
}

void UnityPrint(const char* string)
{
    printf("%s", string);
}

void UnityPrintLen(const char* string, const UNITY_UINT32 length)
{
    printf("%.*s", (int)length, string);
}

void UnityPrintNumberByStyle(const UNITY_INT number, const UNITY_DISPLAY_STYLE_T style)
{
    switch (style)
    {
        case UNITY_DISPLAY_STYLE_HEX8:    printf("0x%02X", (UNITY_UINT8)number);  break;
        case UNITY_DISPLAY_STYLE_HEX16:   printf("0x%04X", (UNITY_UINT16)number); break;
        case UNITY_DISPLAY_STYLE_HEX32:   printf("0x%08X", (UNITY_UINT32)number); break;
        case UNITY_DISPLAY_STYLE_UINT:    printf("%u", (UNITY_UINT)number);       break;
        case UNITY_DISPLAY_STYLE_FLOAT:   printf("%f", (UNITY_FLOAT)number);      break;
        default:                          printf("%d", number);                   break;
    }
}

void UnityPrintNumber(const UNITY_INT number)
{
    UnityPrintNumberByStyle(number, UNITY_DISPLAY_STYLE_INT);
}

void UnityPrintNumberUnsigned(const UNITY_UINT number)
{
    UnityPrintNumberByStyle(number, UNITY_DISPLAY_STYLE_UINT);
}

void UnityPrintNumberHex(const UNITY_INT number, const char nibbles)
{
    switch (nibbles)
    {
        case 2: UnityPrintNumberByStyle(number, UNITY_DISPLAY_STYLE_HEX8);  break;
        case 4: UnityPrintNumberByStyle(number, UNITY_DISPLAY_STYLE_HEX16); break;
        default: UnityPrintNumberByStyle(number, UNITY_DISPLAY_STYLE_HEX32); break;
    }
}

void UnityPrintFloat(const UNITY_FLOAT number)
{
    UnityPrintNumberByStyle((UNITY_INT)number, UNITY_DISPLAY_STYLE_FLOAT);
}

void UnityBegin(const char* file)
{
    Unity.TestFile = file;
    Unity.CurrentTestName = NULL;
    Unity.CurrentTestLineNumber = 0;
    Unity.NumberOfTests = 0;
    Unity.TestFailures = 0;
    Unity.TestIgnores = 0;
    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;
}

int UnityEnd(void)
{
    UnityPrint("-----------------------\n");
    UnityPrintNumber((UNITY_INT)(Unity.NumberOfTests));
    UnityPrint(" Tests ");
    UnityPrintNumber((UNITY_INT)(Unity.TestFailures));
    UnityPrint(" Failures ");
    UnityPrintNumber((UNITY_INT)(Unity.TestIgnores));
    UnityPrint(" Ignored\n");
    if (Unity.TestFailures == 0U)
    {
        UnityPrintOk();
    }
    else
    {
        UnityPrintFail();
    }
    return (int)(Unity.TestFailures);
}

void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum)
{
    Unity.CurrentTestName = FuncName;
    Unity.CurrentTestLineNumber = (UNITY_UINT)FuncLineNum;
    Unity.NumberOfTests++;
    if (TEST_PROTECT())
    {
        setUp();
        Func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
    }
    UnityConcludeTest();
}

void UnityPrintOk(void)
{
    UnityPrint("OK\n");
}

void UnityPrintFail(void)
{
    UnityPrint("FAIL\n");
}

void UnityConcludeTest(void)
{
    if (Unity.CurrentTestIgnored)
    {
        Unity.TestIgnores++;
    }
    else if (!Unity.CurrentTestFailed)
    {
        UnityPrintOk();
    }
    else
    {
        UnityPrintFail();
        Unity.TestFailures++;
    }

    Unity.CurrentTestFailed = 0;
    Unity.CurrentTestIgnored = 0;
}

// Weak symbol implementations for setUp and tearDown
__attribute__((weak)) void setUp(void) {}
__attribute__((weak)) void tearDown(void) {}


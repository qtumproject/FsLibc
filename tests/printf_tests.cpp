#include <UnitTest++.h>

#include "stdio_fixture.h"

SUITE(PrintF)
{
    TEST_FIXTURE(StdIOFixture, BasicPrintFTest)
    {
        int r = fslc_fprintf(&stream, "Hello, World!\n");
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFStringTest)
    {
        int r = fslc_fprintf(&stream, "Hello from %s!\n", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintF2StringsTest)
    {
        int r = fslc_fprintf(&stream, "%s from %s!\n", "Hello", "PrintF");
        
        CHECK_EQUAL("Hello from PrintF!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFCharTest)
    {
        int r = fslc_fprintf(&stream, "Hello, %corld!\n", 'W');
        
        CHECK_EQUAL("Hello, World!\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPercentTest)
    {
        int r = fslc_fprintf(&stream, "Special offer: 50%% off!");
        
        CHECK_EQUAL("Special offer: 50% off!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        const char *expected_str = "Testing a few % of all possibilities!";
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK(r >= 0);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFPrePostMultiEofTest)
    {
        stream.pre_output = fixture_preop;
        stream.post_output = fixture_postop;
        
        eof_counter = 20;
        
        int r = fslc_fprintf(&stream, "Testing %s%% of all possibilities%c", "a few ", '!');
        
        const char *expected_str = "Testing a few % of a";
        //                          12345678901234567890
        
        std::vector<FuncCallItem> expected_calls;
        expected_calls.push_back({ CalledFunc::PreOp, 0 });
        for (const char *c = expected_str; *c; ++c)
            expected_calls.push_back({ CalledFunc::PutC, *c });
        expected_calls.push_back({ CalledFunc::PutC, 'l' }); // EOF
        expected_calls.push_back({ CalledFunc::PostOp, 0 });

        CHECK(r < 0);
        CHECK_EQUAL(expected_calls.size(), FuncCallLog.size());
        CHECK_ARRAY_EQUAL(expected_calls, FuncCallLog, FuncCallLog.size());
        
        CHECK_EQUAL(expected_str, ostring.str());
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %d!", 42);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 42!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFZeroIntTest)
    {
        int r = fslc_fprintf(&stream, "Zero is %d!", 0);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Zero is 0!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %d!", -54);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Less than zero: -54!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUIntMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max uint is %u\n", -1);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Max uint is 4294967295\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicHexTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %x!", 0x74df);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 74df!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFBasicUpperHexTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %X!", 0x74df);
        
        CHECK(r >= 0);
        CHECK_EQUAL("The answer is 74DF!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFZeroHexTest)
    {
        int r = fslc_fprintf(&stream, "Zero is %x!", 0);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Zero is 0!", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUHExMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max hex is %x\n", -1);
        
        CHECK(r >= 0);
        CHECK_EQUAL("Max hex is ffffffff\n", ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFLongIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %ld!", 435434432L);
        
        int e = eprintf("The answer is %ld!", 435434432L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFLongNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %ld!", -57299223L);
        
        int e = eprintf("Less than zero: %ld!", -57299223L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max ulong is %lu\n", -1L);
        
        int e = eprintf("Max ulong is %lu\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long hex is %lx\n", -1L);
        
        int e = eprintf("Max long hex is %lx\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFULongHexUpperMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long hex is %lX\n", -1L);
        
        int e = eprintf("Max long hex is %lX\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongIntTest)
    {
        int r = fslc_fprintf(&stream, "The answer is %lld!", 435432343442444432LL);
        
        int e = eprintf("The answer is %lld!", 435432343442444432LL);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFVeryLongNegativeTest)
    {
        int r = fslc_fprintf(&stream, "Less than zero: %lld!", -5729932434424223L);
        
        int e = eprintf("Less than zero: %lld!", -5729932434424223L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max ulonglong is %llu\n", -1L);
        
        int e = eprintf("Max ulonglong is %llu\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long long hex is %llx\n", -1L);
        
        int e = eprintf("Max long long hex is %llx\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
    
    TEST_FIXTURE(StdIOFixture, PrintFUVeryLongUpperHexMaxTest)
    {
        int r = fslc_fprintf(&stream, "Max long long hex is %llX\n", -1L);
        
        int e = eprintf("Max long long hex is %llX\n", -1L);
        
        CHECK_EQUAL(e, r);
        CHECK_EQUAL(expected_fstring.get(), ostring.str());
        CHECK_EQUAL(ostring.str().size(), r);
    }
}
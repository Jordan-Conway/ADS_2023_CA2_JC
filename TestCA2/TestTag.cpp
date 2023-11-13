#include "CppUnitTest.h"
#include "Tag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTag
{
    TEST_CLASS(TestTag)
    {
    public:
        TEST_METHOD(Test_Not_Closing_Tag)
        {
            Tag t1("dir", OPENING);
            Tag t2("dir", OPENING);

            Assert::IsFalse(t1.closes(t2));
        }

        TEST_METHOD(Test_Closing_Tag_Correct_Opener)
        {
            Tag t1("dir", OPENING);
            Tag t2("dir", CLOSING);

            Assert::IsTrue(t2.closes(t1));
        }

        TEST_METHOD(Test_Closing_Tag_Incorrect_Opener)
        {
            Tag t1("file", OPENING);
            Tag t2("dir", CLOSING);

            Assert::IsFalse(t2.closes(t1));
        }
    };
}
#include "CppUnitTest.h"
#include "Tree.h"
#include "Tag.h"
#include "XMLValidator.h"
#include "XMLValidator.cpp"
#include <iostream>
#include <fstream>
#include <optional>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCA2
{
    TEST_CLASS(TestXMLValidatorNoTags)
    {
    public:
        TEST_METHOD(Test_Validator_No_Tags)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testNoTags.txt");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Assert::IsFalse(tree.has_value(), L"Tree should not have value");
        }

        TEST_METHOD(Test_Validator_One_Tag)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testOneTag.txt");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Tag expectedTag("dir", OPENING);
            Tree<Tag> expected(expectedTag);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Assert::IsTrue(tree.value().data == expected.data);
        }
    };
}
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
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Tag expectedTag("root", OPENING);
            Tree<Tag> expected(expectedTag);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Assert::IsTrue(tree.value().data == expected.data);
        }

        TEST_METHOD(Test_Validator_Tag_With_Children)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testTagWithChildren.txt");
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Tag parent("root", OPENING);
            Tag child("dir", OPENING);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Assert::IsTrue(tree.value().data == parent);
            Assert::IsTrue(tree.value().children->getIterator().currentNode->data->data == child);
        }
    };
}
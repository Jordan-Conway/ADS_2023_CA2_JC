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
    TEST_CLASS(TestXMLValidator)
    {
    public:
        TEST_METHOD(Test_Validator_No_Tags)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testNoTags.txt");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Assert::IsFalse(tree.has_value(), L"Tree should not have value");
            file.close();
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
            Assert::IsTrue(tree.value().data == expected.data, L"Tags do not match");
            file.close();
        }

        TEST_METHOD(Test_Validator_Tag_With_Children)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testTagWithChildren.xml");
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Tag parent("root", OPENING);
            Tag child("dir", OPENING);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Assert::IsTrue(tree.value().data == parent);
            Assert::IsTrue(tree.value().children->getIterator().currentNode->data->data == child);
            file.close();
        }

        TEST_METHOD(Test_Validator_Three_Layers)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testThreeLayers.txt");
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Tag parent("root", OPENING);
            Tag child1("file", OPENING);
            Tag child2("dir", OPENING);
            Tag child21("file", OPENING);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Assert::IsTrue(tree.value().data == parent, L"Root is incorrect");
            DListIterator<Tree<Tag>*> iter = tree.value().children->getIterator();
            Assert::IsTrue(iter.currentNode->data->data == child1, L"First child is incorrect");
            iter.advance();
            Assert::IsTrue(iter.currentNode->data->data == child2, L"Second child is incorrect");
            DListIterator<Tree<Tag>*> childIter = iter.currentNode->data->children->getIterator();
            Assert::IsTrue(childIter.currentNode->data->data == child21, L"Third layer child is incorrect");
            file.close();
        }

        TEST_METHOD(Test_Validator_Non_Closed_Tag)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testNonClosedTag.txt");
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Assert::IsFalse(tree.has_value(), L"Tree should not have value");
            file.close();

        }

        TEST_METHOD(Test_Validator_Get_Name)
        {
            XMLValidator validator;
            std::ifstream file;
            file.open("testName.txt");
            Assert::IsTrue(file.good(), L"Error in file");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Assert::IsTrue(tree.has_value(), L"Tree should have value");
            Tag expected("file", OPENING);
            expected.setName("TestFile");
            Assert::IsTrue(tree.value().data == expected, L"Tags do not match");
        }
    };
}
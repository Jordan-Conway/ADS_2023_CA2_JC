#include "CppUnitTest.h"
#include "Tree.h"
#include "Tag.h"
#include "XMLValidator.h"
#include "XMLValidator.cpp"
#include <iostream>
#include <fstream>
#include <optional>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestXMLTagParser
{
    TEST_CLASS(TestXMLValidatorNoTags)
    {
    public:
        TEST_METHOD(Test_Validator_No_Tags)
        {;
            XMLValidator validator;
            std::ifstream file;
            file.open("testNoTags.txt");
            std::optional<Tree<Tag>> tree = validator.validate(file);
            Assert::IsFalse(tree.has_value());
        }
    };
}
#include "CppUnitTest.h"
#include "XMLTagParser.cpp"
#include "Tag.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    
namespace TestCA2
{
    TEST_CLASS(TestXMLParser)
    {
    public:
        TEST_METHOD(Test_Contains_Tag_Empty_String)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "";
            bool result = xmlTagParser.containsTag(toTest);
            Assert::IsFalse(result);
        }
        TEST_METHOD(Test_Contains_Tag_No_Tag)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "Hello";
            bool result = xmlTagParser.containsTag(toTest);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Test_Contains_Tag_One_Tag)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "<name>";
            bool result = xmlTagParser.containsTag(toTest);
            Assert::IsTrue(result);
        }

        TEST_METHOD(Test_Contains_Tag_Malformed_Tag)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "<name<";
            bool result = xmlTagParser.containsTag(toTest);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Test_Has_Attributes_Empty_String)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "";
            bool result = xmlTagParser.hasAttributes(toTest);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Test_Has_Attributes_Valid_Tag_No_Atrributes)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "<name>";
            bool result = xmlTagParser.hasAttributes(toTest);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Test_Has_Attributes_Valid_Tag_With_Spaces)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "<name >";
            bool result = xmlTagParser.hasAttributes(toTest);
            Assert::IsFalse(result);
        }

        TEST_METHOD(Test_Has_Attributes_Valid_Tag_With_Atrributes)
        {
            XMLTagParser xmlTagParser;
            std::string toTest = "<script id=\"__gaOptOutExtension\"/>";
            bool result = xmlTagParser.hasAttributes(toTest);
            Assert::IsTrue(result);
        }


        TEST_METHOD(Test_Get_Tags_From_String_Empty_String)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "";
            std::list<Tag> expected = {};
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected == actual, L"Empty string did not result in empty list");
        }

        TEST_METHOD(Test_Get_Tags_From_String_No_Tags)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "Hello World";
            std::list<Tag> expected = {};
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected == actual, L"String with no tags did not result in empty list");
        }

        TEST_METHOD(Test_Get_Tags_From_String_One_Tag)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<dir>";
            std::list<Tag> expected = {
                Tag("dir", TagType::OPENING)
            };
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsFalse(actual.empty(), L"Returned list is empty");
            Assert::IsTrue(expected.front() == actual.front(), L"Failed to return one tag");
        }

        TEST_METHOD(Test_Get_Tags_From_String_Multiple_Strings)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<name>description</name>";
            std::list<Tag> expected = {
                Tag("name", TagType::OPENING),
                Tag("name", TagType::CLOSING)
            };
            expected.front().setContent("description");
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected.front() == actual.front(), L"First tag is incorrect");
            Assert::IsTrue(expected.back() == actual.back(), L"Second tag is incorrect.");
        }

        TEST_METHOD(Test_Get_Tags_From_String_Selfclosing_Tag)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<script/>";
            std::list<Tag> expected = {
                Tag("script", TagType::SELFCLOSING)
            };
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected.front() == actual.front(), L"Tags do not match");
        }

        TEST_METHOD(Test_Get_Tags_From_String_Opening_Tag_With_Attributes)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<name for=\"world\">";
            std::list<Tag> expected = {
                Tag("name", TagType::OPENING)
            };
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected.front() == actual.front(), L"Tags do not match");
        }

        TEST_METHOD(Test_Get_Tags_From_String_Selfclosing_Tag_With_Attributes)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<script id=\"__gaOptOutExtension\"/>";
            std::list<Tag> expected = {
                Tag("script", TagType::SELFCLOSING)
            };
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected.front() == actual.front(), L"Tags do not match");
        }

        TEST_METHOD(Test_Get_Tag_Name)
        {
            XMLTagParser xmlTagParser;
            std::string xmlString = "<name>Name</name>";
            std::list<Tag> expected = {
                Tag("name", OPENING),
                Tag("name", CLOSING)
            };
            expected.front().setContent("Name");
            std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
            Assert::IsTrue(expected.front() == actual.front(), L"Tags do not match");
        }


    };
}

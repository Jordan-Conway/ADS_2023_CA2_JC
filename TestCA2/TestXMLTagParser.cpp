#include "CppUnitTest.h"
#include "XMLTagParser.cpp"
#include "Tag.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	
namespace TestXMLTagParser
{
	TEST_CLASS(TestCA2)
	{
	public:
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
			std::list<Tag> expected = {};
			expected.push_back(Tag("dir", TagType::OPENING));
			std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
			Assert::IsTrue(expected == actual, L"Failed to return one tag");
		}

		TEST_METHOD(Test_Get_Tags_From_String_Multiple_Strings)
		{
			XMLTagParser xmlTagParser;
			std::string xmlString = "<name>description</name>";
			std::list<Tag> expected = {};
			expected.push_back(Tag("name", TagType::OPENING));
			expected.push_back(Tag("name", TagType::CLOSING));
			std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
			Assert::IsTrue(expected == actual, L"Failed to return two tags");
		}

		TEST_METHOD(Test_Get_Tags_From_String_Selfclosing_Tag)
		{
			XMLTagParser xmlTagParser;
			std::string xmlString = "<script id=\"__gaOptOutExtension\"/>";
			std::list<Tag> expected = {};
			expected.push_back(Tag("script", TagType::SELFCLOSING));
			std::list<Tag> actual = xmlTagParser.getTagsFromString(xmlString);
			Assert::IsTrue(expected == actual, L"Failed to return one self-closing tag");
		}
	};
}

#include "CppUnitTest.h"
#include "../CA2/XMLTagParser.h"
#include "../CA2/Tag.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> 
			static std::wstring ToString<Tag>(const Tag& t) {
				return ("{tagName:" + t.getTagName() + ",tagType:" + TagTypeToString(t.getTagType()) + "}");
			}
		}
	}
}
	

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
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Test_Get_Tags_From_String_No_Tags)
		{

		}

		TEST_METHOD(Test_Get_Tags_From_String_One_Tag)
		{

		}

		TEST_METHOD(Test_Get_Tags_From_String_Multiple_Strings)
		{

		}

		TEST_METHOD(Test_Get_Tags_From_String_Selfclosing_Tag)
		{

		}
	};
}

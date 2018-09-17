#include "CppUnitTest.h"

#include "rvi_base.h"
#include "serialization.h"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Serialization_UnitTests
{
    using namespace rvi;
    TEST_CLASS(StringSerializationTests)
    {
    public:
        TEST_METHOD(SerializeString)
        {
            std::string s = "This is a test string!";
            std::vector<U8> dataContainer;
            Serializer::SerializeString(dataContainer, s);
            Assert::IsTrue(dataContainer.size() == s.size() + 3);
            for (int i = 3; i < s.size(); i++)
            {
                Assert::IsTrue(dataContainer[i] == s[i - 3]);
            }
        }

        TEST_METHOD(SerializeStringRoundtrip)
        {
            std::string s = "This is a test string!";
            std::vector<U8> dataContainer;
            Serializer::SerializeString(dataContainer, s);
            size_t offset = 0;
            std::string deserialized = Serializer::DeserializeString(dataContainer, offset);
            Assert::AreEqual(s, deserialized);
        }

        TEST_METHOD(SerializeU16String)
        {
            std::u16string s(u"This is a test string!");
            std::vector<U8> dataContainer;
            Serializer::SerializeU16String(dataContainer, s);
            Assert::IsTrue(dataContainer.size() == (s.size() * sizeof(std::u16string::value_type)) + 3);
            for (int i = 3; i < dataContainer.size(); i += sizeof(char16_t))
            {
                char16_t ch = (char16_t)(dataContainer[i+1] | (dataContainer[i] << 8));
                Assert::IsTrue(s[(i - 3) / 2] == ch);
            }
        }

        TEST_METHOD(SerializeU16StringRoundtrip)
        {
            std::u16string s(u"This is a test string!");
            std::vector<U8> dataContainer;
            Serializer::SerializeU16String(dataContainer, s);
            size_t offset = 0;
            std::u16string deserialized = Serializer::DeserializeU16String(dataContainer, offset);
            Assert::IsTrue(s == deserialized);
        }

        TEST_METHOD(SerializeU32String)
        {
            std::u32string s(U"This is a test string!");
            std::vector<U8> dataContainer;
            Serializer::SerializeU32String(dataContainer, s);
            Assert::IsTrue(dataContainer.size() == (s.size() * sizeof(std::u32string::value_type)) + 3);
            for (int i = 3; i < dataContainer.size(); i += sizeof(char32_t))
            {
                char32_t ch =
                    (char16_t)((dataContainer[i + 3])
                        | (dataContainer[i + 2] << 8)
                        | (dataContainer[i + 1] << 16)
                        | (dataContainer[i] << 24));
                Assert::IsTrue(s[(i - 3) / sizeof(ch)] == ch);
            }
        }

        TEST_METHOD(SerializeU32StringRoundtrip)
        {
            std::u32string s(U"This is a test string!");
            std::vector<U8> dataContainer;
            Serializer::SerializeU32String(dataContainer, s);
            size_t offset = 0;
            std::u32string deserialized = Serializer::DeserializeU32String(dataContainer, offset);
            Assert::IsTrue(s == deserialized);
        }
    };
}
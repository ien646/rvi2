#include "CppUnitTest.h"

#include "rvi_base.h"
#include "serialization.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    using namespace rvi;
    TEST_CLASS(StringSerializationTests)
    {
    public:
        TEST_METHOD(Test_SerializeString)
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
        
        TEST_METHOD(Test_SerializeStringRoundtrip)
        {
            std::string s = "This is a test string!";
            std::vector<U8> dataContainer;
            Serializer::SerializeString(dataContainer, s);
            size_t offset = 0;
            std::string deserialized = Serializer::DeserializeString(dataContainer, offset);
            Assert::AreEqual(s, deserialized);
        }
    };
}
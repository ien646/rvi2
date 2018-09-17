#include "CppUnitTest.h"

#include "rvi_base.h"
#include "serialization.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    using namespace rvi;
    TEST_CLASS(IntegerSerializationTests)
    {
    public:
        TEST_METHOD(Test_SerializeInteger)
        {
            U8 u8 = 0x43;
            U16 u16 = 0x3A71;
            U32 u32 = 0x098B66E5;
            U64 u64 = 0x1A9866E5A98B66E5;

            std::vector<U8> dataContainer;

            size_t sz = rvi::Serializer::SerializeInteger<U8>(dataContainer, u8);
            Assert::AreEqual(dataContainer[0], u8);
            Assert::AreEqual(sz, (size_t)sizeof(u8));

            sz = rvi::Serializer::SerializeInteger<U16>(dataContainer, u16);
            Assert::AreEqual(dataContainer[2], (U8)(u16 >> 0));
            Assert::AreEqual(dataContainer[1], (U8)(u16 >> 8));
            Assert::AreEqual(sz, (size_t)sizeof(u16));

            sz = rvi::Serializer::SerializeInteger<U32>(dataContainer, u32);
            Assert::AreEqual(dataContainer[6], (U8)(u32 >> 0));
            Assert::AreEqual(dataContainer[5], (U8)(u32 >> 8));
            Assert::AreEqual(dataContainer[4], (U8)(u32 >> 16));
            Assert::AreEqual(dataContainer[3], (U8)(u32 >> 24));
            Assert::AreEqual(sz, (size_t)sizeof(u32));

            sz = rvi::Serializer::SerializeInteger<U64>(dataContainer, u64);
            Assert::AreEqual(dataContainer[14], (U8)(u64 >> 0));
            Assert::AreEqual(dataContainer[13], (U8)(u64 >> 8));
            Assert::AreEqual(dataContainer[12], (U8)(u64 >> 16));
            Assert::AreEqual(dataContainer[11], (U8)(u64 >> 24));
            Assert::AreEqual(dataContainer[10], (U8)(u64 >> 32));
            Assert::AreEqual(dataContainer[9], (U8)(u64 >> 40));
            Assert::AreEqual(dataContainer[8], (U8)(u64 >> 48));
            Assert::AreEqual(dataContainer[7], (U8)(u64 >> 56));
            Assert::AreEqual(sz, (size_t)sizeof(u64));
        }

        TEST_METHOD(Test_DeserializeInteger)
        {
            std::vector<U8> dataContainer =
            {
                0xA1, 0xB2, 0xC3, 0xD4,
                0xA5, 0xB6, 0xC7, 0xD8
            };

            size_t offset = 0;
            U8 u8 = rvi::Serializer::DeserializeInteger<U8>(dataContainer, offset);
            Assert::AreEqual(u8, dataContainer[0]);
            Assert::AreEqual(offset, (size_t)1);

            offset = 2;
            u8 = rvi::Serializer::DeserializeInteger<U8>(dataContainer, offset);
            Assert::AreEqual(u8, dataContainer[2]);
            Assert::AreEqual(offset, (size_t)3);

            offset = 7;
            u8 = rvi::Serializer::DeserializeInteger<U8>(dataContainer, offset);
            Assert::AreEqual(u8, dataContainer[7]);
            Assert::AreEqual(offset, (size_t)8);

            offset = 0;
            U16 u16 = rvi::Serializer::DeserializeInteger<U16>(dataContainer, offset);
            Assert::IsTrue(u16 == (U16)0xA1B2);
            Assert::AreEqual(offset, (size_t)2);

            offset = 2;
            u16 = rvi::Serializer::DeserializeInteger<U16>(dataContainer, offset);
            Assert::IsTrue(u16 == (U16)0xC3D4);
            Assert::AreEqual(offset, (size_t)4);

            offset = 6;
            u16 = rvi::Serializer::DeserializeInteger<U16>(dataContainer, offset);
            Assert::IsTrue(u16 == (U16)0xC7D8);
            Assert::AreEqual(offset, (size_t)8);

            offset = 0;
            U32 u32 = rvi::Serializer::DeserializeInteger<U32>(dataContainer, offset);
            Assert::IsTrue(u32 == (U32)0xA1B2C3D4);
            Assert::AreEqual(offset, (size_t)4);

            offset = 4;
            u32 = rvi::Serializer::DeserializeInteger<U32>(dataContainer, offset);
            Assert::IsTrue(u32 == (U32)0xA5B6C7D8);
            Assert::AreEqual(offset, (size_t)8);

            offset = 0;
            U64 u64 = rvi::Serializer::DeserializeInteger<U64>(dataContainer, offset);
            Assert::IsTrue(u64 == (U64)0xA1B2C3D4A5B6C7D8);
            Assert::AreEqual(offset, (size_t)8);
        }
    };
}
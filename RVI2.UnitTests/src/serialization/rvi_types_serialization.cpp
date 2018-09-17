#include "CppUnitTest.h"

#include "rvi_base.h"
#include "vector2.h"
#include "color_rgba.h"
#include "line.h"
#include "vertex.h"
#include "serialization.h"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Serialization_UnitTests
{
    using namespace rvi;
    TEST_CLASS(RviTypesSerilizationTests)
    {
    public:
        TEST_METHOD(Vector2SerializationRoundtrip)
        {
            std::vector<U8> dataContainer;
            Vector2 v(0.05F, 7.55F);
            Serializer::SerializeVector2(dataContainer, v);
            size_t offset = 0;
            Vector2 res = Serializer::DeserializeVector2(dataContainer, offset);

            Assert::IsTrue(v == res);
        }

        TEST_METHOD(ColorRGBASerializationRoundtrip)
        {
            std::vector<U8> dataContainer;
            ColorRGBA c(152, 177, 54, 222);
            Serializer::SerializeColorRGBA(dataContainer, c);
            size_t offset = 0;
            ColorRGBA res = Serializer::DeserializeColorRGBA(dataContainer, offset);

            Assert::IsTrue(c == res);
        }

        TEST_METHOD(VertexSerializationRoundtrip)
        {
            std::vector<U8> dataContainer;
            Vertex v(Vector2(0.5F, 0.999F), ColorRGBA::FUCHSIA_LIGHT());
            Serializer::SerializeVertex(dataContainer, v);
            size_t offset = 0;
            Vertex res = Serializer::DeserializeVertex(dataContainer, offset);

            Assert::IsTrue(v == res);
        }

        TEST_METHOD(LineSerializationRoundtrip)
        {
            std::vector<U8> dataContainer;
            Vertex a(Vector2(5, 0.7F), ColorRGBA::BLUE());
            Vertex b(Vector2(7, 0.98F), ColorRGBA::RED_LIGHT());
            Line v(a, b);
            Serializer::SerializeLine(dataContainer, v);
            size_t offset = 0;
            Line res = Serializer::DeserializeLine(dataContainer, offset);

            Assert::IsTrue(v == res);
        }
    };
}
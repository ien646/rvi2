#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <definition.hpp>
#include <client_context.hpp>
#include <line.hpp>

#include "random_gen.hpp"

using namespace rvi;

class Mock_ClientContext : public ClientContext
{
public:
    MOCK_METHOD0(MockCall, void());
};

TEST(Definition, AddInstruction)
{
    bool mock_flag = false;
    Vertex vx1, vx2;
    DefinitionInstruction inst = [&](ClientContext& ctx){ mock_flag = true; };

    Definition def("test_def");
    def.AddInstruction(std::move(std::move(inst)));

    auto& sequence = def.GetSequence();
    testing::NiceMock<Mock_ClientContext> ctx;
    sequence.at(0)(ctx);

    ASSERT_EQ(1, sequence.size());
    ASSERT_TRUE(mock_flag);
}

TEST(Definition, Clear)
{
    Definition def("test_def");
    DefinitionInstruction inst = [&](ClientContext& ctx){ return; };
    size_t icount = static_cast<size_t>(std::max(10, std::abs(GetRandomInt())));
    for(size_t i = 0; i < icount; i++)
    {
        def.AddInstruction(std::move(std::move(inst)));
    }

    auto& sequence = def.GetSequence();
    ASSERT_EQ(sequence.size(), icount);

    def.Clear();

    ASSERT_EQ(sequence.size(), 0);
}

TEST(Definition, ExecuteOnContext)
{
    testing::NiceMock<Mock_ClientContext> ctx;
    Definition def("test_def");
    Vertex vxf, vxt;
    DefinitionInstruction inst = [&](ClientContext& ctx)
    {
        // Just cheat a little bit
        Mock_ClientContext* mctx = reinterpret_cast<Mock_ClientContext*>(&ctx);
        mctx->MockCall();
    };

    size_t icount = static_cast<size_t>(std::max(10, std::abs(GetRandomInt())));
    EXPECT_CALL(ctx, MockCall()).Times(icount);

    for(size_t i = 0; i < icount; i++)
    {
        auto copy = inst;
        def.AddInstruction(std::move(copy));
    }

    def.ExecuteOnContext(*reinterpret_cast<ClientContext*>(&ctx));
}
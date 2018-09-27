#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <definition.hpp>
#include <client_context.hpp>
#include <line.hpp>

#include "random_gen.hpp"
#include "utils.hpp"

using namespace rvi;
static random_gen rnd;

class mock_client_context : public client_context
{
public:
    MOCK_METHOD0(mock_call, void());
};

TEST(definition, add_instruction)
{
    bool mock_flag = false;
    vertex vx1, vx2;
    definition_inst inst = [&](client_context& ctx)
    { 
        UNREFERENCED_PARAMETER(ctx);
        mock_flag = true; 
    };

    definition def("test_def");
    def.add_instruction(std::move(std::move(inst)));

    auto& sequence = def.get_sequence();
    testing::NiceMock<mock_client_context> ctx;
    sequence.at(0)(ctx);

    ASSERT_EQ(static_cast<size_t>(1), sequence.size());
    ASSERT_TRUE(mock_flag);
}

TEST(definition, clear)
{
    definition def("test_def");
    definition_inst inst = [&](client_context& ctx)
    { 
        UNREFERENCED_PARAMETER(ctx);
        return;
    };
    size_t icount = static_cast<size_t>(std::max(10, std::abs(rnd.get_random_int())));
    for(size_t i = 0; i < icount; i++)
    {
        def.add_instruction(std::move(std::move(inst)));
    }

    auto& sequence = def.get_sequence();
    ASSERT_EQ(sequence.size(), icount);

    def.clear();

    ASSERT_EQ(sequence.size(), static_cast<size_t>(0));
}

TEST(definition, execute_on_context)
{
    testing::NiceMock<mock_client_context> ctx;
    definition def("test_def");
    vertex vxf, vxt;
    definition_inst inst = [&](client_context& ctx)
    {
        // Just cheat a little bit
        mock_client_context* mctx = reinterpret_cast<mock_client_context*>(&ctx);
        mctx->mock_call();
    };

    int icount = std::max(10, std::abs(rnd.get_random_int()));
    EXPECT_CALL(ctx, mock_call()).Times(icount);

    for(int i = 0; i < icount; i++)
    {
        auto copy = inst;
        def.add_instruction(std::move(copy));
    }

    def.execute_on_context(*reinterpret_cast<client_context*>(&ctx));
}
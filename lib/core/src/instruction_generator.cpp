#include "instruction_generator.hpp"

#define CAPTURE_RVALUEREF(x) &x
#define NOCAPTURE

typedef rvi::DefinitionInstruction INSTRUCTION;

using std::string;

namespace rvi
{
    INSTRUCTION InstructionGenerator::DrawLine(Vector2 from, Vector2 to)
    {
        return[=](ClientContext& c)
        { c.DrawLine(from, to); };
    }

    INSTRUCTION InstructionGenerator::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        return[=](ClientContext& c)
        { c.DrawLine(from, fromColor, to, toColor); };
    }

    INSTRUCTION InstructionGenerator::DrawLine(Vertex from, Vertex to)
    {
        return[=](ClientContext& c)
        { c.DrawLine(from, to); };
    }

    INSTRUCTION InstructionGenerator::SelectFrame(const string& name)
    {
        return[=](ClientContext& c)
        { c.SelectFrame(name); };
    }

    INSTRUCTION InstructionGenerator::SelectFrame(string&& name)
    {
        return[&](ClientContext& c)
        { c.SelectFrame(std::move(name)); };
    }

    INSTRUCTION InstructionGenerator::ReleaseFrame()
    {
        return[NOCAPTURE](ClientContext& c)
        { c.ReleaseFrame(); };
    }

    INSTRUCTION InstructionGenerator::SetCurrentColor(ColorRGBA color)
    {
        return[=](ClientContext& c) noexcept
        { c.SetCurrentColor(color); };
    }

    INSTRUCTION InstructionGenerator::SetCurrentTransform(const Transform2& tform)
    {
        return[=](ClientContext& c) noexcept
        { c.SetCurrentTransform(tform); };
    }

    INSTRUCTION InstructionGenerator::SetCurrentTransform(Transform2&& tform)
    {
        return[&](ClientContext& c) noexcept
        { c.SetCurrentTransform(std::move(tform)); };
    }

    INSTRUCTION InstructionGenerator::AddDefinition(const Definition& instruction)
    {
        return[instruction](ClientContext& c)
        { c.AddDefinition(instruction); };
    }

    INSTRUCTION InstructionGenerator::AddDefinition(Definition&& instruction)
    {
        return[CAPTURE_RVALUEREF(instruction)](ClientContext& c)
        { c.AddDefinition(std::move(instruction)); };
    }
}
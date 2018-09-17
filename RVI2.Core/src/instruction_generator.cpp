#include "instruction_generator.h"

#define CAPTURE_RVALUEREF(x) &x
#define NOCAPTURE
#define IGEN_LAMB_ARGS (ClientContext& c)

namespace rvi
{
    Definition::Instruction InstructionGenerator::DrawLine(Vector2 from, Vector2 to)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, to); };
    }

    Definition::Instruction InstructionGenerator::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, fromColor, to, toColor); };
    }

    Definition::Instruction InstructionGenerator::DrawLine(Vertex from, Vertex to)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, to); };
    }

    Definition::Instruction InstructionGenerator::SelectFrame(const std::string& name)
    {
        return [=]IGEN_LAMB_ARGS
        { c.SelectFrame(name); };
    }

    Definition::Instruction InstructionGenerator::SelectFrame(std::string&& name)
    {
        return [&]IGEN_LAMB_ARGS
        { c.SelectFrame(std::move(name)); };
    }

    Definition::Instruction InstructionGenerator::ReleaseFrame()
    {
        return [NOCAPTURE]IGEN_LAMB_ARGS
        { c.ReleaseFrame(); };
    }

    Definition::Instruction InstructionGenerator::SetCurrentColor(ColorRGBA color)
    {
        return [=]IGEN_LAMB_ARGS
        { c.SetCurrentColor(color); };
    }

    Definition::Instruction InstructionGenerator::SetCurrentTransform(const Transform2& tform)
    {
        return [=]IGEN_LAMB_ARGS
        { c.SetCurrentTransform(tform); };
    }

    Definition::Instruction InstructionGenerator::SetCurrentTransform(Transform2&& tform)
    {
        return [&]IGEN_LAMB_ARGS
        { c.SetCurrentTransform(std::move(tform)); };
    }

    Definition::Instruction InstructionGenerator::AddDefinition(const std::string& name, const Definition& instruction)
    {
        return[name, instruction]IGEN_LAMB_ARGS
        { c.AddDefinition(name,instruction); };
    }

    Definition::Instruction InstructionGenerator::AddDefinition(const std::string& name, Definition&& instruction)
    {
        return [name, CAPTURE_RVALUEREF(instruction)]IGEN_LAMB_ARGS
        { c.AddDefinition(name, std::move(instruction)); };
    }

    Definition::Instruction InstructionGenerator::AddDefinition(std::string&& name, const Definition& instruction)
    {
        return[CAPTURE_RVALUEREF(name), instruction]IGEN_LAMB_ARGS
        { c.AddDefinition(std::move(name),instruction); };
    }

    Definition::Instruction rvi::InstructionGenerator::AddDefinition(std::string&& name, Definition&& instruction)
    {
        return [CAPTURE_RVALUEREF(name), CAPTURE_RVALUEREF(instruction)]IGEN_LAMB_ARGS
        { c.AddDefinition(std::move(name), std::move(instruction)); };
    }
}
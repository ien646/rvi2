#include "instruction_generator.h"

#define CAPTURE_RVALUEREF(x) &x
#define NOCAPTURE
#define IGEN_LAMB_ARGS (ClientContext& c)

typedef rvi::DefinitionInstruction INSTRUCTION;

using std::string;

namespace rvi
{
	INSTRUCTION InstructionGenerator::DrawLine(Vector2 from, Vector2 to)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, to); };
    }

	INSTRUCTION InstructionGenerator::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, fromColor, to, toColor); };
    }

	INSTRUCTION InstructionGenerator::DrawLine(Vertex from, Vertex to)
    {
        return [=]IGEN_LAMB_ARGS
        { c.DrawLine(from, to); };
    }

	INSTRUCTION InstructionGenerator::SelectFrame(const string& name)
    {
        return [=]IGEN_LAMB_ARGS
        { c.SelectFrame(name); };
    }

	INSTRUCTION InstructionGenerator::SelectFrame(string&& name)
    {
        return [&]IGEN_LAMB_ARGS
        { c.SelectFrame(std::move(name)); };
    }

	INSTRUCTION InstructionGenerator::ReleaseFrame()
    {
        return [NOCAPTURE]IGEN_LAMB_ARGS
        { c.ReleaseFrame(); };
    }

	INSTRUCTION InstructionGenerator::SetCurrentColor(ColorRGBA color)
    {
        return [=]IGEN_LAMB_ARGS noexcept
        { c.SetCurrentColor(color); };
    }

	INSTRUCTION InstructionGenerator::SetCurrentTransform(const Transform2& tform)
    {
        return [=]IGEN_LAMB_ARGS noexcept
        { c.SetCurrentTransform(tform); };
    }

	INSTRUCTION InstructionGenerator::SetCurrentTransform(Transform2&& tform)
    {
        return [&]IGEN_LAMB_ARGS noexcept
        { c.SetCurrentTransform(std::move(tform)); };
    }

	INSTRUCTION InstructionGenerator::AddDefinition(const string& name, const Definition& instruction)
    {
        return[name, instruction]IGEN_LAMB_ARGS
        { c.AddDefinition(name,instruction); };
    }

	INSTRUCTION InstructionGenerator::AddDefinition(const string& name, Definition&& instruction)
    {
        return [name, CAPTURE_RVALUEREF(instruction)]IGEN_LAMB_ARGS
        { c.AddDefinition(name, std::move(instruction)); };
    }

	INSTRUCTION InstructionGenerator::AddDefinition(string&& name, const Definition& instruction)
    {
        return[CAPTURE_RVALUEREF(name), instruction]IGEN_LAMB_ARGS
        { c.AddDefinition(std::move(name),instruction); };
    }

	INSTRUCTION InstructionGenerator::AddDefinition(string&& name, Definition&& instruction)
    {
        return [CAPTURE_RVALUEREF(name), CAPTURE_RVALUEREF(instruction)]IGEN_LAMB_ARGS
        { c.AddDefinition(std::move(name), std::move(instruction)); };
    }
}
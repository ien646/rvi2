#pragma once

#include "client_context.h"
#include "definition.h"

namespace rvi
{
    class InstructionGenerator
    {
    public:
        static Definition::Instruction DrawLine(Vector2 from, Vector2 to);
        static Definition::Instruction DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor);
        static Definition::Instruction DrawLine(Vertex from, Vertex to);

        static Definition::Instruction SelectFrame(const std::string& name);
        static Definition::Instruction SelectFrame(std::string&& name);

        static Definition::Instruction ReleaseFrame();

        static Definition::Instruction SetCurrentColor(ColorRGBA color);

        static Definition::Instruction SetCurrentTransform(const Transform2& tform);
        static Definition::Instruction SetCurrentTransform(Transform2&& tform);

        static Definition::Instruction AddDefinition(const std::string& name, const Definition& instruction);
        static Definition::Instruction AddDefinition(const std::string& name, Definition&& instruction);
        static Definition::Instruction AddDefinition(std::string&& name, const Definition& instruction);
        static Definition::Instruction AddDefinition(std::string&& name, Definition&& instruction);
    };
}
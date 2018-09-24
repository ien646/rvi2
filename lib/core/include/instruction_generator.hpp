#pragma once

#include "client_context.hpp"
#include "definition.hpp"

namespace rvi
{
    class InstructionGenerator
    {
    public:
        static DefinitionInstruction DrawLine(Vector2 from, Vector2 to);
        static DefinitionInstruction DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor);
        static DefinitionInstruction DrawLine(Vertex from, Vertex to);

        static DefinitionInstruction SelectFrame(const std::string& name);
        static DefinitionInstruction SelectFrame(std::string&& name);

        static DefinitionInstruction ReleaseFrame();

        static DefinitionInstruction SetCurrentColor(ColorRGBA color);

        static DefinitionInstruction SetCurrentTransform(const Transform2& tform);
        static DefinitionInstruction SetCurrentTransform(Transform2&& tform);

        static DefinitionInstruction AddDefinition(const Definition& instruction);
        static DefinitionInstruction AddDefinition(Definition&& instruction);
    };
}
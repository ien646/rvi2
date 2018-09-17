#include "client_context.h"

namespace rvi
{
    ClientContext::ClientContext() noexcept
        : _mainFrame(MAIN_FRAMENAME)
        , _selectedFrame(_mainFrame)
        , _contextId(Random().GetUnsigned64())
    { 
        _frameStack.push(_mainFrame);
    }

    U64 ClientContext::ContextId() const
    {
        return _contextId;
    }

    void ClientContext::DrawLine(Vector2 from, Vector2 to)
    {
        _selectedFrame.AddLine
        (
            Vertex(from, _selectedFrame.Color()),
            Vertex(to, _selectedFrame.Color())
        );
    }

    void ClientContext::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        _selectedFrame.AddLine
        (
            Vertex(from, fromColor),
            Vertex(to, toColor)
        );
    }

    void ClientContext::DrawLine(Vertex from, Vertex to)
    {
        _selectedFrame.AddLine(from, to);
    }

    void ClientContext::SelectFrame(const std::string& name)
    {
        if (!_selectedFrame.ContainsChildFrame(name))
        {
            _selectedFrame = _selectedFrame.AddChildFrame(name);
        }
        else
        {
            _selectedFrame = _selectedFrame.GetChildFrame(name);
        }
        _frameStack.push(_selectedFrame);
    }

    void ClientContext::SelectFrame(std::string&& name)
    {
        if (!_selectedFrame.ContainsChildFrame(name))
        {
            _selectedFrame = _selectedFrame.AddChildFrame(std::move(name));
        }
        else
        {
            _selectedFrame = _selectedFrame.GetChildFrame(name);
        }
        _frameStack.push(_selectedFrame);
    }

    void ClientContext::ReleaseFrame()
    {
        _frameStack.pop();
        _selectedFrame = _frameStack.top();
    }

    void ClientContext::SetCurrentColor(ColorRGBA color)
    {
        _selectedFrame.SetColor(color);
    }

    void ClientContext::SetCurrentTransform(const Transform2 & tform)
    {
        _selectedFrame.SetTransform(tform);
    }

    void ClientContext::SetCurrentTransform(Transform2 && tform)
    {
        _selectedFrame.SetTransform(std::move(tform));
    }

    const Transform2& ClientContext::GetCurrentTransform() const
    {
        return _selectedFrame.Transform();
    }

    void ClientContext::SetCurrentOffset(Vector2 offset)
    {
        _selectedFrame.SetOffset(offset);
    }

    void ClientContext::SetCurrentRotation(float rotation)
    {
        _selectedFrame.SetRotation(rotation);
    }

    void ClientContext::SetCurrentScale(Vector2 scale)
    {
        _selectedFrame.SetScale(scale);
    }

    Vector2 ClientContext::GetCurrentOffset() const
    {
        return _selectedFrame.Transform().Position;
    }

    float ClientContext::GetCurrentRotation() const
    {
        return _selectedFrame.Transform().Rotation;
    }

    Vector2 ClientContext::GetCurrentScale() const
    {
        return _selectedFrame.Transform().Scale;
    }

    void ClientContext::ClearFrame()
    {
        _selectedFrame.ClearLines();
    }

    void ClientContext::AddDefinition(const std::string& name, const Definition& instruction)
    {
        DISCARD _localDefinitions.emplace(name, instruction);
    }

    void ClientContext::AddDefinition(std::string&& name, const Definition& instruction)
    {
        DISCARD _localDefinitions.emplace(std::move(name), instruction);
    }

    void ClientContext::AddDefinition(const std::string& name, Definition&& instruction)
    {
        DISCARD _localDefinitions.emplace(name, std::move(instruction));
    }

    void ClientContext::AddDefinition(std::string&& name, Definition&& instruction)
    {
        DISCARD _localDefinitions.emplace(std::move(name), std::move(instruction));
    }
}
#include "client_context.h"

namespace rvi
{
	#if RVI_COMPILER_MSVC
	#pragma warning(suppress: 26439)
	#endif
    ClientContext::ClientContext()
        : _mainFrame(MAIN_FRAMENAME) 
        , _selectedFrame(_mainFrame)
        , _contextId(Random().GetUnsigned64())
    { 
        _frameStack.push(_mainFrame);
    }

    U64 ClientContext::ContextId() const noexcept
    {
        return _contextId;
    }

    void ClientContext::DrawLine(Vector2 from, Vector2 to)
    {
        _selectedFrame.get().AddLine
        (
            Vertex(from, _selectedFrame.get().Color()),
            Vertex(to, _selectedFrame.get().Color())
        );
    }

    void ClientContext::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        _selectedFrame.get().AddLine
        (
            Vertex(from, fromColor),
            Vertex(to, toColor)
        );
    }

    void ClientContext::DrawLine(Vertex from, Vertex to)
    {
        _selectedFrame.get().AddLine(from, to);
    }

    void ClientContext::SelectFrame(const std::string& name)
    {
        if (!_selectedFrame.get().ContainsChildFrame(name))
        {
            _selectedFrame = _selectedFrame.get().AddChildFrame(name);
        }
        else
        {
            _selectedFrame = _selectedFrame.get().GetChildFrame(name);
        }
        _frameStack.push(_selectedFrame);
    }

    void ClientContext::SelectFrame(std::string&& name)
    {
        if (!_selectedFrame.get().ContainsChildFrame(name))
        {
            _selectedFrame = _selectedFrame.get().AddChildFrame(std::move(name));
        }
        else
        {
            _selectedFrame = _selectedFrame.get().GetChildFrame(name);
        }
        _frameStack.push(_selectedFrame);
    }

    bool ClientContext::ReleaseFrame()
    {
        if (&_selectedFrame.get() == &_mainFrame)
        {
            return false;
        }
        _frameStack.pop();
        _selectedFrame = _frameStack.top();
        return true;
    }

    bool ClientContext::DeleteFrame(const std::string& name)
    {
        return _selectedFrame.get().DeleteChildFrame(name);
    }

    void ClientContext::SetCurrentColor(ColorRGBA color) noexcept
    {
        _selectedFrame.get().SetColor(color);
    }

    void ClientContext::SetCurrentTransform(const Transform2& tform) noexcept
    {
        _selectedFrame.get().SetTransform(tform);
    }

    void ClientContext::SetCurrentTransform(Transform2&& tform) noexcept
    {
        _selectedFrame.get().SetTransform(std::move(tform));
    }

    const Transform2& ClientContext::GetCurrentTransform() const noexcept
    {
        return _selectedFrame.get().Transform();
    }

    void ClientContext::SetCurrentOffset(Vector2 offset) noexcept
    {
        _selectedFrame.get().SetOffset(offset);
    }

    void ClientContext::SetCurrentRotation(float rotation) noexcept
    {
        _selectedFrame.get().SetRotation(rotation);
    }

    void ClientContext::SetCurrentScale(Vector2 scale) noexcept
    {
        _selectedFrame.get().SetScale(scale);
    }

    Vector2 ClientContext::GetCurrentOffset() const noexcept
    {
        return _selectedFrame.get().Transform().Position;
    }

    float ClientContext::GetCurrentRotation() const noexcept
    {
        return _selectedFrame.get().Transform().Rotation;
    }

    Vector2 ClientContext::GetCurrentScale() const noexcept
    {
        return _selectedFrame.get().Transform().Scale;
    }

    void ClientContext::ClearFrame() noexcept
    {
        _selectedFrame.get().ClearLines();
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

    std::vector<Line> ClientContext::GetSnapshot()
    {
        return _mainFrame.GetModulatedLines(DEFAULT_TRANSFORM);
    }
}
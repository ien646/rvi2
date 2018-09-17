#include "client_context.h"

#include <sstream>
#include <iterator>

namespace rvi
{
    #if RVI_COMPILER_MSVC
    #pragma warning(suppress: 26439)
    #endif
    ClientContext::ClientContext()
        : _mainFrame(MAIN_FRAMENAME)
        , _selectedFrame(_mainFrame)
    {
        _frameStack.push_back(_mainFrame);
    }

    ClientContext ClientContext::CreateNew()
    {
        return ClientContext();
    }

    void ClientContext::DrawLine(Vector2 from, Vector2 to)
    {
        _selectedFrame.get().AddLine
        (
            Vertex(from, _selectedFrame.get().Color()),
            Vertex(to, _selectedFrame.get().Color())
        );
        MarkFrameAsModified();
    }

    void ClientContext::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        _selectedFrame.get().AddLine
        (
            Vertex(from, fromColor),
            Vertex(to, toColor)
        );
        MarkFrameAsModified();
    }

    void ClientContext::DrawLine(Vertex from, Vertex to)
    {
        _selectedFrame.get().AddLine(from, to);
        MarkFrameAsModified();
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
        _frameStack.push_back(_selectedFrame);
        _cachedFramePathNeedsRebuild = true;
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
        _frameStack.push_back(_selectedFrame);
        _cachedFramePathNeedsRebuild = true;
    }

    bool ClientContext::ReleaseFrame()
    {
        if (&_selectedFrame.get() == &_mainFrame)
        {
            return false;
        }
        _cachedFramePathNeedsRebuild = true;
        _frameStack.pop_back();
        _selectedFrame = _frameStack.back();
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
        MarkFrameAsModified();
    }

    void ClientContext::AddDefinition(const std::string& name, const Definition& instruction)
    {
        DISCARD_RESULT _localDefinitions.emplace(name, instruction);
    }

    void ClientContext::AddDefinition(std::string&& name, const Definition& instruction)
    {
        DISCARD_RESULT _localDefinitions.emplace(std::move(name), instruction);
    }

    void ClientContext::AddDefinition(const std::string& name, Definition&& instruction)
    {
        DISCARD_RESULT _localDefinitions.emplace(name, std::move(instruction));
    }

    void ClientContext::AddDefinition(std::string&& name, Definition&& instruction)
    {
        DISCARD_RESULT _localDefinitions.emplace(std::move(name), std::move(instruction));
    }

    void ClientContext::DeleteDefinition(const std::string& name)
    {
        _localDefinitions.erase(name);
    }

    const std::string& ClientContext::GetCurrentFramePath()
    {
        if (_cachedFramePathNeedsRebuild)
        {
            _cachedFramePath.clear();
            for (auto& frame : _frameStack)
            {
                _cachedFramePath += frame.get().Name();
            }
            _cachedFramePathNeedsRebuild = false;
        }
        return _cachedFramePath;
    }

    const std::pair<Transform2, Frame&> ClientContext::FramePathToFrameWithTransform(const std::string& fPath)
    {
        std::stringstream ss(fPath);
        std::string aux;
        Frame* currentFrame = nullptr;
        Transform2 currentTransform;

        currentFrame = &_mainFrame;
        currentTransform = DEFAULT_TRANSFORM;

        while (std::getline(ss, aux, FRAMEPATH_SEPARATOR))
        {
            if (aux != MAIN_FRAMENAME)
            {
                currentTransform = currentTransform.Merge(currentFrame->Transform());
                currentFrame = &currentFrame->GetChildFrame(aux);
            }
        }
        return std::pair<Transform2, Frame&>(currentTransform, *currentFrame);
    }

    void ClientContext::MarkFrameAsModified()
    {
        const std::string& fPath = GetCurrentFramePath();
        if (_modifiedFramePaths.count(fPath) == 0)
        {
            DISCARD_RESULT _modifiedFramePaths.insert(fPath);
        }
    }

    std::vector<Line> ClientContext::GetFullSnapshot()
    {
        return _mainFrame.GetModulatedLines(DEFAULT_TRANSFORM);
    }

    std::vector<Line> ClientContext::GetPartialSnapshot()
    {
        std::vector<Line> result;
        for (auto& fpath : _modifiedFramePaths)
        {
            const auto pair = FramePathToFrameWithTransform(fpath);
            const Transform2 parentTform = pair.first;
            const Frame& frame = pair.second;

            std::vector<Line> lines = frame.GetModulatedLines(parentTform);
            std::move(lines.begin(), lines.end(), std::back_inserter(result));
        }
        _modifiedFramePaths.clear();
        return result;
    }
}
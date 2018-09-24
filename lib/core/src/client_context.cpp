#include "client_context.hpp"

#include <sstream>
#include <iterator>

namespace rvi
{ 
    const char ClientContext::FRAMEPATH_SEPARATOR = ':';
    const std::string ClientContext::MAIN_FRAMENAME = "__MAINFRAME__";

    #if RVI_COMPILER_MSVC
    #pragma warning(suppress: 26439)
    #endif
    ClientContext::ClientContext()
        : _mainFrame(MAIN_FRAMENAME)
        , _selectedFrame(_mainFrame)
    {
        _frameStack.push_back(_mainFrame);
    }

    void ClientContext::DrawLine(Vector2 from, Vector2 to)
    {
        Line ln(Vertex(from, _selectedFrame.get().Color()),
                Vertex(to,  _selectedFrame.get().Color()));

        _selectedFrame.get().AddLine(std::move(ln));
        MarkFrameAsModified();
    }

    void ClientContext::DrawLine(Vector2 from, ColorRGBA fromColor, Vector2 to, ColorRGBA toColor)
    {
        _selectedFrame.get().AddLine(Line(Vertex(from, fromColor), Vertex(to, toColor)));
        MarkFrameAsModified();
    }

    void ClientContext::DrawLine(Vertex from, Vertex to)
    {        
        _selectedFrame.get().AddLine(Line(from, to));
        MarkFrameAsModified();
    }

    void ClientContext::DrawLine(Line&& ln)
    {
        _selectedFrame.get().AddLine(std::move(ln));
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

    const rvi::Frame& ClientContext::SelectedFrame() const noexcept
    {
        return _selectedFrame;
    }

    bool ClientContext::IsDefaultFrameSelected() const noexcept
    {
        return &_mainFrame == &_selectedFrame.get();
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

    size_t ClientContext::FrameCount() const noexcept
    {
        size_t result = 1;
        result += _mainFrame.ChildFrameCount(true);
        return result;
    }

    void ClientContext::ClearFrame() noexcept
    {
        _selectedFrame.get().ClearLines();
        MarkFrameAsModified();
    }

    void ClientContext::AddDefinition(const Definition& instruction)
    {
        DISCARD_RESULT _localDefinitions.emplace(instruction.Name(), instruction);
    }

    void ClientContext::AddDefinition(Definition&& instruction)
    {
        auto name = instruction.Name();
        DISCARD_RESULT _localDefinitions.emplace(name, instruction);
    }    

    void ClientContext::DeleteDefinition(const std::string& name)
    {
        _localDefinitions.erase(name);
    }

    bool ClientContext::ExecDefinition(const std::string& defName)
    {
        if (_localDefinitions.count(defName) == 0)
        {
            return false;
        }
        Definition def = _localDefinitions.at(defName);
        def.ExecuteOnContext(*this);
        return true;
    }

    bool ClientContext::ExistsDefinition(const std::string& defName)
    {
        return _localDefinitions.count(defName) > 0;
    }

    const std::string& ClientContext::GetCurrentFramePath()
    {
        static const std::string separator = std::string(1, FRAMEPATH_SEPARATOR);

        if (_cachedFramePathNeedsRebuild)
        {
            _cachedFramePath.clear();
            _cachedFramePath = _frameStack[0].get().Name();
            for (size_t i = 1; i < _frameStack.size(); i++)
            {
                _cachedFramePath.append(separator);
                _cachedFramePath.append(_frameStack[i].get().Name());
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

    std::vector<Line> ClientContext::GetFlattenedFullSnapshot() const
    {
        return _mainFrame.GetFlattenedModulatedLines(DEFAULT_TRANSFORM);
    }

    std::vector<Line> ClientContext::GetFlattenedPartialSnapshot()
    {
        std::vector<Line> result;
        for (auto& fpath : _modifiedFramePaths)
        {
            const auto pair = FramePathToFrameWithTransform(fpath);
            const Transform2 parentTform = pair.first;
            const Frame& frame = pair.second;

            std::vector<Line> lines = frame.GetFlattenedModulatedLines(parentTform);
            std::move(lines.begin(), lines.end(), std::back_inserter(result));
        }
        _modifiedFramePaths.clear();
        return result;
    }

    std::unordered_map<std::string, std::vector<Line>> ClientContext::GetRelativePartialSnapshot()
    {
        std::unordered_map<std::string, std::vector<Line>> result;
        for (auto& fpath : _modifiedFramePaths)
        {
            const auto pair = FramePathToFrameWithTransform(fpath);
            const Transform2 parentTform = pair.first;
            const Frame& frame = pair.second;

            auto entry = std::make_pair(fpath, frame.GetFlattenedModulatedLines(parentTform));
            result.insert(std::move(entry));
        }
        _modifiedFramePaths.clear();
        return result;
    }
}
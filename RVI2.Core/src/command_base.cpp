#include "command_base.h"

namespace rvi
{
    void CommandBase::BuildChecksum()
    {
        U8 result = Header;
        for (U8 byte : Data)
        {
            result += byte;
        }
        Checksum = result;
    }

    void CommandBase::AppendData(const std::vector<U8>& data)
    {
        std::copy(data.begin(), data.end(), std::back_inserter(this->Data));
    }

    void CommandBase::AppendData(std::vector<U8>&& data)
    {
        std::move(data.begin(), data.end(), std::back_inserter(this->Data));
    }

    std::vector<U8> CommandBase::GetSerialized()
    {
        BuildData();
        BuildChecksum();

        std::vector<U8> result;
        result.reserve(Data.size() + 2);
        result.push_back(Header);
        std::copy(Data.begin(), Data.end(), std::back_inserter(result));
        result.push_back(Checksum);

        return result;
    }
}
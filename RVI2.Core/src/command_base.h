#pragma once

#include "rvi_base.h"

namespace rvi
{
    class CommandBase
    {
    public:
        U8 Header = 0;
        std::vector<U8> Data;
        U8 Checksum = 0;

        std::vector<U8> GetSerialized();

    private:
        void BuildChecksum();

    protected:
        void AppendData(const std::vector<U8>& data);
        void AppendData(std::vector<U8>&& data);

        virtual void BuildData() = 0;
    };
}
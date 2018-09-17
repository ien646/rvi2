#include "rvi_base.h"

namespace rvi
{
    U64 Random::GetUnsigned64()
    {
        return _distributionU64(_mTwisterEngine);
    }

    U32 Random::GetUnsigned32()
    {
        return _distributionU32(_mTwisterEngine);
    }

    U16 Random::GetUnsigned16()
    {
        return _distributionU16(_mTwisterEngine);
    }

    I64 Random::GetSigned64()
    {
        return _distributionI64(_mTwisterEngine);
    }

    I32 Random::GetSigned32()
    {
        return _distributionI32(_mTwisterEngine);
    }

    I16 Random::GetSigned16()
    {
        return _distributionI16(_mTwisterEngine);
    }


}
#pragma once

#include "rvi_base.h"

namespace rvi
{
	class RemoteCmdBase
	{
	public:
		U8 Header;
		std::vector<U8> Data;
		U8 Checksum;

		void BuildChecksum();
	};
}
#include "remote_cmd_base.h"

namespace rvi
{
	void RemoteCmdBase::BuildChecksum()
	{
		U8 result = Header;
		for (U8 byte : Data)
		{
			result += byte;
		}
		Checksum = result;
	}
}
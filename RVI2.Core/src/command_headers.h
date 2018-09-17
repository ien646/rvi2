#pragma once

#include "rvi_base.h"

namespace rvi
{
	enum class RVI_COMMAND_HEADER : U8
	{
		NOP = 0,
		REQUEST_ACK = 1,
		RESPONSE_ACK = 2,
		DRAW_LINE = 3,
		SELECT_FRAME = 4,
		DELETE_FRAME = 5,
		CLEAR_FRAME = 6
	};
}
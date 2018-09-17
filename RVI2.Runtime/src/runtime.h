#pragma once

#include <unordered_map>

#include "client_context.h"

namespace rvi
{
	class Runtime
	{
	private:
		std::unordered_map<U64, ClientContext> _clientContexts;
	public:
		Runtime() = default;
		Runtime(const Runtime& copy_src) = delete;
		Runtime(Runtime&& mv_src) = delete;

		U64 InitNewContext();
		bool DestroyContext(U64 contextId);
	};
}
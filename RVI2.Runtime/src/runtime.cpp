#include "runtime.h"

namespace rvi
{
	U64 Runtime::InitNewContext()
	{
		ClientContext clientContext = ClientContext::CreateNew();
		U64 contextId = clientContext.ContextId();
		DISCARD _clientContexts.emplace(contextId, clientContext);
		return contextId;
	}

	bool Runtime::DestroyContext(U64 contextId)
	{
		if (_clientContexts.count(contextId) > 0)
		{
			_clientContexts.erase(contextId);
			return true;
		}
		return false;
	}
}
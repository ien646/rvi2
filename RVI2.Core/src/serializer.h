#pragma once

#include <vector>
#include "rvi_base.h"
#include "vector2.h"
#include "vertex.h"

namespace rvi
{
	class Serializer
	{
	public:
		static std::vector<U8> GetBytes(U16 data);
		static std::vector<U8> GetBytes(U32 data);
		static std::vector<U8> GetBytes(U64 data);
		static std::vector<U8> GetBytes(float data);
		static std::vector<U8> GetBytes(Vector2 data);
		static std::vector<U8> GetBytes(ColorRGBA data);
		static std::vector<U8> GetBytes(const std::string& data);		
		static std::vector<U8> GetBytes(Vertex vx);

		static U16 GetU16(const std::vector<U8>& data);
		static U32 GetU32(const std::vector<U8>& data);
		static U64 GetU64(const std::vector<U8>& data);
	};
}
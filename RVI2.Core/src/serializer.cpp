#include "serializer.h"

namespace rvi
{
	std::vector<U8> Serializer::GetBytes(U16 data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));

		U8* dataPtr = (U8*)&data;
		result[0] = dataPtr[0];
		result[1] = dataPtr[1];

		return result;
	}

	std::vector<U8> Serializer::GetBytes(U32 data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));

		U8* dataPtr = (U8*)&data;
		result[0] = dataPtr[0];
		result[1] = dataPtr[1];
		result[2] = dataPtr[2];
		result[3] = dataPtr[3];

		return result;
	}

	std::vector<U8> Serializer::GetBytes(U64 data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));

		U8* dataPtr = (U8*)&data;
		result[0] = dataPtr[0];
		result[1] = dataPtr[1];
		result[2] = dataPtr[2];
		result[3] = dataPtr[3];
		result[4] = dataPtr[4];
		result[5] = dataPtr[5];
		result[6] = dataPtr[6];
		result[7] = dataPtr[7];

		return result;
	}

	std::vector<U8> Serializer::GetBytes(float data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));

		U8* dataPtr = (U8*)&data;
		result[0] = dataPtr[0];
		result[1] = dataPtr[1];
		result[2] = dataPtr[2];
		result[3] = dataPtr[3];

		return result;
	}

	std::vector<U8> Serializer::GetBytes(const std::string& data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(U16) + data.size());

		// Size data
		std::vector<U8> sizeData = Serializer::GetBytes((U16)data.size());
		std::move(sizeData.begin(), sizeData.end(), std::back_inserter(result));

		// String data
		std::copy(data.begin(), data.end(), std::back_inserter(result));

		return result;
	}

	std::vector<U8> Serializer::GetBytes(Vector2 data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));

		std::vector<U8> dataX = Serializer::GetBytes(data.X);
		std::vector<U8> dataY = Serializer::GetBytes(data.X);

		std::move(dataX.begin(), dataX.end(), std::back_inserter(result));
		std::move(dataY.begin(), dataY.end(), std::back_inserter(result));

		return result;
	}

	std::vector<U8> Serializer::GetBytes(ColorRGBA data)
	{
		std::vector<U8> result;
		result.reserve(sizeof(data));
		result[0] = data.R;
		result[1] = data.G;
		result[2] = data.B;
		result[3] = data.A;

		return result;
	}

	std::vector<U8> Serializer::GetBytes(Vertex vx)
	{
		std::vector<U8> result;
		result.reserve(sizeof(vx));

		std::vector<U8> positionData = Serializer::GetBytes(vx.Position);
		std::vector<U8> colorData = Serializer::GetBytes(vx.VertexColor);

		std::move(positionData.begin(), positionData.end(), std::back_inserter(result));
		std::move(colorData.begin(), colorData.end(), std::back_inserter(result));

		return result;
	}

	U16 Serializer::GetU16(const std::vector<U8>& data)
	{
		U16 result;

		U8* resultPtr = (U8*)&result;
		resultPtr[0] = data[0];
		resultPtr[1] = data[1];

		return result;
	}

	U32 Serializer::GetU32(const std::vector<U8>& data)
	{
		U32 result;

		U8* resultPtr = (U8*)&result;
		resultPtr[0] = data[0];
		resultPtr[1] = data[1];
		resultPtr[2] = data[2];
		resultPtr[3] = data[3];

		return result;
	}

	U64 Serializer::GetU64(const std::vector<U8>& data)
	{
		U64 result;

		U8* resultPtr = (U8*)&result;
		resultPtr[0] = data[0];
		resultPtr[1] = data[1];
		resultPtr[2] = data[2];
		resultPtr[3] = data[3];
		resultPtr[4] = data[4];
		resultPtr[5] = data[5];
		resultPtr[6] = data[6];
		resultPtr[7] = data[7];

		return result;
	}

}
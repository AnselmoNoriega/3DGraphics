#include "PrimitivesManager.h"
#include "Rasterizer.h"

PrimitivesManager::PrimitivesManager()
{

}

PrimitivesManager::~PrimitivesManager()
{
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

bool PrimitivesManager::BeginDraw(Topology topology)
{
	mBegingDraw = true;
	mTopology = topology;
	mVertexBuffer.clear();
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& vertex)
{
	mVertexBuffer.push_back(vertex);
}

bool PrimitivesManager::EndDraw()
{
	if (!mBegingDraw)
	{
		return false;
	}

	switch (mTopology)
	{
	case Topology::Line:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); i += 2)
		{
			Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Triangle:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); i += 3)
		{
			Rasterizer::Get()->DrawTriangle(mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
		}
	}
	break;
	default:
		return false;
	}

	mBegingDraw = false;
	return true;
}

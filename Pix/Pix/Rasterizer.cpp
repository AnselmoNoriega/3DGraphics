#include "Rasterizer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v.pos.x, v.pos.y, v.color);
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	float dx = v1.pos.x - v0.pos.x;
	float dy = v1.pos.y - v0.pos.y;

	Vertex startV, endV;

	if (std::abs(dy) < std::abs(dx))
	{
		if (v0.pos.x < v1.pos.x)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float x = startV.pos.x; x <= endV.pos.x; ++x)
		{
			float t = (x - startV.pos.x) / (endV.pos.x - startV.pos.x);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}
	else
	{
		if (v0.pos.y < v1.pos.y)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float y = startV.pos.y; y <= endV.pos.y; ++y)
		{
			float t = (y - startV.pos.y) / (endV.pos.y - startV.pos.y);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	switch (mFillMode)
	{
	case FillMode::WireFrame:
	{
		DrawLine(v0, v1);
		DrawLine(v1, v2);
		DrawLine(v2, v0);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { v0, v1, v2 };
		std::sort(sortedVertices.begin(), sortedVertices.end(),
			[](const Vertex& lhs, const Vertex& rhs)
			{
				return lhs.pos.y < rhs.pos.y;
			});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
}

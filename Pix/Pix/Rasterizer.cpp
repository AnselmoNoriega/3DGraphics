#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"

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

void Rasterizer::SetShadeMode(ShadeMode mode)
{
	mShadeMode = mode;
}

ShadeMode Rasterizer::GetShadeMode()
{
	return mShadeMode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	if (DepthBuffer::Get()->CheckDepthBuffer(v.pos.x + 0.5f, v.pos.y + 0.5f, v.pos.z))
	{
		mColor = v.color;
		if (mShadeMode == ShadeMode::Phoh)
		{
			mColor *= LightManager::Get()->ComputeLightColor(v.worldPos, v.worldNormal);
		}
		DrawPoint(v.pos.x + 0.5f, v.pos.y + 0.5f);
	}
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	if (MathHelper::CheckEqual(v0.pos, v1.pos))
	{
		DrawPoint(v0);
	}
	else
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
			for (float x = std::floor(startV.pos.x); x <= std::floor(endV.pos.x + 0.5f); ++x)
			{
				float t = (x - startV.pos.x) / (endV.pos.x - startV.pos.x);
				Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phoh);
				DrawPoint(v);
			}
		}
		else
		{
			//startV = (v0 * (v0.pos.y < v1.pos.y) + v1 * (v0.pos.y >= v1.pos.y));
			//endV = (v1 * (v0.pos.y < v1.pos.y) + v0 * (v0.pos.y >= v1.pos.y));

			startV = (v0.pos.y < v1.pos.y) ? v0 : v1;
			endV = (v0.pos.y < v1.pos.y) ? v1 : v0;

			for (float y = startV.pos.y; y <= endV.pos.y; ++y)
			{
				float t = (y - startV.pos.y) / (endV.pos.y - startV.pos.y);
				Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phoh);
				DrawPoint(v);
			}
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v0, Vertex v1, Vertex v2)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v1.color = v0.color;
		v2.color = v0.color;
	}

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
		DrawFilledTriangle(v0, v1, v2);
	}
	break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	std::vector<Vertex> sortedVertices = { v0, v1, v2 };
	std::sort(sortedVertices.begin(), sortedVertices.end(),
		[](const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.pos.y < rhs.pos.y;
		});

	if (MathHelper::CheckEqual(sortedVertices[0].pos.y, sortedVertices[1].pos.y))
	{
		DrawTopFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else if (MathHelper::CheckEqual(sortedVertices[1].pos.y, sortedVertices[2].pos.y))
	{
		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else
	{
		float t = (sortedVertices[1].pos.y - sortedVertices[0].pos.y) / (sortedVertices[2].pos.y - sortedVertices[0].pos.y);
		Vertex splitVertex = LerpVertex(sortedVertices[0], sortedVertices[2], t, mShadeMode == ShadeMode::Phoh);

		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], splitVertex);
		DrawTopFilledTriangle(sortedVertices[1], splitVertex, sortedVertices[2]);
	}
}

void Rasterizer::DrawTopFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex topLeft, topRight;
	if (v0.pos.x < v1.pos.x)
	{
		topLeft = v0;
		topRight = v1;
	}
	else
	{
		topLeft = v1;
		topRight = v0;
	}

	float dy = v2.pos.y - v0.pos.y;
	for (float y = v0.pos.y; y <= v2.pos.y; ++y)
	{
		float t = (y - v0.pos.y) / dy;
		Vertex leftVertex = LerpVertex(topLeft, v2, t, mShadeMode == ShadeMode::Phoh);
		Vertex rightVertex = LerpVertex(topRight, v2, t, mShadeMode == ShadeMode::Phoh);
		DrawLine(leftVertex, rightVertex);
	}
}

void Rasterizer::DrawBottomFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex bottomLeft, bottomRight;
	if (v0.pos.x < v1.pos.x)
	{
		bottomLeft = v1;
		bottomRight = v2;
	}
	else
	{
		bottomLeft = v2;
		bottomRight = v1;
	}

	float dy = v2.pos.y - v0.pos.y;
	for (float y = v0.pos.y; y <= v2.pos.y; ++y)
	{
		float t = (y - v0.pos.y) / dy;
		Vertex leftVertex = LerpVertex(v0, bottomLeft, t, mShadeMode == ShadeMode::Phoh);
		Vertex rightVertex = LerpVertex(v0, bottomRight, t, mShadeMode == ShadeMode::Phoh);
		DrawLine(leftVertex, rightVertex);
	}
}

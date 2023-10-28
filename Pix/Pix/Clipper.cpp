#include "Clipper.h"
#include "Viewport.h"

const int BIT_INSIDE = 0;
const int BIT_LEFT   = 1 << 1;
const int BIT_RIGHT  = 1 << 2;
const int BIT_BOTTOM = 1 << 3;
const int BIT_TOP    = 1 << 4;

enum class ClipEdge : int
{
	LEFT,
	BOTTTOM,
	RIGHT,
	TOP,
	COUNT
};

bool IsInFront(ClipEdge edge, const Vec3& pos)
{
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	switch (edge)
	{
	case ClipEdge::LEFT: return pos.x > minX;
	case ClipEdge::BOTTTOM: return pos.y < maxY;
	case ClipEdge::RIGHT: return pos.x < maxX;
	case ClipEdge::TOP: return pos.y > minY;
	default: break;
	}

	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v0, const Vertex& v1)
{
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	float t = 0.0f;
	switch (edge)
	{
	case ClipEdge::LEFT:    t = (minX - v0.pos.x) / (v1.pos.x - v0.pos.x); break;
	case ClipEdge::BOTTTOM: t = (maxY - v0.pos.y) / (v1.pos.y - v0.pos.y); break;
	case ClipEdge::RIGHT:   t = (maxX - v0.pos.x) / (v1.pos.x - v0.pos.x); break;
	case ClipEdge::TOP:     t = (minY - v0.pos.y) / (v1.pos.y - v0.pos.y); break;
	default: break;
	}

	return LerpVertex(v0, v1, t);
}

int GetOutputCode(float x, float y)
{
	int code = BIT_INSIDE;
	if (x < Viewport::Get()->GetMinX())
	{
		code |= BIT_LEFT;
	}
	else if (x > Viewport::Get()->GetMaxX())
	{
		code |= BIT_RIGHT;
	}
	if (y < Viewport::Get()->GetMinY())
	{
		code |= BIT_TOP;
	}
	if (y > Viewport::Get()->GetMaxY())
	{
		code |= BIT_BOTTOM;
	}

	return code;
}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

Clipper::Clipper()
{
}
Clipper::~Clipper()
{
}

void Clipper::OnNewFrame()
{
	mIsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!mIsClipping)
	{
		return true;
	}

	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	return v.pos.x >= minX && v.pos.x <= maxX && v.pos.y >= minY && v.pos.y <= maxY;
}

bool Clipper::ClipLine(Vertex& v0, Vertex& v1)
{
	if (!mIsClipping)
	{
		return true;
	}

	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();

	int codeV0 = GetOutputCode(v0.pos.x, v0.pos.y);
	int codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);

	bool accept = false;
	while (!accept)
	{
		if ((codeV0 | codeV1) == BIT_INSIDE)
		{
			accept = true;
		}
		else if ((codeV0 & codeV1) > 0)
		{
			break;
		}
		else
		{
			float t = 0.0f;
			int outCodeActive = (codeV1 > codeV0) ? codeV1 : codeV0;
			if (outCodeActive & BIT_TOP) //(outCodeActive & BIT_TOP) > 0
			{
				t = (minY - v0.pos.y) / (v1.pos.y - v0.pos.y);
			}
			else if (outCodeActive & BIT_BOTTOM)
			{
				t = (maxY - v0.pos.y) / (v1.pos.y - v0.pos.y);
			}
			else if (outCodeActive & BIT_RIGHT)
			{
				t = (maxX - v0.pos.x) / (v1.pos.x - v0.pos.x);
			}
			else if (outCodeActive & BIT_LEFT)
			{
				t = (minX - v0.pos.x) / (v1.pos.x - v0.pos.x);
			}

			if (outCodeActive == codeV0)
			{
				v0 = LerpVertex(v0, v1, t);
				codeV0 = GetOutputCode(v0.pos.x, v0.pos.y);
			}
			else
			{
				v1 = LerpVertex(v0, v1, t);
				codeV1 = GetOutputCode(v1.pos.x, v1.pos.y);
			}
		}
	}

	return accept;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (!mIsClipping)
	{
		return true;
	}

	std::vector<Vertex> newVertices;

	for (int i = 0; i < (int)ClipEdge::COUNT; ++i)
	{
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (size_t j = 0; j < vertices.size(); ++j)
		{
			size_t np1 = (j + 1) % vertices.size();
			const Vertex& v0 = vertices[j];
			const Vertex& v1 = vertices[np1];
			bool isInfrontV0 = IsInFront(edge, v0.pos);
			bool isInfrontV1 = IsInFront(edge, v1.pos);


			if (isInfrontV0 && isInfrontV1)
			{
				newVertices.push_back(v1);
			}
			else if (isInfrontV0 && !isInfrontV1)
			{
				newVertices.push_back(ComputeIntersection(edge, v0, v1));
			}
			else if (!isInfrontV0 && !isInfrontV1)
			{

			}
			else if (!isInfrontV0 && isInfrontV1)
			{
				newVertices.push_back(ComputeIntersection(edge, v0, v1));
				newVertices.push_back(v1);
			}
		}

		vertices = newVertices;
	}

	return vertices.size() > 0;
}

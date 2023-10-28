#include "Clipper.h"
#include "Viewport.h"

const int BIT_INSIDE = 0;
const int BIT_LEFT   = 1 << 1;
const int BIT_RIGHT  = 1 << 2;
const int BIT_BOTTOM = 1 << 3;
const int BIT_TOP    = 1 << 4;

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

	return false;
}

#include "Graphics.h"
#include "Clipper.h"
#include "Viewport.h"
#include "MatrixStack.h"
#include "PrimitivesManager.h"
#include "LightManager.h"
#include "MaterialManager.h"
#include "DepthBuffer.h"
#include "Camera.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	PrimitivesManager::Get()->OnNewFrame();
	DepthBuffer::Get()->OnNewFrame();
	LightManager::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
}
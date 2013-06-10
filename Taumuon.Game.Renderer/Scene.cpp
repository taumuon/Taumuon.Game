#include "pch.h"
#include "Scene.h"

namespace Taumuon { namespace Game { namespace Renderer {

Scene::Scene(void)
	:
	_sceneInt(ref new SceneInt())
{
}

void Scene::Initialize(_In_ ID3D11Device1* device)
{
	_sceneInt->Initialize(device);
}

void Scene::UpdateForWindowSizeChange(float width, float height)
{
	_sceneInt->UpdateForWindowSizeChange(width, height);
}

void Scene::UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
	_sceneInt->UpdateDevice(device, context, renderTargetView);
}

void Scene::Render()
{
	_sceneInt->Render();
	OnRendering();
}

Cube^ Scene::CreateCube()
{
	return _sceneInt->CreateCube();
}

} } }
#include "pch.h"
#include "SceneInt.h"

namespace Taumuon { namespace Game { namespace Renderer {

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

SceneInt::SceneInt()
	:
	_cubeRenderer(ref new CubeRenderer())
{
}

void SceneInt::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	_cubeRenderer->CreateDeviceResources();

	InitialiseBuffers();
}

void SceneInt::Initialize(_In_ ID3D11Device1* device)
{
	Direct3DBase::Initialize(device);

	_cubeRenderer->Initialize(device);
}

void SceneInt::UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
	Direct3DBase::UpdateDevice(device, context, renderTargetView);

	_cubeRenderer->UpdateDevice(device, context);
}

void SceneInt::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	float aspectRatio = _windowBounds.Width / _windowBounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	if (aspectRatio < 1.0f)
	{
		fovAngleY /= aspectRatio;
	}

	XMStoreFloat4x4(
		&_constantBufferData.projection,
		XMMatrixTranspose(
			XMMatrixPerspectiveFovRH(
				fovAngleY,
				aspectRatio,
				0.01f,
				100.0f
				)
			)
		);
}

void SceneInt::Render()
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
	_d3dContext->ClearRenderTargetView(
		_renderTargetView.Get(),
		midnightBlue
		);

	_d3dContext->ClearDepthStencilView(
		_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	_d3dContext->OMSetRenderTargets(
		1,
		_renderTargetView.GetAddressOf(),
		_depthStencilView.Get()
		);

	for(auto& cube : _cubes)
	{
		cube->Render(_constantBufferData);
	}
}

Cube^ SceneInt::CreateCube()
{
	auto cube = ref new Cube(_cubeRenderer);
	_cubes.push_back(cube);
	return cube;
}

void SceneInt::InitialiseBuffers()
{
    XMVECTOR eye = XMVectorSet(-10.0f, 0.7f, -8.0f, 0.0f);
    XMVECTOR at = XMVectorSet(0.0f, 8.0f, 0.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	auto matrix = XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up));
	XMStoreFloat4x4(&_constantBufferData.view, matrix);
}

} } }
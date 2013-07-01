#include "pch.h"
#include "Scene.h"
#include "Cube.h"
#include "CubeRenderer.h"
#include "Camera.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

Scene::Scene(std::shared_ptr<Camera> camera)
	:
	m_camera(camera),
	m_cubeRenderer(std::make_shared<CubeRenderer>())
{
}

void Scene::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	m_cubeRenderer->CreateDeviceResources(m_d3dDevice.Get(), m_d3dContext.Get());

	InitialiseBuffers();
}

void Scene::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;

	// Note that the m_orientationTransform3D matrix is post-multiplied here
	// in order to correctly orient the scene to match the display orientation.
	// This post-multiplication step is required for any draw calls that are
	// made to the swap chain render target. For draw calls to other targets,
	// this transform should not be applied.
	XMStoreFloat4x4(
		&m_constantBufferData.projection,
		XMMatrixTranspose(
			XMMatrixMultiply(
				XMMatrixPerspectiveFovRH(
					fovAngleY,
					aspectRatio,
					0.01f,
					100.0f
					),
				XMLoadFloat4x4(&m_orientationTransform3D)
				)
			)
		);
}

void Scene::InitialiseBuffers()
{
	m_constantBufferData.view = m_camera->GetViewMatrix();
}

void Scene::Render()
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		midnightBlue
		);

	m_d3dContext->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	for(auto& cube : m_cubes)
	{
		cube->Render(m_constantBufferData);
	}

}

std::shared_ptr<Cube> Scene::CreateCube()
{
	auto cube = std::make_shared<Cube>(m_cubeRenderer);
	m_cubes.push_back(cube);
	return cube;
}

void Scene::RemoveCube(const std::shared_ptr<Cube>& cube)
{
	auto it = std::find(begin(m_cubes), end(m_cubes), cube);
	if (it != end(m_cubes))
	{
		m_cubes.erase(it);
	}
}

// toymaker.info/Games/html/picking.html
DirectX::XMFLOAT3 Scene::GetPickRay(float x, float y)
{
	auto projection = XMLoadFloat4x4(&m_constantBufferData.projection);
	auto view = XMLoadFloat4x4(&m_constantBufferData.view);
	auto world = XMMatrixIdentity();

	auto pointX = (((2.0f * x) / m_windowBounds.Width) - 1.0f) * -1.0f;
	auto pointY = (((2.0f * y) / m_windowBounds.Height) - 1.0f) * 1.0f;

	pointX = pointX / m_constantBufferData.projection._11;
	pointY = pointY / m_constantBufferData.projection._22;

	// NOTE: not using auto to avoid alignment bug
	// connect.microsoft.com/VisualStudio/feedback/details/761026/xmmatrix-not-properly-aligned-when-using-c-11-auto-keyword
	XMMATRIX viewMatrix = XMLoadFloat4x4(&m_constantBufferData.view);
	XMMATRIX inverse = DirectX::XMMatrixInverse(nullptr, viewMatrix);
	XMFLOAT4X4 inverseViewMatrix;
	XMStoreFloat4x4(&inverseViewMatrix, inverse);

	auto direction = XMFLOAT3
	(
		(pointX * inverseViewMatrix._11) + (pointY * inverseViewMatrix._21) + inverseViewMatrix._31,
		(pointX * inverseViewMatrix._12) + (pointY * inverseViewMatrix._22) + inverseViewMatrix._32,
		(pointX * inverseViewMatrix._13) + (pointY * inverseViewMatrix._23) + inverseViewMatrix._33
	);

	auto origin = XMFLOAT3 (inverseViewMatrix._41 , inverseViewMatrix._42, inverseViewMatrix._43);

	XMVECTOR directionVector = XMLoadFloat3(&direction);
	XMVECTOR originVector = XMLoadFloat3(&origin);
	
	XMVECTOR result = XMVectorSubtract(originVector, directionVector);

	XMVECTOR normalizedResultVector = XMVector3Normalize(result);

	XMFLOAT3 normalizedResult;
	XMStoreFloat3(&normalizedResult, normalizedResultVector);
	return normalizedResult;
}
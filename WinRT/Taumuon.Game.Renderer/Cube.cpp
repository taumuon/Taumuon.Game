#include "pch.h"
#include "Cube.h"
#include <DirectXMath.h>

#include "DirectXHelper.h"

//using namespace Microsoft::WRL;
//using namespace Windows::Foundation;
//using namespace Windows::UI::Core;
//using namespace DirectX;

namespace Taumuon { namespace Game { namespace Renderer {

Cube::Cube(CubeRenderer^ cubeRenderer)
	: _cubeRenderer(cubeRenderer)
{
}

Cube::~Cube()
{
}

void Cube::Transform(Taumuon::Game::Common::Transform^ transform)
{
	DirectX::XMVECTOR data;
	auto quaternion = transform->Quaternion;
	DirectX::XMVECTORF32 floatingVector = XMVector32FromQuat(quaternion);
	data = floatingVector;

	auto rotationMatrix = DirectX::XMMatrixRotationQuaternion(data);
	auto translationMatrix = XMMatrixFromTrans(transform->Location);
	_modelMatrix = DirectX::XMMatrixTranspose(rotationMatrix * translationMatrix);
}

void Cube::Render(ModelViewProjectionConstantBuffer& constantBufferData)
{
	XMStoreFloat4x4(&constantBufferData.model, _modelMatrix);

	_cubeRenderer->Render(constantBufferData);
}

} } }
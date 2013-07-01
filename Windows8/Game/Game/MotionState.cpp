#include "pch.h"
#include "MotionState.h"
#include "ITransformable.h"

using namespace DirectX;

MotionState::MotionState(const btTransform &initialTransform, const std::shared_ptr<ITransformable>& transformable)
	:
	m_initialTransform(initialTransform),
	m_transformable(transformable)
{
}

MotionState::~MotionState(void)
{
}

void MotionState::getWorldTransform(btTransform &worldTransform) const
{
	worldTransform = m_initialTransform;
}

void MotionState::setWorldTransform(const btTransform &worldTransform)
{
	auto worldRotation = worldTransform.getRotation();
	XMVECTORF32 rotation = { worldRotation.getX(), worldRotation.getY(), worldRotation.getZ(), worldRotation.getW() };
	XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(rotation);
	
	auto worldTranslation = worldTransform.getOrigin();
	XMMATRIX translationMatrix = DirectX::XMMatrixTranslation(worldTranslation.getX(), worldTranslation.getY(), worldTranslation.getZ());

	XMMATRIX modelMatrix = DirectX::XMMatrixTranspose(rotationMatrix * translationMatrix);
	
	XMFLOAT4X4 modelMatrixFloat4x4;
	XMStoreFloat4x4(&modelMatrixFloat4x4, modelMatrix);
	m_transformable->Transform(modelMatrixFloat4x4);
}

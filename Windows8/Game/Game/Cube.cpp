#include "pch.h"
#include "Cube.h"
#include "CubeRenderer.h"
#include "Buffers.h"

Cube::Cube(const std::shared_ptr<CubeRenderer>& cubeRenderer)
	:
	m_cubeRenderer(cubeRenderer)
{
}

Cube::~Cube(void)
{
}

void Cube::Render(ModelViewProjectionConstantBuffer& constantBufferData)
{
	constantBufferData.model = m_modelMatrix;

	m_cubeRenderer->Render(constantBufferData);
}

void Cube::Transform(const DirectX::XMFLOAT4X4& transform)
{
	m_modelMatrix = transform;
}
#pragma once

#include "ITransformable.h"

class CubeRenderer;
struct ModelViewProjectionConstantBuffer;

// TODO: rename this to GameObject - something like that
// Add an interface to CubeRenderer something like IRenderable ?
// refactor out once have more object types to draw.
class Cube : public ITransformable
{
public:
	Cube(const std::shared_ptr<CubeRenderer>& cubeRenderer);
	~Cube(void);
	void Render(ModelViewProjectionConstantBuffer& constantBufferData);
	virtual void Transform(const DirectX::XMFLOAT4X4& transform);
private:
	Cube(const Cube&);
	Cube& operator=(const Cube&);

	std::shared_ptr<CubeRenderer> m_cubeRenderer;
	DirectX::XMFLOAT4X4 m_modelMatrix;
};


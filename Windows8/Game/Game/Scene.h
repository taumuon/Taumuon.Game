#pragma once

#include "Direct3DBase.h"
#include "Buffers.h"

class CubeRenderer;
class Cube;
class Camera;

// This class renders a simple spinning cube.
ref class Scene sealed : public Direct3DBase
{
public:
	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
internal:
	Scene(std::shared_ptr<Camera> camera);

	std::shared_ptr<Cube> CreateCube();
	void RemoveCube(const std::shared_ptr<Cube>& cube);
	DirectX::XMFLOAT3 GetPickRay(float x, float y);
	const Camera& GetCamera() { return *m_camera.get(); }
private:
	void InitialiseBuffers();

	ModelViewProjectionConstantBuffer m_constantBufferData;

	std::shared_ptr<CubeRenderer> m_cubeRenderer;
	std::shared_ptr<Camera> m_camera;
	std::vector<std::shared_ptr<Cube>> m_cubes;
};

#pragma once

#include "Direct3DBase.h"
#include <memory>

#include "Cube.h"
#include "CubeRenderer.h"

namespace Taumuon { namespace Game { namespace Renderer {

	ref class SceneInt sealed : public Direct3DBase
	{
	public:
		SceneInt();

		// Direct3DBase methods.
		virtual void CreateDeviceResources() override;
		virtual void CreateWindowSizeDependentResources() override;
		virtual void Render() override;
	internal:
		Cube^ CreateCube();
		void InitialiseBuffers();
		virtual void Initialize(_In_ ID3D11Device1* device) override;
		virtual void UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView) override;
	private:

		uint32 _indexCount;
		ModelViewProjectionConstantBuffer _constantBufferData;

		std::vector<Cube^> _cubes;
		CubeRenderer^ _cubeRenderer;
	};

} } }
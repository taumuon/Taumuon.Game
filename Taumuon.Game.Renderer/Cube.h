#pragma once

#include <wrl.h>
#include <memory>

#include <DirectXMath.h>
#include "CubeRenderer.h"

using namespace Taumuon::Game::Common;

namespace Taumuon { namespace Game { namespace Renderer {

	public ref class Cube sealed : ITransformable
	{
	private:
		~Cube();
	public:
		virtual void Transform(Transform^ transform);
	internal:
		Cube(CubeRenderer^ renderer);
		void Render(ModelViewProjectionConstantBuffer& constantBufferData);
	private:
		DirectX::XMMATRIX _modelMatrix;
		CubeRenderer^ _cubeRenderer;
	};

} } }

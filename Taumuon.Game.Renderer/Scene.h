#pragma 

#include "SceneInt.h"

namespace Taumuon { namespace Game { namespace Renderer {

public delegate void OnRenderingHandler();

public ref class Scene sealed
{
public:
	Scene(void);
	Cube^ CreateCube();
	event OnRenderingHandler^ OnRendering;
internal:
	void Initialize(_In_ ID3D11Device1* device);
	void UpdateForWindowSizeChange(float width, float height);
	void UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView);
	void Render();
private:
	SceneInt^ _sceneInt;
};

} } }
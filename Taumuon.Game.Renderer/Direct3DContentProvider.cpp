#include "pch.h"
#include "Direct3DContentProvider.h"

using namespace Taumuon::Game::Renderer;

Direct3DContentProvider::Direct3DContentProvider(Direct3DBackground^ controller) :
	_controller(controller)
{
	_controller->RequestAdditionalFrame += ref new RequestAdditionalFrameHandler([=] ()
		{
			if (_host)
			{
				_host->RequestAdditionalFrame();
			}
		});
}

// IDrawingSurfaceContentProviderNative interface
HRESULT Direct3DContentProvider::Connect(_In_ IDrawingSurfaceRuntimeHostNative* host, _In_ ID3D11Device1* device)
{
	_host = host;

	return _controller->Connect(host, device);
}

void Direct3DContentProvider::Disconnect()
{
	_controller->Disconnect();
	_host = nullptr;
}

HRESULT Direct3DContentProvider::PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Inout_ DrawingSurfaceSizeF* desiredRenderTargetSize)
{
	return _controller->PrepareResources(presentTargetTime, desiredRenderTargetSize);
}

HRESULT Direct3DContentProvider::Draw(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
	return _controller->Draw(device, context, renderTargetView);
}
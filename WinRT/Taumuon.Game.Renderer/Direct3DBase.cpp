#include "pch.h"
#include "Direct3DBase.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;

// Constructor.
Direct3DBase::Direct3DBase()
{
}

// Initialize the Direct3D resources required to run.
void Direct3DBase::Initialize(_In_ ID3D11Device1* device)
{
	_d3dDevice = device;
	CreateDeviceResources();
}

// These are the resources that depend on the device.
void Direct3DBase::CreateDeviceResources()
{
}

void Direct3DBase::UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView)
{
	_d3dContext = context;
	_renderTargetView = renderTargetView;

	if (_d3dDevice.Get() != device)
	{
		_d3dDevice = device;
		CreateDeviceResources();

		// Force call to CreateWindowSizeDependentResources.
		_renderTargetSize.Width  = -1;
		_renderTargetSize.Height = -1;
	}

	ComPtr<ID3D11Resource> renderTargetViewResource;
	_renderTargetView->GetResource(&renderTargetViewResource);

	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		renderTargetViewResource.As(&backBuffer)
		);

	// Cache the rendertarget dimensions in our helper class for convenient use.
    D3D11_TEXTURE2D_DESC backBufferDesc;
    backBuffer->GetDesc(&backBufferDesc);

    if (_renderTargetSize.Width  != static_cast<float>(backBufferDesc.Width) ||
        _renderTargetSize.Height != static_cast<float>(backBufferDesc.Height))
    {
        _renderTargetSize.Width  = static_cast<float>(backBufferDesc.Width);
        _renderTargetSize.Height = static_cast<float>(backBufferDesc.Height);
        CreateWindowSizeDependentResources();
    }

	// Set the rendering viewport to target the entire window.
	CD3D11_VIEWPORT viewport(
		0.0f,
		0.0f,
		_renderTargetSize.Width,
		_renderTargetSize.Height
		);

	_d3dContext->RSSetViewports(1, &viewport);
}

// Allocate all memory resources that depend on the window size.
void Direct3DBase::CreateWindowSizeDependentResources()
{
	// Create a depth stencil view.
	CD3D11_TEXTURE2D_DESC depthStencilDesc(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		static_cast<UINT>(_renderTargetSize.Width),
		static_cast<UINT>(_renderTargetSize.Height),
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
		);

	ComPtr<ID3D11Texture2D> depthStencil;
	DX::ThrowIfFailed(
		_d3dDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			)
		);

	CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
	DX::ThrowIfFailed(
		_d3dDevice->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&_depthStencilView
			)
		);
}

void Direct3DBase::UpdateForWindowSizeChange(float width, float height)
{
	_windowBounds.Width  = width;
	_windowBounds.Height = height;
}
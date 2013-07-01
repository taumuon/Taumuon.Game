#pragma once

#include "DirectXHelper.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class Direct3DBase abstract
{
internal:
	Direct3DBase();

	virtual void Initialize(_In_ ID3D11Device1* device);
	virtual void CreateDeviceResources();
	virtual void UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context, _In_ ID3D11RenderTargetView* renderTargetView);
	virtual void CreateWindowSizeDependentResources();
	virtual void UpdateForWindowSizeChange(float width, float height);
	virtual void Render() = 0;

protected private:
	// Direct3D Objects.
	Microsoft::WRL::ComPtr<ID3D11Device1> _d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _d3dContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;

	// Cached renderer properties.
	Windows::Foundation::Size _renderTargetSize;
	Windows::Foundation::Rect _windowBounds;
};
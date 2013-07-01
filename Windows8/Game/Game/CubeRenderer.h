#pragma once
#include "Buffers.h"

class CubeRenderer
{
public:
	void CreateDeviceResources(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context);
	void Render(const ModelViewProjectionConstantBuffer& constantBufferData);
	CubeRenderer(void);
	virtual ~CubeRenderer(void);
private:
	CubeRenderer(const CubeRenderer&);
	CubeRenderer& operator=(const CubeRenderer&);

	bool m_loadingComplete;
	uint32 m_indexCount;

	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
};


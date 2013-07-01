#include "pch.h"
#include "CubeRenderer.h"
#include "DirectXHelper.h"

namespace Taumuon { namespace Game { namespace Renderer {


CubeRenderer::CubeRenderer()
	:
		_loadingComplete(false),
		_indexCount(0)
{
}

// Initialize the Direct3D resources required to run.
void CubeRenderer::Initialize(_In_ ID3D11Device1* device)
{
	_d3dDevice = device;
	CreateDeviceResources();
}


CubeRenderer::~CubeRenderer(void)
{
}

void CubeRenderer::CreateDeviceResources()
{
	_loadingComplete = false;

	auto loadVSTask = DX::ReadDataAsync("SimpleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync("SimplePixelShader.cso");

	auto createVSTask = loadVSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			_d3dDevice->CreateVertexShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&_vertexShader
				)
			);

		const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DX::ThrowIfFailed(
			_d3dDevice->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				fileData->Data,
				fileData->Length,
				&_inputLayout
				)
			);
	});

	auto createPSTask = loadPSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			_d3dDevice->CreatePixelShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&_pixelShader
				)
			);

		CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			_d3dDevice->CreateBuffer(
				&constantBufferDesc,
				nullptr,
				&_constantBuffer
				)
			);
	});

	auto createCubeTask = (createPSTask && createVSTask).then([this] () {
		VertexPositionColor cubeVertices[] = 
		{
			{DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f)},
			{DirectX::XMFLOAT3(-0.5f, -0.5f,  0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
			{DirectX::XMFLOAT3(-0.5f,  0.5f, -0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
			{DirectX::XMFLOAT3(-0.5f,  0.5f,  0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 1.0f)},
			{DirectX::XMFLOAT3( 0.5f, -0.5f, -0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
			{DirectX::XMFLOAT3( 0.5f, -0.5f,  0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f)},
			{DirectX::XMFLOAT3( 0.5f,  0.5f, -0.5f), DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f)},
			{DirectX::XMFLOAT3( 0.5f,  0.5f,  0.5f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			_d3dDevice->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&_vertexBuffer
				)
			);

		unsigned short cubeIndices[] = 
		{
			0,2,1, // -x
			1,2,3,

			4,5,6, // +x
			5,7,6,

			0,1,5, // -y
			0,5,4,

			2,6,7, // +y
			2,7,3,

			0,4,6, // -z
			0,6,2,

			1,3,7, // +z
			1,7,5,
		};

		_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);
		DX::ThrowIfFailed(
			_d3dDevice->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&_indexBuffer
				)
			);
	});

	createCubeTask.then([this] () {
		_loadingComplete = true;
	});
}

void CubeRenderer::UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context)
{
	_d3dContext = context;

	if (_d3dDevice.Get() != device)
	{
		_d3dDevice = device;
		CreateDeviceResources();
	}
}


void CubeRenderer::Render(ModelViewProjectionConstantBuffer& constantBufferData)
{
	// Only draw the cube once it is loaded (loading is asynchronous).
	if (!_loadingComplete)
	{
		return;
	}

	_d3dContext->UpdateSubresource(
		_constantBuffer.Get(),
		0,
		NULL,
		&constantBufferData,
		0,
		0
		);

	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	_d3dContext->IASetVertexBuffers(
		0,
		1,
		_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	_d3dContext->IASetIndexBuffer(
		_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0
		);

	_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_d3dContext->IASetInputLayout(_inputLayout.Get());

	_d3dContext->VSSetShader(
		_vertexShader.Get(),
		nullptr,
		0
		);

	_d3dContext->VSSetConstantBuffers(
		0,
		1,
		_constantBuffer.GetAddressOf()
		);

	_d3dContext->PSSetShader(
		_pixelShader.Get(),
		nullptr,
		0
		);

	_d3dContext->DrawIndexed(
		_indexCount,
		0,
		0
		);
}

} } }
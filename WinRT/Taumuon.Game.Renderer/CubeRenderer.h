#pragma once

namespace Taumuon { namespace Game { namespace Renderer {

	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};

	ref class CubeRenderer
	{
	public:
		void CreateDeviceResources();
		virtual ~CubeRenderer(void);
	internal:
		CubeRenderer();
		void Initialize(_In_ ID3D11Device1* device);
		void Render(ModelViewProjectionConstantBuffer& constantBufferData);
	    void UpdateDevice(_In_ ID3D11Device1* device, _In_ ID3D11DeviceContext1* context);
	private:
		bool _loadingComplete;
		uint32 _indexCount;

		Microsoft::WRL::ComPtr<ID3D11Device1> _d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1> _d3dContext;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer> _constantBuffer;
	};

} } }

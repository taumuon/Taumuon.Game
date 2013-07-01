#pragma once

class Camera
{
public:
	Camera(DirectX::XMFLOAT3 eye,
		   DirectX::XMFLOAT3 at,
		   DirectX::XMFLOAT3 up);
	const DirectX::XMFLOAT3 GetEye() { return m_eye; }
	const DirectX::XMFLOAT3 GetAt() { return m_at; }
	const DirectX::XMFLOAT3 GetUp() { return m_up; }
	const DirectX::XMFLOAT4X4 GetViewMatrix() { return m_viewMatrix; }
	virtual ~Camera(void);
private:
	DirectX::XMFLOAT3 m_eye;
	DirectX::XMFLOAT3 m_at;
	DirectX::XMFLOAT3 m_up;
	DirectX::XMFLOAT4X4 m_viewMatrix;
};


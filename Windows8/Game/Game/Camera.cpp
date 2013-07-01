#include "pch.h"
#include "Camera.h"

using namespace DirectX;

Camera::Camera(XMFLOAT3 eye, XMFLOAT3 at, XMFLOAT3 up)
	:
	m_eye(eye),
	m_at(at),
	m_up(up)
{
	XMMATRIX matrix = XMMatrixTranspose(XMMatrixLookAtRH(XMLoadFloat3(&eye), XMLoadFloat3(&at), XMLoadFloat3(&up)));
	XMStoreFloat4x4(&m_viewMatrix, matrix);
}

Camera::~Camera(void)
{
}

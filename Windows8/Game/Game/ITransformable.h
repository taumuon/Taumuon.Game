#pragma once

// TODO: on all interfaces, could make them struct __declspec(novtable) and remove the d'tor
class ITransformable
{
public:
	virtual ~ITransformable() {}
	virtual void Transform(const DirectX::XMFLOAT4X4& transform) = 0;
};
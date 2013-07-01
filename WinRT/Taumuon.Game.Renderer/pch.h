//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <memory>
#include <vector>
#include <agile.h>

namespace Taumuon {	namespace Game { namespace Renderer {

	inline DirectX::XMVECTORF32 XMVector32FromQuat(Taumuon::Game::Common::Quaternion^ quaternion)
	{
		DirectX::XMVECTORF32 floatingVector = { static_cast<float>(quaternion->X),
									   static_cast<float>(quaternion->Y),
									   static_cast<float>(quaternion->Z), 
									   static_cast<float>(quaternion->W) };
		return floatingVector;
	}

	inline DirectX::XMMATRIX XMMatrixFromTrans(Taumuon::Game::Common::Vector3^ translation)
	{
		auto translationMatrix = DirectX::XMMatrixTranslation(static_cast<float>(translation->X),
													 static_cast<float>(translation->Y), 
													 static_cast<float>(translation->Z));
		return translationMatrix;
	}
} } }
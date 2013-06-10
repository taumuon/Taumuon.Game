//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <memory>
#include <vector>

#include <btBulletDynamicsCommon.h>

namespace Taumuon {	namespace Game { namespace Physics {

	using namespace Taumuon::Game::Common;

	inline btVector3 btVectorFromVector3(Vector3^ input)
	{
		return btVector3(input->X, input->Y, input->Z);
	}

	inline btQuaternion btQuaternionFromQuaternion(Quaternion^ input)
	{
		return btQuaternion(input->X, input->Y, input->Z, input->W);
	}

	inline btTransform btTransformFromTransform(Transform^ transform)
	{
		auto quaternion = btQuaternionFromQuaternion(transform->Quaternion);
		auto translation = btVectorFromVector3(transform->Location);
		return btTransform(quaternion, translation);
	}

} } }
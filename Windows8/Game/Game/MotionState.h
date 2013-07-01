#pragma once

#include <btBulletDynamicsCommon.h>

class ITransformable;

class MotionState : public btMotionState 
{
public:
	MotionState(const btTransform &initialTransform, const std::shared_ptr<ITransformable>& transformable);
	virtual ~MotionState(void);

	virtual void getWorldTransform(btTransform &worldTransform) const;
	virtual void setWorldTransform(const btTransform &worldTransform);
private:
	MotionState(const MotionState&);
	MotionState& operator=(const MotionState&);

	std::shared_ptr<ITransformable> m_transformable;
	btTransform m_initialTransform;
};


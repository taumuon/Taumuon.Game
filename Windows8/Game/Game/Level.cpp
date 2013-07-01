#include "pch.h"
#include "Level.h"
#include "Scene.h"
#include "Camera.h"
#include "Physics.h"
#include "MotionState.h"
#include "Cube.h"

using namespace DirectX;

Level::Level(void)
	:
	m_physics(std::unique_ptr<Physics>(new Physics()))
{
}

Level::~Level(void)
{
}

void Level::Initialize(Scene^ scene)
{
	m_scene = scene;

	auto groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	m_physics->AddPhysicalObject(std::unique_ptr<btCollisionShape>(groundShape),
								 std::unique_ptr<btMotionState>(groundMotionState),
								 0,
								 btVector3(0,0,0));

	auto halfWidth = 0.5f;
	for(float height=halfWidth; height < (halfWidth * 44.0f); height += (halfWidth * 2.0f))
	{
		for(float i=-(halfWidth * 10.0f); i < (halfWidth * 10.0f); i += (halfWidth * 2.0f))
		{
			auto cube = m_scene->CreateCube();
			m_cubes.push_back(cube);

			auto x = i;
			auto y = height;
			auto z = 0.0f;

			auto fallShape = new btBoxShape(btVector3(btScalar(halfWidth), btScalar(halfWidth), btScalar(halfWidth)));
			auto motionState = new MotionState(btTransform(btQuaternion(0,0,0,1),btVector3(x,y,z)), cube);
			btScalar mass = 10;
			btVector3 fallInertia(0,0,0);
			fallShape->calculateLocalInertia(mass,fallInertia);
			m_physics->AddPhysicalObject(std::unique_ptr<btCollisionShape>(fallShape),
										 std::unique_ptr<btMotionState>(motionState),
										 mass,
										 fallInertia);

			m_motionStateToCubeMap[motionState] = cube;
		}
	}
}

void Level::Update()
{
	m_physics->Update();
	m_scene->Render();
}

void Level::OnPointerPressed(float x, float y)
{
	auto camera = m_scene->GetCamera();
	auto rayFrom = camera.GetEye();
	auto pickRay = m_scene->GetPickRay(x, y);

	auto rigidBody = m_physics->RayTest(rayFrom, pickRay);

	if (rigidBody == nullptr)
	{
		return;
	}

	auto motionState = reinterpret_cast<MotionState*>(rigidBody->getMotionState());

	auto entry = m_motionStateToCubeMap.find(motionState);
	
	if (entry != end(m_motionStateToCubeMap))
	{
		auto cube = entry->second;

		m_scene->RemoveCube(cube);
		m_physics->RemoveRigidBody(rigidBody);

		auto it = std::find(begin(m_cubes), end(m_cubes), cube);
		if (it != end(m_cubes))
		{
			m_cubes.erase(it);
		}
	}
}
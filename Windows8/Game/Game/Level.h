#pragma once

ref class Scene;
class Physics;
class Cube;
class MotionState;

class Level
{
public:
	Level(void);
	virtual ~Level(void);

	void Initialize(Scene^ scene);
	void Update();

	void OnPointerPressed(float x, float y);
private:
	Level(const Level&);
	Level& operator=(const Level&);

	Scene^ m_scene;

	std::unique_ptr<Physics> m_physics;
	std::vector<std::shared_ptr<Cube>> m_cubes;
	std::map<MotionState*, std::shared_ptr<Cube>> m_motionStateToCubeMap;
};


using System.Collections.Generic;

namespace Taumuon.Game
{
    using Physics;
    using Common;
    using Renderer;

    public class Level
    {
        private readonly PhysicsEngine _physics = new PhysicsEngine();
        private readonly List<Cube> _cubes = new List<Cube>();

        public void Initialise(Scene scene)
        {
            scene.OnRendering += () =>
                {
                    for (int i = 0; i < 10; ++i)
                    {
                        _physics.Update();
                    }
                };

            _physics.AddStaticPlane(new ShapeParameters(new Vector3(0.0, 0.0, 0.0),
                                                        new Transform(new Vector3(0.0, -1.0, 0.0),
                                                                      new Quaternion(0.0, 0.0, 0.0, 1.0)),
                                                        null),
                                    new Vector3(0.0, 1.0, 0.0),
                                    1.0);

            for (var height = 0.5f; height < 22.0f; height += 1.3f)
            {
                for (var i = -5.0f; i < 5.0f; i += 1.1f)
                {
                    var cube = scene.CreateCube();
                    _cubes.Add(cube);

                    var x = -height / 10.0f;
                    var y = height;
                    var z = i;

                    _physics.AddBox(new ShapeParameters(new Vector3(0.0, 0.0, 0.0),
                                                        new Transform(new Vector3(x, y, z),
                                                                       new Quaternion(0.0, 0.0, 0.0, 1.0)),
                                                        cube),
                                    new Vector3(0.5, 0.5, 0.5));
                }
            }

            _physics.Update();
        }
    }
}

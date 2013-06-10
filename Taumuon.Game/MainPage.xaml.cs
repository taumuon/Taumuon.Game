using System;
using System.Windows;
using Taumuon.Game.Renderer;

namespace Taumuon.Game
{
    public partial class MainPage
    {
        private Direct3DBackground _d3dBackground;
        private Level _level;

        // Constructor
        public MainPage()
        {
            InitializeComponent();
        }

        private void DrawingSurfaceBackground_Loaded(object sender, RoutedEventArgs e)
        {
            if (_d3dBackground == null)
            {
                _d3dBackground = new Direct3DBackground();

                // Set window bounds in dips
                _d3dBackground.WindowBounds = new Windows.Foundation.Size(
                    (float)Application.Current.Host.Content.ActualWidth,
                    (float)Application.Current.Host.Content.ActualHeight
                    );

                // Set native resolution in pixels
                _d3dBackground.NativeResolution = new Windows.Foundation.Size(
                    (float)Math.Floor(Application.Current.Host.Content.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f),
                    (float)Math.Floor(Application.Current.Host.Content.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f)
                    );

                // Set render resolution to the full native resolution
                _d3dBackground.RenderResolution = _d3dBackground.NativeResolution;

                // Hook-up native component to DrawingSurfaceBackgroundGrid
                DrawingSurfaceBackground.SetBackgroundContentProvider(_d3dBackground.CreateContentProvider());
                DrawingSurfaceBackground.SetBackgroundManipulationHandler(_d3dBackground);

                _level = new Level();
                _level.Initialise(_d3dBackground.Scene);
            }
        }
    }
}
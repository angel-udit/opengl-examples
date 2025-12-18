
// Este código es de dominio público
// angel.rodriguez@udit.es

#ifndef SCENE_HEADER
#define SCENE_HEADER

    #include "Camera.hpp"
    #include "Skybox.hpp"

    namespace udit
    {

        class Scene
        {
        private:

            Camera camera;
            Skybox skybox;

            int    width;
            int    height;

            float  angle_around_x;
            float  angle_around_y;
            float  angle_delta_x;
            float  angle_delta_y;

            bool   pointer_pressed;
            float  last_pointer_x;
            float  last_pointer_y;

        public:

            Scene(int width, int height);

            void update   ();
            void render   ();

        public:

            void resize   (int width, int height);
            void on_drag  (float pointer_x, float pointer_y);
            void on_click (float pointer_x, float pointer_y, bool down);

        };

    }

#endif

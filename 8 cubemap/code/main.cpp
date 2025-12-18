
// Este código es de dominio público
// angel.rodriguez@udit.es

#include "Scene.hpp"
#include <Window.hpp>
#include <SDL3/SDL_main.h>

using udit::Scene;
using udit::Window;

int main (int , char * [])
{
    constexpr unsigned viewport_width  = 1024;
    constexpr unsigned viewport_height =  576;

    Window window("OpenGL example", viewport_width, viewport_height, { 3, 3 });    
    Scene  scene (viewport_width, viewport_height);

    bool  exit        = false;
    float mouse_x     = 0;
    float mouse_y     = 0;
    bool  button_down = false;

    do
    {
        // Se procesan los eventos acumulados:

        SDL_Event event;

        while (SDL_PollEvent (&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                {
                    auto   buttons = SDL_GetMouseState (&mouse_x, &mouse_y);
                    auto left_down = buttons &  SDL_BUTTON_MASK(SDL_BUTTON_LEFT);

                    if (left_down && not button_down) scene.on_click (mouse_x, mouse_y, button_down = true);

                    break;
                }

                case SDL_EVENT_MOUSE_BUTTON_UP:
                {
                    auto   buttons = SDL_GetMouseState (&mouse_x, &mouse_y);
                    auto left_down = buttons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT);

                    if (not left_down && button_down) scene.on_click (mouse_x, mouse_y, button_down = false);

                    break;
                }

                case SDL_EVENT_MOUSE_MOTION:
                {
                    SDL_GetMouseState (&mouse_x, &mouse_y);

                    scene.on_drag (mouse_x, mouse_y);

                    break;
                }

                case SDL_EVENT_QUIT:
                {
                    exit = true;
                }
            }
        }

        // Se actualiza la escena:

        scene.update ();

        // Se redibuja la escena:

        scene.render ();

        // Se actualiza el contenido de la ventana:

        window.swap_buffers ();
    }
    while (not exit);

    SDL_Quit ();

    return 0;
}

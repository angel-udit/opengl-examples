//
// Este código es de dominio público
// angel.rodriguez@udit.es
//

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_main.h>

int main (int , char * [])
{
    constexpr int window_width  = 1024;
    constexpr int window_height =  576;

    // Se hace inicializa SDL:

    if (not SDL_Init (SDL_INIT_VIDEO))
    {
        SDL_Log ("Error initializing SDL.");
    }
    else
    {
        // Se preconfigura el contexto de OpenGL:

        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER,          1);
        SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);

        // Se crea la ventana activando el soporte para OpenGL:

        SDL_Window * window = SDL_CreateWindow
        (
           "OpenGL window example",
            window_width,
            window_height,
            SDL_WINDOW_OPENGL
        );

        if (not window)
        {
            SDL_Log ("Error creating the window.");
        }
        else
        {
            // Se toma el buffer de la ventana para dibujar en él:

            SDL_GLContext gl_context = SDL_GL_CreateContext (window);

            if (not gl_context)
            {
                SDL_Log ("Error creating the OpenGL context.");
            }
            else
            {
                // Se activa la sincronización vertical con el display:

                SDL_GL_SetSwapInterval (1);

                // ALERTA: se usa OpenGL clásico solo porque el código es mucho más compacto:

                glClearColor (.5f, .5f, 1.f, 1.f);

                bool exit = false;

                do
                {
                    // Se procesan los eventos acumulados:

                    SDL_Event event;

                    while (SDL_PollEvent (&event))
                    {
                        if (event.type == SDL_EVENT_QUIT)
                        {
                            exit = true;
                        }
                    }

                    // Se borra la ventana (buffer oculto) con el color de fondo:

                    glClear (GL_COLOR_BUFFER_BIT);

                    // Se actualiza el contenido de la ventana:

                    SDL_GL_SwapWindow (window);
                }
                while (not exit);

                SDL_GL_DestroyContext (gl_context);
            }

            SDL_DestroyWindow (window);
        }

        SDL_Quit ();
    }

    return 0;
}

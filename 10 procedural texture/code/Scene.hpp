
// Este código es de dominio público
// angel.rodriguez@udit.es

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <memory>
    #include <string>
    #include <glad/gl.h>
    #include <Color.hpp>
    #include <Color_Buffer.hpp>
    #include "Cube.hpp"

    namespace udit
    {

        class Scene
        {
        private:

            typedef Color_Buffer< Rgba8888 > Color_Buffer;

        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLuint program_id;

            GLint  model_view_matrix_id;
            GLint  projection_matrix_id;

            Cube   cube;

            float  angle;
            float  depth;
            float  speed;

        public:

            Scene(int width, int height);
           ~Scene();

            void   update ();
            void   render ();
            void   resize (int  width, int height);

        private:

            GLuint compile_shaders        ();
            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);
        };

    }

#endif

#ifndef FICELLE_H_INCLUDED
#define FICELLE_H_INCLUDED

#include <GL/glew.h>
// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Includes
#include "Shader.h"
#include "Sphere.h"

class Ficelle{
    public:
        Ficelle(float taille,float diametre, std::string const vertexShader, std::string const fragmentShader,Sphere Sphere);
        ~Ficelle();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
        void deplacement(float x,float y,float z);
    private:
        Shader m_shader;
        float m_nbvertice;
        float m_taille;
        float m_vertices[90];
        float m_verticesS[90];
        float m_couleurs[90];
};
#endif // FICELLE_H_INCLUDED

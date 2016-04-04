#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Sphere
{
     public:
        Sphere(float taille, std::string const vertexShader, std::string const fragmentShader, float cx, float cy, float cz);
        ~Sphere();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
        void updateEvenements();
        void Normalise();
        float getcx();
        float getcz();
        float getcy();

    private:
        Shader m_shader;
        float m_vertices[18720];
        float m_couleurs[18720];
        float m_nbvertice;
        float m_taille;
        float m_cx;
        float m_cy;
        float m_cz;
        float m_y;
};

#endif // SPHERE_H_INCLUDED

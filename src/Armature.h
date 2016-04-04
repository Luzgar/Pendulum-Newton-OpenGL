#ifndef ARMATURE_H_INCLUDED
#define ARMATURE_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Armature
{
    public:
        Armature(float longeur1, float largeur1, float hauteur1, std::string const vertexShader, std::string const fragmentShader, float cx, float cy, float cz);
        ~Armature();
        void afficher(glm::mat4 &projection, glm::mat4 &modelview);
    private:
        Shader m_shader;
        float m_nbvertice;
        float m_taille;
        float m_vertices[108];
        float m_couleurs[108];
};

#endif // ARMATURE_H_INCLUDED

#include "Armature.h"

Armature::Armature(float longeur1,float largeur1,float hauteur1,std::string const vertexShader,std::string const fragmentShader,float cx,float cy,float cz): m_shader(vertexShader, fragmentShader)
{
    m_shader.charger();
    longeur1=longeur1/2;
    largeur1=largeur1/2;
    float vertice[] = {cx + longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy, cz - largeur1 / 4, //face 1
                     cx + longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy, cz - largeur1 / 4, cx + longeur1 / 2, cy, cz - largeur1 / 4, //face 1
                     cx + longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx-longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, //face2
                     cx + longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx-longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, //face2
                     cx - longeur1 / 2, cy, cz - largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, cx + longeur1 / 2, cy, cz - largeur1 / 4, //face 3
                     cx + longeur1 / 2, cy, cz - largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz - largeur1 / 4, //face3
                     cx + longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy, cz + largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, //face 4
                     cx - longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz + largeur1 / 4,//face4
                     cx - longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy, cz - largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz - largeur1 / 4,
                     cx - longeur1 / 2, cy, cz + largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx - longeur1 / 2, cy + hauteur1, cz - largeur1 / 4,
                     cx + longeur1 / 2, cy, cz + largeur1 / 4, cx + longeur1 / 2, cy, cz - largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz - largeur1 / 4,
                     cx + longeur1 / 2, cy, cz + largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz + largeur1 / 4, cx + longeur1 / 2, cy + hauteur1, cz - largeur1 / 4};
    m_nbvertice=108;//définie le nombre de vertices a afficher
    for(int i = 0; i < m_nbvertice; i += 3)
    {
       m_vertices[i] = vertice[i];
       m_vertices[i+1] = vertice[i+1];
       m_vertices[i+2] = vertice[i+2];
       m_couleurs[i] = 204.00 / 255.00;
       m_couleurs[i+1] = 193.00 / 255.00;
       m_couleurs[i+2] = 91.00 / 255.00;
    }
}

Armature::~Armature() {}

void Armature::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());
    // Envoi des vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
    glEnableVertexAttribArray(0);
    // Envoi de la couleur
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_couleurs);
    glEnableVertexAttribArray(1);
    // Envoi des matrices
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
    // Rendu
    glDrawArrays(GL_TRIANGLES, 0,m_nbvertice/3);
    // Désactivation des tableaux
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    // Désactivation du shader
    glUseProgram(0);
}

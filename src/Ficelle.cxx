#include"ficelle.h"

Ficelle::Ficelle(float taille,float diametre, std::string const vertexShader, std::string const fragmentShader,Sphere Sphere): m_shader(vertexShader, fragmentShader)
{
   m_shader.charger();
   //recupération du centre de la sphère pour le placement
   float cx = Sphere.getcx();
   float cy = Sphere.getcy();
   float cz = Sphere.getcz();
   taille = taille/2;
   diametre = diametre/2;

   float vertices[] = {cx + diametre / 2, cy,cz-diametre / 2, cx-diametre / 2, cy, cz - diametre / 2, cx + diametre / 2, cy, cz + diametre / 2, // Face 1
                       cx - diametre / 2, cy,cz+diametre / 2, cx-diametre / 2, cy, cz - diametre / 2, cx + diametre / 2, cy, cz + diametre / 2, // Face 1
                       cx + diametre / 2, cy,cz-diametre / 2, cx+diametre / 2, cy, cz + diametre / 2, cx + diametre/2,cy+taille,cz+diametre / 2, // Face 2
                       cx + diametre / 2, cy,cz-diametre / 2, cx+diametre / 2, cy + taille, cz - diametre / 2, cx + diametre / 2, cy + taille, cz + diametre / 2, // Face 2
                       cx + diametre / 2, cy,cz+diametre / 2, cx-diametre / 2, cy, cz + diametre / 2 ,cx + diametre / 2, cy + taille, cz + diametre / 2, // Face 3
                       cx - diametre / 2, cy,cz+diametre / 2, cx-diametre / 2, cy + taille, cz + diametre / 2, cx + diametre / 2, cy + taille, cz + diametre / 2, // Face 3
                       cx - diametre / 2, cy,cz-diametre / 2, cx-diametre / 2, cy, cz + diametre / 2, cx-diametre / 2, cy + taille, cz - diametre / 2, // Face 4
                       cx - diametre / 2, cy,cz+diametre / 2, cx-diametre / 2, cy + taille, cz + diametre / 2, cx - diametre / 2, cy + taille, cz - diametre / 2, // Face 4
                       cx + diametre / 2, cy,cz-diametre / 2, cx-diametre / 2, cy, cz - diametre / 2, cx + diametre / 2, cy + taille, cz - diametre / 2, // Face 5
                       cx + diametre / 2, cy,cz-diametre / 2, cx+diametre / 2, cy + taille, cz - diametre / 2, cx + diametre / 2, cy + taille, cz - diametre / 2, // Face 5
                       cx + diametre / 2, cy+taille, cz - diametre / 2, cx-diametre / 2, cy + taille, cz-diametre / 2, cx + diametre / 2, cy + taille, cz + diametre / 2, // Face 6
                       cx - diametre / 2, cy+taille, cz + diametre / 2, cx-diametre / 2, cy + taille, cz-diametre / 2, cx + diametre / 2, cy + taille, cz + diametre / 2,}; // Face 6

    m_nbvertice = 90;
    for(int i = 0; i < m_nbvertice; i++)
    {
       m_vertices[i] = vertices[i];
       m_verticesS[i]= vertices[i];
       m_couleurs[i] = 1.0;
    }
}

Ficelle::~Ficelle() {}

void Ficelle::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader
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
    //Désactivation des tableaux
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    // Désactivation du shader
    glUseProgram(0);
}

void Ficelle::deplacement(float x,float y,float z)
{
    for(int i = 0; i < m_nbvertice; i++)
       m_vertices[i] = m_verticesS[i];
    for(unsigned i = 0; i < 18; i += 3)
    {
      m_vertices[i] = m_vertices[i] + x;
      m_vertices[i+1] = m_vertices[i+1] + y;
      m_vertices[i+2] = m_vertices[i+2] + z;
    }
    //définie les changements
    bool changement = true;
    for(unsigned i = 18; i <= m_nbvertice - 18; i += 9)
    {
      m_vertices[i] = m_vertices[i] + x;
      m_vertices[i+1] = m_vertices[i+1] + y;
      m_vertices[i+2] = m_vertices[i+2] + z;
      if(changement)//le triangle a 2 points qui dois bouger
      {
         m_vertices[i+3] = m_vertices[i+3] + x;
         m_vertices[i+4] = m_vertices[i+4] + y;
         m_vertices[i+5] = m_vertices[i+5] + z;
      }
      changement = !changement;
    }
}

#include "Sphere.h"

using namespace glm;

Sphere::Sphere(float taille, std::string const vertexShader, std::string const fragmentShader, float cx, float cy, float cz) : m_shader (vertexShader, fragmentShader)
{
    m_shader.charger();

    taille /= 2;
    //initialisation des variables membres
    m_taille = taille;
    m_cx = cx;
    m_cy = cy;
    m_cz = cz;
    m_nbvertice = 0;

     float nbdec = 8; // Définit la précision de la sphère
    float ax;
    float ay;
    float az;
    float bx;
    float by;
    float bz;
    float y;

    y = cy + (taille / sqrt(2));// Calcul permettant de trouver le sommet d'une pyramide
    m_y = y;
// Envoi du sommet dans le tableau
    m_vertices[0] = cx;
    m_vertices[1] = y;
    m_vertices[2] = cz;

    int j = 0;// Définit les vertices qui seront des nouveaux sommets des triangles
    int cpt = 0;// Positionnement de j dans le tableau
    float coeff = taille / nbdec;// Sert à définir la distance des nouveaux points créés
    int i = 0; // Variables parcourant le tableau

    //Création des 8 faces
    for(unsigned face = 0; face < 8; ++face)
    {
        for(;;)
        {
            ax = m_vertices[j];
            ay = m_vertices[j+1];
            az = m_vertices[j+2];
            m_vertices[i] = ax;
            m_vertices[i+1] = ay;
            m_vertices[i+2] = az;

            switch(face)
            {
                case 0:
                    bx = ax + coeff;
                    by = ay - coeff;
                    bz = az - coeff;
                break;
                case 1:
                    bx = ax + coeff;
                    by = ay - coeff;
                    bz = az + coeff;
                break;
                case 3:
                    y = -y;
                case 2:
                    bx = ax - coeff;
                    by = ay - coeff;
                    bz = az - coeff;
                break;
                case 4:
                    bx = ax + coeff;
                    by = ay + coeff;
                    bz = az - coeff;
                break;
                case 5:
                    bx = ax - coeff;
                    by = ay + coeff;
                    bz = az + coeff;
                break;
                case 6:
                case 7:
                    bx = ax - coeff;
                    by = ay + coeff;
                    bz = az - coeff;
                break;
                break;
            }

            m_vertices[i+3] = bx;
            m_vertices[i+4] = by;
            m_vertices[i+5] = bz;

            switch(face)
            {
                case 0:
                case 3:
                case 4:
                case 7:
                    bz = az + coeff;
                break;
                case 1:
                    bx = ax - coeff;
                break;
                case 2:
                case 5:
                case 6:
                    bx = ax + coeff;
                break;
                break;
            }

            m_vertices[i+6] = bx;
            m_vertices[i+7] = by;
            m_vertices[i+8] = bz;

            j += 3;

            ++cpt;
            // Eviter les doublons
            if(cpt%3 == 0)
            {
                j += 3;
                ++cpt;
            }
            // Eviter les doublons
            if(j > 6 && m_vertices[j] == m_vertices[j-6] && m_vertices[j+1] == m_vertices[j-5] && m_vertices[j+2] == m_vertices[j-4])
            {
                j += 3;
                ++cpt;
            }

            i += 9;
            // Conditions de sortie de chaque face
            if(face == 0 && bx == cx + taille && by == y - taille && bz == cz + taille)
                break;

            if (face == 1 && bx == cx - taille && by == y - taille && bz == cz + taille)
                break;

            if (face == 2 && bx == cx + taille && by == y - taille && bz == cz - taille)
                break;

            if(face == 3 && bx == cx - taille && by == y - taille && bz == cz + taille)
                break;

            if(face == 4 && bx == cx + taille && by == -y - taille && bz == cz + taille)
                break;

            if(face == 5 && bx == cx + taille && by == -y - taille && bz == cz + taille)
                break;

            if(face == 6 && bx == cx + taille && by == -y - taille && bz == cz - taille)
                break;

            if(face == 7 && bx == cx - taille && by == -y - taille && bz == cz + taille)
                break;
        }

        if(face == 3)
            y = -y;// Changement de sommet pour faire la pyramide du bas

        j = i;
        cpt = 0;
        m_vertices[j] = cx;
        m_vertices[j+1] = y;
        m_vertices[j+2] = cz;
    }
    // Algorithme combleur de trous
    int compteur = 0;
    int compteurface = 1;
    while (compteurface <= 8)
    {
        for (unsigned k = 1; k < nbdec; ++k)
            for (unsigned l = 0; l < k; ++l)
            {
                m_vertices[i] = m_vertices[compteur+3];
                m_vertices[i+1] = m_vertices[compteur+4];
                m_vertices[i+2] = m_vertices[compteur+5];

                m_vertices[i+3] = m_vertices[compteur+6];
                m_vertices[i+4] = m_vertices[compteur+7];
                m_vertices[i+5] = m_vertices[compteur+8];

                m_vertices[i+6] = m_vertices[compteur+6 +(k*9)];
                m_vertices[i+7] = m_vertices[compteur+7 +(k*9)];
                m_vertices[i+8] = m_vertices[compteur+8 +(k*9)];

                i += 9;
                compteur += 9;
            }
            compteur += (nbdec*9);
            ++compteurface;
    }

    m_nbvertice = i;
    // Chargement des couleurs
    for(int l = 0; l < m_nbvertice;)
    {
        m_couleurs[l++] = 80.0 / 255.0;
        m_couleurs[l++] = 80.0 / 255.0;
        m_couleurs[l++] = 80.0 / 255.0;

        m_couleurs[l++] = 180.0 / 255.0;
        m_couleurs[l++] = 180.0 / 255.0;
        m_couleurs[l++] = 180.0 / 255.0;

        m_couleurs[l++] = 1;
        m_couleurs[l++] = 1;
        m_couleurs[l++] = 1;
    }
}

Sphere::~Sphere() {}

void Sphere::afficher(glm::mat4 &projection, glm::mat4 &modelview)
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
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
    // Rendu
    glDrawArrays(GL_TRIANGLES, 0, m_nbvertice / 3);
    // Désactivation des tableaux
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    // Désactivation du shader
    glUseProgram(0);
}


void Sphere::Normalise()
{
    // Taille de la normalisation
    float length(m_taille);
    float ax;
    float ay;
    float az;
    // Positionnement du point correspondant au centre de la sphère
    ax = m_cx;
    ay = m_cy;
    az = m_cz;
    float bx;
    float by;
    float bz;
    float dx;
    float dy;
    float dz;
    // Boucle cherchant le nouveau point normalisé
    for(int i = 0; i <= m_nbvertice; i += 3)
    {
        bx = m_vertices[i];
        by = m_vertices[i+1];
        bz = m_vertices[i+2];

        dx = bx - ax;
        dy = by - ay;
        dz = bz - az;

        dx = (dx * length / sqrt(dx*dx+dy*dy+dz*dz));
        dy = (dy * length / sqrt(dx*dx+dy*dy+dz*dz));
        dz = (dz * length / sqrt(dx*dx+dy*dy+dz*dz));

        dx += ax;
        dy += ay;
        dz += az;

        m_vertices[i] = dx;
        m_vertices[i+1] = dy;
        m_vertices[i+2] = dz;
    }
}

float Sphere::getcz()
{
    return m_cz;
}

float Sphere::getcx()
{
    return m_cx;
}

float Sphere::getcy()
{
    return m_cy;
}

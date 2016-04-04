#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>
#include <string>

#include "math.h"
#include "Shader.h"
#include "SceneOpenGL.h"
#include "Sphere.h"
#include "Ficelle.h"
#include "Armature.h"

using namespace glm;

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre)
{
    //chargement des variables
    m_titreFenetre = titreFenetre;
    m_largeurFenetre = largeurFenetre;
    m_hauteurFenetre = hauteurFenetre;
    m_fenetre = 0;
    m_contexteOpenGL = 0;
}

SceneOpenGL::~SceneOpenGL()
{
    //destruction contexte SDL
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    //Test Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //Création de la fenêtre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    //vérification de la création de la fenêtre
    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    // Création du contexte OpenGL
    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);
    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();
        return false;
    }
    return true;
}

bool SceneOpenGL::initGL()
{
    // On initialise GLEW
    GLenum initialisationGLEW(glewInit());
    // Si l'initialisation a échoué :
    if(initialisationGLEW != GLEW_OK)
    {
        // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;
        // On quitte la SDL
        SDL_GL_DeleteContext(m_contexteOpenGL);
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    // Tout s'est bien passé, on retourne true
    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    bool Fin = false; //quand finir le programme
    unsigned int frameRate = 40; //temps de reprise de la boucle principale 40fps
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0); //variables pour calculer le temps écoulé
    bool stop = true;//sert à définir laquelle des sphères doit monter
    bool tour = true;//sert à définir laquelle des sphères doit monter
    float xt = M_PI - acos(4/3); //sert à la translation de la sphère 1 et positionne à une coordonnée équivalente à x=4
    float yt = M_PI / 2; //sert à la translation de la sphère 1 et positionne à une coordonnée équivalente à y=3
    float xr = -M_PI / 2; //sert à la translation de la sphère 2 et positionne à une coordonnée équivalente à x=0
    float yr = -M_PI;// sert à la translation de la sphère 2 et positionne à une coordonnée équivalente à y=0
    float camera = 0;// variable pour la rotation de la caméra
    // création et initialisation des matrices
    mat4 projection;
    mat4 modelview;

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    mat4(1.0);

    //création des objets
    Sphere sphere(1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", 0, 0, 0);
    sphere.Normalise();
    Ficelle fic(8, 0.1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", sphere);

    Sphere sphere1(1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", 1, 0, 0);
    sphere1.Normalise();
    Ficelle fic1(8, 0.1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", sphere1);

    Sphere sphere2(1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", 2, 0, 0);
    sphere2.Normalise();
    Ficelle fic2(8, 0.1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", sphere2);

    Sphere sphere3(1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", -1, 0, 0);
    sphere3.Normalise();
    Ficelle fic3(8, 0.1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", sphere3);

    Sphere sphere4(1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", -2, 0, 0);
    sphere4.Normalise();
    Ficelle fic4(8, 0.1, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", sphere4);

    Armature Arm(14, 2, 0.2, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag", 0, 4, 0);

    while(!Fin)
    {
        debutBoucle = SDL_GetTicks();
        //Placement de la caméra
        modelview = lookAt(vec3(0, 0, 10), vec3(0, 0, 0), vec3(0,1, 0));

        // Gestion des évènements
        SDL_PollEvent(&m_evenements);

        if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            Fin = true;
        if(m_evenements.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
            Fin = true;
        //Mise en place de la rotation
        mat4 Test3 = mat4(cos(camera), 0, -sin(camera), 0,
                        0, 1, 0, 0,
                        sin(camera), 0, cos(camera), 0,
                        0, 0, 0, 1);

        modelview *= Test3;
        camera += 0.01;

        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Incrémentation de la variable pour la translation
        if(stop)
        {
            //Descente de la sphère 1
            if (tour)
            {
                xt += 0.1;
                yt += 0.1;
                if(3 * cos(xt) >= 0)
                    tour = false;
            }
            //Montée de la sphère 2
            else
            {
                xr += 0.1;
                yr += 0.1;
                if(3 * cos(xr) >= 2)
                    stop = false;
            }
        }
        else
        {
            //Descente de la sphère 2
            if (!tour)
            {
                xr -= 0.1;
                yr -= 0.1;
                if(3 * cos(xr) <= 0)
                    tour = true;
            }
            //Montée de la sphère 1
            else
            {
                xt -= 0.1;
                yt -= 0.1;
                if(3 * cos(xt) <= -2)
                    stop = true;
            }
        }

        // Sauvegarde de la matrice modelview
        mat4 sauvegardeModelview = modelview;

        //Affichage des objets dans modelview
        Arm.afficher(projection, modelview);
        sphere.afficher(projection, modelview);
        fic.afficher(projection, modelview);
        fic1.afficher(projection, modelview);
        sphere1.afficher(projection, modelview);
        sphere3.afficher(projection, modelview);
        fic3.afficher(projection, modelview);

        //Translation sphère 2
        mat4 Translation1 = mat4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                3*cos(xr), 3*cos(yr)+3, 0, 1);

        modelview *= Translation1;
        sphere2.afficher(projection, modelview);
        modelview = sauvegardeModelview;
        fic2.deplacement(3 * cos(xr), 3 * cos(yr) + 3, 0);
        fic2.afficher(projection, modelview);

        //translation sphère 4
        mat4 Translation2 = mat4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                3*cos(xt), 3*cos(yt)+3, 0, 1);

        modelview *= Translation2;
        sphere4.afficher(projection, modelview);
        modelview = sauvegardeModelview;
        fic4.deplacement(3 * cos(xt), 3 * sin(xt) + 3, 0);
        fic4.afficher(projection, modelview);

        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;
        // Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}

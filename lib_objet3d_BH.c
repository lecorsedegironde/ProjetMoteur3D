#include <math.h>
#include "lib_objet3d.h"
#include "lib_mat.h"

/**
 * Crée un objet 3d vide
 * Cet objet n'est pas une camera
 *
 * @return un pointeur sur objet3d
 */
t_objet3d *objet_vide_BH() {

    t_objet3d *objet3d = malloc(sizeof(t_objet3d));

    objet3d->est_trie = false;
    objet3d->est_camera = false;
    objet3d->tete = NULL;

    return objet3d;
}

/**
 * Crée une camera
 * zone l*h dans le champ n->f
 *
 * @param l
 * @param h
 * @param n
 * @param f
 * @param d
 * @return un pointeur sur camera
 */
t_objet3d *camera_BH(double l, double h, double n, double f, double d) {

    t_objet3d *camera = malloc(sizeof(t_objet3d));

    camera->est_trie = false;
    camera->est_camera = true;

    camera->largeur = l;
    camera->hauteur = h;
    camera->proche = n;
    camera->loin = f;
    camera->distance_ecran = d;

    camera->tete = NULL;

    return camera;
}

/**
 * Création d'un parallépipède
 *
 * @param lx longeur x
 * @param ly largeur x
 * @param lz profondeur z
 * @return un pointeur sur objet 3d parallépipède
 */
t_objet3d *parallelepipede_BH(double lx, double ly, double lz) {
    t_objet3d *parallepipede = objet_vide();
    //Création des maillons (12 triangles)
    //Création des points
    t_point3d *a = definirPoint3d(-lx / 2, -ly / 2, -lz / 2);
    t_point3d *b = definirPoint3d(lx / 2, -ly / 2, -lz / 2);
    t_point3d *c = definirPoint3d(lx / 2, ly / 2, -lz / 2);
    t_point3d *d = definirPoint3d(-lx / 2, ly / 2, -lz / 2);
    t_point3d *e = definirPoint3d(-lx / 2, -ly / 2, lz / 2);
    t_point3d *f = definirPoint3d(lx / 2, -ly / 2, lz / 2);
    t_point3d *g = definirPoint3d(lx / 2, ly / 2, lz / 2);
    t_point3d *h = definirPoint3d(-lx / 2, ly / 2, lz / 2);

    //Maillon pour la chaine
    t_maillon *maillonTMP = NULL;

    for (int i = 0; i < 12; ++i) {
        t_maillon *maillon = malloc(sizeof(t_maillon));
        maillon->pt_suiv = NULL;

        switch (i) {
            case 0:
                //DBC Arrière par rapport cam défaut
                maillon->face = definirTriangle3d(b, d, c);
                maillon->couleur = ROUGEC;
                break;
            case 1:
                //ABD Arrière par rapport cam défaut TRIANGLE S'AFFICHE PAS !
                maillon->face = definirTriangle3d(a, b, d);
                maillon->couleur = ROUGEF;
                break;
            case 2:
                //DCG
                maillon->face = definirTriangle3d(d, c, g);
                maillon->couleur = VERTC;
                break;
            case 3:
                //DGH
                maillon->face = definirTriangle3d(d, g, h);
                maillon->couleur = VERTC;
                break;
            case 4:
                //HGF
                maillon->face = definirTriangle3d(h, g, f);
                maillon->couleur = BLEUC;
                break;
            case 5:
                //HFE
                maillon->face = definirTriangle3d(h, f, e);
                maillon->couleur = BLEUC;
                break;
            case 6:
                //EFB
                maillon->face = definirTriangle3d(e, f, b);
                maillon->couleur = JAUNEC;
                break;
            case 7:
                //AEB
                maillon->face = definirTriangle3d(a, e, b);
                maillon->couleur = JAUNEC;
                break;
            case 8:
                //HAE
                maillon->face = definirTriangle3d(h, a, e);
                maillon->couleur = PALEC;
                break;
            case 9:
                //HAD
                maillon->face = definirTriangle3d(h, a, d);
                maillon->couleur = PALEC;
                break;
            case 10:
                //FGC
                maillon->face = definirTriangle3d(f, g, c);
                maillon->couleur = ROSEC;
                break;
            case 11:
                //FCB
                maillon->face = definirTriangle3d(f, c, b);
                maillon->couleur = ROSEC;
                break;
            default:
                //WTF?
                return NULL;
        }

        if (i == 0) {
            parallepipede->tete = maillon;
        } else {
            maillonTMP->pt_suiv = maillon;
        }
        maillonTMP = maillon;
    }

    return parallepipede;
}

/**
 * Créé une sphere 3d
 */
t_objet3d *sphere_BH(double r, double nlat, double nlong) {
    return sphereCreation(r, nlat, nlong, true);
}

/**
 * Créé une sphere 3d avec des couleurs particulières
 */
t_objet3d *sphere_amiga_BH(double r, double nlat, double nlong) {
    return sphereCreation(r, nlat, nlong, false);
}

/**
 * Créé une sphere à partir des paramètres passés à la fonction
 *
 * @param r le rayon de la sphere
 * @param nlat le nombre de latitudes
 * @param nlong le nombre de longitudes
 * @param colorGeneration is color gen nedded ?
 * @return un pointeur sur objet 3d sphere
 */
t_objet3d *sphereCreation(double r, double nlat, double nlong, t_bool colorGeneration) {
    t_objet3d *sphere = objet_vide();

    //Maillon pour la création
    t_maillon *maillonTMP = NULL;
    t_bool isHead = true;

    //Couleurs
    Uint32 couleur1 = VERTC;
    Uint32 couleur2 = BLEUC;
    Uint32 couleur3 = ROSEC;
    Uint32 couleur4 = JAUNEC;


    //Tableau de stockage des points
    t_point3d *pointsPos[(int) nlat][(int) nlong];

    //Double boucle for imbriquée pour définir les points
    for (int i = 1; i < nlat + 1; ++i) {
        double theta = (i * M_PI) / (nlat + 1);
        double sinTheta = sin(theta);
        double cosTheta = cos(theta);

        for (int j = 0; j < nlong; ++j) {
            double phi = (j * 2 * M_PI) / nlong;
            double sinPhi = sin(phi);
            double cosPhi = cos(phi);

            double x = r * sinTheta * sinPhi;
            double y = -r * cosTheta;
            double z = r * sinTheta * cosPhi;

            pointsPos[i - 1][j] = definirPoint3d(x, y, z);
        }
    }

    //On définit les points d'origine
    t_point3d *p0 = definirPoint3d(0, -r, 0);
    t_point3d *p1 = definirPoint3d(0, r, 0);

    //Maintenant que l'on a défini les points, on peut créer les triangles
    for (int i = 0; i < nlat - 1; ++i) {
        for (int j = 0; j < nlong - 1; ++j) {

            //Création des maillons
            t_maillon *maillon1 = malloc(sizeof(t_maillon));
            t_maillon *maillon2 = malloc(sizeof(t_maillon));

            if (colorGeneration) {
                maillon1->couleur = ((i + j) % 2) ? couleur1 : couleur3;
                maillon2->couleur = ((i + j) % 2) ? couleur2 : couleur4;
            } else {
                maillon1->couleur = ((i + j) % 2) ? BLANC : ROUGEC;
                maillon2->couleur = ((i + j) % 2) ? BLANC : ROUGEC;
            }

            //On défini deux triangles -> un caré
            maillon1->face = definirTriangle3d(pointsPos[i][j], pointsPos[i][j + 1], pointsPos[i + 1][j + 1]);

            maillon2->face = definirTriangle3d(pointsPos[i][j], pointsPos[i + 1][j], pointsPos[i + 1][j + 1]);

            maillon1->pt_suiv = maillon2;

            if (isHead) {
                sphere->tete = maillon1;
                isHead = false;
            } else {
                maillonTMP->pt_suiv = maillon1;
            }
            maillonTMP = maillon2;
            if (i == 0) {
                //Création des maillons
                t_maillon *maillon3 = malloc(sizeof(t_maillon));
                t_maillon *maillon4 = malloc(sizeof(t_maillon));

                if (colorGeneration) {
                    maillon3->couleur = (j % 2) ? couleur3 : couleur2;
                    maillon4->couleur = (j % 2) ? couleur4 : couleur1;
                } else {
                    maillon3->couleur = (j % 2) ? ROUGEC : BLANC;
                    maillon4->couleur = (j % 2) ? BLANC : ROUGEC;
                }

                //On défini deux triangles -> un caré
                maillon3->face = definirTriangle3d(p0, pointsPos[0][j], pointsPos[0][j + 1]);

                maillon4->face = definirTriangle3d(pointsPos[(int) nlat - 1][j], pointsPos[(int) nlat - 1][j + 1], p1);

                //On ajoute les trianlges à la suite
                maillonTMP->pt_suiv = maillon3;
                maillon3->pt_suiv = maillon4;
                maillonTMP = maillon4;
            }
        }

        //Création des maillons
        t_maillon *maillon1 = malloc(sizeof(t_maillon));
        t_maillon *maillon2 = malloc(sizeof(t_maillon));

        if (colorGeneration) {
            maillon1->couleur = (i % 2) ? couleur1 : couleur3;
            maillon2->couleur = (i % 2) ? couleur2 : couleur4;
        } else {
            maillon1->couleur = (i % 2) ? ROUGEC : BLANC;
            maillon2->couleur = (i % 2) ? ROUGEC : BLANC;
        }

        //On défini deux triangles -> un caré
        maillon1->face = definirTriangle3d(pointsPos[i][(int) (nlong - 1)], pointsPos[i][0], pointsPos[i + 1][0]);

        maillon2->face = definirTriangle3d(pointsPos[i][(int) (nlong - 1)], pointsPos[i + 1][(int) (nlong - 1)],
                                           pointsPos[i + 1][0]);

        //On ajoute les trianlges à la suite
        maillonTMP->pt_suiv = maillon1;
        maillon1->pt_suiv = maillon2;
        maillonTMP = maillon2;

        if (i == 0) {
            //Les deux derniers triangles
            t_maillon *maillon3 = malloc(sizeof(t_maillon));
            t_maillon *maillon4 = malloc(sizeof(t_maillon));

            if (colorGeneration) {
                maillon4->couleur = (i % 2) ? couleur2 : couleur3;
                maillon3->couleur = (i % 2) ? couleur1 : couleur4;
            } else {
                maillon3->couleur = ROUGEC;
                maillon4->couleur = BLANC;
            }

            //On défini deux triangles -> un caré
            maillon3->face = definirTriangle3d(p0, pointsPos[i][(int) nlong - 1], pointsPos[i][0]);

            maillon4->face = definirTriangle3d(pointsPos[(int) nlat - 1][(int) nlong - 1], pointsPos[(int) nlat - 1][0],
                                               p1);

            //On ajoute les trianlges à la suite
            maillonTMP->pt_suiv = maillon3;
            maillon3->pt_suiv = maillon4;
            maillonTMP = maillon4;
        }
    }

    return sphere;
}

/**
 * Créé un arbre à partir des paramètres lx, ly et lz
 * @param lx longeur
 * @param ly hauteur
 * @param lz profondeur
 * @return un pointeur sur objet3d de l'arbre
 */
t_objet3d *arbre_BH(double lx, double ly, double lz) {
    //Création objet 3d
    t_objet3d *arbre = objet_vide();

    //Création du parralépipède
    t_objet3d *base = parallelepipede(lx, ly, lz);

    //Création des points
    t_point3d *a = definirPoint3d(-lx / 2, ly / 2, -lz / 2);
    t_point3d *b = definirPoint3d(lx / 2, ly / 2, -lz / 2);
    t_point3d *c = definirPoint3d(lx / 2, ly / 2, lz / 2);
    t_point3d *d = definirPoint3d(-lx / 2, ly / 2, lz / 2);
    t_point3d *e = definirPoint3d(0, (ly / 2) + lz, 0);

    //Changement de couleurs de la base
    t_maillon *maillonTMP = base->tete;
    //Itérateur pour la couleur
    int i = 0;

    while (maillonTMP != NULL) {
        switch (i % 4) {
            case 0:
                maillonTMP->couleur = MARRON4;
                break;
            case 1:
                maillonTMP->couleur = MARRON1;
                break;
            case 2:
                maillonTMP->couleur = MARRON3;
                break;
            case 3:
                maillonTMP->couleur = MARRON2;
                break;

            default:
                break;
        }

        maillonTMP = maillonTMP->pt_suiv;
        ++i;
    }

    //Création des feuilles
    //Remise à null de tmp
    maillonTMP = NULL;
    for (int j = 0; j < 4; ++j) {
        t_maillon *maillon = malloc(sizeof(t_maillon));
        maillon->pt_suiv = NULL;

        switch (j) {
            case 0:
                maillon->face = definirTriangle3d(a, b, e);
                maillon->couleur = VERTC;
                break;
            case 1:
                maillon->face = definirTriangle3d(b, c, e);
                maillon->couleur = VERTF;
                break;
            case 2:
                maillon->face = definirTriangle3d(c, d, e);
                maillon->couleur = VERTC;
                break;
            case 3:
                maillon->face = definirTriangle3d(d, a, e);
                maillon->couleur = VERTF;
                break;
            default:
                //Well shit.
                break;
        }

        if (j == 0) {
            arbre->tete = maillon;
        } else {
            maillonTMP->pt_suiv = maillon;
        }
        maillonTMP = maillon;
    }

    composerObjet3d(arbre, base);

    return arbre;
}

/**
 * Retourne un damier NOIR et BLANC en fonction des paramètres passés
 * @param lx longueur
 * @param lz largeur
 * @param nx nb de carrés en longueur
 * @param nz nb de carrés en largeur
 * @return un pointeur sur objet3d
 */
t_objet3d *damier_BH(double lx, double lz, double nx, double nz) {
    //Création objet 3d
    t_objet3d *damier = objet_vide();

    //Création du 1er maillon
    t_maillon *maillonTMP = NULL;

    //Double boucle for imbriquée pour créer le damier
    t_bool isHead = true;

    for (int i = 0; i < nz; ++i) {
        for (int j = 0; j < nz; ++j) {
            //Création des maillons
            t_maillon *maillon1 = malloc(sizeof(t_maillon));
            t_maillon *maillon2 = malloc(sizeof(t_maillon));

            //Définir les deux points x et z
            double x = (i * lx) / (int) nx - lx / 2;
            double x_1 = ((i + 1) * lx) / (int) nx - lx / 2;
            double z = (j * lz) / (int) nz - lz / 2;
            double z_1 = ((j + 1) * lz) / (int) nz - lz / 2;

            //Création des points
            t_point3d *a = definirPoint3d(x, 0, z);
            t_point3d *b = definirPoint3d(x_1, 0, z);
            t_point3d *c = definirPoint3d(x_1, 0, z_1);
            t_point3d *d = definirPoint3d(x, 0, z_1);

            //Define color
            Uint32 col = 0;
            if ((i % 2) == 0) {
                (j % 2) ? (col = BLANC) : (col = NOIR);
            } else {
                (j % 2) ? (col = NOIR) : (col = BLANC);
            }

            maillon1->couleur = col;
            maillon2->couleur = col;

            maillon1->face = definirTriangle3d(a, b, c);

            maillon2->face = definirTriangle3d(a, d, c);

            maillon1->pt_suiv = maillon2;

            if (isHead) {
                damier->tete = maillon1;
                isHead = false;
            } else {
                maillonTMP->pt_suiv = maillon1;
            }
            maillonTMP = maillon2;
        }
    }
    return damier;
}

/**
 * Effectuer une copie d'un objet 3d en dupliquant tous ses maillons
 * @param o l'objet à copier
 * @return un pointeur sur la copie de l'objet
 */
t_objet3d *copierObjet3d_BH(t_objet3d *o) {
    t_objet3d *copyObject;

    //Copie des propriétés
    if (o->est_camera == true) {
        copyObject = camera(o->largeur, o->hauteur, o->proche, o->loin, o->distance_ecran);
    } else {
        copyObject = objet_vide();
        copyObject->tete = cloneMaillon(o->tete);
        copyObject->est_trie = true;
    }
    return copyObject;
}

/**
 * Clone les maillons d'une liste chaînée de manière récursive
 *
 * @param list liste à trier
 * @return une liste triée
 */
t_maillon *cloneMaillon(t_maillon *list) {
    if (list == NULL) {
        return NULL;
    }
    t_maillon *newMaillon = malloc(sizeof(t_maillon));
    newMaillon->couleur = list->couleur;
    newMaillon->face = copierTriangle3d(list->face);
    newMaillon->pt_suiv = cloneMaillon(list->pt_suiv);
    return newMaillon;
}

/**
 * Prend 2 objets 3d pour n'en faire qu'un seul
 *
 * @param o l'objet 3d récepteur
 * @param o2 l'objet 3d que l'on va rajouter à o
 */
void composerObjet3d_BH(t_objet3d *o, t_objet3d *o2) {
    //On va quand même tester, voir si c'est pas des cameras
    if (!o->est_camera && !o2->est_camera) {

        if (o->tete != NULL) {
            t_maillon *maillonTMP = o->tete;

            while (maillonTMP->pt_suiv != NULL) {
                maillonTMP = maillonTMP->pt_suiv;
            }
            maillonTMP->pt_suiv = o2->tete;

        } else o->tete = o2->tete;
    }
    free(o2);
}

/**
 * Prend 2 objets 3d pour n'en faire qu'un seul et les enlève les faces qui n'apparaissent pas
 * @param o est retourné
 * @param o2
 * @param camera
 */
void composerObjet3d_limite_en_z_BH(t_objet3d *o, t_objet3d *o2, t_objet3d *camera) {
    //Composer les objets avec uniquement les faces qui apparaissent dans la camera
    //On commence par composer les deux objets grace à la fonction idoine o2 est free dans cette fonction
    composerObjet3d(o, o2);
    //o n'est plus trié
    o->est_trie = false;
    //On récoupère la tête
    t_maillon *maillonTMP = o->tete;
    t_maillon *oldMaillon = o->tete;
    //Est-ce que c'est la tête de la liste ?
    t_bool isHead = true;

    while (maillonTMP->pt_suiv != NULL) {
        double zMoyen = zmoyen(maillonTMP->face);

        //Si le zmoyen ne rentre pas on retire la face
        if (zMoyen < camera->loin || zMoyen > camera->proche) {
            //On retire le maillon
            if (!isHead) oldMaillon->pt_suiv = maillonTMP->pt_suiv;
            else o->tete = maillonTMP->pt_suiv;
        } else {
            if (isHead) isHead = false;
            oldMaillon = maillonTMP;
        }
        //On passe au maillon suivant
        maillonTMP = maillonTMP->pt_suiv;
    }
}

/**
 * Libérer tout les maillons de la chaine d'un objet 3d
 *
 * @param o l'objet à libérer
 */
void libererObjet3d_BH(t_objet3d *o) {
    t_maillon *maillonTMP = o->tete;

    while (maillonTMP != NULL) {
        freeTriangle(maillonTMP->face);
        maillonTMP = maillonTMP->pt_suiv;
    }

    free(maillonTMP);
    free(o->tete);
    free(o);
}

/**
 * Centre de gravité d'un objet 3d
 *
 * @param o objet dont on veut le centre de gravité
 * @return le centre de gravité
 */
t_point3d *centreGraviteObjet3d_BH(t_objet3d *o) {
    //Récupère les centres de gravité de tous les triangles et on les ajoute
    int i = 0; //Nb triangles
    double x = 0, y = 0, z = 0;
    t_maillon *maillonTMP = o->tete;

    while (maillonTMP != NULL) {
        t_point3d *point3d = centreGraviteTriangle3d(maillonTMP->face);
        x += point3d->xyzt[0];
        y += point3d->xyzt[1];
        z += point3d->xyzt[2];
        free(point3d);
        maillonTMP = maillonTMP->pt_suiv;
        ++i;
    }

    return definirPoint3d(x / i, y / i, z / i);
}

/**
 * On parcours l'objet pour dessiner chaque triangle
 *
 * @version 1 peintre
 * @param surface
 * @param pt_objet
 * @param camera
 */
void dessinerObjet3d_BH(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera) {
    t_maillon *maillonTMP = pt_objet->tete;

    if (maillonTMP != NULL) {
        //Trier liste
        if (!pt_objet->est_trie) mergeSortZ(&maillonTMP);

        while (maillonTMP->pt_suiv != NULL) {
            remplirTriangle3d(surface, maillonTMP->face, maillonTMP->couleur, camera->largeur, camera->hauteur,
                              camera->distance_ecran);
            maillonTMP = maillonTMP->pt_suiv;
        }
    }
}

/**
 * Pour chaque maillon appliquer la translation
 *
 * @param pt_objet
 * @param vecteur
 */
void translationObjet3d_BH(t_objet3d *pt_objet, t_point3d *vecteur) {
    //Création de la matrice
    double matTranslation[4][4];
    matrice_translation(vecteur, matTranslation);
    transformationObjet3d(pt_objet, matTranslation);
}

/**
 * Applique une rotation à un objet 3d
 *
 * @param pt_objet
 * @param centre
 * @param degreX
 * @param degreY
 * @param degreZ
 */
void rotationObjet3d_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {
    //Création de la matrice de rotation
    double a = cos(degreX), b = sin(degreX), c = cos(degreY), d = sin(degreY), e = cos(degreZ), f = sin(degreZ);
    double matRotation[4][4] = {{c * e,                (-c) * f,             d,        0},
                                {b * d * e + a * f,    -(b * d * f) + a * e, -(b * c), 0},
                                {-(a * d * e) + b * f, a * d * f + b * e,    a * c,    0},
                                {0,                    0,                    0,        1}};
    translationObjet3d(pt_objet, ORIGIN);
    transformationObjet3d(pt_objet, matRotation);
    translationObjet3d(pt_objet, centre);
}

/**
 * Applique une matrice de transformation à un objet
 *
 * @param pt_objet
 * @param mat
 */
void transformationObjet3d_BH(t_objet3d *pt_objet, double mat[4][4]) {
    t_maillon *maillonTMP = pt_objet->tete;

    while (maillonTMP != NULL) {
        transformationTriangle3d(maillonTMP->face, mat);
        maillonTMP = maillonTMP->pt_suiv;
    }
}

/**
 * Fonction qui permet de trier un objet
 *
 * @param objet3d objet à trier
 */
void sortObjet3d(t_objet3d * objet3d) {
    mergeSortZ(&objet3d->tete);
}

/**
 * MergeSort pour pouvoir trier la liste en fonction des z_moyens
 *
 * @param pMaillon le pointeur sur la liste à trier
 */
void mergeSortZ(t_maillon **pMaillon) {
    //Création des pointeurs temporaires
    t_maillon *head = *pMaillon;
    t_maillon *a;
    t_maillon *b;

    //Si la liste est vide ou ne contient qu'un seul élémet -> On quitte
    if (head != NULL) {
        if (head->pt_suiv != NULL) {
            //Divise la liste en 2
            frontBackSplit(head, &a, &b);

            //Tri récursif de ces deux parties
            mergeSortZ(&a);
            mergeSortZ(&b);

            //On fusionne les deux listes triées
            *pMaillon = sortedMergeZ(a, b);
        }
    }
}

/**
 * Permet de diviser une liste en deux
 * Si il a un nombre impair de maillons -> dans la première partie
 * Méthode des pointeurs fast and slow
 *
 * @param source la liste a trier
 * @param frontRef pointeur sur la première partie
 * @param backRef pointeur sur la seconde partie
 */
void frontBackSplit(t_maillon *source, t_maillon **frontRef, t_maillon **backRef) {
    t_maillon *fast;
    t_maillon *slow;

    //Si la liste fait moins de 2 maillons
    if (source == NULL || source->pt_suiv == NULL) {
        //On met la liste dans la tête et on renvoie NULL dans la deuxième liste
        *frontRef = source;
        *backRef = NULL;
    } else {
        //Le pointeur fast va deux fois plus vite que le pointeur slow donc lorsqu'il arrive à la fin de la liste
        //l'autre ne sera qu'au milieu de celle-ci
        slow = source;
        fast = source->pt_suiv;

        while (fast != NULL) {
            fast = fast->pt_suiv;
            //Si celui-ci n'est pas NULL -> pas à la fin de la liste on peut avancer
            if (fast != NULL) {
                //On peut donc avancer slow ici (pour pouvoir avoir le cas des listes de longueur impaire)
                slow = slow->pt_suiv;
                fast = fast->pt_suiv;
            }
        }
        //Donc slow est au milieu de la liste
        *frontRef = source;
        *backRef = slow->pt_suiv;
        //Divise la liste en deux :
        slow->pt_suiv = NULL;
    }
}

/**
 * Fusionne deux listes triées
 * /!\ Fusion récursive : changer pour itérative ?
 *
 * @param a liste 1
 * @param b liste 2
 * @return une liste triée dans le bon ordre
 */
t_maillon *sortedMergeZ(t_maillon *a, t_maillon *b) {
    t_maillon *result = NULL;

    //Cas de bases
    if (a == NULL) {
        result = b;
    } else if (b == NULL) {
        result = a;
    } else {
        //Ici on vérifie l'ordre des données
        if (zmoyen(a->face) <= zmoyen(b->face)) {
            result = a;
            //Récursion
            result->pt_suiv = sortedMergeZ(a->pt_suiv, b);
        } else {
            result = b;
            //Récursion
            result->pt_suiv = sortedMergeZ(a, b->pt_suiv);
        }
    }
    return result;
}

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;

enum couleur { vide = 0,rouge, jaune };
typedef vector <vector < couleur>>  Grille;

/*--- Start class jeu ---*/
class jeu
{
public:
    jeu(size_t taille = 8 );
    bool jouer (size_t, couleur);
    couleur gagnant() const ;
    bool fini(couleur&) const;
    void affiche();
    size_t get_taille() const
    {
        return grille.size();
    }
    void init(size_t t)
    {
        grille.clear(); //vider du vector , and resize vector a 0
        grille.resize(t, vector<couleur>(t,vide) );
    }
protected :
    Grille grille;
};
jeu::jeu(size_t taille):grille (taille, vector<couleur>(taille,vide))
{}//Grille est comme a une matrice[taille][taille] de type couleur
//Start Jeu::jouer
bool jeu::jouer(unsigned int nc,couleur col)
{
    // Si le numero de colonne est supérieur à la taille ==> le coupe n.est pas valide
    if (nc >= get_taille())
    {
        return false;
    }
    // Si la colonne est pleine ==> le coup n'est pas valide :
    if (grille[0][nc] != vide)
    {
        return false;
    }

    // On parcourt la colonne en partant du bas jusqu'a trouver une case vide */
    size_t ligne(get_taille() - 1);
    while (grille[ligne][nc] != vide)
    {
        --ligne;
    }

    // On remplit la case vide trouvee
    grille[ligne][nc] = col;
    return true;
}
/*---- End jeu::jouer ----*/

/* --- Start jeu :: gagnant() ----*/
couleur jeu :: gagnant() const
{
    //Start test ligne
    for(int i = 0 ; i < get_taille(); i++ )
    {
        for(int j=0 ; j< get_taille()-3; j++)
        {
            couleur ver = grille[i][j];
            if(ver!=vide)  //si la case n'est pas vide vérifier est-ce qu'il y a gagnant
            {
                if(ver == grille[i][j+ 1] && ver == grille[i][j + 2 ] && ver ==grille[i][j+3])  //Verification ligne
                {
                    return ver ;
                }

            }

        }
    }
    //start test Colonne
    for(int i = 0 ; i < get_taille()-3; i++ )
    {
        for(int j=0 ; j< get_taille(); j++)
        {
            couleur ver = grille[i][j];
            if(ver!=vide)
            {
                if(ver == grille[i+1][j] && ver == grille[i+2][j] && ver ==grille[i+3][j])  //Verification colonne
                {
                    return ver ;
                }

            }

        }
    }
    //Start test diagonal : verification diagonal vers right
    for(int i = 0 ; i <get_taille()-3; i++ )
    {
        for(int j=3 ; j<get_taille(); j++)
        {
            couleur ver = grille[i][j];
            if(ver!=vide)
            {
                if(ver == grille[i+1][j-1] && ver == grille[i+2][j-2] && ver ==grille[i+3][j-3])
                {
                    return ver ;
                }

            }
        }
    }
    //Start test diagonal  : verification diagonal to left
    for(int i = 3 ; i <get_taille(); i++ )
    {
        for(int j=0 ; j<get_taille()-3; j++)
        {
            couleur ver = grille[i][j];
            if(ver!=vide)
            {
                if(ver == grille[i-1][j+1] && ver == grille[i-2][j+2] && ver ==grille[i-3][j+3])
                {
                    return ver ;
                }
            }
        }
    }
}
/*---- End jeu :: gagnant() -----*/

/*----Start jeu :: affiche()  --- */
void jeu:: affiche()
{
    cout << endl;
    for(int i =0 ; i <get_taille() ; i++ )
    {
        cout << " |";
        //for( kase : grille[i])
        for(int j= 0 ; j<get_taille(); j++)
        {
            if (grille[i][j] == vide)
            {
                cout << ' ';
            }
            else if (grille[i][j] == rouge)
            {
                cout << 'O';
            }
            else
            {
                cout << 'X';
            }
            cout << "|";
        }
        cout << endl;
    }

    cout << '_';
    for(size_t i= 0; i <= get_taille() -1 ; ++i)
    {
        cout << "_" << i;
    }
    cout << "_";

    cout << endl << endl;
}

/*End jeu :: affiche() */

/*----End Class jeu ---*/

/*----Start class joueur ---*/
class joueur
{
public:
    joueur(couleur c, string n )
    {
        col=c;
        nom=n;
    }
    ~joueur();
    virtual jouer (jeu&) = 0 ;
    couleur getCol()
    {
        return col;
    }
    string getNom()
    {
        return nom;
    }

protected:
    couleur col;
    string nom;
};
/*----End class joueur ---*/

/*---- Start humain class --- */
class humain: public joueur
{
public:
    humain(couleur c=rouge,string name= "player") : joueur(c,name) {}

    jouer(jeu& j);
};

humain::jouer(jeu& j)
{
    string s= " ";
    int n=-1;
    do
    {
        cout<<"Tour de "<< getNom()<<" -> Entez le numero de colonne a jouer ( 0 --> "<<j.get_taille()-1<<" ) :  ";
        /*dans la partie suivante de code si on utilise une variable entière on va avoir un problème
         si l'utilisateur tape un caractère ou symbole ==> le programme s'arrête ! pour résoudre ce problème
          j'ai essayé de prendre une caractères et de le converter le vers un entier .  */

        cin>>s;
        if(s.length() < 3 )
        {
            n=stoi(s); //convertir string to int
        }
    }
    while(!j.jouer(n,col));   //si la position n'est valide il faut redemander de rentrer le numéro de colonne
}

/*---- end humain class --- */

/*---- Start ordi class --- */
class ordi: public joueur
{
public:
    ordi(couleur c=jaune,string name= "Ordinateur") : joueur(c,name) {}
    jouer(jeu& j);
};
ordi::jouer(jeu& j)
{
    int r=-1;
    cout<<"Tour Ordinateur --> " <<endl;
    do
    {
        r=rand() % j.get_taille() ; //l'ordinateur joue aléatoirement ( entre 0  et taille de grille - 1 )
    }
    while(! j.jouer(r,col));
}
/*---- End humain class --- */

/*----- Start class partie --- */
class partie
{
public:

    partie(joueur *j1,joueur *j2,size_t T )
    {
        players[0]=j1;
        players[1]=j2;
        j.init(T);
    }
    void lancer();
    void vider();

protected:
    joueur  *players[2];
    jeu j;
};
void partie::lancer()
{
    unsigned int tr=0;
    while(tr < (j.get_taille() * j.get_taille() ) && j.gagnant() == vide  )  //non pleine est le colour de gagnant !=vide
    {
        if(tr%2==0)
        {
            players[1]->jouer(j);
        }
        else
        {
            players[0]->jouer(j);
        }
        tr++;
        j.affiche();
    }
    if(j.gagnant()!=vide)
    {
        string gn="";
        cout << "Le nombre des tours est : " <<tr<<endl;
        for(int i=0; i<2; i++)
        {
            if(j.gagnant() == players[i]->getCol())
            {
                if(players[i]->getNom() == "Ordinateur")
                    gn="OOPS! ";
                else
                    gn="Felicitation! ";
                cout<< gn <<"Le gangant est : "<<players[i]->getNom()<<endl;
            }
        }
    }
    else
    {
        cout<<"La partie terminee sans gagnant !!"<<endl;
    }
}
void partie::vider()
{
    delete [] players;
}
/*---End class partie ---*/

int main()
{
    int choix;//Mode de jeu ( 2 jouers ou avec Ordinateur )
    size_t taille = -1 ; //taille de grille
    string nomj1,nomj2;
    do
    {
        cout<<"Donnez la taille de grille ( 6 --> 15 ) : " ;
        cin>>taille;
    }
    while(taille < 6  || taille > 15 );  //j'ai choisi que la taille doit être supérieur à 5 est inférieure à 10
    do
    {
        cout <<"Bienvenue ! \nChoisi le mode de jeu  : " <<endl;
        cout<<"\t1: Avec Ordinateur \n\t2: 2 Joueurs "<<endl<<"--> ";
        cin>>choix;
    }
    while(choix!=1 && choix !=2);
    if(choix == 1)
    {
        cout<<"Nom de Joueur : ";
        cin>>nomj1;
        cout << endl;
        partie p ( new ordi(rouge), new humain(jaune,nomj1), taille );
        p.lancer();
        p.vider();
    }
    else
    {
        cout<<"Nom Joueur 1 : ";
        cin>>nomj1;
        cout << endl;
        cout<<"Nom Joueur 2 : ";
        cin>>nomj2;
        cout <<endl;

        partie p ( new humain(rouge,nomj2), new humain(jaune,nomj1), taille ); /*J'ai commencé par le nom2 pour que le jouer 1 commencer
                                                       parce-que la ne méthode lancer que programmer que le joueur commence avant l'ordi*/
        p.lancer();
        p.vider();
    }


    return 0;
}

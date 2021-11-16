#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdlib.h>

#include "ContinuousAdaptativeWalker.h"

using namespace std;

ContinuousAdaptativeWalker::ContinuousAdaptativeWalker(){
    m_name="a simple walker";
    m_pos=1.0;
    m_D=1.0; //the default is the D=1.0 diffusive constant
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

ContinuousAdaptativeWalker::ContinuousAdaptativeWalker(string name, double pos,double D,int seed): m_name(name),m_pos(pos),m_D(D),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

ContinuousAdaptativeWalker::~ContinuousAdaptativeWalker()
{
    gsl_rng_free(m_rng);
}

void ContinuousAdaptativeWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "diffusive coefficient : " << m_D << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;
}

//getters
double ContinuousAdaptativeWalker::get_pos() const {
    return m_pos;
}

double ContinuousAdaptativeWalker::get_D() const {
    return m_D;
}

double ContinuousAdaptativeWalker::get_max() const {
    return m_max;
}

double ContinuousAdaptativeWalker::get_min() const {
    return m_min;
}

long ContinuousAdaptativeWalker::get_lifetime() const {
    return m_lifetime;
}

int ContinuousAdaptativeWalker::get_seed() const {
    return m_seed;
}

//setters
void ContinuousAdaptativeWalker::set_pos(double pos){
     m_pos=pos;
}

void ContinuousAdaptativeWalker::set_D(double D){
     m_D=D;
}

void  ContinuousAdaptativeWalker::set_max(double max){
    m_max=max;
}

void  ContinuousAdaptativeWalker::set_min(double min){
    m_min=min;
}

void  ContinuousAdaptativeWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  ContinuousAdaptativeWalker::set_seed(long seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void ContinuousAdaptativeWalker::move(int verbose){
    // petit probleme si on a deux barieres
    //il faut checker qu'on puisse passer des parametres dans la fonction move meme si elle est virtuelle
    //on prent la ref sigma^2=2Dt

    double sigma_min=0.0001; // on ne fixe pas de sigma max pour l'instant, on verra les resultatsv plus tard
    double sigma_tmp = fabs(m_pos)/2;

    if (sigma_tmp<sigma_min){
        sigma_tmp=sigma_min;
    }

    double m = gsl_ran_gaussian(m_rng, sigma_tmp); //the basic move is a gaussian step of sigma prop to the closest boundary
    m_pos=m_pos+((double) m);
    //on change aussi la maniere de compter le temps
    m_lifetime+=sigma_tmp*sigma_tmp/(2*m_D);
    if(m_pos>m_max){
        m_max=m_pos;
    }
    else if(m_min>m_pos){
        m_min=m_pos;
    }
    if(verbose==1){
        cout << "position : " << m_pos << endl;
    }
}

//other funtions
void ContinuousAdaptativeWalker::move_til_death(int verbose){
    while(isAlive()){
        move(verbose);
    }
}

bool ContinuousAdaptativeWalker::isAlive() const
{//cela nous permet de prendre la convention crossing en compte, de toute manière on ne tombera jamais sur zero pile
    return (m_pos>=0); 
}

int ContinuousAdaptativeWalker::move_fixed_max(double borne)
{
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0;
    }
    return 1;
}

void  ContinuousAdaptativeWalker::move_fixed_time(long time)
{
    for(long i =0;i<time;i++){
        move();
    }
}


double ContinuousAdaptativeWalker::split_prob(double s0, double s1,double s2, int const n)
{
    int i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le #include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        m_min=m_pos;
        while(m_pos>=s1 && m_pos<=s2){ //attentionn aux inegalités ici
            //cout << "in here" << endl;
            move(0);
        }
        result[i]=(int)(m_pos>s2);
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}

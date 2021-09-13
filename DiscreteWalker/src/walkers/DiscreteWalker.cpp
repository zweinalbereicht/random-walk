#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <string>
#include <vector>

//#include "../../pcg-cpp-0.98/include/pcg_test.h"


#include "DiscreteWalker.h"
#include "BiasedWalker.h"
#include "RiemannWalker.h"
#include "SATWWalker.h"


using namespace std;


DiscreteWalker::DiscreteWalker(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

DiscreteWalker::DiscreteWalker(string name, long pos,int seed): m_name(name),m_pos(pos),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,seed);
}

DiscreteWalker::~DiscreteWalker()
{
    gsl_rng_free(m_rng);
}

void
DiscreteWalker::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;
}

//getters
long DiscreteWalker::get_pos() const {
    return m_pos;
}

long DiscreteWalker::get_max() const {
    return m_max;
}

long DiscreteWalker::get_min() const {
    return m_min;
}

long DiscreteWalker::get_lifetime() const {
    return m_lifetime;
}

int DiscreteWalker::get_seed() const {
    return m_seed;
}

gsl_rng* DiscreteWalker::get_rng() const {
    return m_rng;
}

//setters
void DiscreteWalker::set_pos(long pos){
     m_pos=pos;
}

void DiscreteWalker::set_random_pos(long N){
     m_pos=1+gsl_rng_uniform_int(m_rng,N-1);
}

void  DiscreteWalker::set_max(long max){
    m_max=max;
}

void  DiscreteWalker::set_min(long min){
    m_min=min;
}

void  DiscreteWalker::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  DiscreteWalker::set_seed(long seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void
DiscreteWalker::move(int verbose){
    int m = gsl_ran_bernoulli(m_rng, 0.5); //the basic move is +1 or -1 with equal probability
    m_pos+=1-2*m;
    m_lifetime+=1;
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
void
DiscreteWalker::move_til_death(int verbose){
    while(isAlive()){
        move(verbose);
    }
}

void
DiscreteWalker::move_til_death_bounded(long N,int verbose)
{
    while(isAlive()){
        move(verbose);
        if (m_pos>=N){
            //cout << "old position : " << m_pos << endl;
            m_pos=(long) m_pos%(N); //encore un probleme à corriger ici
            //cout << "relocating position : " << m_pos << endl;
        }
        else if (m_pos<0)
        {
            //cout << "old position : " << m_pos << endl;
            m_pos = (long)((((N)-((-m_pos)%(N))))%N);
            //cout << "relocating position : " << m_pos << endl;
        }
    }
}

long
DiscreteWalker::move_til_death_bounded_record_territory(long N,int verbose)
{
    vector<int> territory(N); //the territory on which we walk
    long i=0;
    for(;i<N;i++)
        territory[i]=0;

    while(isAlive()){
        move(verbose);
        if (m_pos>=N){
            //cout << "old position : " << m_pos << endl;
            m_pos=(long) m_pos%(N); //encore un probleme à corriger ici
            //cout << "relocating position : " << m_pos << endl;
        }
        else if (m_pos<0)
        {
            //cout << "old position : " << m_pos << endl;
            m_pos = (long)((((N)-((-m_pos)%(N))))%N);
            //cout << "relocating position : " << m_pos << endl;
        }
        territory[m_pos]+=1;
    }

    long result=0; // parcourons le tableau de sortie
    for(i=0;i<N;i++)
        if(territory[i]>0)
            result+=1;

    return result;
}

bool DiscreteWalker::isAlive() const
{
    return (m_pos>0); //strict inequality here
}

int DiscreteWalker::move_fixed_max(long borne)
{
    m_max = m_pos;
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0; //if success
    }
    return 1;
}

void  DiscreteWalker::move_fixed_time(long time)
{
    for(long i =0;i<time;i++){
        move();
    }
}


double DiscreteWalker::split_prob(long s0, long s1,long s2, long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le #include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        m_min=m_pos;
        while(m_pos>s1 && m_pos<s2){ //attention aux inegalités ici, c'est strict, on s'arrete lorsque l'on touche
            move(0);
        }
        result[i]=(int)(m_pos>=s2); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    //cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}

double DiscreteWalker::max_prob(long s0, long s1,long const n)
{
    long i;
    //int result[n];
    vector<int> result(n); //encore une autre version, ne pas oublier le #include <vector> en haut sinon ça ne marche pas.
    //result=(int*) malloc(sizeof(int)*n); old C version
    for(i=0;i<n;i++){
        m_lifetime=0;
        m_pos=s0;
        m_max=m_pos;
        m_min=m_pos;
        while(m_pos>0 && m_pos<=s1){ //attention aux inegalités ici, c'est strict, on s'arrete lorsque l'on touche 0 ou que l'on depasse strictement s1
            move(0);
        }
        result[i]=(int)(m_max==s1); //same thing here, watch the strictness
    }
    double m=0;
    for(i=0;i<n;i++){
        m+=result[i];
    }
    //cout << m << endl;
    //free(result); old C version, using fixed size declaration in the above
    return (double)(m/n);
}

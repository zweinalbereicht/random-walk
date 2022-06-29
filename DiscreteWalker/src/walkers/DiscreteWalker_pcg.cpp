#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <stdlib.h>

#include "pcg_random_walk.h"


#include "DiscreteWalker_pcg.h"

using namespace std;


DiscreteWalker_pcg::DiscreteWalker_pcg(){
    m_name="a simple walker";
    m_pos=1;
    m_max=m_pos;
    m_min=m_pos;
    m_lifetime=0;
    m_seed=1;
    m_rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(m_rng,m_seed);
}

DiscreteWalker_pcg::DiscreteWalker_pcg(string name, long pos,int seed): m_name(name),m_pos(pos),m_max(pos), m_min(pos), m_seed(seed),m_lifetime(0)
{
    m_rng = gsl_rng_alloc(gsl_rng_pcg);
    gsl_rng_set(m_rng,seed);
}

DiscreteWalker_pcg::~DiscreteWalker_pcg()
{
    gsl_rng_free(m_rng);
}

void DiscreteWalker_pcg::print_details() const
{
    cout << "name : " << m_name << endl;
    cout << "position : " << m_pos << endl;
    cout << "maximum : " << m_max << endl;
    cout << "minimum : " << m_min << endl;
    cout << "age : " << m_lifetime << endl;
    cout << "seed : " << m_seed << endl;
}

//getters
long DiscreteWalker_pcg::get_pos() const {
    return m_pos;
}

long DiscreteWalker_pcg::get_max() const {
    return m_max;
}

long DiscreteWalker_pcg::get_min() const {
    return m_min;
}

long DiscreteWalker_pcg::get_lifetime() const {
    return m_lifetime;
}

int DiscreteWalker_pcg::get_seed() const {
    return m_seed;
}

//setters
void DiscreteWalker_pcg::set_pos(long pos){
     m_pos=pos;
}

void DiscreteWalker_pcg::set_random_pos(long N){
     m_pos=1+gsl_rng_uniform_int(m_rng,N-1);
}

void  DiscreteWalker_pcg::set_max(long max){
    m_max=max;
}

void  DiscreteWalker_pcg::set_min(long min){
    m_min=min;
}

void  DiscreteWalker_pcg::set_lifetime(long lifetime){
    m_lifetime=lifetime;
}

void  DiscreteWalker_pcg::set_seed(long seed){
    m_seed=seed;
    gsl_rng_set(m_rng,m_seed);
}

//the basic move function
void DiscreteWalker_pcg::move(int verbose){
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
void DiscreteWalker_pcg::move_til_death(int verbose){
    while(isAlive()){
        move(verbose);
    }
}

void DiscreteWalker_pcg::move_til_death_bounded(long N,int verbose)
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

bool DiscreteWalker_pcg::isAlive() const
{
    return (m_pos>0); //strict inequality here
}

int DiscreteWalker_pcg::move_fixed_max(long borne)
{
    while(isAlive() && m_pos<=borne){
        move();
    }
    if (!isAlive() && m_max==borne){
        return 0; //if success
    }
    else{
        return 1;
    }
}
int  DiscreteWalker_pcg::move_fixed_time(long time)
{

    while(isAlive() && m_lifetime<=time){
        move();
    }
    if (!isAlive() && m_lifetime==time){
        return 0; //if success
    }
    else{
        return 1;
    }
}


double DiscreteWalker_pcg::split_prob(long s0, long s1,long s2, long const n)
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

double DiscreteWalker_pcg::max_prob(long s0, long s1,long const n)
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

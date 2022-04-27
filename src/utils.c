#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>

// génération d'un entier mpz aléatoire comprs entre 0 et max-1 inclu.
void mpz_alea(mpz_t a, mpz_t max){
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    mpz_urandomm(a,state,max);
    gmp_randclear(state);
}

// permet de stocker la représentation binaire de n dans le tableau nb utilisable pour square et multiply
void mpz_bin(mpz_t n, int *nb){
    int size = mpz_sizeinbase(n,2);
    mpz_t q;
    mpz_init(q);
    mpz_set(q,n);
    while(size != 0){
        nb[size-1] = mpz_fdiv_q_ui(q,q,2);
        size--;
    }
    mpz_clear(q);
}

// calcule a puissance exp modulo n, nb = représentation binaire de exp, stockage resultat dans resul
void sq_mul(mpz_t a, mpz_t exp, mpz_t n, int *nb, mpz_t resul){
    mpz_set(resul,a);
    for(int i = 1; i<mpz_sizeinbase(exp,2); i++){
        mpz_mul(resul,resul,resul);
        mpz_mod (resul, resul, n);
        if(nb[i]){
            mpz_mul(resul,resul,a); 
            mpz_mod (resul, resul, n);}
    }
}


int test_f(mpz_t n, mpz_t a, int *nb){
    mpz_t un, resul;
    mpz_init_set_ui(un,1);
    mpz_init(resul);
    sq_mul(a,n,n,nb,resul);
    int p = mpz_congruent_p(resul,un,n);
    mpz_clear(un);
    mpz_clear(resul);
    return p;
}

int test_fermat(int k, mpz_t n){
    int *nb ;
    nb = malloc(mpz_sizeinbase(n,2)*sizeof(int));
    mpz_t n2;
    mpz_init_set(n2,n);
    mpz_sub_ui(n2,n,1);
    mpz_bin(n2,nb);
    mpz_clear(n2);
    int cpt = 0;
    for(int i =0; i<k; i++){
        mpz_t a;
        mpz_init(a);
        mpz_alea(a,n);
        if(mpz_cmp_ui(a,1)<=0){mpz_add_ui(a,a,2);} //alea compris entre 1 et n-1
        if(mpz_cmp(a,n)==0){mpz_sub_ui(a,a,2);} //alea compris entre 1 et n-1
        if(test_f(n,a,nb) == 1){
            cpt++; //premier
        }
        mpz_clear(a);
    }
    free(nb);
    return cpt; //composé
}

// détermine décomposition n-1 = t*2^s ; n,t impairs
// limite : n en entrée doit impérativement être impair 
int decomp(mpz_t n, mpz_t t){
    mpz_t n2,q,res;
    int s;
    s = 0;
    mpz_init_set(n2,n);
    mpz_sub_ui(n2,n,1);
    mpz_init(q);
    mpz_init(res);
    while(!mpz_mod_ui(res,q,2)){
        mpz_fdiv_q_ui(q,n2,2);
        mpz_set(n2,q);
        s++;
    }
    mpz_set(t,q);
    mpz_clear(n2);
    mpz_clear(q);
    mpz_clear(res);
    return s;
}

// algorithme de miller-rabin, renvoie cpt != 0 si composé, cpt=0 pour nombre premier probable
int miller_rabin(mpz_t n, int k){
    mpz_t t;
    mpz_t y, un, mun;
    mpz_init_set_ui(un,1);
    mpz_init(mun);
    mpz_neg(mun,un);
    mpz_init(t);
    mpz_init(y);
    int s = decomp(n,t);
    if(!s){
        printf("\nDécomposition de n impossible.\n");
        exit(EXIT_FAILURE);
    }
    
    int *nb_mr;
    nb_mr = malloc(sizeof(int)*mpz_sizeinbase(t,2));
    mpz_bin(t,nb_mr);

    int cpt=0;
    int tem=0;

    for(int i=0; i<k; i++){
        mpz_t a;
        mpz_init(a);
        mpz_alea(a,n);
            if(mpz_cmp_ui(a,1)<=0){mpz_add_ui(a,a,1);} //alea compris entre 0 et n
            if(mpz_cmp(a,n)==0){mpz_sub_ui(a,a,1);} //alea compris entre 0 et n
        sq_mul(a,t,n,nb_mr,y);
        mpz_clear(a);

        if(!mpz_congruent_p(y,un,n) && !mpz_congruent_p(y,mun,n)){
            for(int j=0; j<(s-1); j++){
                mpz_mul(y,y,y);
                if(mpz_congruent_p(y,un,n)){
                    cpt++;
                }
                if(mpz_congruent_p(y,mun,n)){
                    tem=1;
                    break;
                }
            } 
            if(tem){break;}
            cpt++;
        }
     //premier
    }
    mpz_clear(t);
    mpz_clear(y);
    mpz_clear(un);
    mpz_clear(mun);
    free(nb_mr);

return cpt;
}

void ex_time(clock_t begin, clock_t end){
    double ex_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTemps d'exécution du programme : %f s.\n",ex_time);
}
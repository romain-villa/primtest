#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include "utils.h"

#define IT_MIN 10 // définition nombre d'itérations k minimal

int main(int argc, char** argv){
    clock_t begin = clock();
    // vérification du bon nombre d'arguments
    if(argc != 3) 
    {
        printf("Nombre d'arguments invalide : veuillez saisir respectivement n puis k\n");
        exit(EXIT_FAILURE);
    }
    
    char* num = argv[1]; //recupération nombre n dans chaine caractère
    int k = atoi(argv[2]); // k itérations

    // nombre d'itérations minimal fixé à 10 (arbitraire)
    if(k < IT_MIN) 
    {
        printf("Nombre d'itération k invalide, il doit etre superieur ou egal à %d\n",IT_MIN);
        exit(EXIT_FAILURE);
    }

    mpz_t n;
    mpz_init(n);

    // vérification de la validité du nombre saisi et conversion de la chaine de caractère en entier exploitable
    if (mpz_set_str(n, num, 10)) 
    {
        printf("Nombre n invalide\n");
        mpz_clear(n);
        exit(EXIT_FAILURE);
    }
    
    printf("\n >>>>>>>>>>>TEST DE FERMAT<<<<<<<<<<\n");
    
    if(mpz_cmp_ui(n,4)<0){
        printf("\nNombre saisi inférieur a 4, le test de Fermat ne peut pas être exécuté.\n");
        goto MILLER_RABIN;
    }

    int cpt = test_fermat(k,n);
    
    if((k-cpt)!=0){
        gmp_printf("\nLe nombre %Zd est composé.\n",n);}
        else {
            gmp_printf("\nLe nombre %Zd est probablement premier.\n",n);}

    MILLER_RABIN: printf("\n >>>>>>>TEST DE MILLER-RABIN<<<<<<<<\n");
    
    // vérifie la parité, indispensable pour l'algorithme de Miller-Rabin
    if(mpz_divisible_ui_p(n,2)){
        printf("\nNombre saisi pair, le test de Miller-Rabin ne peut pas être exécuté.\n");
        mpz_clear(n);
        exit(EXIT_SUCCESS);
        }

    cpt = miller_rabin(n,k);

    if(!cpt){
        gmp_printf("\nLe nombre %Zd est probablement premier.\n",n);}
        else {
            gmp_printf("\nLe nombre %Zd est composé.\n",n);}

    mpz_clear(n);
    clock_t end = clock();
    ex_time(begin,end);

exit(EXIT_SUCCESS);
}

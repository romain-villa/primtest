Romain VILLA et Massina AMMAD - UVSQ

[GitHub repository](https://github.com/romain-villa/primtest)

# TEST DE PRIMALITE

Ce programme est l'implémentation de deux tests de primalité probabilistes à l'aide de la librairie GNU Multiple Precision Arithmetic. Il s'agit des deux algorithmes suivants : 
- Le test de Fermat 
- Le test de Miller-Rabin

Un algorithme d'exponentiation modulaire est également implémenté :
- *Square and multiply*

Tout l'intérêt du programme est de pouvoir tester la primalité de grands nombres (quelques milliers de bits). Un fichier ```prime.txt``` contenant des nombres premiers de 32 à 49152 bits est mis à disposition dans le répertoire ```src``` pour tester le programme.

## Installation

L'utilisateur doit disposer du compilateur GCC et avoir installé la librairie [GMP 6.2.1](https://gmplib.org/) et disposer d'une distribution UNIX.
Pour installer le programme, il faut décompresser l'archive et suivre les étapes suivantes :
 ```
~/primtest$ ./configure

~/primtest$ cd src

~/primtest/src$ make
```

## Exécution

```
~/primtest/src$ ./primtest n k
```
*avec n le nombre à tester et k le nombre d'itérations des algorithmmes*

### Contraintes

> n et k doivent obligatoirement être fournis.

- contraintes sur n :

Pour que le test de Fermat s'exécute, n doit être supérieur à 4 tandis que pour le test de Miller-Rabin, n doit nécessairement être impair.
Ces deux contraintes n'empêchent pas l'exécution du programme car elles se compensent selon l'algorithme.

- contraintes sur k :

Par défaut, le nombre k d'itérations doit être supérieur ou égal à 10.
Ce nombre peut être modifié dans le fichier ```main.c``` en changeant la définition de la macro ```ÌT_MIN```.

## Fonctionnement

### Test de Fermat

Ce test, basé sur le Petit théorème de Fermat, vise à vérifier si un nombre aléatoire a porté à la puissance n-1 modulo n est congru à 1 ou non. S'il ne l'est pas, on peut conclure que n est composé avec certitude. Dans le cas contraire, le test renvoie que n est premier avec une probabilité estimée a 1/2. Ainsi, pour k itérations, la probabilité que le test se trompe s'élève à 1/ 2^k^.



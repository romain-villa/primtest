Romain VILLA et Massina AMMAD - UVSQ
[GitHub repository](https://github.com/romain-villa/primtest)

# TEST DE PRIMALITE

Ce programme est l'implémentation de deux tests de primalité probabilistes à l'aide de la librairie GNU Multiple Precision Arithmetic. Il s'agit des deux algorithmes suivants : 
- Le test de Fermat 
- Le test de Miller-Rabin
Un algorithme d'exponentiation modulaire est également implémenté :
- *Square and multiply*

Tout l'intérêt du programme est de pouvoir tester la primalité de grands nombres (quelques milliers de bits). Un fichier ```prime.txt``` contenant des nombres premiers de 32 à 49152 bits est mis à disposition pour tester le programme.

## Installation

L'utilisateur doit disposer du compilateur GCC et avoir installé la librairie [GMP 6.2.1](https://gmplib.org/).
Pour installer le programme, il faut décompresser l'archive et suivre les étapes suivantes :
> ```./configure```
> ```cd src```
> ```make```
Pour l'éxécuter:
> ```./primtest n k```
*avec n le nombre à tester et k le nombre d'itérations des algorithmmes*

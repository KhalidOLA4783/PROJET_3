#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n ;// n est un compteur mais global.
struct Contact {
char name[200] ;
char email_address[50];
char phone_number[16];
};// D�claration de  la structure de contact .

struct Contact contacts[20];  // contacts[20] une variable  struct contact global .

int ajouter (char name[200] , char email_address[50]  ,char phone_number[16]){
struct Contact p ;// p est juste une variable struct contact locale
if(n>=20)  // si le compteur n est superieur ou egale a 20 (le 20 au niveau de la valeur contacts)
    return -1 ;//alors le programme retourne -1 .
strcpy(p.name,name);
strcpy(p.phone_number,phone_number);
strcpy(p.email_address,email_address) ;

/* Les trois strcpy permet de copier le nom , le  numero de telephone , l'adresse dans les variables de p .*/
contacts[n++] = p ;      //j'ai affecter la valeur de contacts a p .
}

void afficher(){
int i ;

FILE *fichier = fopen("inexistant.txt", "w");
if (fichier == NULL) {
printf("Erreur d'ouverture du fichier\n");
}

else {
    for( i = 0 ; i<n ; i++){
    fprintf(fichier," CONTACT[%d] : \n Name : %s ; \n Email address: %s; \n Phone Number : %s \n.  ",i+1 ,contacts[i].name,contacts[i].email_address, contacts[i].phone_number);
}
fclose(fichier);
}


}
int main(){
int n ;
printf("Hello workhaledld");
return 0 ;
}



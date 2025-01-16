#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Contacts {
char name[200] ;
char email_address[50];
char phone_number[16];
};// Declaration de  la structure de contact.

struct Contacts contact;  // contacts une variable  struct contact global.

/*-------------AJOUTER CONTACT-----------------------------------------*/
char relation_avec_point(char email_address[50])
{
int pos1 , pos2 ;
for(int i = 0 ; i<strlen(email_address) ; i++)
{
    if(email_address[i]!='@')
    {
        pos1 = pos1 + 1 ;
    }
    else
    {
        break ;
    }
}

for(int i = 0 ; i<strlen(email_address) ; i++)
{
    if(email_address[i]!='.')
    {
        pos2 = pos2 + 1 ;
    }
    else
    {
        break ;
    }
}

if(pos2 < pos1)
{
    return -1 ;
}
else
{
    return 1 ;
}

}

 char verification_des_caracters(char email_address[50])
{
int n;
for(int i = 0 ; i<strlen(email_address) ; i++)
{
    if( email_address[i] =='.' || email_address[i] == '_' || email_address[i]== '-' || email_address[i] == '@'  || isalnum(email_address[i]) )
    {
        n++ ;
    }
}
if(n==strlen(email_address))
{
    return 1 ;
}
else
    return -1 ;
}

 void Ajouter_Contacts()
     {
         FILE *F ;
         F = fopen("Contacts.txt","a");//Mode de lecture.
         fflush(stdin);
       if ( F  == NULL){
         printf("Erreur d'ouverture du fichier.\n");
        }
        else
        {
            printf("\n");
            printf("----------------------Ajout de contact----------------------\n");
            printf("\nEnter youre name---->>>>>>>>\n Name: ");
            gets(contact.name);
            fflush(stdin);
            printf("\n") ;
            printf("Enter youre email ---->>>>>>>>>\n Email : ");
            gets(contact.email_address);
            while(verification_des_caracters(contact.email_address) == -1 || strstr(contact.email_address, "@") == NULL || relation_avec_point(contact.email_address)== -1 || strstr(contact.email_address , " ") !=NULL  || strstr(contact.email_address,".com")==NULL)
            {
            printf("\n' @ ' or '.com ' or 'the number digits is lower at 16' is strictly for bidden in your email. That is why \n ") ;
            printf("\nEnter again your e-mail -->>>>>\n Email : ");
            gets(contact.email_address);
            }
            fflush(stdin);
            do{
            printf("\nEnter your Number ------>>>>\n Number : ");
            gets(contact.phone_number);
              }  while( strlen(contact.phone_number) >10 || strstr(contact.phone_number , " ") !=NULL);
            fflush(stdin);
            fprintf(F,"%s ; %s ; %s \n",contact.name,contact.email_address,contact.phone_number);
            fclose(F);
        }
    }

int main()
{ 
  int choix ; char rep[4];
    printf("Hello world!\n");
    do
    {
       system("cls");
       printf("********************************MENU*******************************\n");
       printf("1- Ajouter un nouveau contact.\n");
       printf("2- Modifier les informations d�un contact existant.\n");
       printf("3 -Rechercher un contact par son nom.\n");
       printf("4 -Supprimer un contact de la liste.\n");
       printf("5- Affichier tout les contacts.\n");
       printf("6- Quitter. \n \n");
        printf("\nEntrez Votre choix-------->>>>>\n Choix = ");
        scanf("%d",&choix);
        getchar();

    switch(choix)
    {
        case 1 : Ajouter_Contacts() ;
        break;
        case 2 : Modify();
        break;
        case 3 : Recherch();
        break;
        case 4 : Delete() ;
        break;
        case 5 : Afficher();
        break;
        case 6 : break;
        default :
        printf("Choix invalide");
        break;
    }

    printf("\n\nVouliez vous continuer------>>>>>>\n Reponse : ");
    scanf("%s",rep);
    fflush(stdin);

    }while(strcmp(rep,"oui") == 0);
return 0 ;
}


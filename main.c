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
char relation_avec_numero_de_telephone_isalpha(char phone_number[55])
{
int i ;
int n = 0;
for(i = 0 ; i<strlen(phone_number) ; i++)
{
    if(isalpha(phone_number[i])){
        n++;
    }
}
if(n == 0)
{
    return 1 ;
}
else
{
    return -1 ;
}
}

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
    if(isalnum(email_address[i])|| email_address[i] =='.' || email_address[i] == '_' || email_address[i]== '-' || email_address[i] == '@')
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
        char reponse[4];
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
            printf("\nEntrez votre nom---->>>>>>>>\n Name: ");
            gets(contact.name);
            fflush(stdin);
            printf("\n") ;
            printf("Entrez votre email ---->>>>>>>>>\n Email : ");
            gets(contact.email_address);
            while(verification_des_caracters(contact.email_address) == -1 || strstr(contact.email_address, "@") == NULL || relation_avec_point(contact.email_address)== -1 || strstr(contact.email_address , " ") !=NULL  || strstr(contact.email_address,".com")==NULL)
            {
            printf("\n' @ ' or '.com ' or 'the number digits is lower at 16' is strictly for bidden in your email. That is why \n ") ;
            printf("\nEnter again your e-mail -->>>>>\n Email : ");
            gets(contact.email_address);
            }
            fflush(stdin);
            do{
            printf("\nEntrez votre numero ------>>>>\n Number : ");
            gets(contact.phone_number);
              }  while( strlen(contact.phone_number) >10 || strstr(contact.phone_number , " ") !=NULL || relation_avec_numero_de_telephone_isalpha(contact.phone_number) == -1);
            fflush(stdin);
            printf("\n\nVoulez vous enregistrer le contact------>>>>>>\n Reponse : ");
            scanf("%s",reponse);
            if(strcmp(reponse,"oui")==0)
            {
                fprintf(F,"%s ; %s ; %s \n",contact.name,contact.email_address,contact.phone_number);
                printf("Contact enregistre avec succes.\n");
            }
            else
            {
                printf("Contact non enregistre.\n");
            }
            
            fclose(F);
        }
    }



void Modifier_Contact() {
    char email_modification[50];
    int found = 0;
    
    printf("Entrez l'email du contact à modifier: ");
    gets(email_modification);  // Demander l'email du contact à modifier
    
    FILE *F = fopen("Contacts.txt", "r+");  // Ouvrir le fichier en lecture et écriture
    if (F == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    
    FILE *temp = fopen("temp.txt", "w");  // Créer un fichier temporaire pour enregistrer les modifications
    if (temp == NULL) {
        printf("Erreur de création du fichier temporaire.\n");
        fclose(F);
        return;
    }

    while (fscanf(F, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number) != EOF) {
        if (strcmp(contact.email_address, email_modification) == 0) {
            found = 1;
            printf("Contact trouvee! Entrez les nouvelles informations.\n");

            // Modifier le nom
            printf("\nEntrez le nouveau nom---->>>>>>>>\n Name: ");
            gets(contact.name);

            // Modifier l'email (optionnel)
             printf("Entrez le nouveau email ---->>>>>>>>>\n Email : ");
            gets(contact.email_address);
            while (verification_des_caracters(contact.email_address) == -1 || strstr(contact.email_address, "@") == NULL || relation_avec_point(contact.email_address) == -1 || strstr(contact.email_address, " ") != NULL || strstr(contact.email_address, ".com") == NULL) {
                printf("L'email est invalide, try again.\n");
                 printf("Entrez le nouveau email ---->>>>>>>>>\n Email : ");
                 gets(contact.email_address);
            }

            // Modifier le numéro de téléphone
            do {
                printf("\nEntrez le nouveau numero ------>>>>\n Number : ");
                gets(contact.phone_number);
            } while (strlen(contact.phone_number) > 10 || strstr(contact.phone_number, " ") != NULL);
            
            fprintf(temp, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number);  // Sauvegarder les modifications dans le fichier temporaire
        } else {
            fprintf(temp, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number);  // Conserver le contact non modifié
        }
    }

    if (!found) {
        printf("Aucun contact trouve avec cet email.\n");
    }

    fclose(F);
    fclose(temp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove("Contacts.txt");
    rename("temp.txt", "Contacts.txt");

    printf("Modification terminee.\n");
}
void Supprimer_Contact() {
    char email_suppression[50];
    int found = 0;

    printf("Entrez l'email du contact a supprimer: ");
    gets(email_suppression);  // Demander l'email du contact à supprimer

    FILE *F = fopen("Contacts.txt", "r");  // Ouvrir le fichier en lecture
    if (F == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");  // Créer un fichier temporaire pour enregistrer les contacts restants
    if (temp == NULL) {
        printf("Erreur de creation du fichier temporaire.\n");
        fclose(F);
        return;
    }

    while (fscanf(F, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number) != EOF) {
        if (strcmp(contact.email_address, email_suppression) == 0) {
            found = 1;
            printf("Contact trouvee et supprimee.\n");
        } else {
            fprintf(temp, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number);
        }
    }

    if (!found) {
        printf("Aucun contact trouvee avec cet email.\n");
    }

    fclose(F);
    fclose(temp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove("Contacts.txt");
    rename("temp.txt", "Contacts.txt");

}

void Afficher()
{
    FILE *F ;
    F = fopen("Contacts.txt","r");
     if ( F  == NULL)
        {
        printf("Erreur d'ouverture du fichier.\n");
        }
    else
        {
          printf("\n La liste des contact est :\n\n");
    printf("Name \t\t Email adress \t\t Phone Number \n");
    do
    {
      fscanf(F,"%s ;%s ;%s \n",contact.name,contact.email_address,contact.phone_number);
      fflush(stdin);
      printf("%s\t\t",contact.name);
      printf("%s\t\t  ",contact.email_address);
      printf("%s\t\t\n",contact.phone_number);
      printf("\n");
    }while(!feof(F));
    fclose(F);
        }

}

void rechercher_contact(){

    char nom_rechercher[50];

    printf("\n");
            printf("----------------------Recherche de contact----------------------\n");
    printf("Entrez le nom du contact a rechercher: ");
    gets(nom_rechercher);  // Demander le nom du contact à rechercher-

    FILE *F = fopen("Contacts.txt", "r+");  // Ouvrir le fichier en lecture et écriture
    if (F == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    else
    {
     FILE *temp = fopen("temp.txt", "w");  // Créer un fichier temporaire pour enregistrer les modifications
    if (temp == NULL) {
        printf("Erreur de creation du fichier temporaire.\n");
        fclose(F);
        return;
    }
int found = 0;
 while (fscanf(F, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number) != EOF) {

        if (strcmp(contact.name, nom_rechercher) == 0) {
            found = 1;
    printf("\nVoila les informations du contact :\nNom:%s\n\nContact:\n%s\nEmail :%s",contact.name, contact.phone_number, contact.email_address);
        }
}
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
        case 2 : Modifier_Contact();
        break;
        case 3 : rechercher_contact();
        break;
        case 4 : Supprimer_Contact() ;
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
    getchar();

    }while(strcmp(rep,"oui") == 0);

    return 0;
}

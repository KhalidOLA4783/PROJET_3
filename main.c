#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            printf("Contact trouvé! Entrez les nouvelles informations.\n");

            // Modifier le nom
            printf("Entrez le nouveau nom : ");
            gets(contact.name);

            // Modifier l'email (optionnel)
            printf("Entrez le nouveau email : ");
            gets(contact.email_address);
            while (verification_des_caracters(contact.email_address) == -1 || strstr(contact.email_address, "@") == NULL || relation_avec_point(contact.email_address) == -1 || strstr(contact.email_address, " ") != NULL || strstr(contact.email_address, ".com") == NULL) {
                printf("L'email est invalide, essayez encore.\n");
                printf("Entrez le nouveau email : ");
                gets(contact.email_address);
            }

            // Modifier le numéro de téléphone
            do {
                printf("Entrez le nouveau numéro de téléphone : ");
                gets(contact.phone_number);
            } while (strlen(contact.phone_number) > 10 || strstr(contact.phone_number, " ") != NULL);
            
            fprintf(temp, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number);  // Sauvegarder les modifications dans le fichier temporaire
        } else {
            fprintf(temp, "%s ; %s ; %s\n", contact.name, contact.email_address, contact.phone_number);  // Conserver le contact non modifié
        }
    }

    if (!found) {
        printf("Aucun contact trouvé avec cet email.\n");
    }

    fclose(F);
    fclose(temp);

    // Remplacer l'ancien fichier par le fichier temporaire
    remove("Contacts.txt");
    rename("temp.txt", "Contacts.txt");

    printf("Modification terminée.\n");
}


int main()
{ 
printf("Hello world");
Ajouter_Contacts();
 Modifier_Contact();
return 0 ;
}

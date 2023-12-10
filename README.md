# projet-de-C, Jérôme BALTHAZAR, Julien BLANCHARD, Séverin ETIEVANT

Voici ce qui fonctionne dans notre projet : 

  Partie 1
  
  Nous avons réussie à faire toutes les fonctions.
  Nous pouvons créer une liste et y insérer les valeurs que l'on veut, ces valeurs vont se ranger dans l'ordre croissant.
  Nous pouvons afficher la liste correctement

  Partie 2 
  
  Nous avons toutes les fonctions c'est à dire la recherche classique, par niveaux et remplir une liste par niveaux
  On se rend bien compte que la recherche par dichotomie est plus efficace que la recherche au niveau 0
  Cependant dans notre code on se rend compte que la recherche par dichotomie n'est pas optimal
  En effet, on voit que la recherche sur le niveau 0 fait une courbre exponentielle et normalement la recherche par dichotomie doit être stable or là nous avons une légère hausse du temps (voir image)

courbe au niveau 0 :

![image](https://github.com/MrMisteer/projet-de-C/assets/129770157/db41d01d-22b7-45ef-955e-61e3a9311b1f)

Courbe par recherche par dichotomie :

![image](https://github.com/MrMisteer/projet-de-C/assets/129770157/323580d4-5c14-4ce5-83ab-4b771eaf3519)

  Partie 3
  Nous avons un menu qui permet de :
1. Rechercher un contact, et proposer une complétion automatique à partir de la 3ème lettre entrée
pour le nom ;
2. Afficher les rendez-vous d’un contact ;
3. Créer un contact (avec insertion dans la liste) ;
4. Créer un rendez-vous pour un contact (avec insertion dans la liste si le contact n’existe pas) ;
5. Supprimer un rendez-vous ;

Nous avons la fonction qui permet de sauvegarder la liste mais elle ne fonctionne pas.
Et ne nous n'avons pas l'étude des complexités.

  

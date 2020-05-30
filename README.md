# WeddingQuiz

## Commandes
Mapping des touches sur les intéractions dans la section ```RemoteController``` du fichier de configuration JSON
Quatre interactions sont disponnibles:
1. NEXT
2. RETURN
3. ENTER
4. EDIT


En plus du mapping en configuration, les touches du clavier sont mappées telles que:
* NEXT: flèche droite
* RETURN: flèche gauche
* ENTER: Entrée
* EDIT: Shift

### Page Jingle
Tant que le Jingle tourne, les commandes sont ignorées
* NEXT: Page Questions
* ENTER: Lancement du Jingle
* EDIT: Page Score

### Page Score
* ENTER: Page Question
* EDIT: ENtrée dans l'édition du Score
  * NEXT: Choix de l'équipe 1
      * NEXT: Augmentation du score équipe 1
      * RETURN: Diminution du score équipe 1
  * RETURN: Choix l'équipe 2
      * NEXT: Augmentation du score équipe 2
      * RETURN: Diminution du score équipe 2
    
### Page Questions
* NEXT: Question Suivante si critère rempli
* EDIT: Affichage du score

#### Question Choix Multiple
Critère: Réponse affichée
* NEXT: Proposition suivante
* RETURN: Proposition précédente
* ENTER: Affichage de la réponse si toute les proposition sont présentent

#### Questions Rapides
Critère: toujours vrai



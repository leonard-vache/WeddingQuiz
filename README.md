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
* RETURN: Reset du Jingle

### Page Score
* ENTER: Page Question
* EDIT: Entrée dans l'édition du Score
  * NEXT: Choix de l'équipe 1
      * NEXT: Augmentation du score équipe 1
      * RETURN: Diminution du score équipe 1
  * RETURN: Choix l'équipe 2
      * NEXT: Augmentation du score équipe 2
      * RETURN: Diminution du score équipe 2
    
### Page Questions
* NEXT: Question Suivante si critère rempli
* EDIT: Entrée dans Menu

#### Question Choix Multiple
Critère: Réponse affichée
* NEXT: Proposition suivante
* RETURN: Proposition précédente
* ENTER: Affichage de la réponse si toutes les propositions sont présentes

#### Questions Rapides
Critère: toujours vrai


### Menu
Visible Uniquement depuis la page question
2 Composants -> Score et Content
* NEXT: Composant suivant
* RETURN: Composant précédent
* ENTER: Sélection du composant
  * Score: Affichage page Score
  * Content: Affichage du contenu lié à la question (définit en conf)
             Si il n'y a pas de contenu, retour à la question
  
### Contenu
Visible Uniquement depuis la page question
Peut être une image ou une vidéo
* EDIT: Arret -> retour à la question

#### Image
* EDIT: Retour page question

#### Vidéo
* ENTER: Play/Pause
* RETURN: Retour au début
* EDIT: Retour page question
    



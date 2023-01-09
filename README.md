# Gestion de bibliothèque
## Application  de gestion de bibliothèque en langage C dans le cadre d'un projet de CP2 à l'EILCO
### Réalisé par BOIDOUX Théau et TETART Julian

  Nous arrivons sur le menu de connexion qui nous
propose de nous connecter. Après avoir choisi de se connecter en tapant 1
dans la console et en l'exécutant (entrée), nous pouvons donc maintenant
entrer les identifiants. Comme dit dans une précédente partie, il existe 2 types
de comptes: les lecteurs et les administrateurs.
Premier cas: vous êtes un lecteur et vous voulez donc connaître les
livres que vous avez empruntés. Dans ce cas, vous pouvez vous connecter sur
le compte login: lecteur, Mot de passe: lecteur (voir connexion lecteur). Une
fois connecté, vous avez accès au menu lecteur, qui se divise en deux
catégories. La catégorie liste livre et liste livre emprunter. Liste livre vous
permet d’afficher tous les livres disponibles dans la bibliothèque et liste livre
emprunter affiche tous les livres que le lecteur à emprunter.
Second cas: vous êtes un administrateur et vous souhaitez actualiser la
base de données. Dans ce cas, vous pouvez vous connecter sur le compte :
login: admin, Mot de passe: admin (voir connexion Admin). Nous pouvons
donc accéder à différentes fonctions : gestion livres, emprunt livre, gestions
livre et historique (annexe menu emprunter livre). Tout d’abord, la gestion des
livres (annexe menu gestion de livre), à partir de ce menu, nous pourrons soit
ajouter un livre, soit supprimer un livre, soit modifier un livre ou encore voir la
liste des livres. Ensuite, l’administrateur pourra accéder au menu emprunt
livre(annexe menu emprunt livre), ce menu est composé de la fonction
rechercher un livre à emprunter qui va nous permettre d’emprunter un livre. La
fonction rendre un livre qui va permet d’enregistrer le retour d’un livre et la
fonction livre non rendu, qui affiche la liste des livres qui n’ont pas été rendu.
La fonction menu gestion compte (annexe menu gestion compte) a pour but
de gérer les comptes utilisateurs, on peut grâce à elle créer un compte, en
supprimer un, modifier le mot de passe d’un utilisateur ou encore voir la liste
des différents comptes. Ensuite vient la fonction historique (annexe menu
historique) qui permet soit d’afficher l’historique des connexions ou
l’historique des livres empruntés. Et enfin le menu aide (annexe menu aide),
qui va permettre d’avoir un guide en cas de problème avec l’utilisation de
l’application.


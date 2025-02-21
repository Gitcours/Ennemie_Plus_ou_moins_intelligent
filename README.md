# Raycast

l'idée initial était d'avoir un pathfinding "économique" afin de pouvoir implémenté plusieurs énnemies sans avoir à se soucier de problèmes de performances, l'idée de coupler du raycast avec du pathfinding afin de se déplacé avec pour ainsi, économiser des ressources nous est venu. 
la première implémentation a été un simple raycast entre le centre de l'énnemie et celui du player, un premier problème est survenu, lorsque le player se trouve parallele a un mur, l'énnemie le travers a moitier si le raycast ne touche pas le mure

![image](https://github.com/user-attachments/assets/91fb9343-9519-42e1-8558-5eef2e3db66e)

nous avons donc choisi d'effectuer 4 raycast partant de chaques coins de l'ennemie afin de palier a ce problème.

![image](https://github.com/user-attachments/assets/7ecac326-776f-470e-9628-27ca9c58a6ed)


# Pathfinding A*
Une première implémentation du pathfinding a eu comme problème d'être recalculée à chaque fois différemment, avec des résultats souvent questionnables. Nous avons donc choisi de limiter le rafraîchissement du pathfinding en établissant un délai minimal de 1 seconde pour chaque rafraîchissement et en vérifiant également que la cible est différente de l'ancienne cible. Pour pallier au premier problème, nous avons changé l'algorithme pour utiliser la distance de Manhattan.

# State machine
Bien que notre idée initiale fût d'implémenter un GOAP, nous avons opté pour une machine à états par souci d'efficacité temporelle. Cette dernière fonctionne en prenant en compte les points de vie (PV) de l'ennemi, ainsi que sa distance par rapport au joueur. Un bug nous a permis d'implémenter une "feature" d'effet de groupe où les ennemis s'alertent entre eux. À la base, un vecteur comprenant la dernière position du joueur était utilisé pour définir le comportement de chaque ennemi si le joueur était perdu de vue. Cependant, ce vecteur étant global, tous les ennemis n'ayant pas le joueur en visuel se déplacent tout de même vers lui si un autre événement change l'état de ce vecteur, et reprennent également leur patrouille si un ennemi a "checké" la dernière position du joueur, affirmant à tous (en changeant ce vecteur) que le joueur n'y était pas.

# Signification des differentes couleurs

Vers = patrouillage

![image](https://github.com/user-attachments/assets/2cbbfb18-5054-4697-ac09-dbc0a857d418)


Jaune = verification de la derniere position du joueur

![image](https://github.com/user-attachments/assets/6067f9f8-30f8-4122-aa9f-5e35f3e42c23)


Rouge = chasse le joueur

![image](https://github.com/user-attachments/assets/b3b322e0-4c84-47d5-bdab-9e16935b0e80)


Blanc = fuie le joueur

![image](https://github.com/user-attachments/assets/240b2b77-2262-4c14-af05-d48dcd040749)

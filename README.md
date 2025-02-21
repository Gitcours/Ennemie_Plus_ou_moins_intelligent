#Raycast

l'idée initial était d'avoir un pathfinding "économique" afin de pouvoir implémenté plusieurs énnemies sans avoir à se soucier de problèmes de performances, l'idée de coupler du raycast avec du pathfinding afin de se déplacé avec pour ainsi, économiser des ressources nous est venu. 
la première implémentation a été un simple raycast entre le centre de l'énnemie et celui du player, un premier problème est survenu, lorsque le player se trouve parallele a un mur, l'énnemie le travers a moitier si le raycast ne touche pas le mure

![image](https://github.com/user-attachments/assets/91fb9343-9519-42e1-8558-5eef2e3db66e)

nous avons donc choisi d'effectuer 4 raycast partant de chaques coins de l'ennemie afin de palier a ce problème.

![image](https://github.com/user-attachments/assets/7ecac326-776f-470e-9628-27ca9c58a6ed)


#Pathfinding A*
une première implémentation du pathfinding a eu comme probleme d'être recalculer a chaques fois differement avec des résultat souvent questionnables, nous avons donc choisi le limité le refresh du pathfinding en partant 1s minimal pour chaque refresh et en verifiant également que la cible est différente de l'ancienne cible.
pour palier au premier probleme, nous avons changer l'algorithme pour utiliser la distance de Manhattan.

#State machine
bien que notre idée inital fu d'implémenter un GOAP, nous avons opter pour une state machine par efficasiter de temps, cette derniere foncitonne en prenant en compte les PV de l'énnemi, ainsi que sa distance par rapport au joueur, un bug nous a permis d'implémenter une "feature" d'effet de groupe ou les énemies s'alerte entre eux, a la base, un vecteur comprenant la derniere position du joueur été utiliser pour definire le comportement de chaque énemie si le joueur est perdu de vue, mais ce vecteur étant global, tout les énemies n'ayant pas le joueur en visuel se déplace tout de meme vers lui si un autre énement change l'état de ce vecteur et reprenne également leurs patrouille si un énnemie a "Cheack" la derniere position du joueur afirmant a tous (en changeant ce vecteur) que le player n'y été pas.

Pour les couleurs des énnemies nous avons:

Vers = patrouillage
Jaune = verification de la derniere position du joueur
Rouge = chasse le joueur
Blanc = fuie le joueur

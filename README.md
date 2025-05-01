# RM+

Ce projet ne vise pas à remplacer rm mais plutôt à le compléter, il permet notamment de supprimer des fichiers en ajoutant des exceptions, ce qui permet dêtre plus efficace.

## Installation

Il faut télécharger le binaire en faisant : 
,,,
git clone [repo]
,,,

Puis il faut copier rm+ dans ~/.local/bin et l'ajouter au path dans le fichier .bashrc :
,,,
export PATH="$PATH:$HOME./local/bin:"
,,,

## Utilisation

Une page man n'est toujours pas disponible, mais il est possible de voir les utilisations courantes en tapant : 
,,,
rm+ --help
,,,

## A venir

Ce projet est pour le moment fonctionnel mais le code est très grossier, il est prévu de le rendre rapidement plus modulable afin d'apporter de nouvelles fonctionnalités.

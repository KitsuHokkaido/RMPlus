# RM+

Ce projet ne vise pas à remplacer rm mais plutôt à le compléter, il permet notamment de supprimer des fichiers en ajoutant des exceptions, ce qui permet dêtre plus efficace.

## Installation

Il faut télécharger le projet en faisant : 
```
git clone [repo]
```

Puis il faut le compiler pour cela utiliser la commande :
```
make
```

Puis il faut copier rm+ dans ~/.local/bin et l'ajouter au path dans le fichier .bashrc :
```
export PATH="$PATH:$HOME./local/bin:"
```

## Utilisation

Une page man n'est toujours pas disponible, mais il est possible de voir les utilisations courantes en tapant :
```
rm+ --help
```

```
Command : rm+ [command] [flag1] [param] [flag2] [param]

[command]
* : to delete all the files
files : specify the name of the files

[flags]
 -x : exception of type file or extension
 -s : to delete several files
 -*f : to delete all the files
 -*d to delete all the directories
 -*fd : to delete all the files and directories

[param]
name : you can specify a filename
extension : you can specify a file extension

Example
> rm+ -*f -x file1 file2 : delete all the files excepted file1 and file2
> rm+ -*f -x .txt : delete all the files excepted the files with extension.txt
```
## A venir

Ce projet est pour le moment fonctionnel mais le code est très grossier, il est prévu de le rendre rapidement plus modulable afin d'apporter de nouvelles fonctionnalités.

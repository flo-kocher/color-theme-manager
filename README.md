# **Projet d’IHM : gestionnaire de themes**

Le but de ce projet était de réaliser une application Qt sur Linux en mode Desktop uniquement. Le principe est simple, on doit pouvoir créer ainsi qu'appliquer des thèmes sur des fichiers. Un thème est composé d'une liste de paires de couleurs source et target. Lorsqu'on applique un thème sur un fichier, on remplace alors les occurences de couleurs source par ses couleurs target. De plus, il sera possible de créer ses propres thèmes. Tout cela en devant suivre un cahier des charges bien précis.

## **Fonctionnement de l'application**

### **Mise en page de l'application**

Mon application est une application multi-page où il est possible de naviguer entre 3 pages : la vue principale où sont disposées la totalité des thèmes créés par l'utilisateur, une deuxième page où l'utilisateur pourra chercher un thème et choisir un fichier sur lequel il souhaitera appliquer ce thème et une dernière page qui fera tout ce qui est création de thèmes.

Chaque page est composée, de boutons en haut à gauche permettant de passer fluidement d'une page à une autre ainsi que d'une barre de progression lorsque l'application d'un thème sur un fichier ou projet est longue. On retrouve aussi une zone de texte où sont affichéss toutes les notifications pour guider l'utilisateur lorsqu'il provoque une erreur ou réussit à créer un thème par exemple.

### **Vue principale**

La vue principale est essentiellement composée de la liste de tous les thèmes que l'utilisateur a créé jusqu'à présent, l'application est composé de deux dossiers "icons/" et "themes." où se trouvent respectivement les icônes ainsi que les fichiers xml représentants des thèmes. Ils sont donc très faciles d'accès car rangés dans des dossiers spécifiques.

### **Appliquer un thème**

La page d'application de thème possède un emplacement où il sera possible d'écrire le lien vers le fichier sur lequel on voudra appliquer un thème. De plus, un bouton "Parcourir" ouvrira un explorateur de fichier afin que l'uilisateur puisse directement choisir le fichier voulu. Ensuite sera listé encore une fois l'ensemble des thèmes possibles. L'utilisateur devra en sélectionner un puis cliquer sur le bouton appliquer pour appliquer son thème sur son fichier. Un message d'erreur d'affichera dans la zone de notification si aucun thème n'a été sélectionné ou si aucun fichier n'a été chosis. Le système d'application de thème sur un fichier n'a pas été implémenté mais les fonctions nécessaires à sa création sont déjà implémentées.

### **Créer, modifier, importer un thème**

Cette page est séparée en onglets pour effectuer les différentes actions : 
- créer un thème
- modifier un thème
- importer/mettre à jour un thème depuis internet

#### **Créer/modifier un thème**

Cet onglet demandera dans un premier temps à l'utilisateur d'importer, depuis son gestionnaire de fichiers, une image pour représenter son thème et de donner un nom à celui-ci. Le reste de l'interface permet à l'utilisateur de faire ses paires "source-target", pour cela il peut, au choix, utiliser la spin-box pour chosir le nombre de paires il souhaite générer d'un seul coup, pour éviter d'ajouter une paire une par une. Sinon, il est possible de rajouter une paire en cliquant simplement sur le bouton "Ajouter une paire". Malheuresement je n'ai pas trouvé une manière de supprimer une paire, il faudra donc, si trop de zones de texte ont été créé, soit relancer l'application, ou soit simplement laisser les zones vides. Une fois les paires finies, l'utilisateur pourra sauvegarder son thème, celui-ci sera alors enregistré dans les dossiers des thèmes et d'icônes et sera aussi affiché directement dans l'aperçu des thèmes dans la vue principale. Attention, si l'utilisateur ne spécifie pas d'image ou de nom de thème, l'utilisateur en sera notifié et ne pourra donc pas sauvegarder avant d'avoir résolu ses problèmes.

#### **Importer un thème existant**

Si l'utilisateur souhaite modifier l'un de ses thèmes ou en importer un nouveau dans l'application, il pourra cliquer sur le bouton d'importation et choisir son fichier xml dans son gestionnaire de fichiers. Une autre méthode possible pour l'utilisateur est de Drag & Drop son fichier xml. Malheuresement, je n'ai pas réussi à ne permettre le drag & drop que sur le bouton d'importation, par conséquent le drag & drop est possible peu importe où dans l'application.

#### **Importer un thème depuis internet**

N'ayant pas fait les fonctions permettant de récupérer un xml par lien internet, cet onglet n'est donc pas implémenté, cependant son contenu reste présentable. On retrouve le choix d'une image ainsi que d'un nom de thème. A la différence de la page de création de thème, ici on demande à l'utilisateur d'écrire son lien internet dans la zone de texte. Le bouton "Sauvegarder" permettra donc de créer le thème et le bouton "Mettre à jour" nous renverrait alors dans notre premier onglet afin que l'utilisateur puisse, avant de sauvegarder son thème par lien internet, modifier quelques paires de couleurs.

## **Fonctionnalités**

### **Fonctionnalités implémentées**

Les fonctionnalités implémentées dans mon application sont les suivantes :
- interface multi-pages avec changement de pages par l'utilisation de signaux
- représentation d'un thème par un fichier xml et une image au format png (au lieu de la création d'une classe *Theme*)
- affichage de ces thèmes dans une vue principale
- système de drag and drop d'un fichier xml pour importer un thème qui fonctionne peu importe où dans l'application plutôt que simplement sur la page spécifique (Importer un thème existant)
- messages d'information lorsque l'utilisateur réussit une action ou lorsque au contraire il manque à, par exemple, donner un nom à son thème qu'il souhaite créer
- aucun téléchargement n'est bloquant
- création de thème
- modification d'un thème existant
- utilisation de stylesheets pour améliorer le design de l'application et d'icônes pour représenter les thèmes
- scroll bar pour l'affichage des paires de couleurs
- utilisation d'une spin-box pour générer plus rapidement des paires de couleurs
- prévisualisation de l'image choisie en tant qu'icône de thème
- actualisation instantanée de la zone de notifications et des lieux d'affichage de l'ensemble des thèmes

### **Fonctionnalités non implémentées**

Les fonctionnalités non implémentées dans mon application sont les suivantes :
- application d'un thème sur un fichier
- récupération et mise à jour d'un thème importé depuis un lien internet
- utilisation de la barre de progression pour communiquer à l'utilisateur le temps restant avant la fin de l'application ou de la création de son thème
- le drag & drop qui fonctionne mais sur toute l'application et pas que sur la page dédiée
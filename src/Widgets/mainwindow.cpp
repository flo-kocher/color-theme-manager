#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ColorPair.h"
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>

//variable globale permettant de garder en mémoire le dernier thème sélectionner dans Appliquer/modifier un thème
QString item_theme;
//variable globale permettant de garder en mémoire la dernière image importée dans Appliquer/modifier un thème
QString theme_icon;

int nb_st_widget;

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nb_st_widget = 0;

    //autorise le fait de faire des drags & drops
    //devrait normalement n'être que possible sur le page d'importation de thème, mais malheuresement je n'ai pas réussi à le faire spécifiquement pour cette page
    setAcceptDrops(true);


    //Affichage des thèmes déjà enregistrées dans l'application dans les pages Vue Principale et Appliquer un thème

    //récupération du path vers le dossier themes/
    QDir themes;
    qDebug()<<themes.currentPath();
    QString themes_path = themes.currentPath().append("/../color-theme-manager-florentin/themes");
    qDebug()<<themes_path;
    themes.setPath(themes_path);

    //idem pour le dossier icons/
    QDir icons;
    QString icons_path = icons.currentPath().append("/../color-theme-manager-florentin/icons");
    icons.setPath(icons_path);

    //création de listes des fichiers de chaque dossier
    QStringList files_list = themes.entryList();
    QStringList icons_list = icons.entryList();
    for(int i = 0; i < files_list.size(); i++)
    {
        if(files_list.at(i) != "." && files_list.at(i) != "..")
        {
            //initialisation d'items qui seront insérés au QListWidget de la vue principale et de l'application de thème
            QListWidgetItem *theme = new QListWidgetItem;
            theme->setText(files_list.at(i));
            theme->setIcon(QIcon(icons_path+"/"+icons_list.at(i)));
            theme->setSizeHint(QSize(150,150));
            //obliger d'initialiser séparer les items de l'autre QListWidget, sinon ils ne 'affichent que dans l'une et pas dans l'autre
            QListWidgetItem *theme_bis = new QListWidgetItem;
            theme_bis->setText(files_list.at(i));
            theme_bis->setIcon(QIcon(icons_path+"/"+icons_list.at(i)));
            theme_bis->setSizeHint(QSize(150,150));
            //insertion dans les widgets
            ui->listWidget_2->addItem(theme);
            ui->listWidget->addItem(theme_bis);
        }
    }

    //affichage d'une première paire de couleurs dans la page de création de thèmes
    QWidget *window = ui->tabWidget_3Page1;
    QWidget *st_widget = new QWidget();

    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    st_widget->setParent(window);
    QLineEdit *line_edit_s = new QLineEdit();
    line_edit_s->setFixedWidth(180);
    line_edit_s->setObjectName("line_edit_s"+QString::number(nb_st_widget));
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    line_edit_t->setFixedWidth(180);
    line_edit_t->setObjectName("line_edit_t"+QString::number(nb_st_widget));
    QSpacerItem *spacer_2 = new QSpacerItem(150,20);
    QPushButton *button = new QPushButton("Supprimer");

    QVBoxLayout *vertical_l = new QVBoxLayout(st_widget);
    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    vertical_l->addLayout(layoutt);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_2);
    layoutt->addWidget(button);
    //incrémentation du conteneur du nombre total de source-target widgets dans la page de création de thème
    nb_st_widget++;
    //ajout du widget dans la scroll area
    ui->scrollArea->setWidget(st_widget);
}

MainWindow::~MainWindow()
{
	delete ui;
}

//surcharge de la fonction d'évènement de drag
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

//surcharge de la fonction d'évènement de drop
void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        QString file_name = url.toLocalFile();
        qDebug() << "Dropped file:" << file_name;
    }
    //textBrowser->setPlainText(event->mimeData()->text());
}

//fonction appelé lorsque l'on souhaite notifier dans la zone de notifications
//synchronise la totalité des zones de notifications sur chaque page par la même occasion
void MainWindow::synchronize_notifications(QString text_to_add)
{
    QString last_text = ui->label_main->text();
    ui->label_main->setText(last_text+"\n"+text_to_add);
    ui->label_3->setText(last_text+"\n"+text_to_add);
    ui->label_5->setText(last_text+"\n"+text_to_add);
}

//fonction permettant de créer un fichier XML en utilisant les target et sources ajoutés dans la page de création de thème
void MainWindow::writeXMLFile(QString themename, QList<QLineEdit *> list, QString theme_folder_path){
    //il faut encore déplacer le fichier dans le dossier themes/
    QFile xmlfile(theme_folder_path+"/"+themename.append(".xml"));
    if (!xmlfile.open(QFile::WriteOnly | QFile::Text ))
    {
        qDebug() << "Erreur : fichier déjà ouvert";
        xmlfile.close();
        return;
    }
    QTextStream xmlContent(&xmlfile);

    QDomDocument document;
    //make the root element
    QDomElement root = document.createElement("colors");
    //add it to document
    document.appendChild(root);

    for(int i = 0; i < list.count(); i+=2)
    {
        //création des éléments 'color' de l'xml
        QDomElement color = document.createElement("color");
        color.setAttribute("target", list.at(i+1)->text()); //target
        color.setAttribute("id", "Couleur "+QString::number(i)); //id
        color.setAttribute("source", list.at(i)->text()); //source
        root.appendChild(color);
    }

    xmlContent << document.toString();
}



//ci-dessous les fonctions permettant de changer de pages
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_23_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    ui->lineEdit_19->setText(file_name);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    item_theme = item->text();
}

// Bouton d'application d'un thème sur un fichier
void MainWindow::on_pushButton_clicked()
{
    /*
    border:1px solid black;
    color: white;
    background-color: rgb(238, 238, 236);
     */
    QString file_name = ui->lineEdit_19->text();
    if(item_theme == "" || file_name == "")
    {
        ui->pushButton->setStyleSheet("border:1px solid black;color: white;background-color: rgb(238, 238, 236);");
        synchronize_notifications("\nFile name missing or no selected theme");
    }
    else
    {
        synchronize_notifications("\nFile : "+file_name+" currently applying a theme");
    }

}

//Bouton d'ajout d'une paire de couleurs
void MainWindow::on_pushButton_7_clicked()
{
    QWidget *st_widget = new QWidget();

    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    QLineEdit *line_edit_s = new QLineEdit();
    line_edit_s->setObjectName("line_edit_s"+QString::number(nb_st_widget));
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    line_edit_t->setObjectName("line_edit_t"+QString::number(nb_st_widget));
    QPushButton *button = new QPushButton("Supprimer");

    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(button);

    QString first_widget_name = "st_widget" + QString::number(0);
    QWidget *first_widget = ui->stackedWidget->findChild<QWidget *>(first_widget_name);

    first_widget->layout()->addWidget(st_widget);
    //on ajoute notre nouvelle paire créée dans la scrollArea
    ui->scrollArea->setWidget(first_widget);
    nb_st_widget++;
}

// Bouton Sauvegarder
void MainWindow::on_pushButton_8_clicked()
{
    QWidget *scroll_widget = ui->scrollArea->widget();
    //on fait une liste des QLineEdit pour récupérer les codes hexadécimaux ajoutés
    QList<QLineEdit *> list = scroll_widget -> findChildren<QLineEdit *> ();

    if(ui->label->pixmap().isNull() || ui->lineEdit_6->text() == "")
        synchronize_notifications("\nPas d'icône de thème importé ou pas de nom du thème choisi");
    else
    {
        QDir icons;
        //path vers le dossier icons/
        QString icons_path = icons.currentPath().append("/../color-theme-manager-florentin/icons");
        QPixmap icon = ui->label->pixmap();
        //on la déplace dans le dossier icons/
        icon.save(icons_path+"/"+ui->lineEdit_6->text()+".png");
        QDir themes;
        QString themes_path = themes.currentPath().append("/../color-theme-manager-florentin/themes");
        writeXMLFile(ui->lineEdit_6->text(),list,themes_path);
        synchronize_notifications("\nVotre thème : "+ui->lineEdit_6->text()+" a été créé avec succès");

        //code permettant d'ajouter le thème venant d'être créé à la vue principale
        QListWidgetItem *theme = new QListWidgetItem;
        theme->setText(ui->lineEdit_6->text()+".xml");
        theme->setIcon(QIcon(icons_path+"/"+ui->lineEdit_6->text()+".png"));
        theme->setSizeHint(QSize(150,150));

        QListWidgetItem *theme_bis = new QListWidgetItem;
        theme_bis->setText(ui->lineEdit_6->text()+".xml");
        theme_bis->setIcon(QIcon(icons_path+"/"+ui->lineEdit_6->text()+".png"));
        theme_bis->setSizeHint(QSize(150,150));

        ui->listWidget_2->addItem(theme);
        ui->listWidget->addItem(theme_bis);
    }
}

// Bouton d'ajout d'image pour la création d'un thème
void MainWindow::on_pushButton_6_clicked()
{
    theme_icon = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QPixmap *pix = new QPixmap(theme_icon);
    if(pix->width() < 32 && pix->height() < 32)
        synchronize_notifications("\nTaille de l'icône du thème trop petite (32x32 pixels minimum)");
    else
        ui->label->setPixmap(QPixmap(theme_icon));
}

// Bouton d'ajout d'image pour la création d'un thème par lien internet
void MainWindow::on_pushButton_9_clicked()
{
    theme_icon = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QPixmap *pix = new QPixmap(theme_icon);
    if(pix->width() < 32 && pix->height() < 32)
        synchronize_notifications("\nTaille de l'icône du thème trop petite (32x32 pixels minimum)");
    else
        ui->label_2->setPixmap(QPixmap(theme_icon));
}

// Bouton pour générer plusieurs source_target d'un coup avec la spin box
void MainWindow::on_pushButton_2_clicked()
{
    int value = ui->spinBox->value();
    for(int i = 0; i < value; i++)
    {
        on_pushButton_7_clicked();
    }
}

// Bouton de modification/importation d'un thème déjà existant
void MainWindow::on_pushButton_16_clicked()
{
    QString xml_file = QFileDialog::getOpenFileName(this, "Open a file", QDir::currentPath().append("/../color-theme-manager-florentin/themes"),"Theme Files (*.xml)");
    QStringList list_of_files = xml_file.split(QLatin1Char('/'));
    ui->lineEdit_6->setText(list_of_files.at(list_of_files.count()-1));

    set<ColorPair,CompareColorPair> s;
    XMLReader docu = XMLReader(s);
    QFile fichier(xml_file);
    docu.read(fichier);

    //set contenu dans set_compare
    s = docu.getSet();
    //on rajoute des emplacements de source-target dans l'autre page pour pouvoir afficher les valeurs hexadecimales déjà dans le fichier XML
    if(nb_st_widget < s.size())
    {
        for(int i = 0; i < s.size(); i++)
            on_pushButton_7_clicked();
    }

    //on récupère le widget de la scroll area
    QWidget *scroll_widget = ui->scrollArea->widget();
    //on récupère la liste des QLineEdit pouvoir y afficher les sources et targets du fichier XML
    QList<QLineEdit *> list_of_line_edit = scroll_widget -> findChildren<QLineEdit *> ();

    int i = 0;
    //on parcours l'ensemble des codes hexadécimaux du set et on les place dans les zones de texte au fur et à mesure
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        //qDebug() << "couleurs source et target: " << it->toRGBA(it->getColor1()) << it->toRGBA(it->getColor2());
        list_of_line_edit.at(i)->setText(it->toRGBA(it->getColor1()));
        i++;
        list_of_line_edit.at(i)->setText(it->toRGBA(it->getColor2()));
        i++;
    }

    ui->tabWidget_3->setCurrentIndex(0);
}


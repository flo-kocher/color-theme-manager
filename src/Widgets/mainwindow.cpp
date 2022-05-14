#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ColorPair.h"
#include <iostream>
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

//variable globale permettant de garder en mémoire le dernier thème sélectionner dans Appliquer un thème
QString item_theme;

int nb_st_widget;

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nb_st_widget = 0;

    setAcceptDrops(true);



    /*
    int id = ui->stackedWidget->currentIndex();
    std::cout<<id<<std::endl;

    QStackedWidget *pages = ui->stackedWidget;
    int num  = pages->count();
    std::cout<<num<<std::endl;
    */

    //index:0 page 1
    //index:1 page 2
    //ui->stackedWidget->setCurrentIndex(1);


    // utiliser ça pour accéder au path du projet et donc aux dossiers qui contiendront les icons et les xml
    //QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::currentPath());

    //https://stackoverflow.com/questions/37331270/how-to-create-grid-style-qlistwidget



    /*
    //aller dans le dossier themes/ et voir les fichiers présents dedans
    QDir themes = QDir::currentPath();
    //std::cout<<themes.dirName()<<std::endl;
    QDir p;
    QString path = p.currentPath().append("/themes");
    p.setPath(path);
    qDebug()<<p.dirName();
    qDebug()<<p.count();
    QStringList sl = p.entryList();
    for(int i = 0; i < sl.size(); i++)
    {
        qDebug()<<sl.at(i);
    }
    */


    //Affichage des thèmes déjà enregistrées dans l'application dans les pages Vue Principale et Appliquer un thème

    //récupération du path vers le dossier themes/
    QDir themes;
    QString themes_path = themes.currentPath().append("/themes");
    themes.setPath(themes_path);

    //idem pour le dossier icons/
    QDir icons;
    QString icons_path = icons.currentPath().append("/icons");
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

    /*
    QWidget *window = ui->tabWidget_3Page1;
    QWidget *st_widget = new QWidget();

    //QString last_widget = QString("st_widget").arg(nb_st_widget);
    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    st_widget->setParent(window);
    QLineEdit *line_edit_s = new QLineEdit();
    line_edit_s->setFixedWidth(180);
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    line_edit_t->setFixedWidth(180);
    QSpacerItem *spacer_2 = new QSpacerItem(150,20);
    QPushButton *button = new QPushButton("Supprimer");

    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_2);
    layoutt->addWidget(button);

    st_widget->move(50,270);
    st_widget->show();
    nb_st_widget++;
    */

    QWidget *window = ui->tabWidget_3Page1;
    QWidget *st_widget = new QWidget();
    //ui->scrollArea->setWidget(st_widget);

    //QString last_widget = QString("st_widget").arg(nb_st_widget);
    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    st_widget->setParent(window);
    QLineEdit *line_edit_s = new QLineEdit();
    line_edit_s->setFixedWidth(180);
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    line_edit_t->setFixedWidth(180);
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

    //st_widget->move(50,270);
    //st_widget->show();
    nb_st_widget++;

    // /////////////////////////////////////////////////////////////////////////////////
    //le mets bien dedans, voir le code qu'il faut qu'on garde et ce qu'il faut enlever
    ui->scrollArea->setWidget(st_widget);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();

}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls())
    {
        QString file_name = url.toLocalFile();
        qDebug() << "Dropped file:" << file_name;
    }
}

void MainWindow::synchronize_notifications(QString text_to_add)
{
    QString last_text = ui->label_main->text();
    ui->label_main->setText(last_text+"\n"+text_to_add);
    ui->label_3->setText(last_text+"\n"+text_to_add);
    ui->label_5->setText(last_text+"\n"+text_to_add);
}

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
    //QString file_name = QFileDialog::getOpenFileName(this, "Open a file", QDir::currentPath());

    //QMessageBox::information(this,"..",file_name);
    ui->lineEdit_19->setText(file_name);


    //ui->lineEdit_19->setText("Incroyanle");
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //std::cout<<"je suis appuyé"<<std::endl;
    item_theme = item->text();
}

// Bouton d'application d'un thème sur un fichier
void MainWindow::on_pushButton_clicked()
{
    QString file_name = ui->lineEdit_19->text();
    //qDebug()<<"File_name : "<<file_name<<" and theme name : "<<item_theme;
    synchronize_notifications(file_name);
}


void MainWindow::on_pushButton_7_clicked()
{
    /*
    QWidget *window = ui->tabWidget_3Page1;
    QWidget *st_widget = new QWidget();

    //QString last_widget = QString("st_widget").arg(nb_st_widget);
    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    st_widget->setParent(window);
    QLineEdit *line_edit_s = new QLineEdit();
    line_edit_s->setFixedWidth(180);
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    line_edit_t->setFixedWidth(180);
    QSpacerItem *spacer_2 = new QSpacerItem(150,20);
    QPushButton *button = new QPushButton("Supprimer");

    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_2);
    layoutt->addWidget(button);

    QString last_widget_name = "st_widget" + QString::number(nb_st_widget-1);
    QWidget *last_widget = ui->stackedWidget->findChild<QWidget *>(last_widget_name);
    //qDebug()<<last_widget->pos().x();

    st_widget->move(50,last_widget->pos().y()+40);
    st_widget->show();
    nb_st_widget++;
    */

    /*

    //mettre ce code dans une fonction pour créer le widget dynamique qui fait les sources/targets
    QWidget *window = ui->tabWidget_3Page1;
    QWidget *st_widget = new QWidget();
    nb_st_widget++;

    //QString last_widget = QString("st_widget").arg(nb_st_widget);
    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString last_widget = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(last_widget);

    st_widget->setParent(window);
    QLineEdit *line_edit_s = new QLineEdit();
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    QPushButton *button = new QPushButton("Supprimer");

    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(button);

    st_widget->move(50,300);
    st_widget->show();


    //récupère le dernier st_widget créé
    //QWidget *searched = ui->stackedWidget->findChild<QWidget *>(last_widget);
    //qDebug()<<searched->objectName();

    */

    // il faut maintenant récupérer la position du dernier st_widget
    // puis la mettre un peu en dessous en hauteur

    //ensuite mettre tous ces codes au début de cette fonction pour qu'on puisse appuyer plusieurs fois sur le bouton et afficher plusieurs st_widget les uns après les autres

    QWidget *st_widget = new QWidget();

    //QString last_widget = QString("st_widget").arg(nb_st_widget);
    //donne comme nom au widget créé, "st_widget" + le nombre de st_widget actuellement sur notre interface + 1
    QString current_widget_name = "st_widget" + QString::number(nb_st_widget);
    st_widget->setObjectName(current_widget_name);

    QLineEdit *line_edit_s = new QLineEdit();
    QSpacerItem *spacer_1 = new QSpacerItem(200,20);
    QLineEdit *line_edit_t = new QLineEdit();
    QPushButton *button = new QPushButton("Supprimer");

    QHBoxLayout *layoutt = new QHBoxLayout(st_widget);
    layoutt->addWidget(line_edit_s);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(line_edit_t);
    layoutt->addSpacerItem(spacer_1);
    layoutt->addWidget(button);

    QString first_widget_name = "st_widget" + QString::number(0);
    QWidget *first_widget = ui->stackedWidget->findChild<QWidget *>(first_widget_name);
    //qDebug()<<first_widget->objectName();

    first_widget->layout()->addWidget(st_widget);

    ui->scrollArea->setWidget(first_widget);
    nb_st_widget++;
}

// Bouton Sauvegarder
void MainWindow::on_pushButton_8_clicked()
{
    QWidget *scroll_widget = ui->scrollArea->widget();
    //on fait une liste des QLineEdit pour récupérer les codes hexadécimaux ajoutés
    QList<QLineEdit *> list = scroll_widget -> findChildren<QLineEdit *> ();
    for(int i = 0; i < list.count(); i++)
    {
        qDebug()<<list.at(i)->text();
    }

    /*
    QWidget *all_st_widgets = ui->scrollArea->findChild<QWidget *>("st_widget0");
    qDebug()<<all_st_widgets->objectName();

    //QLayout *st_layout = all_st_widgets->layout();
    QLayout *layout = all_st_widgets -> findChild<QLayout *> ();
    QList<QWidget *> list = layout -> findChildren<QWidget *> ();
    for(int i = 0; i < list.count(); i++)
    {
        qDebug()<<list.at(i);
    }
    */
}

// Bouton d'ajout d'image pour la création d'un thème
void MainWindow::on_pushButton_6_clicked()
{
    QString picture_url = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QPixmap *pix = new QPixmap(picture_url);
    if(pix->width() < 32 && pix->height() < 32)
        synchronize_notifications("\nTaille de l'icône du thème trop petite (32x32 pixels minimum)");
    else
        ui->label->setPixmap(QPixmap(picture_url));
}

// Bouton d'ajout d'image pour la création d'un thème par lien internet
void MainWindow::on_pushButton_9_clicked()
{
    QString picture_url = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath());
    QPixmap *pix = new QPixmap(picture_url);
    if(pix->width() < 32 && pix->height() < 32)
        synchronize_notifications("\nTaille de l'icône du thème trop petite (32x32 pixels minimum)");
    else
        ui->label_2->setPixmap(QPixmap(picture_url));
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
    QString xml_file = QFileDialog::getOpenFileName(this, "Open a file", QDir::currentPath().append("/themes"),"Theme Files (*.xml)");
    QStringList list_of_files = xml_file.split(QLatin1Char('/'));
    ui->lineEdit_6->setText(list_of_files.at(list_of_files.count()-1));

/*
        XMLReader docu;
        QFile fichier(list_of_files.at(list_of_files.count()-1));
        XMLReader::SetType setFile = docu.read(fichier);

        for (auto it = setFile.begin(); it != setFile.end(); ++it)
        {
                qDebug() << "voilà les couleurs: " << it->toRGBA(it->getColor1()) << it->toRGBA(it->getColor2()); // afficher les valeurs de toutes les paires du fichier


                QListWidgetItem * targetTag = new QListWidgetItem(it->toRGBA(it->getColor1()));
                QListWidgetItem * sourceTag = new QListWidgetItem(it->toRGBA(it->getColor2()));

                targetTag->setFlags(targetTag->flags() | Qt::ItemIsEditable);
                sourceTag->setFlags(sourceTag->flags() | Qt::ItemIsEditable);

                ui->listSource->addItem(sourceTag);
                ui->listTarget->addItem(targetTag);

        }

*/
    ui->tabWidget_3->setCurrentIndex(0);

}


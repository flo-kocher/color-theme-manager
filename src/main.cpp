#include "mainwindow.h"
#include <QApplication>
#include <ColorPair.h>
#include <QDebug>

/*  FAIRE UN FICHIER .CPP ET .H QUE QUE POUR XML READER !
 *
 *
 * FAIRE LES TESTS DANS LE MAIN
 * ET APPELER GENRE DES FONCTIONS QUI S'APELLENT
 * TEST_FONCTIONNALITE_1()
 *
 * ET LES APPELER UNE PAR UNE DANS LE MAIN
 *
 *
 *
 */

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
    ColorPair c1 = ColorPair("Couleur 01","#003265ff","#123225ff");
    ColorPair c2 = ColorPair("Couleur 02","#00aeeaff","#00bfeaff");
/*
    QColor color = c1.fromRGBA("Couleur 01");
    qDebug()<<color;
    QString string = c1.toRGBA(color);
    qDebug()<<string;
*/
    // test fonctionnement de classe CompareColorPair et de la surcharge
    CompareColorPair colorpair;
    bool res = colorpair(c1,c2);
    qDebug() << res;


    set<ColorPair,CompareColorPair> s;

    s.insert(c1);
    s.insert(c2);
    qDebug()<<&s;
    set<ColorPair,CompareColorPair>::iterator itr;
    for (itr=s.begin();itr !=s.end();itr++)
        qDebug()<<&itr;

//    XMLReader reader = XMLReader(s);
//    reader.read("petitTheme.xml");
/*
    XMLReader xml = XMLReader(s);
    qDebug()<<xml.getSet();
    */
	w.show();
	return a.exec();

}

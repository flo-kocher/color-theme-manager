#include "mainwindow.h"
#include <QApplication>
#include <ColorPair.h>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
    /*//Test de la création de deux ColorPairs
    ColorPair c1 = ColorPair("Couleur 01","#003265ff","#123225ff");
    ColorPair c2 = ColorPair("Couleur 02","#00aeeaff","#00bfeaff");

    //Test fonctionnement de la classe CompareColorPair et de la surcharge
    CompareColorPair colorpair;
    bool res = colorpair(c1,c2);
    qDebug() <<"Bool "<< res;
    */

    /*//Test de l'utilisation de la fonction XMLReader::read()
    set<ColorPair,CompareColorPair> s;
    QFile file;
    file.setFileName("/home/flo/ihm/color-theme-manager-florentin/petitTheme.xml");

    XMLReader reader = XMLReader(s);
    reader.read(file);
    */
	w.show();
	return a.exec();
}

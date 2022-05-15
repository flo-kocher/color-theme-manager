#include "ColorPair.h"

ColorPair::ColorPair(const ColorPair &color){
    m_id = color.m_id;
    color1 = color.color1;
    color2 = color.color2;
}

ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2){
    m_id = id;
    this->color1 = color1;
    this->color2 = color2;
}

ColorPair::ColorPair(const QString &id){
    m_id = id;
}

QString ColorPair::toRGBA(const QColor &color){
    QString argb = color.name(QColor::HexArgb);
    QString rgb = color.name(QColor::HexRgb);

    argb.remove(0,1); //enleve le '#'
    argb.remove(2,6); //laisse seulement 'aa'

    return rgb+argb;
}

QColor ColorPair::fromRGBA(const QString &colorStr){
    QColor color;
    QString first_part = colorStr;
    QString cp_colorStr = colorStr;

    first_part.remove(1,6);
    cp_colorStr.remove(0,1);
    cp_colorStr.remove(6,2);
    //qDebug() << colorStr;
    //qDebug() << first_part+cp_colorStr;
    color.setNamedColor(first_part+cp_colorStr);
    return color;
}

QString ColorPair::getId(){
    return m_id;
}

QColor ColorPair::getColor1() const{
    return color1;
}
QColor ColorPair::getColor2() const {
    return color2;
}

void ColorPair::setId(QString &id){
    m_id = id;
}

void ColorPair::setColor1(QColor &color){
    color1 = color;
}
void ColorPair::setColor2(QColor &color){
    color2 = color;
}

bool CompareColorPair::operator()(ColorPair pair1,ColorPair pair2) const{
    if(pair1.getId() < pair2.getId())
        return true;
    else
        return false;
}

XMLReader::XMLReader(const set<ColorPair,CompareColorPair> &compare){
    set_compare = compare;
}

set<ColorPair,CompareColorPair> XMLReader::getSet(){
    return set_compare;
}

bool XMLReader::read(QFile& file)
{
    //mon DomDocument
    QDomDocument xmlBOM;
    //essaye de lire le fichier
    if (!file.open(QIODevice::ReadOnly ))
    {
        //Affiche une erreur si on arrive pas à trouver le fichier
        std::cerr << "Lecture du dossier impossible" << std::endl;
        return false;
    }
    //on ajoute notre fichier à mon DomDocument
    xmlBOM.setContent(&file);
    file.close();

    QDomElement dom_tree = xmlBOM.documentElement();
    QDomElement xml = dom_tree.firstChild().toElement();
    while(!xml.isNull())
    {
        if (xml.tagName() == "color")
        {
            QString _id = xml.attribute("id","No id found");
            QColor _source = ColorPair::fromRGBA(xml.attribute("source","No source found"));
            QColor _target = ColorPair::fromRGBA(xml.attribute("target","No target found"));
            //on fait notre paire de couleurs
            ColorPair mycolor(_id, _source, _target);
            //et on l'insère dans le set
            this->set_compare.insert(mycolor);
        }
        xml = xml.nextSibling().toElement();
    }

    return true;
}

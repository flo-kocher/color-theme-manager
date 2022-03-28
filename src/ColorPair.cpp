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
    qDebug() << colorStr;
    qDebug() << first_part+cp_colorStr;
    color.setNamedColor(first_part+cp_colorStr);
    return color;
}

QString ColorPair::getId(){
    return m_id;
}

QColor ColorPair::getColor1(){
    return color1;
}
QColor ColorPair::getColor2(){
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

void XMLReader::read(const QString &filename){
    QFile file(filename);
    file.open(stderr,QIODevice::ReadOnly | QFile::Text);
    //lire ligne par ligne et genre stocker les balises dans un ColorPair/jsplus quoi et les mettre dans le set


/*
    QXmlStreamReader reader;
    reader.setDevice(&file);
    reader.readNext();
    reader.readNext();
    reader.readNext();
    qDebug()<<reader.readElementText();

    while(!reader.atEnd()){
        if(reader.isStartElement() == false){
            if(reader.name() == "colors"){
                reader.readNext();
            }
        }
    }
    */
}

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

static QString toRGBA(const QColor &color){
    QString argb = color.name(QColor::HexArgb);
    QString rgb = color.name(QColor::HexRgb);

    argb.remove(0,1); //enleve le '#'
    argb.remove(2,6); //laisse seulement 'aa'

    return rgb+argb;
}

static QColor fromRGBA(const QString &colorStr){
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

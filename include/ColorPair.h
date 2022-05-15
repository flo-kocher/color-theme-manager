#ifndef COLORPAIR_H
#define COLORPAIR_H
#include <QColor>
#include <QString>
#include <QDebug>
#include <set>
#include <QFile>
#include <QDomDocument>
#include <iostream>

using namespace std;

class ColorPair{
private:
    QString m_id;
    QColor color1;
    QColor color2;
public:
    ColorPair(); //constructeur vide
    ColorPair(const ColorPair &color); //con. par copie
    ColorPair(const QString &id, const QColor &color1, const QColor &color2);
    ColorPair(const QString &id); //initialisant uniquement l'identifiant
    //methodes
    static QString toRGBA(const QColor &color);
    static QColor fromRGBA(const QString &colorStr);

    //getter
    QString getId();
    QColor getColor1()const ;
    QColor getColor2()const ;
    //setter
    void setId(QString &id);
    void setColor1(QColor &color);
    void setColor2(QColor &color);
};

class CompareColorPair{
public:
    bool operator() (ColorPair pair1,ColorPair pair2) const;

};

class XMLReader{
private:
    set<ColorPair,CompareColorPair> set_compare;
public:
    XMLReader(); //con. vide
    XMLReader(const set<ColorPair,CompareColorPair> &compare);

    bool read(QFile& file);

    set<ColorPair,CompareColorPair> getSet();
};

#endif // COLORPAIR_H

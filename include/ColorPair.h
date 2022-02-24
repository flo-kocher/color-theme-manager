#ifndef COLORPAIR_H
#define COLORPAIR_H
#include <QColor>
#include <QString>
#include <QDebug>

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

    QString getId();
    QColor getColor1();
    QColor getColor2();

    void setId(QString &id);
    void setColor1(QColor &color);
    void setColor2(QColor &color);

    static QString toRGBA(const QColor &color);
    static QColor fromRGBA(const QString &colorStr);
};

#endif // COLORPAIR_H

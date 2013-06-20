/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "Spieler.h"

Spieler::Spieler(QWidget *parent, Insel *insel, const int x, const int y) {
    _lblPunkte.setParent(this);
    _lblPunkte.setCaption("Punkte");
    _lblPunkte.move(0,0);
    _lblPunkte.resize(150,PADDING_TOP);
    _lblPunkte.setVisible(true);
    _lblSchritte.setParent(this);
    _lblSchritte.setCaption("Schritte");
    _lblSchritte.move(150,0);
    _lblSchritte.resize(150,PADDING_TOP);
    _lblSchritte.setVisible(true);
    setParent(parent);
    resize(maximumSize());
    _x=x; _y=y;
    _insel=insel;
    setVisible(true);
}

void Spieler::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    QPen pen;

    pen.setWidth(10);
    QColor c=QColor(Qt::gray);
    pen.setColor(c);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(pen);

    float feldSize=_insel->feldSize();
    p.drawEllipse(QRectF(feldSize*_x, feldSize*_y+PADDING_TOP, feldSize, feldSize)); //x,y,w,h
    p.end();

    QWidget::paintEvent(event);
}

bool Spieler::bewegen(const int dX, const int dY) {
    if(_insel->darfBetretenWerden(_x+dX,_y+dY) && _lblSchritte.getValue()>0) {
        _x+=dX;
        _y+=dY;
        _lblSchritte.add(-1);
        update();
        return true;
    } else {
        return false;
    }
}

bool Spieler::trockenlegen(const int dX, const int dY) {
    if(_insel->gibStatus(_x+dX,_y+dY)==1 && _lblSchritte.getValue()>0) {
        _insel->trockenlegen(_x+dX,_y+dY);
        _lblSchritte.add(-1);
        _lblPunkte.add(1);
        update();
        return true;
    } else {
        return false;
    }
}

bool Spieler::nehmen(const int dX, const int dY) {
    if(_insel->gibGegenstandstyp(_x+dX,_y+dY)!=KEIN) {
        Gegenstandstyp g=_insel->gegenstandNehmen(_x+dX,_y+dY);
        switch(g) {
            case KEIN: break;
            case PUNKTE: _lblPunkte.add(50); break;
            case SCHRITTE: _lblSchritte.add(3); break;
            case FLUTLEVEL: _insel->flutlevelSenken(3); break;
        }

        _lblSchritte.add(-1);
        _lblPunkte.add(50);
        update();
        return true;
    } else {
        return false;
    }
}

int Spieler::gibVerbliebeneSchritte() const {
    return _lblSchritte.getValue();
}

void Spieler::naechsteRunde() {
    _lblSchritte.setValue(3);
}

void Spieler::punkteHinzufuegen(int n) {
    _lblPunkte.add(n);
}

bool Spieler::istTot() {
    return !_insel->darfBetretenWerden(_x,_y);
}

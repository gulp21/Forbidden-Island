/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "Insel.h"

Insel::Insel(QWidget *parent) {
    setParent(parent);
    move(0,PADDING_TOP);
    resize(maximumSize());
    bool b=true;
    flutkartenstapel_.karteHinzufuegen(b);
    flutkartenstapel_.karteHinzufuegen(b);
    b=false;
    for(int i=0; i<8; i++) flutkartenstapel_.karteHinzufuegen(b);
    flutkartenstapel_.mischen();
    flutlevel_=0;
    untergegangeneFelder_=0;
    setVisible(true);
}

float Insel::feldSize() const {
    float ysize = (static_cast<float>(parentWidget()->geometry().height())-PADDING_TOP)/insel_.length();
    float xsize = static_cast<float>(parentWidget()->geometry().width())/insel_[0].length();
    return (xsize < ysize) ? xsize : ysize;
}

void Insel::paintEvent(QPaintEvent * /*event*/) {
    QPainter p(this);
    p.setPen(Qt::black);

    float size = feldSize();

    for (int i=0; i<insel_.length(); i++) {
        for (int j=0; j<insel_[i].length(); j++) {
            if (insel_[i][j]->gibStatus() == 0) {
                p.setBrush(Qt::yellow);
                p.drawRect(QRectF(j*size, i*size, size, size)); //x,y,w,h
                p.fillRect(QRectF(j*size, i*size, size, size), Qt::Dense6Pattern);
            }
            else if (insel_[i][j]->gibStatus() == 1) {
                p.setBrush(Qt::cyan);
                p.drawRect(QRectF(j*size, i*size, size, size)); //x,y,w,h
            }
            else if (insel_[i][j]->gibStatus() == 2) {
                p.setBrush(Qt::blue);
                p.drawRect(QRectF(j*size, i*size, size, size)); //x,y,w,h
            }
            // Gegenstände zeichnen
            switch (insel_[i][j]->gibGegenstandstyp()) {
                case KEIN:
                    break;
                case PUNKTE:
                    p.setBrush(Qt::yellow);
                    p.drawEllipse(QRectF(j*size+(size/4), i*size+(size/4), size-(size/2), size-(size/2))); //x,y,w,h
                    break;
                case SCHRITTE:
                    p.setBrush(Qt::black);
                    p.drawEllipse(QRectF(j*size+(size/4), i*size+(size/4), size-(size/2), size-(size/2))); //x,y,w,h
                    break;
                case FLUTLEVEL:
                    p.setBrush(Qt::gray);
                    p.drawEllipse(QRectF(j*size+(size/4), i*size+(size/4), size-(size/2), size-(size/2))); //x,y,w,h
                    break;
            }
        }
    }
    p.end();
}

void Insel::zeileAnhaengen(const QList<Feld *> zeile) {
    insel_.append(zeile);
    for (int i=0; i<zeile.length(); i++) {
        //qDebug() << i;
        feldkartenstapel_.karteHinzufuegen(zeile[i]);
        if (zeile[i]->gibStatus() == 2) {
             untergegangeneFelder_++;
        }
    }
    feldkartenstapel_.mischen();
    inselgroesse_=insel_[0].length()*insel_.length();
}

void Insel::fluten(const int x, const int y) {
    insel_[y][x]->fluten();
    if(insel_[y][x]->gibStatus()==2)
        untergegangeneFelder_++;
}

void Insel::trockenlegen(const int x, const int y) {
    if(insel_[y][x]->gibStatus()==2)
        untergegangeneFelder_--;
    insel_[y][x]->trockenlegen();
}

short int Insel::gibStatus(const int x, const int y) const {
	if(x<0 || y<0 || y>=insel_.length() || x>=insel_[0].length())
		return -1;
	return insel_[y][x]->gibStatus();
}

Gegenstandstyp Insel::gibGegenstandstyp(const int x, const int y) const {
    if(x<0 || y<0 || y>=insel_.length() || x>=insel_[0].length())
        return KEIN;
    return insel_[y][x]->gibGegenstandstyp();
}

Gegenstandstyp Insel::gegenstandNehmen(const int x, const int y) {
    Gegenstandstyp g;
    g=gibGegenstandstyp(x, y);
    insel_[y][x]->gegenstandEntfernen();
    return g;
}

bool Insel::darfBetretenWerden(const int x, const int y) const {
	return (gibStatus(x,y)==1 || gibStatus(x,y)==0);
}

void Insel::gegenstandAblegen(const int x, const int y, const Gegenstandstyp typ) {
    insel_[y][x]->gegenstandAblegen(typ);
}

bool Insel::flutmanager() {
    bool returnValue=false;

    if(flutkartenstapel_.karteZiehen()) {
        flutlevel_++;
        feldkartenstapel_.gezogeneMischen();
        returnValue=true;
    }
    qDebug() << "Flutlevel:" << flutlevel_ << inselgroesse_ << untergegangeneFelder_;

    for(int i=0; (i<flutlevel_) && (untergegangeneFelder_ < inselgroesse_); i++) {
        Feld *f;
        // nicht überflutetes Feld finden
        do {
            f=feldkartenstapel_.karteZiehen();
        } while(f->gibStatus()==2);
        f->fluten();
        if(f->gibStatus()==2)
            untergegangeneFelder_++;
    }

    return returnValue;
}

void Insel::flutlevelSenken(int n) {
    flutlevel_-=n;
    if(flutlevel_<0)
        flutlevel_=0;
}

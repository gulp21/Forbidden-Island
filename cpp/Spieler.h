/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SPIELER_H
#define SPIELER_H

#include <QObject>
#include <qpainter.h>
#include "CountingLabel.h"
#include "Insel.h"

class Spieler : public QWidget {
    private:
        //! Position des Spielers auf der Insel
        int _x, _y;
        CountingLabel _lblPunkte, _lblSchritte;
        //! Insel, auf der sich der Spieler befindet
        Insel *_insel;
        //! zeichnet den Spieler
        void paintEvent(QPaintEvent *event);

    public:
        //! legt einen neuen Spieler an der Position @param x, @param y an,
        //! der sich in @param parent zeichnet und auf der Insel @param insel steht
        explicit Spieler(QWidget *parent, Insel *insel, const int x, const int y);
        //! bewegt den Spieler um @param dX nach links/rechts und @param dY nach oben/unten
        //! @returns true, wenn die Aktion erfolgreich (d.h. erlaubt) war
        //! in diesem Fall wird Schrittezähler um eins verringert
        bool bewegen(const int dX, const int dY);
        //! legt das entsprechende Feld neben dem Spieler trocken
        //! @returns true, wenn die Aktion erfolgreich (d.h. erlaubt) war;
        //! in diesem Fall werden ein Punkt hinzugefügt und der Schrittezähler um eins verringert
        bool trockenlegen(const int dX, const int dY);
        //! nimmt den Gegenstand des entsprechenden Felds neben dem Spieler auf
        //! @returns true, wenn ein Gegenstand aufgenommen werden konnte
        bool nehmen(const int dX, const int dY);
        //! @returns die Anzahl der verbliebenen Schritte
        int gibVerbliebeneSchritte() const;
        //! beginnt die nächste Runde, indem die Anzahl der verbliebenen Schritte auf 3 gesetzt wird
        void naechsteRunde();
        //! fügt @param n Punkte hinzu
        void punkteHinzufuegen(int n);
        //! @returns true, wenn der Spieler auf einem untergegangenen Feld steht
        bool istTot();
    
};

#endif // SPIELER_H

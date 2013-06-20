/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _Insel_
#define _Insel_

#include "Feld.h"
#include "Kartenstapel.h"
#include <QDebug>
#include <QList>
#include <QObject>
#include <QWidget>
#include <qpainter.h>

const int PADDING_TOP=20;

/*!
 * \brief Repsäentiert eine Insel, d.h. eine rechteckige Anordnung von Feldern
 * \see \class Feld
 */

class Insel : public QWidget {
	private:
        //! repräsentiert die Insel
        //! intern werden die Koordinaten von 0 bis n-1 gezählt
		//! [zeile][spalte]
        QList< QList<Feld*> > insel_;
        Kartenstapel<bool> flutkartenstapel_;
        Kartenstapel<Feld*> feldkartenstapel_;
        int flutlevel_;
        int untergegangeneFelder_;
        //! Anzahl der Inselfelder
        int inselgroesse_;
        //! zeichnet alle Felder mit ihren Gegenständen; die Größe passt sich an die Größe des Fensters an
        void paintEvent(QPaintEvent *event);
		
	public:
		//! erstellt eine neue Insel
        Insel(QWidget *parent);
        //! Zeile von Feldern zur Insel hinzufügen
        void zeileAnhaengen(const QList<Feld *> zeile);
        //! überflutet das Feld mit den Koordinaten @param x und @param y
        void fluten(const int x, const int y);
        //! legt das Feld mit den Koordinaten @param x und @param y trocken
        void trockenlegen(const int x, const int y);
        //! @returns den Status des Feldes mit den Koordinaten @param x und @param y
        //! (gibt -1 zurück, wenn das Feld nicht existiert)
        short int gibStatus(const int x, const int y) const;
        //! @returns den Typ des Gegenstades des Feldes mit den Koordinaten @param x und @param y
        Gegenstandstyp gibGegenstandstyp(const int x, const int y) const;
        //! @returns den Typ des Gegenstades des Feldes mit den Koordinaten @param x und @param y und entfernt des Gegenstand
        Gegenstandstyp gegenstandNehmen(const int x, const int y);
        //! @returns true, wenn das Feld mit den Koordinaten @param x und @param y nicht untergegangen ist
        bool darfBetretenWerden(const int x, const int y) const;
        //! legt auf dem Felde mit den Koordinaten @param x und @param y einen gegenstand vom Typ @param typ ab
        void gegenstandAblegen(const int x, const int y, const Gegenstandstyp typ);
        //! @returns die Seitenlänge eines Feldes abhängig von der Fenstergröße
        float feldSize() const;
        //! steuert das Flutlevel durch ziehen von Feld- und Flurkarten und überflutet entsprechende Felder
        //! @returns true, wenn das Flutlevel erhöht wurde
        bool flutmanager();
        //! senkt das Flutlevel um @param n und stellt sicher, dass es nicht kleiner als 0 wird
        void flutlevelSenken(int n);
};

#endif // _Insel_

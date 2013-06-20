/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _Feld_
#define _Feld_

#include <QList>
#include <QDebug>

enum Gegenstandstyp {
    KEIN=0,
    PUNKTE=1,
    SCHRITTE=2,
    FLUTLEVEL=3
};

/*!
 * \brief Repräsentiert ein einzelnes Inselfeld, d.h. Status und Gegenstand
 */

class Feld {
	private:
		//! 0: trocken, 1: geflutet, 2: untergegangen;
        short status_;
        Gegenstandstyp gegenstand_;
		
	public:
		//! erstellt eine neue Insel
        Feld(const char status);
        //! erhöht den Status um 1 (trocken -> geflutet, geflutet -> untergegangen)
		void fluten();
        //! setzt den Status auf 0 (trocken)
		void trockenlegen();
        //! @returns den Status
        short gibStatus() const;
        //! legt auf dem Feld einen Gegenstand vom Typ @param typ ab
        void gegenstandAblegen(const Gegenstandstyp typ);
        //! @returns den Typ des Gegenstandes auf dem Feld (evtl. KEIN)
        Gegenstandstyp gibGegenstandstyp() const;
        //! entfernt den Gegenstand des Feldes
        void gegenstandEntfernen();
};

#endif // _Feld_

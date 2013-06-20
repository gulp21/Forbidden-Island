/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KARTENSTAPEL_H
#define KARTENSTAPEL_H

#include <QList>
#include <QDebug>
#include "Feld.h"

/*!
 * \brief Template-Klasse für einen Kartenstapel
 */

template<typename T>
class Kartenstapel {
    private:
        //! aktuelle Position im Stapel (d.h. _pos Karten wurde bisher gezogen)
        int _pos;
        QList<T> _karten;
    public:
        //! erstellt einen leeren Kartenstapel
        Kartenstapel() {
            _pos=0;
        }
        
        //! @param n: bis zur Karte n mischen
        void mischen(const int n) {
            for(int i=2*_karten.length(); i>0; i--) {
                int a=rand()%(n+1);
                int b=rand()%(n+1);
                T tmp=_karten[a];
                _karten[a]=_karten[b];
                _karten[b]=tmp;
            }
        }
        
        //! mischt den gesamten Stepel
        void mischen() {
            mischen(_karten.length()-1);
        }

        //! mischt alle Karten, die bisher gezogen wurden
        void gezogeneMischen() {
            mischen(_pos);
            _pos=0;
        }
        
        //! fügt die Karte @param karte zum Stapel hinzu
        void karteHinzufuegen(const T &karte) {
            _karten.append(karte);
        }
        
        //! @returns die oberste (d.h. _pos+1. Karte) Karte und legt diese zu Seite
        T karteZiehen() {
            if(_pos>=_karten.length()) {
                _pos=0;
                mischen();
            }
            return _karten[_pos++];
        }
};

#endif // KARTENSTAPEL_H

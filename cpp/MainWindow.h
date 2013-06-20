/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include <QMainWindow>
#include <QKeyEvent>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QStringList>

#include "Insel.h"
#include "Spieler.h"

/*!
 * \brief Hauptfenster, welches Spieler und Insel enthält und die Gameloop steuert
 * \see \class Insel
 * \see \class Spieler
 */

class MainWindow : public QMainWindow {
	private:
		void keyPressEvent(QKeyEvent *event);
        //! startet ein neues Spiel durch Aufrufen von _init und _gameLoopStart
        void _newGame();
        //! initialisiert Insel und Spieler, bestehende Inseln und Spieler werden ggf. zerstört
        //! die Insel, Gegenstände und die Startposition des Spielers werden aus einer Textdatei eingelesen
        void _init();
        //! weist den Spieler an, die nächste Runde zu starten
        void _gameLoopStart();
        //! prüft, ob der Spieler tot ist, ruft Flutmanager der Insel auf bzw. zeigt Spiel-zu-Ende-Meldung
        void _gameLoopEnd();
        //! zeigt die Spiel-zu-Ende-Meldung und fragt, ob ein neues Spiel gestartet werden soll
        void _gameEndMessage();

        Insel* _insel;
        Spieler* _spieler;
	
	public:
        //! erstellt ein neues Hauptfenster und startet ein neues Spiel
		MainWindow();
        //! zerstört Spieler und Insel
        ~MainWindow();
};

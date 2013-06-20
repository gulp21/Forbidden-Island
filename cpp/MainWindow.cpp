/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "MainWindow.h"

MainWindow::MainWindow() {
    resize(500,500);
    _insel=0;
    _spieler=0;
    _newGame();
}

MainWindow::~MainWindow() {
    delete _insel;
    delete _spieler;
}

void MainWindow::_newGame() {
    _init();
    _gameLoopStart();
}

void MainWindow::_init() {
    if(_insel!=0) {
        delete _insel;
    }

    QFile feldDatei("feld.txt");
    feldDatei.open(QIODevice::ReadOnly);

    QString zeile;

    do { // while zeile!="GAMEBOARDEND"
        zeile=feldDatei.readLine();
        //qDebug() << zeile;
        if(zeile.startsWith("GAMEBOARDSTART")) {
            QStringList werte=zeile.split(QRegExp("[ ,]"));
            _insel=new Insel(this);
            for(int i=0; i<werte[2].toInt(); i++) {
                zeile=feldDatei.readLine();
                QList<Feld*> inselzeile;
                for(int j=0; j<werte[1].toInt(); j++) {
                    Feld *f=new Feld(zeile[j].toLatin1());
                    inselzeile.append(f);
                }
                _insel->zeileAnhaengen(inselzeile);
            } // for each Zeile
        } // if GAMEBOARDSTART
    } while(!zeile.startsWith("GAMEBOARDEND"));

    zeile=feldDatei.readLine();

    while(!zeile.startsWith("ROUND")) { // while zeile != "ROUND"
        QStringList gegenstand=zeile.split(",");
        _insel->gegenstandAblegen(gegenstand[0].toInt()-1, gegenstand[1].toInt()-1,
                                  static_cast<Gegenstandstyp>(gegenstand[2].toInt()));
        zeile=feldDatei.readLine();
    }

    QStringList startposition=zeile.split(QRegExp("[ ,]")); //startposition[2]: x, startposition[3]: y

    feldDatei.close();

    if(_spieler!=0) {
        delete _spieler;
    }
    _spieler=new Spieler(this, _insel, startposition[2].toInt()-1, startposition[3].toInt()-1);

}

void MainWindow::_gameLoopStart() {
    _spieler->naechsteRunde();
}

void MainWindow::_gameLoopEnd() {
    if(_insel->flutmanager()) {
        _spieler->punkteHinzufuegen(-1);
    }
    if (!_spieler->istTot()) {
        _gameLoopStart();
    } else {
        qDebug() << "ende";
        update();
        // Spiel beendet
        _gameEndMessage();
    }
}

void MainWindow::_gameEndMessage() {
    QMessageBox msgBox;
    msgBox.setText("Sie sind ertrunken.");
    QPushButton *newGameButton = msgBox.addButton("Neues Spiel", QMessageBox::AcceptRole);
    msgBox.addButton("Beenden", QMessageBox::RejectRole);

    msgBox.exec();

    if(msgBox.clickedButton()==reinterpret_cast<QAbstractButton*>(newGameButton)) {
        _newGame();
    } else {
        close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Trockenlegen von Feldern
    if(event->modifiers()==Qt::ShiftModifier) {
        if(event->key()==Qt::Key_5 || event->key()==Qt::Key_Return) {
            qDebug() << "DRY CURRENT";
            _spieler->trockenlegen(0,0);
        } else if(event->key()==Qt::Key_6 || event->key()==Qt::Key_Right) {
            qDebug() << "DRY EAST";
            _spieler->trockenlegen(1,0);
        } else if(event->key()==Qt::Key_2 || event->key()==Qt::Key_Down) {
            qDebug() << "DRY SOUTH";
            _spieler->trockenlegen(0,1);
        } else if(event->key()==Qt::Key_4 || event->key()==Qt::Key_Left) {
            qDebug() << "DRY WEST";
            _spieler->trockenlegen(-1,0);
        } else if(event->key()==Qt::Key_8 || event->key()==Qt::Key_Up) {
            qDebug() << "DRY NORTH";
            _spieler->trockenlegen(0,-1);
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
    // Aufnehmen von Gegenständen
    } else if(event->modifiers()==Qt::AltModifier) {
        if(event->key()==Qt::Key_5 || event->key()==Qt::Key_Return) {
            qDebug() << "TAKE CURRENT";
            _spieler->nehmen(0,0);
        } else if(event->key()==Qt::Key_6 || event->key()==Qt::Key_Right) {
            qDebug() << "TAKE EAST";
            _spieler->nehmen(1,0);
        } else if(event->key()==Qt::Key_2 || event->key()==Qt::Key_Down) {
            qDebug() << "TAKE SOUTH";
            _spieler->nehmen(0,1);
        } else if(event->key()==Qt::Key_4 || event->key()==Qt::Key_Left) {
            qDebug() << "TAKE WEST";
            _spieler->nehmen(-1,0);
        } else if(event->key()==Qt::Key_8 || event->key()==Qt::Key_Up) {
            qDebug() << "TAKE NORTH";
            _spieler->nehmen(0,-1);
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
     } else if(event->modifiers()==Qt::ControlModifier) {
        if(event->key()== Qt::Key_N) {
            qDebug() << "Neues Spiel";
            _newGame();
        } else if(event->key()==Qt::Key_Q){
            qDebug() << "Spiel beenden";
            close();
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
     // Spieler bewegen
     } else {
        if(event->key()==Qt::Key_5 || event->key()==Qt::Key_Return) {
            qDebug() << "GO CURRENT";
            _spieler->bewegen(0,0);
        } else if(event->key()==Qt::Key_6 || event->key()==Qt::Key_Right) {
            qDebug() << "GO EAST";
            _spieler->bewegen(1,0);
        } else if(event->key()==Qt::Key_2 || event->key()==Qt::Key_Down) {
            qDebug() << "GO SOUTH";
            _spieler->bewegen(0,1);
        } else if(event->key()==Qt::Key_4 || event->key()==Qt::Key_Left) {
            qDebug() << "GO WEST";
            _spieler->bewegen(-1,0);
        } else if(event->key()==Qt::Key_8 || event->key()==Qt::Key_Up) {
            qDebug() << "GO NORTH";
            _spieler->bewegen(0,-1);
        } else {
            QWidget::keyPressEvent(event);
            return;
        }
    }
    
    if(_spieler->gibVerbliebeneSchritte()==0) {
        _gameLoopEnd();
    }/* else if(_spieler->istTot()) {
        qDebug() << "ende";
        _gameEndMessage();
    }*/
}

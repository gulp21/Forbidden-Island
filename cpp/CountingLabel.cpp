/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "CountingLabel.h"

CountingLabel::CountingLabel() {
    _value=0;
    setStyleSheet("color:purple;font-size:20px;");
}

void CountingLabel::setCaption(const QString str) {
    _caption=str;
}

void CountingLabel::paintEvent(QPaintEvent *event) {
    setText(QString("%1: %2").arg(_caption).arg(_value));
    QLabel::paintEvent(event);
}

void CountingLabel::add(const int n) {
    _value+=n;
    update();
}

int CountingLabel::getValue() const {
    return _value;
}


void CountingLabel::setValue(const int n) {
    _value=n;
    update();
}

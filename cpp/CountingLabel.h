/*
Verbotene Insel
Copyright (C) 2013 Markus Brenneis, Lucas Gersch, Alexander Matheisen

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COUNTINGLABEL_H
#define COUNTINGLABEL_H

#include <QLabel>

/*!
 * \brief Constructs a label with the text "caption: value"
 */
class CountingLabel : public QLabel {
    private:
        int _value;
        QString _caption;
        void paintEvent(QPaintEvent *event);
    public:
        CountingLabel();
        //! sets the caption of the label to @param str
        void setCaption(const QString str);
        //! adds @param n to the value and repaints the label
        void add(const int n);
        //! @returns the value of the label
        int getValue() const;
        //! sets value to @param n and repaints the label
        void setValue(const int n);
};

//CountingLabel operator+(CountingLabel const& lhs, int const& rhs);

#endif // COUNTINGLABEL_H

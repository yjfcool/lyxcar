/*  This file is part of the KDE project
    Copyright (C) 2006-2007 Matthias Kretz <kretz@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), Trolltech ASA 
    (or its successors, if any) and the KDE Free Qt Foundation, which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public 
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PHONON_UI_EFFECTWIDGET_P_H
#define PHONON_UI_EFFECTWIDGET_P_H

#include "effectwidget.h"
#include "effectparameter.h"
#include <QtCore/QHash>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_PHONON_EFFECTWIDGET

namespace Phonon
{
    class EffectWidgetPrivate
    {
        Q_DECLARE_PUBLIC(EffectWidget)
        protected:
            EffectWidgetPrivate(Effect *effect);

            EffectWidget *q_ptr;

        private:
            Effect *effect;
            QHash<QObject *, EffectParameter> parameterForObject;

            void _k_setToggleParameter(bool checked);
            void _k_setIntParameter(int value);
            void _k_setDoubleParameter(double value);
            void _k_setStringParameter(const QString &);
            void _k_setSliderParameter(int);

            void autogenerateUi();
    };
} // namespace Phonon

#endif //QT_NO_PHONON_EFFECTWIDGET

QT_END_NAMESPACE

#endif // PHONON_UI_EFFECTWIDGET_P_H

// vim: sw=4 ts=4 tw=80

/*
 * Copyright (C) 2008-2009 Pavlov Denis
 *
 * Comments unavailable.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
*/

#include "jogdial.h"

ALyxJogdial::ALyxJogdial(QWidget *parent, ASkinner *s) : 
    ALyxControl(parent) {
    
}

ALyxJogdial::~ALyxJogdial() {
    qDebug() << "ALyxJogdial destroyed";
}

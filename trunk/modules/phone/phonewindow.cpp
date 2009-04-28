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

#include "phonewindow.h"

phoneWindow::phoneWindow(QWidget *parent, ASkinner *skinner, Phonon::AudioOutput *output) {
    QLabel *phoneLabel = new QLabel(this);
    phoneLabel->setText("SonyEricsson K510");
    phoneLabel->move(10, 10);
    phoneLabel->setFixedSize(200, 30);
    phoneLabel->setFont(QFont("Calibri", 16));

    phoneButtons[0][0] = new QPushButton("1", this);
    phoneButtons[0][0]->setFixedSize(80, 80);
    phoneButtons[0][0]->move(10, 50);

    phoneButtons[1][0] = new QPushButton("2", this);
    phoneButtons[1][0]->setFixedSize(80, 80);
    phoneButtons[1][0]->move(100, 50);

    phoneButtons[2][0] = new QPushButton("3", this);
    phoneButtons[2][0]->setFixedSize(80, 80);
    phoneButtons[2][0]->move(190, 50);

    phoneButtons[0][1] = new QPushButton("4", this);
    phoneButtons[0][1]->setFixedSize(80, 80);
    phoneButtons[0][1]->move(10, 140);

    phoneButtons[1][1] = new QPushButton("5", this);
    phoneButtons[1][1]->setFixedSize(80, 80);
    phoneButtons[1][1]->move(100, 140);

    phoneButtons[2][1] = new QPushButton("6", this);
    phoneButtons[2][1]->setFixedSize(80, 80);
    phoneButtons[2][1]->move(190, 140);

    phoneButtons[0][2] = new QPushButton("7", this);
    phoneButtons[0][2]->setFixedSize(80, 80);
    phoneButtons[0][2]->move(10, 230);

    phoneButtons[1][2] = new QPushButton("8", this);
    phoneButtons[1][2]->setFixedSize(80, 80);
    phoneButtons[1][2]->move(100, 230);

    phoneButtons[2][2] = new QPushButton("9", this);
    phoneButtons[2][2]->setFixedSize(80, 80);
    phoneButtons[2][2]->move(190, 230);

    phoneButtons[0][3] = new QPushButton("*", this);
    phoneButtons[0][3]->setFixedSize(80, 80);
    phoneButtons[0][3]->move(10, 320);

    phoneButtons[1][3] = new QPushButton("0", this);
    phoneButtons[1][3]->setFixedSize(80, 80);
    phoneButtons[1][3]->move(100, 320);

    phoneButtons[2][3] = new QPushButton("#", this);
    phoneButtons[2][3]->setFixedSize(80, 80);
    phoneButtons[2][3]->move(190, 320);
    
    QLineEdit *phoneNumber = new QLineEdit(this);
    phoneNumber->resize(350, 50);
    phoneNumber->move(300, 25);
    phoneNumber->setFont(QFont("Calibri", 20));
    phoneNumber->setReadOnly(true);
    phoneNumber->setText("+74232316158");
    
    ALyxListWidget *contactsList = new ALyxListWidget(this);
    contactsList->move(300, 100);
    contactsList->setFixedSize(350, 320);
    
    ALyxListWidgetItem *item = new ALyxListWidgetItem(contactsList, "Contact 1\n+79024809956");
    contactsList->addItem(item);
}

phoneWindow::~phoneWindow() {

}

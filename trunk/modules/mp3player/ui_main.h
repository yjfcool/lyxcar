/********************************************************************************
** Form generated from reading ui file 'main.ui'
**
** Created: Fri 23. Jan 09:33:28 2009
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_mp3player
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *frame_3;
    QVBoxLayout *vboxLayout1;
    QLabel *titleLabel;
    QSlider *timeLine;
    QFrame *visualWidget;
    QVBoxLayout *vboxLayout2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *hboxLayout;
    QTextEdit *testText;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QToolButton *toolButton;
    QTreeView *mediaTree;
    QTreeWidget *playListTree;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QSpacerItem *spacerItem;
    QWidget *tab_3;
    QFrame *frame;
    QHBoxLayout *hboxLayout1;
    QToolButton *firstBtn;
    QToolButton *prevBtn;
    QToolButton *playBtn;
    QToolButton *nextBtn;
    QToolButton *lastBtn;
    QToolButton *ejectBtn;

    void setupUi(QWidget *mp3player)
    {
    if (mp3player->objectName().isEmpty())
        mp3player->setObjectName(QString::fromUtf8("mp3player"));
    mp3player->resize(645, 494);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(mp3player->sizePolicy().hasHeightForWidth());
    mp3player->setSizePolicy(sizePolicy);
    vboxLayout = new QVBoxLayout(mp3player);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    frame_3 = new QFrame(mp3player);
    frame_3->setObjectName(QString::fromUtf8("frame_3"));
    sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
    frame_3->setSizePolicy(sizePolicy);
    frame_3->setMinimumSize(QSize(16, 100));
    frame_3->setMaximumSize(QSize(16777215, 130));
    frame_3->setFrameShape(QFrame::StyledPanel);
    frame_3->setFrameShadow(QFrame::Sunken);
    vboxLayout1 = new QVBoxLayout(frame_3);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    titleLabel = new QLabel(frame_3);
    titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
    QFont font;
    font.setPointSize(20);
    titleLabel->setFont(font);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);

    vboxLayout1->addWidget(titleLabel);

    timeLine = new QSlider(frame_3);
    timeLine->setObjectName(QString::fromUtf8("timeLine"));
    timeLine->setOrientation(Qt::Horizontal);
    timeLine->setTickPosition(QSlider::TicksBelow);

    vboxLayout1->addWidget(timeLine);


    vboxLayout->addWidget(frame_3);

    visualWidget = new QFrame(mp3player);
    visualWidget->setObjectName(QString::fromUtf8("visualWidget"));
    visualWidget->setFrameShape(QFrame::StyledPanel);
    visualWidget->setFrameShadow(QFrame::Sunken);
    vboxLayout2 = new QVBoxLayout(visualWidget);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    tabWidget = new QTabWidget(visualWidget);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    QFont font1;
    font1.setPointSize(16);
    tabWidget->setFont(font1);
    tabWidget->setIconSize(QSize(32, 32));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    hboxLayout = new QHBoxLayout(tab);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    testText = new QTextEdit(tab);
    testText->setObjectName(QString::fromUtf8("testText"));

    hboxLayout->addWidget(testText);

    tabWidget->addTab(tab, QIcon(QString::fromUtf8("../skins/default/icons/office.png")), QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    gridLayout = new QGridLayout(tab_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    toolButton = new QToolButton(tab_2);
    toolButton->setObjectName(QString::fromUtf8("toolButton"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
    toolButton->setSizePolicy(sizePolicy1);
    toolButton->setIcon(QIcon(QString::fromUtf8("../skins/default/icons/cdplayer.png")));
    toolButton->setIconSize(QSize(32, 32));
    toolButton->setCheckable(true);
    toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    gridLayout->addWidget(toolButton, 0, 0, 1, 1);

    mediaTree = new QTreeView(tab_2);
    mediaTree->setObjectName(QString::fromUtf8("mediaTree"));
    mediaTree->setAnimated(true);

    gridLayout->addWidget(mediaTree, 0, 1, 4, 1);

    playListTree = new QTreeWidget(tab_2);
    playListTree->setObjectName(QString::fromUtf8("playListTree"));
    playListTree->setColumnCount(2);

    gridLayout->addWidget(playListTree, 0, 2, 4, 1);

    toolButton_2 = new QToolButton(tab_2);
    toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
    sizePolicy1.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
    toolButton_2->setSizePolicy(sizePolicy1);
    toolButton_2->setIcon(QIcon(QString::fromUtf8("../skins/default/icons/mp3player.png")));
    toolButton_2->setIconSize(QSize(32, 32));
    toolButton_2->setCheckable(true);
    toolButton_2->setChecked(true);
    toolButton_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    gridLayout->addWidget(toolButton_2, 1, 0, 1, 1);

    toolButton_3 = new QToolButton(tab_2);
    toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
    sizePolicy1.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
    toolButton_3->setSizePolicy(sizePolicy1);
    toolButton_3->setIcon(QIcon(QString::fromUtf8("../skins/default/icons/usbflash.png")));
    toolButton_3->setIconSize(QSize(32, 32));
    toolButton_3->setCheckable(true);
    toolButton_3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    gridLayout->addWidget(toolButton_3, 2, 0, 1, 1);

    spacerItem = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 3, 0, 1, 1);

    tabWidget->addTab(tab_2, QIcon(QString::fromUtf8("../skins/default/icons/www.png")), QString());
    tab_3 = new QWidget();
    tab_3->setObjectName(QString::fromUtf8("tab_3"));
    tabWidget->addTab(tab_3, QIcon(QString::fromUtf8("../skins/default/icons/cdplayer.png")), QString());

    vboxLayout2->addWidget(tabWidget);


    vboxLayout->addWidget(visualWidget);

    frame = new QFrame(mp3player);
    frame->setObjectName(QString::fromUtf8("frame"));
    sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy1);
    frame->setAutoFillBackground(false);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    hboxLayout1 = new QHBoxLayout(frame);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    firstBtn = new QToolButton(frame);
    firstBtn->setObjectName(QString::fromUtf8("firstBtn"));
    sizePolicy.setHeightForWidth(firstBtn->sizePolicy().hasHeightForWidth());
    firstBtn->setSizePolicy(sizePolicy);
    firstBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_start.png")));
    firstBtn->setIconSize(QSize(32, 32));
    firstBtn->setAutoRaise(true);

    hboxLayout1->addWidget(firstBtn);

    prevBtn = new QToolButton(frame);
    prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
    sizePolicy.setHeightForWidth(prevBtn->sizePolicy().hasHeightForWidth());
    prevBtn->setSizePolicy(sizePolicy);
    prevBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_rew.png")));
    prevBtn->setIconSize(QSize(32, 32));
    prevBtn->setAutoRaise(true);

    hboxLayout1->addWidget(prevBtn);

    playBtn = new QToolButton(frame);
    playBtn->setObjectName(QString::fromUtf8("playBtn"));
    sizePolicy.setHeightForWidth(playBtn->sizePolicy().hasHeightForWidth());
    playBtn->setSizePolicy(sizePolicy);
    playBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_play.png")));
    playBtn->setIconSize(QSize(32, 32));
    playBtn->setAutoRaise(true);

    hboxLayout1->addWidget(playBtn);

    nextBtn = new QToolButton(frame);
    nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
    sizePolicy.setHeightForWidth(nextBtn->sizePolicy().hasHeightForWidth());
    nextBtn->setSizePolicy(sizePolicy);
    nextBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_fwd.png")));
    nextBtn->setIconSize(QSize(32, 32));
    nextBtn->setAutoRaise(true);

    hboxLayout1->addWidget(nextBtn);

    lastBtn = new QToolButton(frame);
    lastBtn->setObjectName(QString::fromUtf8("lastBtn"));
    sizePolicy.setHeightForWidth(lastBtn->sizePolicy().hasHeightForWidth());
    lastBtn->setSizePolicy(sizePolicy);
    lastBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_end.png")));
    lastBtn->setIconSize(QSize(32, 32));
    lastBtn->setAutoRaise(true);

    hboxLayout1->addWidget(lastBtn);

    ejectBtn = new QToolButton(frame);
    ejectBtn->setObjectName(QString::fromUtf8("ejectBtn"));
    sizePolicy.setHeightForWidth(ejectBtn->sizePolicy().hasHeightForWidth());
    ejectBtn->setSizePolicy(sizePolicy);
    ejectBtn->setIcon(QIcon(QString::fromUtf8("../skins/default/mp3player/player_eject.png")));
    ejectBtn->setIconSize(QSize(32, 32));
    ejectBtn->setAutoRaise(true);

    hboxLayout1->addWidget(ejectBtn);


    vboxLayout->addWidget(frame);


    retranslateUi(mp3player);

    tabWidget->setCurrentIndex(1);


    QMetaObject::connectSlotsByName(mp3player);
    } // setupUi

    void retranslateUi(QWidget *mp3player)
    {
    mp3player->setWindowTitle(QApplication::translate("mp3player", "Form", 0, QApplication::UnicodeUTF8));
    titleLabel->setText(QApplication::translate("mp3player", "Artist - Album - Title song #1 (03:32)", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("mp3player", "Test tab", 0, QApplication::UnicodeUTF8));
    toolButton->setText(QApplication::translate("mp3player", "CD disc", 0, QApplication::UnicodeUTF8));
    playListTree->headerItem()->setText(0, QApplication::translate("mp3player", "1", 0, QApplication::UnicodeUTF8));
    playListTree->headerItem()->setText(1, QApplication::translate("mp3player", "2", 0, QApplication::UnicodeUTF8));
    toolButton_2->setText(QApplication::translate("mp3player", "Files", 0, QApplication::UnicodeUTF8));
    toolButton_3->setText(QApplication::translate("mp3player", "Usb flash", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mp3player", "Playlists", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mp3player", "Visualizing", 0, QApplication::UnicodeUTF8));
    firstBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    prevBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    playBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    nextBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    lastBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    ejectBtn->setText(QApplication::translate("mp3player", "...", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(mp3player);
    } // retranslateUi

};

namespace Ui {
    class mp3player: public Ui_mp3player {};
} // namespace Ui

#endif // UI_MAIN_H

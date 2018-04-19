#include "createnew.h"

CreateNew::CreateNew(QWidget *parent) : QWidget(parent)
{
    // call function for initialize widgets

    this->initializeWidgets();

    // connect signals with slots

    connect(buttonCancel, SIGNAL(clicked(bool)), this, SLOT(pressButtonCancel()));
    connect(buttonOK, SIGNAL(clicked(bool)), this, SLOT(pressButtonOK()));
}

CreateNew::~CreateNew()
{
    labelInfo->deleteLater();
    lineEditName->deleteLater();
    buttonCancel->deleteLater();
    buttonOK->deleteLater();
    hLayoutButtons->deleteLater();
    mainLayout->deleteLater();
    splitter->deleteLater();

    delete item;
}

void CreateNew::closeEvent(QCloseEvent *event)
{
    if (pressedCancel && !pressedOK)
        emit closeWindow("__ignore__");

    if (pressedOK && !pressedCancel)
        emit closeWindow(this->lineEditName->text());

    pressedCancel = false;
    pressedOK = false;

    event->accept();
}

void CreateNew::initializeWidgets()
{
    // Initialize object of QLabel

    labelInfo = new QLabel();

    // Initialize object of QLineEdit

    lineEditName = new QLineEdit();

    // Initialize objects of QPushButtons

    buttonCancel = new QPushButton();
    buttonOK = new QPushButton();

    // Initialize object of QHBoxLayout

    hLayoutButtons = new QHBoxLayout();

    // Initialize object of QVBoxLayout

    mainLayout = new QVBoxLayout();

    // Initialize QSplitter

    splitter = new QSplitter();

    // Initialize QSpacerItem

    item = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding);

    // setting QFont { fontLabel }

    fontLabel.setBold(true);
    fontLabel.setItalic(true);
    fontLabel.setPointSize(13);

    // setting Label

    labelInfo->setText("");
    labelInfo->setFont(fontLabel);

    // setting QPushButton { buttonOK | buttonCancel }

    buttonCancel->setText("Cancel");
    buttonOK->setText("OK");

    // add buttons to his layout

    hLayoutButtons->addWidget(buttonCancel);
    hLayoutButtons->addWidget(buttonOK);

    // add widgets on main layout

    mainLayout->addWidget(labelInfo);
    mainLayout->addWidget(lineEditName);
    mainLayout->addLayout(hLayoutButtons);
    mainLayout->addItem(item);
    mainLayout->addWidget(splitter);

    // set current layout as main

    this->setLayout(mainLayout);
}

void CreateNew::pressButtonCancel()
{
    pressedCancel = true;
    pressedOK = false;
    this->close();
}

void CreateNew::pressButtonOK()
{
    pressedOK = true;
    pressedCancel = false;
    this->close();
}

QLabel *CreateNew::getLabelInfo()
{
    return this->labelInfo;
}

QLineEdit *CreateNew::getlineEditName()
{
    return this->lineEditName;
}

QPushButton *CreateNew::getPushButtonOK()
{
    return this->buttonOK;
}

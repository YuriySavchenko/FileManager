#ifndef CREATENEW_H
#define CREATENEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QSplitter>
#include <QSpacerItem>
#include <QCloseEvent>

class CreateNew : public QWidget
{
    Q_OBJECT
public:
    explicit CreateNew(QWidget *parent = nullptr);
    virtual ~CreateNew();

protected:
    virtual void closeEvent(QCloseEvent *);

public:
    // function for initialize widgets

    void initializeWidgets();

private:
    // variable for check of pressing on button Cancel

    bool pressedCancel;
    bool pressedOK;

private:
    // variables

    QLabel *labelInfo;
    QLineEdit *lineEditName;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QHBoxLayout *hLayoutButtons;
    QVBoxLayout *mainLayout;
    QSplitter *splitter;
    QSpacerItem *item;

private:
    // variable for save font

    QFont fontLabel;

signals:

    void closeWindow(QString);

public slots:
    // slot for closing window

    void pressButtonCancel();
    void pressButtonOK();

public:
    // methods which allow get access to private rows

    QLabel *getLabelInfo();
    QLineEdit *getlineEditName();
    QPushButton *getPushButtonOK();

};

#endif // CREATENEW_H

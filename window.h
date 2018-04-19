#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QToolBar>
#include <QPushButton>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QUrl>
#include <QVBoxLayout>
#include <QDir>
#include <QStack>
#include <QListView>
#include <QModelIndex>
#include <QDesktopServices>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFile>

#include "createnew.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    virtual ~Window();

public:
    // function for initialize window

    void initializeWidgets();

private:
    // stack for save last dirs

    QStack<QDir> stackDirs;

private:
    // variables

    QToolBar *menu;
    QPushButton *buttonCreateDir;
    QPushButton *buttonCreateFile;
    QPushButton *buttonHome;
    QPushButton *buttonStepBack;
    QVBoxLayout *mainLayout;
    QListView *listView;
    QFileSystemModel *model;

    CreateNew *newFolder;
    CreateNew *newFile;

public slots:
    // slots for press on button

    void setHomePath();
    void openWindowNewDir();
    void openWindowNewFile();
    void createNewDir(QString);
    void createNewFile(QString);
    void stepBack();

public slots:
    // slot which allow moving in directories

    void openDirectory(const QModelIndex &);

public:
    // function for view MessageBox Critical error

    void messageCritical(QString, QString);
};

#endif // WINDOW_H

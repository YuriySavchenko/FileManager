#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    // call dunction for initialize widgets

    this->initializeWidgets();

    // connect signals with slots

    connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(openDirectory(QModelIndex)));
    connect(buttonStepBack, SIGNAL(clicked(bool)), this, SLOT(stepBack()));
    connect(buttonHome, SIGNAL(clicked(bool)), this, SLOT(setHomePath()));
    connect(buttonCreateDir, SIGNAL(clicked(bool)), this, SLOT(openWindowNewDir()));
    connect(buttonCreateFile, SIGNAL(clicked(bool)), this, SLOT(openWindowNewFile()));
    connect(newFolder, SIGNAL(closeWindow(QString)), this, SLOT(createNewDir(QString)));
    connect(newFile, SIGNAL(closeWindow(QString)), this, SLOT(createNewFile(QString)));
}

Window::~Window()
{
    menu->deleteLater();
    buttonCreateDir->deleteLater();
    buttonCreateFile->deleteLater();
    buttonHome->deleteLater();
    buttonStepBack->deleteLater();
    listView->deleteLater();
    mainLayout->deleteLater();
    newFolder->deleteLater();
    newFile->deleteLater();

    delete model;
}

void Window::initializeWidgets()
{
    // setup icon for this program

    this->setWindowIcon(QIcon(":/images/images/icon.png"));

    // Initialize object of QToolBar

    menu = new QToolBar();

    // Initialize objects of QPushButtons

    buttonCreateDir = new QPushButton();
    buttonCreateFile = new QPushButton();
    buttonHome = new QPushButton();
    buttonStepBack = new QPushButton();

    // Initialize object of QListView

    listView = new QListView(this);

    // Initialize object of QFileIconProvider

    model = new QFileSystemModel();

    // Initialize object of QVBoxLayout

    mainLayout = new QVBoxLayout();

    // Initialize objects of CreateNew

    newFolder = new CreateNew();
    newFile = new CreateNew();

    // setting CreateNew

    newFolder->getLabelInfo()->setText("New folder: ");
    newFile->getLabelInfo()->setText("New File: ");

    // setting list view

    listView->setAutoScroll(true);

    if (QDir("/home/yuriy").exists())
        listView->setIconSize(QSize(60, 45));

    if (QDir("/storage").exists())
        listView->setIconSize(QSize(90, 70));

    // setting buttons

    buttonCreateDir->setIcon(QIcon(":/images/images/newFolder.png"));
    buttonCreateFile->setIcon(QIcon(":/images/images/newFile.png"));
    buttonHome->setIcon(QIcon(":/images/images/home.png"));
    buttonStepBack->setIcon(QIcon(":/images/images/back.png"));

    buttonCreateDir->setIconSize(QSize(50, 50));
    buttonCreateFile->setIconSize(QSize(50, 50));
    buttonHome->setIconSize(QSize(50, 50));
    buttonStepBack->setIconSize(QSize(50, 50));

    // setting model

    model->setFilter((QDir::NoDotAndDotDot | QDir::Dirs) | QDir::Files);

    if (QDir("/home/yuriy").exists())
    {
        model->setRootPath(QDir::homePath());
        listView->setModel(model);
        listView->setRootIndex(model->index(QDir::homePath()));
    }
    else if (QDir("/storage").exists())
    {
        model->setRootPath("/storage");
        listView->setModel(model);
        listView->setRootIndex(model->index("/storage"));
    }

    // add buttons to menu

    menu->addWidget(buttonStepBack);
    menu->addWidget(buttonHome);
    menu->addWidget(buttonCreateDir);
    menu->addWidget(buttonCreateFile);

    // add widget to main layout

    mainLayout->addWidget(menu);
    mainLayout->addWidget(listView);

    // set layout as main

    if (QDir("/storage").exists())
    {
        listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    this->setLayout(mainLayout);
}

void Window::openDirectory(const QModelIndex &index)
{
    QListView *listViewSender = (QListView *) sender();
    QFileInfo fileInfo = model->fileInfo(index);

    if (fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listViewSender->setRootIndex(model->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName() == ".")
        listViewSender->setRootIndex(model->index(""));

    else if (fileInfo.isDir())
    {
        stackDirs.push_back(fileInfo.absoluteFilePath());
        listViewSender->setRootIndex(index);
    }

    else if (fileInfo.isFile())
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
}

void Window::stepBack()
{
    QModelIndex currentIndex = listView->currentIndex();
    QFileInfo fileInfo = model->fileInfo(currentIndex);

    if (!stackDirs.isEmpty())
    {
        QDir currentDir = stackDirs.last();
        stackDirs.pop_back();
        currentDir.cdUp();

        model->setRootPath(currentDir.absolutePath());
        listView->setModel(model);
        listView->setRootIndex(model->index(currentDir.absolutePath()));
    }

    else if (stackDirs.isEmpty())
        messageCritical("Error!", "This is a top directory!");

    listView->clearSelection();
}

void Window::setHomePath()
{
    if (QDir("/home/yuriy").exists())
    {
        model->setRootPath(QDir::homePath());
        listView->setModel(model);
        listView->setRootIndex(model->index(QDir::homePath()));
    }
    else if (QDir("/storage").exists())
    {
        model->setRootPath("/storage");
        listView->setModel(model);
        listView->setRootIndex(model->index("/storage"));
    }
}

void Window::openWindowNewDir()
{
    this->newFolder->show();
}

void Window::openWindowNewFile()
{
    this->newFile->show();
}

void Window::createNewDir(QString name)
{
    if (name == "__ignore__")
        return;

    if (name.isEmpty())
        model->mkdir(model->index(stackDirs.last().absolutePath()), "NewFolder");

    if (!name.isEmpty())
        model->mkdir(model->index(stackDirs.last().absolutePath()), name);
}

void Window::createNewFile(QString name)
{
    if (name == "__ignore__")
        return;

    else if (name.isEmpty())
    {
        name.append(stackDirs.last().absolutePath() + "/");
        name.append("NewFile.txt");
    }

    else if (!name.isEmpty())
    {
        QStringList list = name.split(".");
        QString border = ".txt";

        for (int i=0; i < list.length(); i++)
        {
            if (QString(list[i]) == "txt")
            {
                border.clear();
                return;
            }

        }

        name.append(border);
        name.insert(0, stackDirs.last().absolutePath() + "/");
    }

    QFile file(name);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    else
        file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.close();

    name.clear();
    this->listView->repaint();
}

void Window::messageCritical(QString title, QString message)
{
    QMessageBox::critical(this, title, message);
    return;
}

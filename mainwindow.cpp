/* # DON'T BE A DICK PUBLIC LICENSE

> Version 1.1, December 2016

> Copyright (C) 2020 Faisal Khan (faiszalkhan@gmail.com)

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document.

> DON'T BE A DICK PUBLIC LICENSE
> TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

1. Do whatever you like with the original work, just don't be a dick.

   Being a dick includes - but is not limited to - the following instances:

 1a. Outright copyright infringement - Don't just copy this and change the name.
 1b. Selling the unmodified original with no work done what-so-ever, that's REALLY being a dick.
 1c. Modifying the original work to contain hidden harmful content. That would make you a PROPER dick.

2. If you become rich through modifications, related works/services, or supporting the original work,
share the love. Only a dick would make loads off this work and not buy the original work's
creator(s) a pint.

3. Code is provided with no warranty. Using somebody else's code and bitching when it goes wrong makes
you a DONKEY dick. Fix the problem yourself. A non-dick would submit the fix back. */

/************************************* Includes *************************************/
#include "mainwindow.h"
#include "autosave.h"

/****************************** Function Definitions *********************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    /* TODO: Edit this with your data. This is required for creating the autosave directory */
    QCoreApplication::setOrganizationName("MyOrganization");
    QCoreApplication::setOrganizationDomain("www.myorg.com");
    QCoreApplication::setApplicationName("MyApp");
    QCoreApplication::setApplicationVersion("1.0.0");

    /* This function shall be called everytime your app is started */
    autosaveCheck();
}

/* Function to check if there is an autosave file present. If found, ask the user if it wants recover data */
void MainWindow::autosaveCheck()
{
    autosave = new Autosave(this);
    connect(autosave->timer, SIGNAL(timeout()), this, SLOT(saveDataToAutosave()));

    if(autosave->fileExists())
    {
        autosave->fileRecovery();
    }
    else
    {
        /* Do nothing */
    }
}

/* This function is called when a project file(inteded for autosaving) is opened or created */
//TODO: Call initAutosave() whenever your file is created or opened
void MainWindow::FileOpenedOrCreated(QString filename)
{
    initAutosave(filename);
}

/* This function is called every time the autosave timer is triggerred(3 mins configured). The changes are saved
 * in the autosave file */
//TODO: Reimplement this to save data to the autosave file
void MainWindow::saveDataToAutosave()
{
    //Aboslute filename of the autosave file is autosave->getFilePath()

    /* Implement your code for writing to the autosave file. Do not forget to close the file once the writing is done */
    qDebug("Autosave file write successful");
}

/* Function to initialize autosaving of the project opened or created. Care must be taken about extracing the file
 * name from the absolute filename before calling or inside this function */
void MainWindow::initAutosave(QString filename)
{
    autosave->clearDirectory();
    autosave->setProjectName(filename);
    autosave->createFile();
    autosave->timerStart();
}

/* Since your app has closed gracefully, delete the autosave file. This should also be done when an existing file/project is
   closed by the users consent */
void MainWindow::closeEvent(QCloseEvent *event)
{
    autosave->clearDirectory();
    event->accept();
}

MainWindow::~MainWindow()
{

}

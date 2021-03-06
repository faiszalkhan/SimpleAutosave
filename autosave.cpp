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


/* This file contains the implementation for autosaving the changes done by the user. Autosave file is created in
   the standard app data path. Autosave file is deleted when your app is closed gracefully by the user */

/************************************* Includes *************************************/
#include <QDir>
#include <QDebug>
#include <QObject>
#include <QStandardPaths>
#include <QTimer>
#include "autosave.h"

/****************************** Function Definitions *********************************/
Autosave::Autosave(QObject *parent): QObject(parent)
{
    /* On Windows, the path derives to : C:\Users\UserName\AppData\Roaming\YourComapny\YourApp\Autosave> */
    autosave_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Autosave/";
    autosave_dir.setPath(autosave_path);

    /* If the App Data location directory doesn't exists, create one */
    if(!(autosave_dir.exists()))
    {
        autosave_dir.mkpath(autosave_path);
    }

    timer = new QTimer;
}

/* Autosave shall be attempted every 3 minutes */
void Autosave::timerStart()
{
    timer->start(AUTOSAVE_INTERVAL);
}

/* Function to create a autosave file  */
void Autosave::createFile()
{
    QFile createfile;    

    /* Create auto save file */
    filepath = autosave_path + project_name;
    createfile.setFileName(filepath);
    if(!(createfile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
    {
#ifdef DEBUG
        qDebug()<<"FATAL ERROR: There was a problem in creating autosave file";
#endif
    }

    createfile.close();
}

/* Function to clear the autosave directory */
void Autosave::clearDirectory()
{
    /* Delete all files from autosave directory */
    autosave_dir.setNameFilters(QStringList() << "*.*");
    autosave_dir.setFilter(QDir::Files);
    foreach(QString dirFile, autosave_dir.entryList())
    {
        autosave_dir.remove(dirFile);
    }
}

/* Function to check if an autosave file exists in the App data directory. If a file is found, true
    is returned, else false is returned */
bool Autosave::fileExists()
{    
    if((!(autosave_dir.exists())) || (autosave_dir.isEmpty()))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Autosave::setProjectName(QString name)
{
    project_name = name;
}

/* Function to recover autosave file. This function is called only be called when it is confirmed that
 * a file exists in the autosave directory */
void Autosave::fileRecovery()
{
    QString info_text;
    QFile delete_file;

    /* Get names of the all the autosave files */
    //TODO: Replace the .docx with the extension of your file .whatever.
    QStringList autosave_files = autosave_dir.entryList(QStringList() << "*.docx",QDir::Files);

    if(autosave_files.size() > 1)
    {
        info_text.append("MyApp has found the following files with unsaved changes. Would you like to recover the files? \n");

        foreach(QString filename, autosave_files)
        {
            info_text.append(filename);
            info_text.append('\n');
        }
    }
    else if(autosave_files.size() == 1)
    {
        info_text.append("MyApp has found the following file with unsaved changes. Would you like to recover the file? \n");
        info_text.append(autosave_files.at(0));
    }
    else
    {
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Autosave crash recovery");
    msgBox.setInformativeText(info_text);
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
    msgBox.setDefaultButton(QMessageBox::Save);

    int ret = msgBox.exec();

    if(ret == QMessageBox::Save)
    {
        QString save_dir = QFileDialog::getExistingDirectory(nullptr, tr("Autosave crash recovery"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

        /* Save dialog was closed */
        if(save_dir.isEmpty())
        {
            /* Do nothing */
        }
        else
        {
            QString src_file, dest_file;

            /* Copy all the files from the autosave directory to the selected directory and delete the files autosave directory */
            foreach(QString filename, autosave_files)
            {
                /*Construct the absolute source file name */
                src_file = autosave_path + filename;
                dest_file = save_dir + "/" + filename;
                if(!(QFile::copy(src_file, dest_file)))
                {
                    qDebug("Copying has failed, Do something");
                }
            }

            clearDirectory();
        }
    }
    else if(ret == QMessageBox::Discard)
    {
        clearDirectory();
    }
    else
    {
        /* Do nothing */
    }
}

/* Get the absolute path of the autosave file */
QString Autosave::getFilePath()
{
    return filepath;
}

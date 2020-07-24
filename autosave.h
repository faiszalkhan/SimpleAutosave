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

#ifndef AUTOSAVE_H
#define AUTOSAVE_H

/************************************* Includes *************************************/
#include <QtWidgets>

#define AUTOSAVE_INTERVAL           180000 /* 3 minutes */
//#define DEBUG                            /* Uncomment for Debug messages */

/*************************************** Globals ***************************************/
class QTimer;

/******************************** Class Declaration *********************************/
class Autosave : public QObject
{
    Q_OBJECT

public:

    Autosave(QObject *parent);

    QTimer *timer;

    void timerStart();

    void createFile();

    void clearDirectory();

    bool fileExists();

    void setProjectName(QString name);

    void fileRecovery();

    QString getFilePath(void);

private:

    QString filepath, project_name;

    QString autosave_path;

    QDir autosave_dir;
};

#endif // AUTOSAVE_H

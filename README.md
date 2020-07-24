# SimpleAutosave
Simple Autosave for QT Applications. 

SimpleAutosave is an implementation for auto-saving your project files or any file that you want to autosave. Note that SimpleAutosave only supports autosaving single file.

SimpleAutosave performs the following tasks to achieve autosave. The flow of calling methods is important.

- Saves the file periodically(configurable) in the standard path of the OS.
- If the app is closed gracefully, deletes the autosave file.
- If an autosave file is found when starting the app, user is asked if it wants to recover changes.

## How do I interface my app with SimpleAutosave?

Check how Mainwindow is interfaced with SimpleAutosave. Replace Mainwindow with your interface file.

## Autosaving periodically

- saveDataToAutosave() is called periodically as per the value set in the macro AUTOSAVE_INTERVAL.

## Checking for Autosave file

- autosaveCheck() shall be called in the Mainwindow constructor of your app. If an autosave file is found, the user is shown recovery widget.
- Refer TODO string for changes to be done.

## **License**

SimpleAutosave is free and open-source software, it is released under the [DBAD](https://github.com/alex-spataru/QSimpleUpdater/blob/master/COPYING.md) license.

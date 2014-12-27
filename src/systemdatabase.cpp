#include "systemdatabase.h"

#include <QSqlError>
#include <QApplication>
#include <QFile>
#include <QSqlQuery>

SystemDatabase::SystemDatabase()
{
    open();
}

SystemDatabase::~SystemDatabase()
{
    db.close();
}

void SystemDatabase::open()
{

    /*
     *  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "second");

    QString path = "C:/Qt/Tools/QtCreator/bin/build-untitled-Desktop_Qt_5_3_0_MinGW_32bit-Debug/debug/systemdatabase.db";
    db.setDatabaseName(path);

    if (QFile::exists(path)) {

        if (!db.open())
            qFatal("Could not open database %s", qPrintable(db.lastError().driverText()));

     * */
    db = QSqlDatabase::addDatabase("QSQLITE", "second");
    QString path = QApplication::applicationDirPath() + "/systemdatabase.db";

    db.setDatabaseName(path);

    if (!QFile::exists(path))
    {
        qWarning("%s does not exist", qPrintable(path));
        bool copySuccess = QFile::copy( QString("assets:/systemdatabase.db"), path );
        if ( !copySuccess )
        {
            qFatal("Fail to copy database", qPrintable(path));
        }
    }

    if (!db.open())
        qFatal("Could not open database %s", qPrintable(db.lastError().driverText()));



}

QSqlDatabase &SystemDatabase::handle()
{
    if (!db.isValid())
        open();
    return db;
}

bool SystemDatabase::valid()
{
    return db.isValid();
}

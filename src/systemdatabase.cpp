#include "systemdatabase.h"

#include <QSqlError>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QSqlQuery>

#define CONNECTION_NAME         "second"
#define SYSTEM_DATABASE_NAME    "systemdatabase.db"

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
    db = QSqlDatabase::addDatabase("QSQLITE", CONNECTION_NAME);
    QString path = QApplication::applicationDirPath() + QDir::separator() + SYSTEM_DATABASE_NAME;

    db.setDatabaseName(path);

    if (!QFile::exists(path))
    {
        qWarning("%s does not exist", qPrintable(path));
        if(QFile::exists(QString(":/assets/%1").arg(SYSTEM_DATABASE_NAME)))
        {
            bool copySuccess = QFile::copy(QString(":/assets/%1").arg(SYSTEM_DATABASE_NAME), path );
            if ( !copySuccess )
            {
                qFatal("Fail to copy database %s", qPrintable(SYSTEM_DATABASE_NAME));
            }
        }
        else
        {
            qFatal("Database %s in not in assets", qPrintable(SYSTEM_DATABASE_NAME));
        }
    }

    if (!db.open())
    {
        qFatal("Could not open database %s", qPrintable(db.lastError().driverText()));
    }
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

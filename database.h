#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool openDB();
    void closeDB();

    bool addHistory(const QString &expression, const QString &result);
    QSqlQueryModel* getHistoryModel(QObject *parent);
    void clearHistory();

private:
    DatabaseManager();
    QSqlDatabase m_db;
};

#endif // DATABASE_H

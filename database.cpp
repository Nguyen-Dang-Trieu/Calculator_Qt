#include "database.h"
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("calculator_history.db");
}

bool DatabaseManager::openDB() {
    if (!m_db.open()) return false;

    QSqlQuery query;
    return query.exec("CREATE TABLE IF NOT EXISTS history ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "expression TEXT, "
                      "result TEXT, "
                      "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");
}

bool DatabaseManager::addHistory(const QString &expression, const QString &result) {
    QSqlQuery query;
    query.prepare("INSERT INTO history (expression, result) VALUES (:exp, :res)");
    query.bindValue(":exp", expression);
    query.bindValue(":res", result);
    return query.exec();
}

QSqlQueryModel* DatabaseManager::getHistoryModel(QObject *parent) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT expression, result FROM history ORDER BY timestamp DESC");
    return model;
}

void DatabaseManager::clearHistory() {
    QSqlQuery query;
    query.exec("DELETE FROM history");
}

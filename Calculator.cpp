#include <QSqlQuery>
#include "Calculator.h"
#include "database.h"

Calculator::Calculator(QObject *parent) : QObject(parent) {}

void Calculator::handleInput(const QString &buttonText) {
    bool isNumber;
    buttonText.toDouble(&isNumber);

    if (isNumber || buttonText == ".") {
        if (m_isNewNumber) {
            m_display = buttonText;
            m_isNewNumber = false;
        } else {
            if (buttonText == "." && m_display.contains(".")) return;
            m_display += buttonText;
        }

        if (!m_operation.isEmpty()) {
            m_history = m_previousInput + " " + m_operation + " " + m_display;
        } else {
            m_history = m_display;
        }
        emit historyChanged();

    } else if (buttonText == "AC") {
        m_display = "0";
        m_history = "";
        m_previousInput = "";
        m_operation = "";
        m_isNewNumber = true;
        emit historyChanged();

    }  else if(buttonText == "del") {
        if (!m_isNewNumber) {
            if (m_display.length() > 1) {
                m_display.chop(1);   // xóa ký tự cuối
            } else {
                m_display = "0";
                m_isNewNumber = true;
            }
        }
        if (!m_operation.isEmpty()) {
            m_history = m_previousInput + " " + m_operation + " " + m_display;
        } else {
            m_history = m_display;
        }
        emit historyChanged();

    } else if(buttonText == "+-") {
        if (m_display == "0") return;

        if (m_display.startsWith("-")) {
            m_display.remove(0, 1);   // -123 -> 123
        } else {
            m_display.prepend("-");   // 123 -> -123
        }

        // Update history đang hiển thị
        if (!m_operation.isEmpty()) {
            m_history = m_previousInput + " " + m_operation + " " + m_display;
        } else {
            m_history = m_display;
        }

        emit displayChanged();
        emit historyChanged();

    } else if (buttonText == "=") {
        if (!m_operation.isEmpty()) {
            m_history = m_previousInput + " " + m_operation + " " + m_display + " =";
            emit historyChanged();
        }
        calculate();
        m_operation = "";

    } else { // Khi buttonText = "+, -, *, /"
        if (!m_operation.isEmpty() && !m_isNewNumber) {
                calculate();
        }
        m_previousInput = m_display;
        m_operation = buttonText;
        m_isNewNumber = true;

        m_history = m_previousInput + " " + m_operation;
        emit historyChanged();
    }
    emit displayChanged();
    emit historyChanged();
}

void Calculator::calculate() {
    double first  = m_previousInput.toDouble();
    double second = m_display.toDouble();
    double result = 0;

    QString expression = m_previousInput + " " + m_operation + " " + m_display;

    if(m_operation == "") return;
    else if (m_operation == "+") result = first + second;
    else if (m_operation == "-") result = first - second;
    else if (m_operation == "*") result = first * second;
    else if (m_operation == "/") result = (second != 0) ? first / second : 0;

    m_display = QString::number(result);
    m_isNewNumber = true;

    // Save in database
    DatabaseManager::instance().addHistory(expression, m_display);

    // Send signal
    emit displayChanged();
}


QStringList Calculator::getHistoryList() const {
    QStringList history;
    QSqlQuery query("SELECT expression, result FROM history ORDER BY timestamp DESC");

    while (query.next()) {
        QString exp = query.value(0).toString();
        QString res = query.value(1).toString();
        history.append(exp + " = " + res);
    }
    return history;
}

void Calculator::clearHistory() {
    DatabaseManager::instance().clearHistory();
    emit historyChanged();
}

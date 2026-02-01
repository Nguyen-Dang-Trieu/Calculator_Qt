#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>

class Calculator : public QObject
{
    Q_OBJECT
    // Tạo thuộc tính để hiển thị lên màn hình QML
    Q_PROPERTY(QString display READ display NOTIFY displayChanged)
    Q_PROPERTY(QString history READ history NOTIFY historyChanged)

public:
    explicit Calculator(QObject *parent = nullptr);

    QString display() const { return m_display; }
    QString history() const { return m_history; }

    // Q_INVOKABLE cho phép gọi hàm này từ phía QML
    Q_INVOKABLE void handleInput(const QString &buttonText);
    Q_INVOKABLE QStringList getHistoryList();
    Q_INVOKABLE void clearHistory();

signals:
    void displayChanged();
    void historyChanged();

private:
    void calculate();
    QString m_display = "0"; // Giả trị đang hiển thị trên màn hình
    QString m_history = ""; // Lưu phép tính
    QString m_previousInput; // Lưu toán hạng trước khi người dùng bấm toán tử (+, -, *, \)
    QString m_operation; // Lưu phép toán hiện tại
    bool    m_isNewNumber = true; // Xác định user đang nhập số mới hay nối tiếp số cũ
};

#endif // CALCULATOR_H

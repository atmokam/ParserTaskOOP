#ifndef COMMANDPANE_HPP
#define COMMANDPANE_HPP

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QEvent>


class CommandPane : public QWidget
{
    Q_OBJECT

public:
    
    CommandPane(QWidget* parent = nullptr);
    virtual ~CommandPane();
    
    QLineEdit* getLineEdit() const;
    QTextEdit* getTextEdit() const;

    bool eventFilter(QObject* obj, QEvent* event) override;

public slots:

    void onCommandEntered();

private:

    QLineEdit* lineEdit;
    QTextEdit* textEdit;
};

#endif
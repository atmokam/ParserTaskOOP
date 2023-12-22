#include "CommandPane.hpp"
#include "Application/Application.hpp"
#include <QVBoxLayout>
#include <QKeyEvent>

CommandPane::CommandPane(QWidget* parent)
    : QWidget(parent), lineEdit(new QLineEdit(this)), textEdit(new QTextEdit(this))
{
    textEdit->setReadOnly(true);
    textEdit->setMinimumSize(400, 400);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(lineEdit);
    layout->addWidget(textEdit);

    setLayout(layout);

    connect(lineEdit, &QLineEdit::editingFinished, this, &CommandPane::onCommandEntered);
}

CommandPane::~CommandPane()
{
}

QLineEdit* CommandPane::getLineEdit() const
{
    return lineEdit;
}

QTextEdit* CommandPane::getTextEdit() const
{
    return textEdit;
}

void CommandPane::onCommandEntered()
{
    QString command = lineEdit->text();
    lineEdit->clear(); 
    auto controller = App::Application::getInstance()->getController();
    std::stringstream input = std::stringstream(command.toStdString());

    controller->runCommand(input);
    
    if(controller->getOutputStream().str() != "")
    {
        textEdit->append(controller->getOutputStream().str().c_str());
        controller->getOutputStream().str(std::string{});
    }

}

bool CommandPane::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == lineEdit && event->type() == QEvent::KeyPress) {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return && obj == lineEdit) {
            emit lineEdit->editingFinished();
            return true;
        }
    }
    return false;
}

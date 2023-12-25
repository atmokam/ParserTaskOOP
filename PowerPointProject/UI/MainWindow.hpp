#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "UI/CommandPane.hpp"
#include "UI/Controller.hpp"

namespace UI
{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:

        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private:
        
        CommandPane* commandPane;

    };
}
#endif
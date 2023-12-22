#include "MainWindow.hpp"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), commandPane(new CommandPane(this))
{
    setCentralWidget(commandPane);
    setWindowTitle("PowerPoint Project");
    setMinimumSize(800, 600);
    
}

MainWindow::~MainWindow()
{
}
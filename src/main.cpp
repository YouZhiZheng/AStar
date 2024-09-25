#include <iostream>
#include "mainwindow.hpp"

int main (int argc, char *argv[])
{
    initscr();
    start_color(); // 启用颜色
    cbreak(); // 禁用行缓冲
    noecho();
    curs_set(0);  // 隐藏光标

    MainWindow &window = MainWindow::getInstance();
    window.drawInitialInterface();
    window.printInitialMap();
    window.printShortestPath();
    
    endwin();

    return 0;
}
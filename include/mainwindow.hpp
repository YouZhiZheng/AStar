#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ncurses.h>
#include <memory>
#include <string>
#include <deque>
#include "randomnum.hpp"
#include "astar.hpp"

class MainWindow
{
public:
    MainWindow(const MainWindow &other) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    ~MainWindow();

    static MainWindow& getInstance() {
        if(instance == nullptr)
        {
            instance = new MainWindow(28, 90);
        }
        return *instance;
    }

    void drawInitialInterface();
    void randomGenerateObstacleNodes();
    void printInitialMap();
    void printShortestPath();
private:
    MainWindow(int box_height, int box_width);
    static MainWindow *instance;
    
    astar::Astar *m_astar;
    int m_scr_width, m_scr_height;
    int m_box_width, m_box_height;
    int m_box_start_w, m_box_start_h;
    WINDOW *m_win;
};

#endif
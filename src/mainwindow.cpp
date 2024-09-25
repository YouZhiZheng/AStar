#include "mainwindow.hpp"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(int box_height, int box_width): m_box_height(box_height), m_box_width(box_width)
{
    m_astar = new astar::Astar(box_height - 4, box_width - 2);

    getmaxyx(stdscr, m_scr_height, m_scr_width);
    m_box_start_h = (m_scr_height - m_box_height) / 2;
    m_box_start_w = (m_scr_width - m_box_width ) / 2;

    m_win = newwin(m_box_height, m_box_width, m_box_start_h, m_box_start_w);
}

MainWindow::~MainWindow()
{
    delete instance;
    delete m_astar;
    delwin(m_win);

    instance = nullptr;
    m_astar = nullptr;
    m_win = nullptr;
}

void MainWindow::drawInitialInterface()
{
    std::string message1{"Welcome to use A* algorithm to find the shortest path"};
    std::string message2{"Press any key to Start"};
    int startx = (m_box_width - message1.size()) / 2;
    int starty = m_box_start_h + 3;

    box(m_win, 0, 0); // 绘制框边界
    // 在窗口中间打印消息
    mvwprintw(m_win, starty, startx, "%s", message1.c_str());

    init_pair(1, COLOR_BLUE, COLOR_WHITE); // 初始化颜色对，使用蓝色字体和白色背景
    wattron(m_win, COLOR_PAIR(1)); // 启用颜色对
    // 在消息下方显示“开始”按钮
    mvwprintw(m_win, starty + 5, (m_box_width - message2.size()) / 2, "%s", message2.c_str());
    wattroff(m_win, COLOR_PAIR(1)); // 关闭颜色对

    wrefresh(m_win);
    randomGenerateObstacleNodes();
    wgetch(m_win);
}

void MainWindow::randomGenerateObstacleNodes()
{
    RandomNumGenerator generator(m_astar->get_gridmap()->get_height(), 
                                m_astar->get_gridmap()->get_width());
    std::pair<size_t, size_t> temp;
    point::Point2D *temp_point;
    // 随机随从 25% 的障碍结点
    size_t node_num = m_astar->get_gridmap()->get_height() * m_astar->get_gridmap()->get_width() * 0.25;
    for(size_t i = 0; i < node_num; ++i)
    {
        temp = generator.generateTwo();
        temp_point = &(m_astar->get_gridmap()->get_map())[temp.first][temp.second];
        
        // 判断生成的结点是否是起点和终点
        if(temp_point != m_astar->get_start_point() && temp_point != m_astar->get_end_point())
        {
            temp_point->set_state(point::Point2D::State::Wall);
        }
    }
}

void MainWindow::printInitialMap()
{   
    werase(m_win);
    box(m_win, 0, 0);
    
    init_pair(1, COLOR_WHITE, COLOR_RED); // 起点颜色
    init_pair(2, COLOR_WHITE, COLOR_GREEN); // 终点颜色
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // 墙点颜色 
    init_pair(4, COLOR_BLACK, COLOR_WHITE); // 普通点颜色
    init_pair(5, COLOR_BLUE, COLOR_BLACK); // 提示词颜色

    for(const auto &node_vec: m_astar->get_gridmap()->get_map())
    {
        for(const auto &node: node_vec)
        {
            switch (node.get_state())
            {
                case point::Point2D::State::Ordinary:
                {
                    wattron(m_win, COLOR_PAIR(4));
                    mvwprintw(m_win, node.get_i() + 3, node.get_j() + 1, "*");
                    wattroff(m_win, COLOR_PAIR(4));
                }
                break;
            
                case point::Point2D::State::Wall:
                {
                    wattron(m_win, COLOR_PAIR(3));
                    mvwprintw(m_win, node.get_i() + 3, node.get_j() + 1, "$");
                    wattroff(m_win, COLOR_PAIR(3));
                }
                break;
            }
        }
    }

    std::string message{"Initial Map. Press any key to start pathfinding."};
    wattron(m_win, COLOR_PAIR(5));
    mvwprintw(m_win, 1, (m_box_width - message.size()) / 2, "%s", message.c_str()); // 输出标题
    wattroff(m_win, COLOR_PAIR(5));
    mvwhline(m_win, 2, 1, ACS_HLINE, m_box_width - 2); // 输出分割线
    
    // 设置起点颜色
    wattron(m_win, COLOR_PAIR(1));
    mvwprintw(m_win, 3, 1, "#");
    wattroff(m_win, COLOR_PAIR(1));
    
    // 设置终点颜色
    wattron(m_win, COLOR_PAIR(2));
    mvwprintw(m_win, m_astar->get_gridmap()->get_height() + 2, m_astar->get_gridmap()->get_width(), "#");
    wattroff(m_win, COLOR_PAIR(2));
    
    wrefresh(m_win);
    wgetch(m_win);
}

void MainWindow::printShortestPath()
{
    init_pair(1, COLOR_RED, COLOR_WHITE); // 提示词颜色
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA); // 路径颜色
    init_pair(3, COLOR_BLUE, COLOR_BLACK); // 标题颜色

    std::string message1{"Map with path. Press any key to end the program."};
    wattron(m_win, COLOR_PAIR(3));
    mvwprintw(m_win, 1, (m_box_width - message1.size()) / 2, "%s", message1.c_str()); // 输出标题
    wattroff(m_win, COLOR_PAIR(3));
    mvwhline(m_win, 2, 1, ACS_HLINE, m_box_width - 2); // 输出分割线
   
    wrefresh(m_win);

    std::deque<point::Point2D*> path = m_astar->findPath();

    if(path.empty() || path.back() != m_astar->get_end_point()) // 判断是否成功找到最短路径
    {
        std::string message2 {"There is no shortest path on this map. Press any key to end the program"};
        wattron(m_win, COLOR_PAIR(1));
        mvwprintw(m_win, (m_box_height - 4) / 2, (m_box_width - message2.size()) / 2, "%s", message2.c_str());
        wattroff(m_win, COLOR_PAIR(1));
    }
    else
    {
        // 打印路径上的结点
        wattron(m_win, COLOR_PAIR(2));
        for(const auto &point: path)
        {
            mvwprintw(m_win, point->get_i() + 3, point->get_j() + 1, "#");
        }
        wattroff(m_win, COLOR_PAIR(2));
    }

    wrefresh(m_win);
    wgetch(m_win);
}
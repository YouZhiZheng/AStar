#include "map.hpp"

map::GridMap::GridMap(size_t h, size_t w): m_h(h), m_w(w)
{
    // 初始化 m_map 避免后续频繁的拷贝操作
    m_map.resize(m_h, std::vector<point::Point2D>(m_w));

    for(size_t i = 0; i < m_h; ++i)
    {
        for(size_t j = 0; j < m_w; ++j)
        {
            m_map[i][j] = point::Point2D(i, j);
        }
    }
}

void map::GridMap::printMap()
{
    point::Point2D::State node_state;
    for(size_t i = 0; i < m_h; ++i)
    {
        for(size_t j = 0; j < m_w; ++j)
        {
            node_state = m_map[i][j].get_state();
            switch (node_state)
            {
            case point::Point2D::State::Open :
            case point::Point2D::State::Ordinary : std::cout << "* "; break;
            case point::Point2D::State::Closed : std::cout << "# "; break;
            case point::Point2D::State::Wall : std::cout << "$ "; break;
            }
        }
        std::cout << std::endl;
    }
}
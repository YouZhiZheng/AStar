#include "astar.hpp"

astar::Astar::Astar(size_t map_height, size_t map_width)
{
    m_grid_map = new map::GridMap(map_height, map_width);
    m_start = &((m_grid_map->get_map())[0][0]);
    m_end = &((m_grid_map->get_map())[map_height - 1][map_width - 1]);
}

astar::Astar::~Astar()
{
    delete m_grid_map;

    m_grid_map = nullptr;
    m_start = nullptr;
    m_end = nullptr;
}

void astar::Astar::setWallPoint(const size_t i, const size_t j)
{
    if((i >= 0 && i < m_grid_map->get_height()) && (j >= 0 && j < m_grid_map->get_width()))
    {
        ((m_grid_map->get_map())[i][j]).set_state(point::Point2D::State::Wall); 
    }
}

void astar::Astar::set_start_point(const size_t i, const size_t j)
{
    if((i >= 0 && i < m_grid_map->get_height()) && (j >= 0 && j < m_grid_map->get_width()))
    {
        m_start = &((m_grid_map->get_map())[i][j]);
    }
}

void astar::Astar::set_end_point(const size_t i, const size_t j)
{
    if((i >= 0 && i < m_grid_map->get_height()) && (j >= 0 && j < m_grid_map->get_width()))
    {
        m_end = &((m_grid_map->get_map())[i][j]);
    }
}

std::deque<point::Point2D*>& astar::Astar::findPath()
{   
    // 定义8个方向的相对坐标
    std::vector<std::pair<int, int>> directions = {
                {-1, 0},
        { 0, -1},       { 0, 1},
                { 1, 0}
    };

    point::Point2D *top_point = nullptr;
    
    m_start->set_state(point::Point2D::State::Open);
    m_open_list.push(m_start);

    while(!m_open_list.empty())
    {
        top_point = m_open_list.top();
        m_open_list.pop();
        
        // 判断该点是否已经处理过了
        if(top_point->get_state() == point::Point2D::State::Open)
        {
            // 将其状态设置为已处理
            top_point->set_state(point::Point2D::State::Closed);

            // 判断该点是否是终点
            if(top_point != m_end)
            {
                // 依次访问该结点的邻居结点
                int new_i, new_j, num = 1; // num 用于计算是哪个方向的邻接点，便于计算g值
                size_t g_value = 10;

                for(const auto& dir: directions)
                {
                    new_i = top_point->get_i() + dir.first;
                    new_j = top_point->get_j() + dir.second;

                    // 判断该邻接点是否存在
                    if((new_i >= 0 && new_i < m_grid_map->get_height()) 
                        && (new_j >= 0 && new_j < m_grid_map->get_width()))
                    {
                        size_t new_i_index = static_cast<size_t>(new_i);
                        size_t new_j_index = static_cast<size_t>(new_j);
                        // 障碍结点 或 已经处理的结点 不必进行处理
                        if( m_grid_map->get_map()[new_i_index][new_j_index].get_state() == point::Point2D::State::Wall 
                         || m_grid_map->get_map()[new_i_index][new_j_index].get_state() == point::Point2D::State::Closed)
                        {
                            continue;
                        }
                        
                        // 根据结点状态来进行对应处理
                        switch ((m_grid_map->get_map()[new_i_index][new_j_index]).get_state())
                        {
                            case point::Point2D::State::Ordinary:
                            {
                                (m_grid_map->get_map())[new_i_index][new_j_index].set_g(top_point->get_g() + g_value);

                                (m_grid_map->get_map())[new_i_index][new_j_index].set_h(
                                    std::abs(new_i - m_end->get_i()) + std::abs(new_j - m_end->get_j())
                                );

                                (m_grid_map->get_map())[new_i_index][new_j_index].set_f();
                                (m_grid_map->get_map())[new_i_index][new_j_index].set_parent(top_point);

                                (m_grid_map->get_map())[new_i_index][new_j_index].set_state(point::Point2D::State::Open);
                                m_open_list.push(&((m_grid_map->get_map())[new_i_index][new_j_index]));
                            }
                            break;

                            case point::Point2D::State::Open:
                            {
                                size_t new_g = top_point->get_g() + g_value;

                                // 判断新g值是否小于旧g值
                                if(new_g < (m_grid_map->get_map())[new_i_index][new_j_index].get_g())
                                {
                                    (m_grid_map->get_map())[new_i_index][new_j_index].set_g(new_g);
                                    (m_grid_map->get_map())[new_i_index][new_j_index].set_f();
                                    (m_grid_map->get_map())[new_i_index][new_j_index].set_parent(top_point);

                                    m_open_list.push(&((m_grid_map->get_map())[new_i_index][new_j_index]));
                                }
                            }
                            break;

                            default: break;
                        }
                    }

                    ++num;
                }

            }
            else
            {
                // 如果是终点则将路径存储到path中去
                while(1)
                {
                    m_path.push_front(top_point);
                    
                    if(top_point == m_start) break;
                    else top_point = top_point->get_parent();
                }

                break; // 已找到最短路径, 结束循环
            }
        }
    }

    return m_path;
}
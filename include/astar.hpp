/**
 * *****************************************************************************************************
 * 
 * @file astar.hpp
 * @author zyz (youzhizheng9@gmail.com)
 * @date 2024-09-22
 * @brief 
 * 
 * *****************************************************************************************************
 * @copyright Copyright (c) 2024 YouZhiZheng
 *  
 * This document and the information contained herein are the proprietary property of YouZhiZheng.
 *  
 * The document may not be reproduced, published, distributed or used in any form or by any means,
 * electronic or mechanical, including photocopying, recording, or any information storage and retrieval
 * system, without the prior written permission of YouZhiZheng.
 *  
 * This document is provided for informational purposes only and may not be used for any commercial
 * purpose without the express written consent of YouZhiZheng. YouZhiZheng reserves the right to revise
 * this document at any time without notice.
 * *****************************************************************************************************
 */
#ifndef ASTAR_H
#define ASTAR_H

#include <queue>
#include <deque>
#include <cmath>
#include <utility>
#include "map.hpp"

namespace astar{
    struct ComparePointFValue
    {
        bool operator()(const point::Point2D *a, const point::Point2D *b) 
        {
            return a->get_f() > b->get_f(); // Min-heap: lower f value has higher priority
        }
    };

    class Astar
    {
    public:
        Astar(size_t map_height = 5, size_t map_width = 10);
        ~Astar();

        void setWallPoint(const size_t i, const size_t j);
        void set_start_point(const size_t i, const size_t j);
        void set_end_point(const size_t i, const size_t j);

        point::Point2D* get_start_point() const { return m_start; }
        point::Point2D* get_end_point() const { return m_end; }
        map::GridMap* get_gridmap() { return m_grid_map; }

        std::deque<point::Point2D*>& findPath();

    private:
        map::GridMap *m_grid_map;
        point::Point2D *m_start, *m_end;
        std::priority_queue<point::Point2D*, std::vector<point::Point2D*>, 
                            astar::ComparePointFValue> m_open_list;
        std::deque<point::Point2D*> m_path;
    };
}

#endif // ASTAR_H
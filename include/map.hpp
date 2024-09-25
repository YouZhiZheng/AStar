/**
 * *****************************************************************************************************
 * 
 * @file map.hpp
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
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include "point.hpp"

namespace map{
    class GridMap
    {   
    public:
        GridMap(size_t h = 5, size_t w = 10);
        GridMap(const GridMap &other) = default;
        GridMap& operator=(const GridMap &other) = default;
        ~GridMap() = default;

        size_t get_width() const { return m_w; }
        size_t get_height() const { return m_h; }
        std::vector< std::vector<point::Point2D> >& get_map() { return m_map; }

        void printMap();

    private:
        size_t m_w;
        size_t m_h;
        std::vector< std::vector<point::Point2D> > m_map;
    };
}

#endif // MAP_H
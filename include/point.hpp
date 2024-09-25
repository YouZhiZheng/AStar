/**
 * *****************************************************************************************************
 * 
 * @file point.hpp
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
#ifndef POINT_H
#define POINT_H

#include <cstddef>

namespace point{
    class Point2D
    {
    public:
        enum class State
        {
            Open,
            Closed,
            Wall,
            Ordinary
        };
        
        Point2D(int i = 0, int j = 0): m_i(i), m_j(j) {}
        Point2D(Point2D&& other) noexcept 
            :m_i(other.m_i), m_j(other.m_j), m_g(other.m_g), 
             m_h(other.m_h), m_f(other.m_f), m_state(other.m_state)
            {
                other.m_i = 0;
                other.m_j = 0;
                other.m_g = 0;
                other.m_h = 0;
                other.m_f = 0;
                other.m_state = State::Ordinary;
            }
        Point2D(const Point2D &other) = default;
        Point2D& operator=(const Point2D &other) = default;
        ~Point2D() = default;

        int get_i() const { return m_i; }
        int get_j() const { return m_j; }
        size_t get_g() const { return m_g; }
        size_t get_h() const { return m_h; }
        size_t get_f() const { return m_f; }
        size_t get_weight() const { return m_weight; }
        State get_state() const { return m_state; }
        Point2D *get_parent() { return m_parent; }

        void set_g(const size_t &g) { m_g = g; }
        void set_h(const size_t &h) { m_h = h; }
        void set_f() { m_f = m_g + m_h; }
        void set_weight(const size_t &weight) { m_weight = weight; }
        void set_state(const State &state) { m_state = state; }
        void set_parent(Point2D *parent) { m_parent = parent; }

    private:
        int m_i; // 在该题中点的坐标为整数且只为正
        int m_j;
        size_t m_g = 0;
        size_t m_h = 0;
        size_t m_f = 0;
        size_t m_weight = 1;
        State m_state = State::Ordinary;
        Point2D *m_parent = nullptr;
    };
}

#endif // POINT_H
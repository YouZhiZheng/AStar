set(sources
    src/map.cpp
    src/astar.cpp
    src/mainwindow.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/point.hpp
    include/map.hpp
    include/astar.hpp
    include/randomnum.hpp
    include/mainwindow.hpp
)

set(test_sources
  src/astar_test.cpp
)

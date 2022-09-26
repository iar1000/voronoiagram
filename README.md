# Voronoiagram

## Problem to solve

The Voronoi Diagram describes a partitioning of a plane (or volume) into finitely many cells, given a set of target points.
Each cell defines a set of points, consisting of one target point and all points in the plane (or volume) that are closer to that point, than to any other of the target points.

Given a space $\Omega$ with distance function $d: \Omega \times \Omega \rightarrow \mathbb{R}$ and a set of (indexed) target Points $T$, the Voronoi Cell sourrounding target point $k \in T$ is defined as

$$V_k = \{ x \in \Omega | d(x, k) \leq d(x,q), \forall q\in T. q \neq k\}.$$

**Note:** We are using elements of $T$ also as index to ease the notation.

### Fortune's Algorithm

https://en.wikipedia.org/wiki/Fortune%27s_algorithm


### Approximation via Jump Flooding 

https://en.wikipedia.org/wiki/Jump_flooding_algorithm  
https://observablehq.com/@rreusser/gpu-voronoi-diagrams-using-the-jump-flooding-algorithm
https://jacquesheunis.com/post/fortunes-algorithm/  


## System Architecture

Analyze how your system takes input, produces results, provide interface, and performs any other operations. Describe the system’s work flow. You may consider to use a flow chart but it is not required. Specify the constraints assumed in your system. Describe the modularization of the system.

## API Description

Show how your system can be programmed. You are supposed to implement the system using both C++ and Python. Describe how a user writes a script in the system.

## Engineering Infrastructure

Describe how you plan to put together the engineering system:
Automatic build system and how to build your program.
Version control (show how you will use it).
Testing framework.
Documentation.

Some of the above information should be included in the documentation in your software.
You may use continuous integration, but it is not required. If you use it, describe how it works in your code development.

## Schedule

- **Planning phase (6 weeks from 9/19 to 10/31)**:
- **Week 1 (10/31)**:
- **Week 2 (11/7)**:
- **Week 3 (11/14)**:
- **Week 4 (11/21)**:
- **Week 5 (11/28)**:
- **Week 6 (12/5)**:
- **Week 7 (12/12)**:
- **Week 8 (12/19)**:

## References

[Reference Project Proposals](https://yyc.solvcon.net/en/latest/nsd/schedule/22au_nycu/schedule.html#voronoi-diagram)  
[Guodong Rong (2006), Jump flooding in gpu with applications to voronoi diagram and distance transform](https://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.101.8568&rank=1&q=Jump%20Flooding%20in%20GPU%20with%20Applications%20to%20Voronoi%20Diagram&osm=&ossid=)  
[Guodong Rong (2007), Variants of Jump Flooding Algorithm for Computing Discrete Voronoi Diagrams](https://ieeexplore.ieee.org/document/4276119)

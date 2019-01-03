//
// Created by hollan haule on 1/1/19.
//

#ifndef CLIONPRO1_CGALHANDLER_H
#define CLIONPRO1_CGALHANDLER_H

#include <iostream>
#include "renderUtility.h"
#include <vector>
#include <memory>

#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/Complex_2_in_triangulation_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Implicit_surface_3.h>


// default triangulation for Surface_mesher
using Tr = CGAL::Surface_mesh_default_triangulation_3;
// c2t3
using C2t3 = CGAL::Complex_2_in_triangulation_3<Tr>;
using GT = Tr::Geom_traits;
using Sphere_3 = GT::Sphere_3;
using Point_3 = GT::Point_3;
using FT = GT::FT;

typedef FT (*Function)(Point_3);
using Surface_3 = CGAL::Implicit_surface_3<GT, Function>;

using Vector_3 = GT::Vector_3;

FT sphere_function (Point_3 p) {
    const FT x2=p.x()*p.x(), y2=p.y()*p.y(), z2=p.z()*p.z();
    return x2+y2+z2-1;
}


void generateSphereMesh(std::vector<Vertex>& sphereVertices)
{
    //generating mesh
    Tr tr;            // 3D-Delaunay triangulation
    C2t3 c2t3 (tr);   // 2D-complex in 3D-Delaunay triangulation
    // defining the surface
    Surface_3 surface(sphere_function,             // pointer to function
                      Sphere_3(CGAL::ORIGIN, 2.)); // bounding sphere
    // Note that "2." above is the *squared* radius of the bounding sphere!
    // defining meshing criteria
    CGAL::Surface_mesh_default_criteria_3<Tr> criteria(30.,  // angular bound
                                                       0.1,  // radius bound
                                                       0.1); // distance bound
    // meshing surface
    CGAL::make_surface_mesh(c2t3, surface, criteria, CGAL::Non_manifold_tag());
    std::cout << "Final number of points: " << tr.number_of_vertices() << "\n";

    // for each facet (triangle), print the vertices
    for(C2t3::Facet_iterator fi = c2t3.facets_begin(); fi != c2t3.facets_end(); fi++)
    {

        C2t3::Cell_handle cell    = fi->first;
        int opposite_vertex_index = fi->second;
        //compute normals
        const Point_3& p0 = cell->vertex((opposite_vertex_index)&3)->point();
        const Point_3& p1 = cell->vertex((opposite_vertex_index+1)&3)->point();
        const Point_3& p2 = cell->vertex((opposite_vertex_index+2)&3)->point();
        const Point_3& p3 = cell->vertex((opposite_vertex_index+3)&3)->point();
        Vector_3 n = ( opposite_vertex_index % 2 == 1) ?
                     CGAL::normal(p1, p2, p3) :
                     CGAL::normal(p1, p3, p2);
        Vector_3 v1 = p1 - p0;

        n = n /CGAL::sqrt(n * n);

        //if ( n * v1 < 0 ) { n = -n; }


        for(int i = 0; i < 4; i++)
            if(i != opposite_vertex_index) {
                Vertex v;
                v.Position = glm::vec3(cell->vertex(i)->point().x(),cell->vertex(i)->point().y(),cell->vertex(i)->point().z());


                const Point_3& av = cell->vertex(i)->point();
                //const Point_3& av = cell->vertex((opposite_vertex_index)&3)->point();

                auto eps = 0.1f;

                //std::cout << "Sphere function result: " << sphere_function(p1) << "\n";

                //OLD TEST
                n = (sphere_function(av + (eps * n)) < 0.0) ? -n : n;
                //NEW TEST
                //Vector_3 v1 = p1 - p0;
                //n = (CGAL::angle(n, v1) == CGAL::ACUTE) ? -n:n;
                v.Normal = glm::vec3(n.x(),n.y(),n.z());
                sphereVertices.push_back(v);
            }
    }
}




#endif //CLIONPRO1_CGALHANDLER_H

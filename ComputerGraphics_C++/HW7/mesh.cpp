#include "mesh.h"
#include <fstream>
#include <limits>
#include <string>
#include <algorithm>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

Mesh::Mesh(const Parse* parse, std::istream& in)
{
    std::string file;
    in>>name>>file;
    Read_Obj(file.c_str());
}

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e, t;
    vec3 v;
    vec2 u;
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }

        if(sscanf(line.c_str(), "vt %lg %lg", &u[0], &u[1]) == 2)
        {
            uvs.push_back(u);
        }

        if(sscanf(line.c_str(), "f %d/%d %d/%d %d/%d", &e[0], &t[0], &e[1], &t[1], &e[2], &t[2]) == 6)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
            for(int i=0;i<3;i++) t[i]--;
            triangle_texture_index.push_back(t);
        }
    }
    num_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    double min_t = std::numeric_limits<double>::max();
    Hit hit;
    hit.dist = min_t;

    if(part < 0) {
        for(int i = 0; i < triangles.size(); i++) {
            Hit temp = Intersect_Triangle(ray, i);
            if(temp.Valid() && temp.dist < hit.dist){
                hit.dist = temp.dist;
                hit.triangle = i;
                hit.uv = temp.uv;
            }
        }
    }else {
        hit = Intersect_Triangle(ray, part);
    }
    return hit;
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const Ray& ray, const Hit& hit) const
{
    ivec3 current_triangle = triangles[hit.triangle];

    vec3 AB = vertices[current_triangle[1]] - vertices[current_triangle[0]];
    vec3 AC = vertices[current_triangle[2]] - vertices[current_triangle[0]];

    return cross(AB, AC).normalized();
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
Hit Mesh::Intersect_Triangle(const Ray& ray, int tri) const
{
    vec3 v = vertices[triangles[tri][1]] - vertices[triangles[tri][0]];
    vec3 w = vertices[triangles[tri][2]] - vertices[triangles[tri][0]];
    vec3 u = ray.direction;
    vec3 y = ray.endpoint - vertices[triangles[tri][0]];

    Hit hit;
    hit.dist = -1;
    hit.triangle = tri;

    if (dot(u,this->Normal(ray,hit)) == 0){
        return hit;
    }

    double beta = dot(cross(u,w), y) / dot(cross(u,w), v);
    double gamma = dot(cross(u,v), y) / dot(cross(u,v), w);
    double alpha = 1 - beta - gamma;

    double dist = - dot(cross(v,w), y) / dot(cross(v,w), u);

    if((alpha > -weight_tol && beta > -weight_tol && gamma > -weight_tol)){ //not to future self: small_t test should be here but it did not pass tests when implemented, maybe source of future errors
        vec2 temp;
        temp[0] = (alpha * uvs.at(triangle_texture_index.at(tri)[0])[0]);
        temp[0] += (beta * uvs.at(triangle_texture_index.at(tri)[1])[0]);
        temp[0] += (gamma * uvs.at(triangle_texture_index.at(tri)[2])[0]);
        temp[1] = (alpha * uvs.at(triangle_texture_index.at(tri)[0])[1]);
        temp[1] += (beta * uvs.at(triangle_texture_index.at(tri)[1])[1]);
        temp[1] += (gamma * uvs.at(triangle_texture_index.at(tri)[2])[1]);
        hit.dist = dist;
        hit.uv = temp;
        return hit;
    }
    return hit;
}

std::pair<Box,bool> Mesh::Bounding_Box(int part) const
{
    if(part<0)
    {
        Box box;
        box.Make_Empty();
        for(const auto& v:vertices)
            box.Include_Point(v);
        return {box,false};
    }

    ivec3 e=triangles[part];
    vec3 A=vertices[e[0]];
    Box b={A,A};
    b.Include_Point(vertices[e[1]]);
    b.Include_Point(vertices[e[2]]);
    return {b,false};
}
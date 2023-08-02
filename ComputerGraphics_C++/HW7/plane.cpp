//Student Name: Michael Bettencourt
//Student ID: 862158336
#include "plane.h"
#include "hit.h"
#include "ray.h"
#include <cfloat>
#include <limits>

Plane::Plane(const Parse* parse,std::istream& in)
{
    in>>name>>x>>normal;
    normal=normal.normalized();
}

Plane::Plane(vec3 x1, vec3 normal1){
    x = x1;
    normal = normal1;
}

// Intersect with the plane.  The plane's normal points outside.
Hit Plane::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit;
    double a = dot(ray.direction, normal);
    if (a == 0){
        return hit;
    }
    vec3 b = ray.endpoint - x;
    double c = -(dot(b, normal)/ dot(ray.direction, normal));
    if(c >= small_t){
        hit.dist = c;
    }
    return hit;
}

vec3 Plane::Normal(const Ray& ray, const Hit& hit) const
{
    return normal;
}

std::pair<Box,bool> Plane::Bounding_Box(int part) const
{
    Box b;
    b.Make_Full();
    return {b,true};
}

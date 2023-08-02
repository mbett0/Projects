//Student Name: Michael Bettencourt
//Student ID: 862158336
#include "sphere.h"
#include "ray.h"

Sphere::Sphere(const Parse* parse, std::istream& in)
{
    in>>name>>center>>radius;
}

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
    Hit hit;
    double a = ray.direction.magnitude_squared();
    double b = 2 * dot(ray.direction, ray.endpoint - center);
    double c = ((ray.endpoint - center).magnitude_squared()) - (radius * radius);
    double check = (b*b) - (4*a*c);
    if (check < 0){
        return hit;
    }else{
        double r1 = (-b + sqrt(check))/(2*a);
        double r2 = (-b - sqrt(check))/(2*a);
        if(r2 > r1 && r1 >= small_t){
            hit.dist = r1;
        }else if(r2 <= r1 && r2 >= small_t){
            hit.dist = r2;
        }
    }
    return hit;
}

vec3 Sphere::Normal(const Ray& ray, const Hit& hit) const
{ 
    vec3 normal;
    //TODO; // compute the normal direction
    vec3 temp = ray.Point(hit.dist);
    normal = (temp - center).normalized();
    return normal;
}

std::pair<Box,bool> Sphere::Bounding_Box(int part) const
{
    return {{center-radius,center+radius},false};
}

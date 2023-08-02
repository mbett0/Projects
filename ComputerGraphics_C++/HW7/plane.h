#ifndef __PLANE_H__
#define __PLANE_H__

#include "object.h"

class Parse;

class Plane : public Object
{
public:
    vec3 x;
    vec3 normal;

    Plane(const Parse* parse,std::istream& in);
    Plane(vec3 x1, vec3 normal1);
    virtual ~Plane() = default;

    virtual Hit Intersection(const Ray& ray, int part) const override;
    virtual vec3 Normal(const Ray& ray, const Hit& hit) const override;
    virtual std::pair<Box,bool> Bounding_Box(int part) const override;

    static constexpr const char* parse_name = "plane";
};
#endif

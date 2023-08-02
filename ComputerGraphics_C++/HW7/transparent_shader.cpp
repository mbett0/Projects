#include "transparent_shader.h"
#include "parse.h"
#include "ray.h"
#include "render_world.h"

Transparent_Shader::
Transparent_Shader(const Parse* parse,std::istream& in)
{
    in>>name>>index_of_refraction>>opacity;
    shader=parse->Get_Shader(in);
    assert(index_of_refraction>=1.0);
}

// Use opacity to determine the contribution of this->shader and the Schlick
// approximation to compute the reflectivity.  This routine shades transparent
// objects such as glass.  Note that the incoming and outgoing indices of
// refraction depend on whether the ray is entering the object or leaving it.
// You may assume that the object is surrounded by air with index of refraction
// 1.
vec3 Transparent_Shader::
Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    vec3 color = shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth);
    vec3 direction = ray.direction;
    vec3 reflected_direction = (2 * dot(-ray.direction, normal) * normal + ray.direction);
    Ray reflected_ray(intersection_point, reflected_direction);

    double n1 = 1;
    double n2 = index_of_refraction;
    double cos_theta = dot(-direction, normal);
    double sin2_theta_t = (n1/n2) * (n1/n2) * (1 - cos_theta * cos_theta);
    double cos_theta_t = sqrt(1 - sin2_theta_t);

    double R0 = pow((n1 - n2)/(n1 + n2), 2);
    double reflectance = R0 + (1 - R0) * pow((1 - cos_theta), 5);
   

    if(cos_theta > 1) {
        // Total internal reflection
        color = opacity * render_world.Cast_Ray(reflected_ray, recursion_depth + 1);

    } else {
        vec3 refracted_direction = ((n1/n2) * direction + (n1/n2 * cos_theta - cos_theta_t) * normal);
        Ray refracted_ray(intersection_point, refracted_direction);    
        
        if(reflected_direction.magnitude_squared() < reflectance && cos_theta_t > 1){
            color = (1-reflectance) * color + reflectance * render_world.Cast_Ray(reflected_ray, recursion_depth + 1);
        }
        else if(reflected_direction.magnitude_squared() >= reflectance && cos_theta_t > 1) {
            color = color * (1-reflectance);
        }
        else if(cos_theta_t <= 1){
            color = (1.0 - opacity) * render_world.Cast_Ray(refracted_ray, recursion_depth + 1) * (1.0 / index_of_refraction) + opacity * render_world.Cast_Ray(reflected_ray, recursion_depth + 1) * reflectance;
        }
    }
    if(recursion_depth > render_world.recursion_depth_limit) {
        return vec3(0,0,0);
    }
    else if(cos_theta_t <= 1) {
        color = color * (1 - opacity) + shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth) * opacity;
    }
    else {
        color = color * (1 - reflectance) + shader->Shade_Surface(render_world, ray, hit, intersection_point, normal, recursion_depth) * reflectance;

    }
    return color;
}

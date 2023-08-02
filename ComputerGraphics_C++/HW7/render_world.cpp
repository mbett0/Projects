//Student Name: Michael Bettencourt
//Student ID: 862158336
#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool enable_acceleration;

Render_World::~Render_World()
{
    for(auto a:all_objects) delete a;
    for(auto a:all_shaders) delete a;
    for(auto a:all_colors) delete a;
    for(auto a:lights) delete a;
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
std::pair<Shaded_Object,Hit> Render_World::Closest_Intersection(const Ray& ray) const
{
    //TODO;
    double small = std::numeric_limits<double>::max();
    std::pair<Shaded_Object,Hit> intersect;
    intersect.first = Shaded_Object();
    intersect.second = Hit();
    intersect.second.dist = -1;
    for(int i = 0; i < objects.size(); i++){
        Hit temp = objects.at(i).object->Intersection(ray, -1);
        if (temp.Valid() && temp.dist < small){
            small = temp.dist;
            intersect.first = objects.at(i);
            intersect.second = temp;
            Debug_Scope::level++;
            Pixel_Print("intesect test with ", objects.at(i).object->name, "; hit: ", temp);
            Debug_Scope::level--;
        }else{
            Debug_Scope::level++;
            Pixel_Print("no intersection with ", objects.at(i).object->name);
            Debug_Scope::level--;
        }
    }
    Debug_Scope::level++;
    Pixel_Print("closest intersection; obj: ",intersect.first.object->name, "; hit: ", small);
    Debug_Scope::level--;
    return intersect;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    ray.endpoint = camera.position;
    ray.direction = (camera.World_Position(pixel_index) - camera.position).normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth) const
{
    Pixel_Print("cast ray ", ray);
    //Debug_Scope::level++;
    vec3 color;
    std::pair<Shaded_Object, Hit> p = Closest_Intersection(ray);
    Shaded_Object o = p.first;
    Hit h = p.second;
    


    if(recursion_depth <= recursion_depth_limit && p.second.Valid()){
        color = o.shader->Shade_Surface(*this, ray, h, ray.Point(h.dist), o.object->Normal(ray, h), recursion_depth);
            Pixel_Print("call Shade_Surface with location ", ray.Point(h.dist), "; normal: ", o.object->Normal(ray,h));
            Debug_Scope::level++;
            Pixel_Print("flat shader; color: ", color);
            Debug_Scope::level--;
    }else{
        if(background_shader){
            h.uv=vec2(5,5);
            h.dist=-1;
            color = background_shader->Shade_Surface(*this, ray, h, color, color, recursion_depth);
            Pixel_Print("call Shade_Surface with location ", ray.Point(h.dist), " for background");
            
            Pixel_Print("flat shader; color: ", color);
        }else{
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
        }
    }
    return color;
}

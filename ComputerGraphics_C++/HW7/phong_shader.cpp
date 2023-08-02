#include "light.h"
#include "parse.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

Phong_Shader::Phong_Shader(const Parse* parse,std::istream& in)
{
    in>>name;
    color_ambient=parse->Get_Color(in);
    color_diffuse=parse->Get_Color(in);
    color_specular=parse->Get_Color(in);
    in>>specular_power;
}

vec3 Phong_Shader::Shade_Surface(const Render_World& render_world,const Ray& ray,const Hit& hit,
    const vec3& intersection_point,const vec3& normal,int recursion_depth) const
{
    vec3 color;
    if(render_world.ambient_color){
        color = render_world.ambient_color->Get_Color(hit.uv) * render_world.ambient_intensity * this->color_ambient->Get_Color(hit.uv);
    }
    // }else{
    //     color = this->color_ambient->Get_Color(hit.uv);
    // }
    
    //I = Ra*La + Rd*Ld*max(n*1,0) + Rs*Ls*max(cos x, 0)^a


    for(auto li : render_world.lights){
        vec3 light = li->position - intersection_point;
        vec3 refl = (-light + 2.0 * dot(light, normal) * normal).normalized();

        if(render_world.enable_shadows){
            Ray shad(intersection_point, light);
            std::pair<Shaded_Object, Hit> h = render_world.Closest_Intersection(shad);
            if(h.first.object && h.second.dist < light.magnitude()){
                return color;
            }
        }
        color += this->color_diffuse->Get_Color(hit.uv) * li->Emitted_Light(light) * std::max(dot(normal, light.normalized()), 0.0);

        color += this->color_specular->Get_Color(hit.uv) * li->Emitted_Light(light) * pow(std::max(dot(-ray.direction, refl.normalized()), 0.0), specular_power);
    }
    return color;
}

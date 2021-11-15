#include "Collider.h"

//Variables
Vec4 quaVec;
float a, b, c, D;
bool boxTest[6];

// Collision detection methods:
bool Collider::RaySphereCollisionDetected(Ray& ray, Sphere& sphere)
{
    quadraticEquation(ray, sphere);


    if (D < 0.0f)  // NO  Collision
    {
        return false;
    }
    else
    {
        return true;
    }

}

bool Collider::RayAABCollisionDetected(Ray& ray, AAB& box)
{
    bool detect;
    if (ray.dir.x == 0.0f)
    {
        detect = false;
        boxTest[0] = false;
        boxTest[3] = false;
    }

    if (ray.dir.y == 0.0f)
    {
        detect = false;
        boxTest[1] = false;
        boxTest[4] = false;
    }

    if (ray.dir.z == 0.0f)
    {
        detect = false;
        boxTest[2] = false;
        boxTest[5] = false;
    }

    if (ray.dir.x > 0.0f)
    {
        detect = true;
        boxTest[0] = true;
        boxTest[3] = false;
    }

    if (ray.dir.x < 0.0f)
    {
        detect = true;
        boxTest[0] = false;
        boxTest[3] = true;
    }

    if (ray.dir.y > 0.0f)
    {
        detect = true;
        boxTest[1] = true;
        boxTest[4] = false;
    }

    if (ray.dir.y < 0.0f)
    {
        detect = true;
        boxTest[1] = false;
        boxTest[4] = true;
    }

    if (ray.dir.z > 0.0f)
    {
        detect = true;
        boxTest[2] = true;
        boxTest[5] = false;
    }

    if (ray.dir.z < 0.0f)
    {
        detect = true;
        boxTest[2] = false;
        boxTest[5] = true;
    }

    return detect;
}

Vec3 Collider::RaySphereCollisionPoint(Ray& ray,Sphere& sphere)
{
    if (RaySphereCollisionDetected(ray, sphere))
    {
        //float t; float t1; float t2;
       
       float t;
        float t1 = (-b - sqrt(D)) / (2.0f * a); // t1 = -b - Sqrt(Discriminant)/2a
        float t2 = (-b + sqrt(D)) / (2.0f * a); // t2 = -b + Sqrt(Discriminant)/2a

        bool intersection = false;

        if (t1 >= 0 && t2 >= 0) {

            t = t1 > t2 ? t2 : t1;   
           // t = min(t1, t2);//min is to find the minimum of t1 or t2
            intersection = true;
        }
        else
        {
            if (t1 > 0 && t2 < 0)
            {
                t = t1;
                intersection = true;
            }
            else
            {
                if (t2 > 0 && t1 < 0)
                {
                    t = t2;
                    intersection = true;
                }
            }
        }
        if (intersection == true)
            return ray.currentPosition(t);
        else return Vec3(NAN, NAN, NAN); //-999, -999, -999
    }
  
}

Vec3 Collider::RayAABCollisionPoint(Ray& ray, AAB& box) // Check direction of ray
{
    if (RayAABCollisionDetected(ray, box) == true) {
        float t; Vec3 PI;
        bool intersectionPoint = false;

        if (boxTest[0] && intersectionPoint == false)
        {
            t = (-ray.start.x) / ray.dir.x;
            PI = ray.currentPosition(t); // return start + t * dir
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        if (boxTest[1] && intersectionPoint == false)
        {
            t = (-ray.start.y) / ray.dir.y;
            PI = ray.currentPosition(t);
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        if (boxTest[2] && intersectionPoint == false)
        {
            t = (-ray.start.z) / ray.dir.z;
            PI = ray.currentPosition(t);
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        if (boxTest[3] && intersectionPoint == false)
        {
            t = (box.rx - ray.start.x) / ray.dir.x;
            PI = ray.currentPosition(t);
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        if (boxTest[4] && intersectionPoint == false)
        {
            t = (box.ry - ray.start.y) / ray.dir.y;
            PI = ray.currentPosition(t);
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        if (boxTest[5] && intersectionPoint == false)
        {
            t = (box.rz - ray.start.z) / ray.dir.z;
            PI = ray.currentPosition(t);
            intersectionPoint = RayAABCollisionDetected(ray, box, PI);
        }

        return PI;
    }
}

// V^2 t^2 + 2(S-C).V *t +(S-C)^2 -R^2=0 -->A t^2 +Bt+C=0;
void Collider::quadraticEquation(Ray& ray, Sphere& sphere)
{
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// Calculating Discriminant D tells us whether the ray intersects the sphere | D = b^2 - 4ac   //
// D = (b * b) - 4 * a * c;                                                                    //
// a = quaVec.x | a = V^2                                                                      //
// b = quaVec.y | b = 2(S.V)                                                                   //
// c = quaVec.z | c = S^2 - r^2                                                                //
// discriminant = quaVec.w                                                                     //
// D < 0 (No intersection occurs)                                                              //
// D > 0 (2 distinct points of intersections)                                                  //
//D = 0 (ray is tangent to the sphere/ 1 solution)                                             //
// Smaller t is where the ray enters and larger is where the ray exits                         //
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    //A = V^2 = V.V
    a = (ray.dir.Dot(ray.dir)); //quaVec.x = ray.dir.Dot(ray.dir);

    //B = 2(S-C).V
    b = 2 * ((ray.start - sphere.position).Dot(ray.dir)); //quaVec.y = 2 * ((ray.start - sphere.position).Dot(ray.dir));
    
   //C = S^2 - r^2
   c = ((ray.start - sphere.position).Dot(ray.start - sphere.position)) - (pow(sphere.radius, 2)); //quaVec.z = ((ray.start - sphere.position).Dot(ray.start - sphere.position)) - pow(sphere.radius, 2);

   //D = (b * b) - 4 * a * c;  
   D = (b * b) + (- 4.0f )* a * c; // quaVec.w = (quaVec.y * quaVec.y) - 4 * (quaVec.x * quaVec.z); 
}

bool Collider::RayAABCollisionDetected(Ray& ray, AAB& box, Vec3 PI) // isCollided
{
    if ((PI.x >= 0.0f && PI.x <= box.rx) && (PI.y >= 0.0f && PI.y <= box.ry) && (PI.z >= 0.0f && PI.z <= box.rz))
    {
        return true;
    }
    else
    {
        return false;
    }
}



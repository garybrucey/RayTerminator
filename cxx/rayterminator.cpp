#include <iostream>
#include <math.h>

// Made a 3D vector
struct vec3
{
    int x;
    int y;
    int z;

    vec3(int X=0, int Y=0, int Z=0)
    {
        x = X;
        y = Y;
        z = Z;
    }
};

// See if the ray intersected.
bool rayIntersection(const vec3& pixel, const vec3& view, const int& objCount)
{
    int radius = 30;
    vec3 objCenter(0, objCount*radius*2, 150);
    vec3 hitPoint1;
    vec3 hitPoint2;

    // Ints are SUPER the wrong data type for this lol.
    int a = pow( (pixel.x - view.x), 2)
            + pow( (pixel.y - view.y), 2)
            + pow( (pixel.z - view.z), 2);

    int b = 2 * ( ( (pixel.x - view.x) * (view.x - objCenter.x) )
                + ( (pixel.y - view.y) * (view.y - objCenter.y) )
                + ( (pixel.z - view.z) * (view.z - objCenter.z) )
                );
    int c = pow( (view.x - objCenter.x), 2)
            + pow( (view.y - objCenter.y), 2)
            + pow( (view.z - objCenter.z), 2)
            - pow(radius, 2);

    // This will exceed 32 bits with a large image plane.
    int delta = pow(b, 2) - (4 * a * c);

    if (delta == 0)
    {
        // d=-b/2a
        int d = -b / (2 * a);
        // x = xA + d*(xB-xA)
        // y = yA + d*(yB-yA)
        // z = zA + d*(zB-zA)
        hitPoint1.x = view.x + (d * ( pixel.x - view.x) );
        hitPoint1.y = view.y + (d * ( pixel.y - view.y) );
        hitPoint1.z = view.z + (d * ( pixel.z - view.z) );
        return true;
    }
    else if (delta > 0)
    {
        // d1=(-b-sqrt(Delta))/(2a)
        // d2=(-b+sqrt(Delta))/(2a)
        int d = (-b - sqrt(delta) ) / (2 * a);
        hitPoint1.x = view.x + (d * ( pixel.x - view.x) );
        hitPoint1.y = view.y + (d * ( pixel.y - view.y) );
        hitPoint1.z = view.z + (d * ( pixel.z - view.z) );
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    int width = 640;
    int height = 480;
    int numObjects = 1;
    vec3 view(0,0,0);
    vec3 imagePlane(-width / 2, -height / 2, 100);
    vec3 pixel(0,0,0);

    std::cout << "P3 " << width << " " << height << " 255" << std::endl;

    for (int j=height; j > 0; --j)
    {
        for (int i=0; i < width; ++i)
        {
            // Find the 3D coordinate of the pixel on the image plane.
            pixel.x = imagePlane.x + i;
            pixel.y = imagePlane.y + j;
            pixel.z =  imagePlane.z;
            bool hitConfirmed = false;
            for (int objCount=0; objCount < numObjects; ++objCount)
            {
                if (rayIntersection(pixel, view, objCount) )
                {
                    hitConfirmed = true;
                    break;
                }
            }
            if (hitConfirmed)
            {
                std::cout << "255 255 255 " << std::endl;
            }
            else
            {
                std::cout << "0 0 0 " << std::endl;
            }
        }
    }

    return 0;
}

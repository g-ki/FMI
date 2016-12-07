//
//  Vector2.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/13/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Vector2__
#define __PacManGame__Vector2__

#include <cmath>

class Vector2 {
    
    float sqrLength, length;
    
public:
    float x, y;
    void Set(float, float);
    
    Vector2(float, float);
    Vector2() {}
    
    float GetSqrLength();
    float GetLength();
    
    void Normalize();
    
    Vector2& operator = (const Vector2&);
    Vector2 operator+(const Vector2&);
    Vector2 operator-(const Vector2&);
    Vector2 operator*(const float&);
    Vector2 operator/(const float&);
    bool operator== (const Vector2&);
    bool operator!= (const Vector2&);
    
    static Vector2 one();
    static Vector2 zero();
    static Vector2 up();
    static Vector2 right();
    
    static float Distance(Vector2, Vector2);
    
};

#endif /* defined(__PacManGame__Vector2__) */

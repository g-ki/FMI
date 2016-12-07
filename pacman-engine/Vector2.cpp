//
//  Vector2.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/13/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "Vector2.h"

void Vector2::Set(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2::Vector2(float x, float y){
    this->Set(x, y);
}

float Vector2::GetSqrLength(){
    return x*x + y*y;;
}

float Vector2::GetLength(){
    return sqrtf( x*x + y*y );
}

void Vector2::Normalize(){
    float len = GetLength();
    x /= len;
    y /= len;
}

//Operators
Vector2& Vector2::operator=(const Vector2& v){
    x = v.x;
    y = v.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& v2){
    Vector2 tmp;
    tmp.x = this->x + v2.x;
    tmp.y = this->y + v2.y;
    return tmp;
}

Vector2 Vector2::operator-(const Vector2& v2){
    Vector2 tmp;
    tmp.x = this->x - v2.x;
    tmp.y = this->y - v2.y;
    return tmp;
}

Vector2 Vector2::operator*(const float& s){
    Vector2 tmp;
    tmp.x = this->x*s;
    tmp.y = this->y*s;
    return tmp;
}

Vector2 Vector2::operator/(const float& s){
    return this->operator*(1/s);
}

bool Vector2::operator==(const Vector2& v2){
    return (this->x == v2.x && this->y == v2.y);
}

bool Vector2::operator!=(const Vector2& v2){
    return (this->x != v2.x || this->y != v2.y);
}


// STATIC
Vector2 Vector2::one(){
    return Vector2(1, 1);
}

Vector2 Vector2::zero(){
    return Vector2(0, 0);
}

Vector2 Vector2::up(){
    return Vector2(0, 1);
}

Vector2 Vector2::right(){
    return Vector2(1, 0);
}

float Vector2::Distance(Vector2 a, Vector2 b){
    return sqrtf((a.x - b.x)*(a.x - b.x)+(a.y - b.y)*(a.y - b.y));
}
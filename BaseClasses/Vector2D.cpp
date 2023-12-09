#include "Vector2D.h"

using namespace baseclass;

Vector2D::Vector2D()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(const Vector2D& other)
{
    this->x = other.x;
    this->y = other.y;
}

Vector2D& Vector2D::operator=(const Vector2D& other)
{
    if (this != &other) 
    {
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

Vector2D::Vector2D(Vector2D&& other) noexcept
{
    this->x = std::exchange(other.x, 0.0f);
    this->y = std::exchange(other.y, 0.0f);
}

Vector2D& Vector2D::operator=(Vector2D&& other) noexcept
{
    if (this != &other) {
        this->x = std::exchange(other.x, 0.0f);
        this->y = std::exchange(other.y, 0.0f);
    }
    return *this;
}

Vector2D Vector2D::operator+(Vector2D vectorB) const
{
    return Vector2D(this->x + vectorB.x, this->y + vectorB.y);
}

Vector2D Vector2D::operator+=(Vector2D vectorB)
{
    this->x += vectorB.x;
    this->y += vectorB.y;

    return *this;
}

Vector2D Vector2D::operator-(Vector2D vectorB) const
{
    return Vector2D(this->x - vectorB.x, this->y - vectorB.y);
}

Vector2D Vector2D::operator-=(Vector2D vectorB)
{
    this->x -= vectorB.x;
    this->y -= vectorB.y;

    return *this;
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(this->x * scalar, this->y * scalar);
}

Vector2D Vector2D::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}

bool Vector2D::operator!=(Vector2D vectorB) const
{
	return (std::fabs(this->x - vectorB.x) > epsilon) || (std::fabs(this->y - vectorB.y) > epsilon);
}

bool Vector2D::operator==(Vector2D vectorB) const
{
	return (std::fabs(this->x - vectorB.x) <= epsilon) && (std::fabs(this->y - vectorB.y) <= epsilon);
}

float Vector2D::Dot(Vector2D vectorB)
{
    return (this->x * vectorB.x + this->y * vectorB.y);
}

float Vector2D::Cross(const Vector2D& rhs)
{
	return x * rhs.y - y * rhs.x;
}


float Vector2D::GetMagnitude()
{
    return std::sqrt(x * x + y * y);
}

float Vector2D::SquareMagnitude()
{
    return x * x + y * y;
}

Vector2D Vector2D::Normalize()
{
    float magnitude = this->GetMagnitude();

    if(magnitude != 0.0f)
    {
        float normalizedX = this->x / magnitude;
        float normalizedY = this->y / magnitude;

        return Vector2D(normalizedX, normalizedY);
    }

    std::cerr << "Vector Magnitude is 0! Operation undefined!";
    return Vector2D(0.0f, 0.0f);
}

void Vector2D::Zero()
{
    this->x = 0;
    this->y = 0;}

std::ostream& baseclass::operator<<(std::ostream& os, const Vector2D& vector)
{
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}




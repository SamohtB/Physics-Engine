#include "Vector3D.h"

using namespace baseclass;

Vector3D::Vector3D()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D Vector3D::operator+(Vector3D vectorB) const
{
    return Vector3D(this->x + vectorB.x, this->y + vectorB.y, this->z + vectorB.z);
}

Vector3D Vector3D::operator+=(Vector3D vectorB)
{
    this->x += vectorB.x;
    this->y += vectorB.y;
    this->z += vectorB.z;

    return *this;
}

Vector3D Vector3D::operator-(Vector3D vectorB) const
{
    return Vector3D(this->x - vectorB.x, this->y - vectorB.y, this->z - vectorB.z);
}

Vector3D Vector3D::operator-=(Vector3D vectorB)
{
    this->x -= vectorB.x;
    this->y -= vectorB.y;
    this->z -= vectorB.z;

    return *this;
}

Vector3D Vector3D::operator*(float scalar) const
{
    return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

Vector3D Vector3D::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

float Vector3D::DotProduct(Vector3D vectorB)
{
    return (this->x * vectorB.x + this->y * vectorB.y + this->z * vectorB.z);
}

Vector3D Vector3D::CrossProduct(Vector3D vectorB)
{
    float newX = this->y * vectorB.z - this->z * vectorB.y;
    float newY = this->z * vectorB.x - this->x * vectorB.z;
    float newZ = this->x * vectorB.y - this->y * vectorB.x;

    return Vector3D(newX, newY, newZ);
}

float Vector3D::GetMagnitude()
{
    return std::sqrt(x * x + y *y + z * z);
}

float Vector3D::SquareMagnitude()
{
    return x * x + y *y + z * z;
}

Vector3D Vector3D::Normalize()
{
    float magnitude = this->GetMagnitude();

    if(magnitude != 0)
    {
        float normalizedX = this->x / magnitude;
        float normalizedY = this->y / magnitude;
        float normalizedZ = this->z / magnitude;

        return Vector3D(normalizedX, normalizedY, normalizedZ);
    }

    std::cerr << "Vector Magnitude is 0! Operation undefined!";
    return Vector3D(0.0f, 0.0f, 0.0f);
}

void Vector3D::Zero()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

std::ostream& baseclass::operator<<(std::ostream& os, const Vector3D& vector)
{
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}

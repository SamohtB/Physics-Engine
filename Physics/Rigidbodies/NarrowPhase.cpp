#include "NarrowPhase.h"

using namespace physics;

static inline float TransformToAxis(CollisionBox& box, Vector2D& axis)
{
	return
		box.halfSize.x * std::abs(axis.Dot(box.GetAxisVector(0))) +
		box.halfSize.y * std::abs(axis.Dot(box.GetAxisVector(1)));
}

static inline std::tuple<float,float> ProjectCorners(Vector2D corner[4], Vector2D axis)
{
	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::min();
	for(int i = 0; i < 4; i++)
	{
		Vector2D item = corner[i];
		float projection = item.Dot(axis);
		if(projection < min)
		{
			min = projection;
		}
		if(projection > max)
		{
			max = projection;
		}
	}

	return std::make_tuple(min, max);
}

static inline std::tuple<float, Vector2D> PointSegmentDistance(Vector2D point, Vector2D segmentA, Vector2D segmentB)
{
	Vector2D segmentAB = segmentB - segmentA;
	Vector2D segmentPointA = point - segmentA;
	Vector2D contactPoint = Vector2D();

	float projection = segmentPointA.Dot(segmentAB);
	float abMagnitudeSquared = segmentAB.SquareMagnitude();
	float d = projection / abMagnitudeSquared;

	if(d < 0)
	{
		contactPoint = segmentA;
	}
	else if(d > 1)
	{
		contactPoint = segmentB;
	}
	else
	{
		contactPoint = segmentA + segmentB * d;
	}

	float magnitude = (point - contactPoint).GetMagnitude();
	return std::make_tuple(magnitude, contactPoint);
}

Vector2D CollisionPrimitive::GetAxisVector(int i)
{
	auto matrix = this->body->transformMatrix.getMatrix();
	return Vector2D(matrix[i*4], matrix[i*4+1]);
}

bool IntersectionTests::BoxAndHalfSpace(CollisionBox& box, CollisionFloor& floor)
{
	float projectedRadius = TransformToAxis(box, floor.direction);

	float boxDistance = floor.direction.Dot(box.GetAxisVector(3)) - projectedRadius;

	return boxDistance <= floor.offset;
}

bool IntersectionTests::BoxAndBox(CollisionBox& one, CollisionBox& two)
{
	Vector2D oneCorners[4] = {
		Vector2D(-one.halfSize.x, -one.halfSize.y),
		Vector2D(one.halfSize.x, -one.halfSize.y),
		Vector2D(one.halfSize.x, one.halfSize.y),
		Vector2D(-one.halfSize.x, one.halfSize.y)
	};

	Vector2D twoCorners[4] = {
		Vector2D(-two.halfSize.x, -two.halfSize.y),
		Vector2D(two.halfSize.x, -two.halfSize.y),
		Vector2D(two.halfSize.x, two.halfSize.y),
		Vector2D(-two.halfSize.x, two.halfSize.y)
	};

	for(int i = 0; i < 4; i++)
	{
		sf::Vector2f tempPos = one.body->transformMatrix.transformPoint(sf::Vector2f(oneCorners[i].x, oneCorners[i].y));
		oneCorners[i] = Vector2D(tempPos.x, tempPos.y);

		tempPos = two.body->transformMatrix.transformPoint(sf::Vector2f(twoCorners[i].x, twoCorners[i].y));
		twoCorners[i] = Vector2D(tempPos.x, tempPos.y);
	}

	for(int i = 0; i < 4; i++)
	{
		Vector2D va = oneCorners[i];
		Vector2D vb = oneCorners[(i+1) % 4];

		Vector2D axis = vb - va;
		axis = axis.Normalize();

		float minA, minB, maxA, maxB;
		std::tie(minA, maxA) = ProjectCorners(oneCorners, axis);
		std::tie(minB, maxB) = ProjectCorners(twoCorners, axis);

		if(minA >= maxB || minB >= maxA)
		{
			return false;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		Vector2D va = twoCorners[i];
		Vector2D vb = twoCorners[(i+1) % 4];

		Vector2D axis = vb - va;
		axis = axis.Normalize();

		float minA, minB, maxA, maxB;
		std::tie(minA, maxA) = ProjectCorners(oneCorners, axis);
		std::tie(minB, maxB) = ProjectCorners(twoCorners, axis);

		if(minA >= maxB || minB >= maxA)
		{
			return false;
		}
	}

	return true;
}

unsigned CollisionDetector::BoxAndHalfSpace(CollisionBox& box, CollisionFloor& floor, CollisionData* data)
{
	if(data->contactsLeft <= 0) { return 0; }

	if(!IntersectionTests::BoxAndHalfSpace(box, floor)) { return 0;}

	Vector2D corners[4] = {
		Vector2D(-box.halfSize.x, -box.halfSize.y),	//upper left
		Vector2D(box.halfSize.x, -box.halfSize.y),		//upper right
		Vector2D(box.halfSize.x, box.halfSize.y),		//lower right
		Vector2D(-box.halfSize.x, box.halfSize.y)		//lower left
	};

	RigidbodyContact* contact = data->contacts;
	unsigned contactsUsed = 0;

	for(unsigned i = 0; i < 4; i++)
	{
		Vector2D vertexPos = corners[i];
		sf::Vector2f tempPos = box.body->transformMatrix.transformPoint(sf::Vector2f(vertexPos.x, vertexPos.y));

		vertexPos.x = tempPos.x;
		vertexPos.y = tempPos.y;

		float vertexDistance = vertexPos.Dot(floor.direction);

		if(vertexDistance <= floor.offset)
		{
			contact->contactPoint = floor.direction * (vertexDistance - floor.offset);
			contact->contactPoint += vertexPos;
			contact->contactNormal = floor.direction;
			contact->penetration = floor.offset - vertexDistance;

			contact->restitution = data->restitution;
			contact->body[0] = box.body;
			contact->body[1] = nullptr;

			data->AddContacts(1);
			contact = data->contacts;
			contactsUsed++;

			if(contactsUsed == (unsigned)data->contactsLeft) { return contactsUsed; }
		}
	}

	return contactsUsed;
}

unsigned CollisionDetector::BoxAndBox(CollisionBox& one, CollisionBox& two, CollisionData* data)
{
	RigidbodyContact contact[2];
	unsigned contactsUsed = 0;
	bool isTwo = false;
	float minDistance = std::numeric_limits<float>::max();

	if(!IntersectionTests::BoxAndBox(one, two)) { return 0; }

	Vector2D oneCorners[4] = {
		Vector2D(-one.halfSize.x, -one.halfSize.y),
		Vector2D(one.halfSize.x, -one.halfSize.y),
		Vector2D(one.halfSize.x, one.halfSize.y),
		Vector2D(-one.halfSize.x, one.halfSize.y)
	};

	Vector2D twoCorners[4] = {
		Vector2D(-two.halfSize.x, -two.halfSize.y),
		Vector2D(two.halfSize.x, -two.halfSize.y),
		Vector2D(two.halfSize.x, two.halfSize.y),
		Vector2D(-two.halfSize.x, two.halfSize.y)
	};

	for(int i = 0; i < 4; i++)
	{
		sf::Vector2f tempPos = one.body->transformMatrix.transformPoint(sf::Vector2f(oneCorners[i].x, oneCorners[i].y));
		oneCorners[i] = Vector2D(tempPos.x, tempPos.y);

		tempPos = two.body->transformMatrix.transformPoint(sf::Vector2f(twoCorners[i].x, twoCorners[i].y));
		twoCorners[i] = Vector2D(tempPos.x, tempPos.y);
	}

	for(int i = 0; i < 4; i++)
	{
		Vector2D p = oneCorners[i];

		for(int j = 0; j < 4; j++)
		{
			Vector2D va = twoCorners[j];
			Vector2D vb = twoCorners[(j + 1) % 4];
			Vector2D edge = vb - va;

			Vector2D axis = Vector2D(-edge.y, edge.x);
			axis = axis.Normalize();

			float magnitude;
			Vector2D contactPoint;
			std::tie(magnitude, contactPoint) = PointSegmentDistance(p, va, vb);

			if(magnitude < minDistance)
			{
				minDistance = magnitude;
				contact[0].contactPoint = contactPoint;
				contact[0].body[0] = one.body;
				contact[0].body[1] = two.body;
				contact[0].restitution = data->restitution;
				contact[0].contactNormal = axis;
				contact[0].penetration = magnitude;
				isTwo = false;
			}
			else if(abs(magnitude - minDistance) < 0.01f)
			{
				contact[1].contactPoint = contactPoint;
				contact[1].body[0] = one.body;
				contact[1].body[1] = two.body;
				contact[1].restitution = data->restitution;
				contact[1].contactNormal = axis;
				contact[1].penetration = magnitude;
				isTwo = true;
			}
		}
	}

	for(int i = 0; i < 4; i++)
	{
		Vector2D p = twoCorners[i];

		for(int j = 0; j < 4; j++)
		{
			Vector2D va = oneCorners[j];
			Vector2D vb = oneCorners[(j + 1) % 4];
			Vector2D edge = vb - va;

			Vector2D axis = Vector2D(-edge.y, edge.x);
			axis = axis.Normalize();

			float magnitude;
			Vector2D contactPoint;
			std::tie(magnitude, contactPoint) = PointSegmentDistance(p, va, vb);

			if(magnitude < minDistance)
			{
				minDistance = magnitude;
				contact[0].contactPoint = contactPoint;
				contact[0].body[0] = two.body;
				contact[0].body[1] = one.body;
				contact[0].restitution = data->restitution;
				contact[0].contactNormal = axis;
				contact[0].penetration = magnitude;
				isTwo = false;
			}
			else if(abs(magnitude - minDistance) < 0.01f)
			{
				contact[1].contactPoint = contactPoint;
				contact[1].body[0] = two.body;
				contact[1].body[1] = one.body;
				contact[1].restitution = data->restitution;
				contact[1].contactNormal = axis;
				contact[1].penetration = magnitude;
				isTwo = true;
			}
		}
	}

	*(data->contacts) = contact[0];
	data->AddContacts(1);
	contactsUsed++;

	if(isTwo)
	{
		*(data->contacts) = contact[1];
		data->AddContacts(1);
		contactsUsed++;
	}

	return contactsUsed;
}




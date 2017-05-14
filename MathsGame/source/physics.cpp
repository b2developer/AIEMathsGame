#include "physics.h"

//get a pointer to the singleton
PhysicsSolver* PhysicsSolver::getInstance()
{
	//is defined at the start of the program
	static PhysicsSolver* singleton = nullptr;

	//if the pointer contains no instance, assign one
	if (singleton == nullptr)
	{
		singleton = new PhysicsSolver();
	}

	return singleton;
}

//updates velocities by calculating a collision
void PhysicsSolver::applyImpulse(AdvancedCollision coll)
{
	//if the bodies both have infinite mass, don't apply impulses to them
	if (coll.A->invMass == 0 && coll.B->invMass == 0)
	{
		return;
	}

	//normal to the collision plane
	Vector2 n = coll.normal;

	//normal to the collision points of both objects, used for converting rotational energy to linear energy
	Vector2 rap = coll.A_contact.normal(NormalDirection::LEFT);
	Vector2 rbp = coll.B_contact.normal(NormalDirection::LEFT);

	//relative velocity of the points that collided (takes angular velocity into account)
	Vector2 rv = (coll.B->velocity + rbp * coll.B->angularVelocity) - (coll.A->velocity + rap * coll.A->angularVelocity);

	//combined bounciness of the two bodies
	float e = coll.A->restitution * coll.B->restitution;

	//simplifys the calculation of the inverted mass sum
	float rapdN = rap.dot(n);
	float rbpdN = rbp.dot(n);

	float invSum = coll.A->invMass + coll.B->invMass + rapdN * rapdN * coll.A->invInertia + rbpdN * rbpdN * coll.B->invInertia;

	//impulse scalar, when 'e' == 1, n * j is identical to the reflection formula
	float j = -(1 + e) *  rv.dot(n);
	j /= invSum;

	Vector2 impulse = n * j;

	//linear
	coll.A->velocity += impulse * -1.0f * coll.A->invMass;
	coll.B->velocity += impulse * coll.B->invMass;

	//angular
	coll.A->angularVelocity += rap.dot(impulse * -1.0f) * coll.A->invInertia;
	coll.B->angularVelocity += rbp.dot(impulse) * coll.B->invInertia;

	//recalculate relative velocity for friction
	rv = (coll.B->velocity + rbp * coll.B->angularVelocity) - (coll.A->velocity + rap * coll.A->angularVelocity);

	//get the velocity that moving along the collision plane
	Vector2 t = rv - (n * rv.dot(n));
	t.normalise();

	//combined friction
	float mu = sqrtf(coll.A->friction * coll.A->friction + coll.B->friction * coll.B->friction);

	//friction impulse scalar, negated as friction opposes movement
	float jt = -rv.dot(t);
	jt /= invSum;

	Vector2 frictionImpulse = t * jt * mu;

	//linear
	coll.A->velocity += frictionImpulse * -1.0f * coll.A->invMass;
	coll.B->velocity += frictionImpulse * coll.B->invMass;

	//angular
	coll.A->angularVelocity += rap.dot(frictionImpulse * -1.0f) * coll.A->invInertia;
	coll.B->angularVelocity += rbp.dot(frictionImpulse) * coll.B->invInertia;

}

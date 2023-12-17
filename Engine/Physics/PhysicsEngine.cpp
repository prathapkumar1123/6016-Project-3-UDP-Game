#include "PhysicsEngine.h"

#include <iostream>

PhysicsEngine::PhysicsEngine() {

}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::setVAOManager(VAOManager* mMeshManager) {
	this->mMeshManager = mMeshManager;
}

void PhysicsEngine::setObjects(std::vector<GameObject*>* objects) {
	this->mCollisionObjects = objects;
}

GameObject* PhysicsEngine::findShapeByUniqueID(unsigned int uniqueIDtoFind) {
	for (GameObject* pObject : *mCollisionObjects) {
		if (pObject->getUniqueID() == uniqueIDtoFind) {
			return pObject;
		}
	}

	return NULL;
}

GameObject* PhysicsEngine::findShapeByFriendlyName(std::string friendlyNameToFind) {
	for (GameObject* pObject : *mCollisionObjects) {
		if (pObject->simpleName == friendlyNameToFind) {
			return pObject;
		}
	}

	return NULL;
}

void PhysicsEngine::setSceneBounds(glm::vec3 minVertex, glm::vec3 maxVertex) {
	this->sceneBounds = new BoundingBox3D(minVertex, maxVertex);
}

// There's a ray cast code in chapter 5 of Ericson's book.
// What does this return? 
// It could return all the things that the ray hit.
// You could add some methods that only ray cast through specific objects (like only meshes)
// You could also do something where it returns the "closest" object (maybe form the startXYZ)
bool PhysicsEngine::rayCast(glm::vec3 startXYZ, glm::vec3 endXYZ, std::vector<sPhysicsProperties*>& vecObjectsHit) {
	return false;
}

void PhysicsEngine::updatePhysics(double deltaTime) {
	int loopCount = 0;
	for (GameObject* colObj : *mCollisionObjects) {

		/*std::cout << loopCount << std::endl;
		loopCount++*/;

		if (!colObj) {
			continue;
		}

		if (colObj->isOutOfBounds) {
			continue;
		}

		if (colObj->inverse_mass >= 0.0f) {
			colObj->update(deltaTime);
		}
		
		BoundingBox3D aBounds = BoundingBox3D(colObj->getBoundingBoxMin(), colObj->getBoundingBoxMax());
		colObj->isGoingOutOfBounds = !sceneBounds->contains(aBounds);

		for (GameObject* sceneObj : *mCollisionObjects) {

			if (sceneObj == nullptr)
				continue;

			if (sceneObj->isOutOfBounds) {
				continue;
			}

			if (colObj->simpleName == sceneObj->simpleName) {
				continue;
			}

			if (!colObj->isRigidBody || !sceneObj->isRigidBody) {
				continue;
			}

			BoundingBox3D bBounds = BoundingBox3D(sceneObj->getBoundingBoxMin(), sceneObj->getBoundingBoxMax());

			if (aBounds.intersects(bBounds)) {

				if (colObj->shapeType == AABB && sceneObj->shapeType == AABB) {
					sCollisionEvent* event = new sCollisionEvent();
					colObj->collisionWith[sceneObj->simpleName] = event;
					sceneObj->collisionWith[colObj->simpleName] = event;
					colObj->resolveCollisions();
					sceneObj->resolveCollisions();
				}

				if (colObj->shapeType == SPHERE &&
					sceneObj->shapeType == MESH_OF_TRIANGLES_INDIRECT) {
					if (this->m_Sphere_TriMeshIndirect_IntersectionTest(colObj, sceneObj)) {
						colObj->resolveCollisions();
						sceneObj->resolveCollisions();
					}
					else {
						colObj->collisionWith[sceneObj->simpleName] = nullptr;
						sceneObj->collisionWith[colObj->simpleName] = nullptr;
					}
				}

				if (colObj->shapeType == SPHERE &&
					sceneObj->shapeType == SPHERE) {
					if (this->m_Sphere_Sphere_IntersectionTest(sceneObj, colObj)) {
						colObj->resolveCollisions();
						sceneObj->resolveCollisions();
					}
					else {
						colObj->collisionWith[sceneObj->simpleName] = nullptr;
						sceneObj->collisionWith[colObj->simpleName] = nullptr;
					}
				}

			}
			else {
				colObj->collisionWith[sceneObj->simpleName] = nullptr;
				sceneObj->collisionWith[colObj->simpleName] = nullptr;
			}

		}
	}

}
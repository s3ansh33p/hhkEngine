/**
 * @file rigidbody.hpp
 * @author Sean McGinty (newfolderlocation@gmail.com)
 * @brief Basic rigid body for the engine
 * @version 1.0
 * @date 2021-12-12
 * 
 * @code{cpp}
 * // run the simulation - will need to make a nice way to add particles and render them etc.
 * RunRigidBodySimulation();
 * @endcode
 */

#define NUM_RIGID_BODIES 1

// 2D box shape. Physics engines usually have a couple different classes of shapes
// such as circles, spheres (3D), cylinders, capsules, polygons, polyhedrons (3D)...
typedef struct {
    int width;
    int height;
    int mass;
    int momentOfInertia;
} BoxShape;

// Calculates the inertia of a box shape and stores it in the momentOfInertia variable.
void CalculateBoxInertia(BoxShape *boxShape) {
    int m = boxShape->mass;
    int w = boxShape->width;
    int h = boxShape->height;
    boxShape->momentOfInertia = m * (w * w + h * h) / 12;
}

// Two dimensional rigid body
typedef struct {
    Vector2 position;
    Vector2 linearVelocity;
    int angle;
    int angularVelocity;
    Vector2 force;
    int torque;
    BoxShape shape;
} RigidBody;

// Global array of rigid bodies.
RigidBody rigidBodies[NUM_RIGID_BODIES];

// Prints the position and angle of each body on the output.
// We could instead draw them on screen.
void PrintRigidBodies() {
    for (int i = 0; i < NUM_RIGID_BODIES; ++i) {
        RigidBody *rigidBody = &rigidBodies[i];
        DebugYCounter += 2;
        Debug_Printf(10,DebugYCounter,true,0,"body[%i] p = (%i, %i), a = %i", i, rigidBody->position.x, rigidBody->position.y, rigidBody->angle);
    }
}

// Initializes rigid bodies with random positions and angles and zero linear and angular velocities.
// They're all initialized with a box shape of random dimensions.
void InitializeRigidBodies() {
    for (int i = 0; i < NUM_RIGID_BODIES; ++i) {
        RigidBody *rigidBody = &rigidBodies[i];
        rigidBody->position = (Vector2){10, 10};
        rigidBody->angle = 90; // between 0 and 360
        rigidBody->linearVelocity = (Vector2){0, 0};
        rigidBody->angularVelocity = 0;
        
        BoxShape shape;
        shape.mass = 10;
        shape.width = 3;
        shape.height = 2;
        CalculateBoxInertia(&shape);
        rigidBody->shape = shape;
    }
}

// Applies a force at a point in the body, inducing some torque.
void ComputeForceAndTorque(RigidBody *rigidBody) {
    Vector2 f = (Vector2){0, 100};
    rigidBody->force = f;
    // r is the 'arm vector' that goes from the center of mass to the point of force application
    Vector2 r = (Vector2){rigidBody->shape.width / 2, rigidBody->shape.height / 2};
    rigidBody->torque = r.x * f.y - r.y * f.x;
}

void RunRigidBodySimulation() {
    DebugYCounter = 5; // reset the output position
    int totalSimulationTime = 10; // The simulation will run for 10 seconds.
    int currentTime = 0; // This accumulates the time that has passed.
    int dt = 1; // Each step will take one second.
    
    InitializeRigidBodies();
    PrintRigidBodies();
    
    while (currentTime < totalSimulationTime) {
        
        for (int i = 0; i < NUM_RIGID_BODIES; ++i) {
            RigidBody *rigidBody = &rigidBodies[i];
            ComputeForceAndTorque(rigidBody);
            Vector2 linearAcceleration = (Vector2){rigidBody->force.x / rigidBody->shape.mass, rigidBody->force.y / rigidBody->shape.mass};
            rigidBody->linearVelocity.x += linearAcceleration.x * dt;
            rigidBody->linearVelocity.y += linearAcceleration.y * dt;
            rigidBody->position.x += rigidBody->linearVelocity.x * dt;
            rigidBody->position.y += rigidBody->linearVelocity.y * dt;
            int angularAcceleration = rigidBody->torque / rigidBody->shape.momentOfInertia;
            rigidBody->angularVelocity += angularAcceleration * dt;
            rigidBody->angle += rigidBody->angularVelocity * dt;
        }
        
        PrintRigidBodies();
        currentTime += dt;
    }
}

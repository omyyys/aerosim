#include <cstdio>
#include <iostream>
#include <string>
#include "../raylib/include/raylib.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr double GRAVITY = 9.81;

constexpr double SPEED_INCREMENT = 0.001;
constexpr double PITCH_INCREMENT = 0.005;
constexpr double ALTITUDE_INCREMENT = 0.01;
constexpr double BANK_INCREMENT = 0.005;

class Plane {
    public:
    const char *name;
    const double max_speed;
    const double max_operating_speed;
    const double stall_speed;
    const double critical_aoa;

    Plane(const char *n, double max_spd, double max_op_spd, double stall_spd, double crit_aoa)
        : name(n), max_speed(max_spd), max_operating_speed(max_op_spd), 
          stall_speed(stall_spd), critical_aoa(crit_aoa) {}
};

class Flight {
    private:
    const Plane &plane;
    double speed;
    double vertical_speed;
    double altitude;
    double pitch;
    double aoa;
    double bank_angle;

    public:
    Flight(const Plane& p) : plane(p), speed(0), vertical_speed(0), altitude(0), pitch(0), aoa(0), bank_angle(0) {}

    double get_speed() const { return speed; }
    double get_altitude() const { return altitude; }
    double get_pitch() const { return pitch; }
    double get_aoa() const { return aoa; }
    double get_bank_angle() const { return bank_angle; }

    void update() {
        if (IsKeyDown(KEY_W)) speed += SPEED_INCREMENT;
        if (IsKeyDown(KEY_S)) speed -= SPEED_INCREMENT;
        if (IsKeyDown(KEY_UP)) pitch += PITCH_INCREMENT;
        if (IsKeyDown(KEY_DOWN)) pitch -= PITCH_INCREMENT;
        if (IsKeyDown(KEY_SPACE)) altitude += ALTITUDE_INCREMENT;
        if (IsKeyDown(KEY_LEFT_SHIFT)) altitude -= ALTITUDE_INCREMENT;
        if (IsKeyDown(KEY_RIGHT)) bank_angle += BANK_INCREMENT;
        if (IsKeyDown(KEY_LEFT)) bank_angle -= BANK_INCREMENT;

        if (speed < 0) speed = 0;
        if (altitude < 0) altitude = 0;
        if (pitch > 90) pitch = 90;
        if (pitch < -90) pitch = -90;
    }
};

int main() {
    InitWindow(WIDTH, HEIGHT, "Aerosim");

    Plane plane("Test", 300, 100, 20, 10);
    Flight flight = Flight(plane);

    while (!WindowShouldClose()) {
        flight.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Altitude: %.2f ft", flight.get_altitude()), 10, 10, 20, BLACK);
        DrawText(TextFormat("Speed: %.2f kts", flight.get_speed()), 10, 40, 20, BLACK);
        DrawText(TextFormat("Pitch: %.2f°", flight.get_pitch()), 10, 70, 20, BLACK);
        DrawText(TextFormat("Bank angle: %.2f°", flight.get_bank_angle()), 10, 100, 20, BLACK);
        DrawText(TextFormat("AoA: %.2f°", flight.get_aoa()), 10, 130, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
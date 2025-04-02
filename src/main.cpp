#include <cstdio>
#include <iostream>
#include <cmath>
#include "../raylib/include/raylib.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

constexpr int FPS = 60;

constexpr double GRAVITY = 9.81;

constexpr double SPEED_INCREMENT = 0.1;
constexpr double PITCH_INCREMENT = 0.5;
constexpr double ALTITUDE_INCREMENT = 0.5;
constexpr double BANK_INCREMENT = 0.5;

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
    double x, y, z; // Position coordinates

public:
    Flight(const Plane& p) : plane(p), speed(0), vertical_speed(0), altitude(0), pitch(0), aoa(0), bank_angle(0), x(0), y(0), z(0) {}

    Plane get_plane() const { return plane; }
    double get_speed() const { return speed; }
    double get_altitude() const { return altitude; }
    double get_pitch() const { return pitch; }
    double get_aoa() const { return aoa; }
    double get_bank_angle() const { return bank_angle; }
    double get_vertical_speed() const { return vertical_speed; }
    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }

    void calculate_vertical_speed() {
        vertical_speed = speed * std::sin(pitch * (M_PI / 180.0)) * 60.0;
    }

    void update() {
        calculate_vertical_speed();
        aoa = pitch - bank_angle;

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

        double rad_pitch = pitch * (M_PI / 180.0);
        double rad_bank = bank_angle * (M_PI / 180.0);

        x += speed * std::cos(rad_pitch) * std::cos(rad_bank);
        y += speed * std::sin(rad_pitch);
        z += speed * std::cos(rad_pitch) * std::sin(rad_bank);
    }
};

int main() {
    InitWindow(WIDTH, HEIGHT, "Aerosim");
    SetTargetFPS(FPS);

    Plane plane("Test", 300, 100, 20, 10);
    Flight flight(plane);

    while (!WindowShouldClose()) {
        flight.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Plane: %s", flight.get_plane().name), 10, 10, 20, BLACK);
        DrawText(TextFormat("Altitude: %.2f ft", flight.get_altitude()), 10, 40, 20, BLACK);
        DrawText(TextFormat("Speed: %.2f kts", flight.get_speed()), 10, 70, 20, BLACK);
        DrawText(TextFormat("Pitch: %.2f°", flight.get_pitch()), 10, 100, 20, BLACK);
        DrawText(TextFormat("Bank angle: %.2f°", flight.get_bank_angle()), 10, 130, 20, BLACK);
        DrawText(TextFormat("AoA: %.2f°", flight.get_aoa()), 10, 160, 20, BLACK);
        DrawText(TextFormat("Vertical speed: %.2f ft/min", flight.get_vertical_speed()), 10, 190, 20, BLACK);
        DrawText(TextFormat("x: %.2f, y: %.2f, z: %.2f", flight.get_x(), flight.get_y(), flight.get_z()), 10, 220, 20, BLACK);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include <cstdio>
#include <string>

#include "../raylib/include/raylib.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

class Plane {
    public:

    const std::string name; 
 
    const double max_speed;
    const double max_operating_speed;
    const double stall_speed;
    const double critical_aoa;

    Plane(std::string n, double max_spd, double max_op_spd, double stall_spd, double crit_aoa)
        : name(n), max_speed(max_spd), max_operating_speed(max_op_spd), stall_speed(stall_spd), critical_aoa(crit_aoa) {}
};

class Flight {
    private:

    const Plane plane;
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

    void set_speed(double new_speed) { speed = new_speed; }
    void set_altitude(double new_altitude) { altitude = new_altitude; }
    void set_pitch(double new_pitch) { pitch = new_pitch; }
    void set_aoa(double new_aoa) { aoa = new_aoa; }

    bool is_overspeed() {
        return speed > plane.max_operating_speed;
    }

    bool is_stall() {
        return (aoa > plane.critical_aoa) || (speed < plane.stall_speed && vertical_speed < 0);
    }
};

int main() {
    InitWindow(WIDTH, HEIGHT, "Aerosim");

    Plane plane("Test", 300, 100, 20, 10);
    // Flight flight = Flight(plane);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawText(TextFormat("Speed: %ld", flight.get_speed()), 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

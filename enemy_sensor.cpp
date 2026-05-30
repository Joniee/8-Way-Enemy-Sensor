#include "enemy_sensor.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <cmath>

void EnemySensor::_bind_methods() {
    godot::ClassDB::bind_method(D_METHOD("get_8_wayVision", "enemy_pos", "map_grid", "tile_size", "map_size"), &EnemySensor::get_8_wayVision);
}

PackedFloat32Array EnemySensor::get_8_wayVision(const Vector2 &enemy_pos, const PackedByteArray &map_grid, int tile_size, const Vector2i &map_size) const {

    PackedFloat32Array distances;
    distances.resize(8);

    int start_x = static_cast<int>(enemy_pos.x / tile_size);
    int start_y = static_cast<int>(enemy_pos.y / tile_size);

    int dir_x[8] = { 0,  1, 1, 1, 0, -1, -1, -1 };
    int dir_y[8] = { -1, -1, 0, 1, 1,  1,  0, -1 };

    int max_distance = 48;

    for (int i = 0; i < 8; i++) {
        float distance_found = 1.0f;

        for (int j = 1; j <= max_distance; j++) {
            int check_x = start_x + (dir_x[i] * j);
            int check_y = start_y + (dir_y[i] * j);

            if (check_y < 0 || check_y >= map_size.y || check_x < 0 || check_x >= map_size.x) {
                distance_found = static_cast<float>(j - 1) / max_distance;
                break;
            }

            int index = (check_y * map_size.x) + check_x;
            uint8_t value = map_grid[index];

            if (value == 1) {
                distance_found = static_cast<float>(j) / max_distance;
                break;
            }
        }

        distances[i] = distance_found;
    }

    return distances;
}

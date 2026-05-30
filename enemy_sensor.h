#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


class EnemySensor : public Node {
	GDCLASS(EnemySensor, Node)

protected:
	static void _bind_methods();

public:
	EnemySensor() = default;
	~EnemySensor() override = default;

	PackedFloat32Array get_8_wayVision(const Vector2 &enemy_pos, const PackedByteArray &map_grid, int tile_size, const Vector2i &map_size) const;
};


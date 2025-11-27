#include <cub3d/game.h>

static t_vec2f	get_target_dir(const t_player *player);
static int		validate_target_pos(t_vec2f pos, const t_scene *scene);

void	update_player_dir(t_player *const player, const float delta)
{
	static const float	speed = 0.005f;
	const int			keys_held = player->keys_held;
	float				theta;

	theta = 0;
	if (keys_held & KEYCODELEFT)
		theta -= speed * delta;
	if (keys_held & KEYCODERIGHT)
		theta += speed * delta;
	player->dir = rot_vec2ff(player->dir, theta);
}

void	update_player_pos(t_scene *const scene, const float delta)
{
	static const float	speed = 0.005f;
	const t_vec2f		pos = scene->player.pos;
	const t_vec2f		target_dir = get_target_dir(&scene->player);
	const t_vec2f		target_pos
		= sum_vec2f(pos, mult_vec2ff(target_dir, speed * delta));

	if (!validate_target_pos((t_vec2f){target_pos.x, pos.y}, scene))
		scene->player.pos.x = target_pos.x;
	if (!validate_target_pos((t_vec2f){pos.x, target_pos.y}, scene))
		scene->player.pos.y = target_pos.y;
}

static t_vec2f	get_target_dir(const t_player *const player)
{
	const t_vec2f	dir = player->dir;
	const int		keys_held = player->keys_held;
	t_vec2f			target_dir;

	target_dir = (t_vec2f){0};
	if (keys_held & KEYCODEW)
		target_dir = sum_vec2f(target_dir, (t_vec2f){-dir.x, -dir.y});
	if (keys_held & KEYCODES)
		target_dir = sum_vec2f(target_dir, dir);
	if (keys_held & KEYCODEA)
		target_dir = sum_vec2f(target_dir, (t_vec2f){-dir.y, dir.x});
	if (keys_held & KEYCODED)
		target_dir = sum_vec2f(target_dir, (t_vec2f){dir.y, -dir.x});
	return (norm_vec2f(target_dir));
}

static int	validate_target_pos(const t_vec2f pos, const t_scene *const scene)
{
	const t_box	box = get_box(pos, 0.25f);

	return (check_cell_coll((t_vec2){box.ul.x, box.ul.y}, box, scene)
		|| check_cell_coll((t_vec2){box.dr.x, box.ul.y}, box, scene)
		|| check_cell_coll((t_vec2){box.ul.x, box.dr.y}, box, scene)
		|| check_cell_coll((t_vec2){box.dr.x, box.dr.y}, box, scene));
}

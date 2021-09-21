#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "game_object/GameObject.h"
#include "level/LevelData.h"
#include "geometry/mesh/WireFrame.h"
#include "texture/Texture.h"
#include <memory>

class Background : public GameObject
{
public:

	Background(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale, const std::string& id);
	~Background();

	Background(const Background& copy) = delete;
	Background& operator = (const Background& copy) = delete;

	std::unique_ptr<GameObject> Clone() override;

	void Draw();
	void PreDraw();
	void Update();

private:
	void Init();

private:

	unsigned int m_shader_pair_id;
};

#endif
#pragma once

#include "entities/GameObject.h"
#include <memory>

class Background : public GameObject
{
public:

	Background(WireFrame* mesh, Texture* texture, int shader, const float posX, const float posY, int scale);
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
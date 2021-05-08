#include "GameObjectLabel.h"

GameObjectLabel::GameObjectLabel(int ObjectType, int ObjectSubID)
{
	m_type = ObjectType;
	m_generatedID = ObjectSubID;

	m_label = ConstrID(m_type, m_generatedID);
}

const std::string GameObjectLabel::ConstrID(int ObjectType, int ObjectGeneratedID)
{
	return  std::to_string(m_type) + "." + std::to_string(m_generatedID);
}

bool GameObjectLabel::operator==(const GameObjectLabel& obj)
{
	return ((m_type == obj.m_type) && (m_generatedID == obj.m_generatedID));
}

#pragma once
#include <string>

class GameObjectLabel
{
	public:

		GameObjectLabel(int ObjectType, int ObjectSubID);

		int GetType() const { return m_type; }
		int GetGeneratedID() const { return m_generatedID; }
		std::string GetStrLabel() const { return m_label; }

		bool operator==(const GameObjectLabel&);

	private:

		const std::string ConstrID(int ObjectType, int ObjectGeneratedID);

	private:

		int m_type;
		int m_generatedID;
		std::string m_label;
};
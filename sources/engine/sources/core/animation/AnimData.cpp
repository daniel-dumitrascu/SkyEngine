#include "AnimData.h"



AnimData::AnimData() : m_frame_timmer(0)
{

}

AnimData::AnimData(const AnimData& copy) : m_frame_timmer(copy.m_frame_timmer)
{

}

AnimData::~AnimData()
{
	for (int i = 0; i < m_frames.size(); i++)
		delete m_frames[i];
}

void AnimData::PushStateLimit(int start_frame, int end_frame)
{
	m_state_limits.push_back(new AnimStateLimit(start_frame, end_frame));
}

bool AnimData::GetStateLimit(int index, int* start, int* end) 
{
	if (index < m_state_limits.size() && index >= 0)
	{
		*start = m_state_limits[index]->m_start_frame;
		*end = m_state_limits[index]->m_end_frame;

		return true;
	}
	else
		return false;
}
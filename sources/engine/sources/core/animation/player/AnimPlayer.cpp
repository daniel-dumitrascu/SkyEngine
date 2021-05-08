#include "AnimPlayer.h"


AnimPlayer::AnimPlayer(AnimData* anim_data) : m_curr_state_id(3),
										  	  m_curr_state_start(0),
											  m_curr_state_end(0),
											  m_curr_frame(-1)
{
	if (anim_data)
		m_anim_data = anim_data;

	SetState(m_curr_state_id);
}

AnimPlayer::AnimPlayer(const AnimPlayer& copy)
{

}

AnimPlayer::~AnimPlayer()
{
	m_anim_data = NULL;
}

void AnimPlayer::ResumeAnim()
{
	if (m_anim_data)
	{
		if (m_curr_frame == -1)
			m_curr_frame = m_curr_state_start;
		else
			return;

		/* Set the timmer for this animation state */
		m_anim_timer = m_anim_data->GetTimmer();
		m_anim_timer.Start();
	}
	else
		return;
}

void AnimPlayer::SuspendAnim()
{

}

bool AnimPlayer::PlayAnim()
{
	if (m_anim_timer.IsExceeded())
	{
		if (m_curr_frame >= m_curr_state_end)
		{
			m_curr_frame = 0;
			return false;
		}
		else
		{
			++m_curr_frame;
			return true;
		}
	}
	else
		return true;
}

void AnimPlayer::SetState(const int state_id)
{
	if (m_anim_data && (state_id != m_curr_state_id))
	{
		m_anim_data->GetStateLimit(state_id, &m_curr_state_start, &m_curr_state_end);
		m_curr_state_id = state_id;
		m_curr_frame = -1;
	}	
}

WireFrame* AnimPlayer::GetCurrentFrame()
{
	return m_anim_data->GetFrame(m_curr_frame);
}
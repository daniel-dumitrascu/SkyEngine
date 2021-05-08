#ifndef ANIM_PLAYER
#define ANIM_PLAYER

#include "animation/AnimData.h"
#include "../../time/Time.h"


class AnimPlayer
{
	public:

		AnimPlayer(AnimData* anim_data);
		AnimPlayer(const AnimPlayer& copy);
		~AnimPlayer();

		void ResumeAnim();
		void SuspendAnim();
		bool PlayAnim();
		AnimData* GetAnimData() { return m_anim_data; };

		void SetState(const int state_id);
		WireFrame* GetCurrentFrame();

	private:

		int m_curr_state_id;

		int m_curr_state_start;
		int m_curr_state_end;

		int m_curr_frame;

		AnimData* m_anim_data;
		CoreTime::Timer m_anim_timer;
};


#endif
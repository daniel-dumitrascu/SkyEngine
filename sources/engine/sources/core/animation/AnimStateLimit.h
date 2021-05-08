#ifndef ANIM_STATE_LIMIT
#define ANIM_STATE_LIMIT

struct AnimStateLimit
{
	AnimStateLimit(int s, int e) : m_start_frame(s), m_end_frame(e) { }

	int m_start_frame;
	int m_end_frame;
};

#endif
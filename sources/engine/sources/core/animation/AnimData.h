#ifndef RAW_ANIMATION_DATA_H
#define RAW_ANIMATION_DATA_H

#include "geometry/Polygon.h"
#include "geometry/mesh/WireFrame.h"
#include "animation/AnimStateLimit.h"
#include <iostream>
#include <vector>
#include <memory>


class AnimData
{

	public:

		AnimData(); 
		AnimData(const AnimData& copy);
		~AnimData() = default;

		void PushFrame(WireFrame* frame) { m_frames.push_back(std::unique_ptr<WireFrame>(frame)); }
		WireFrame* GetFrame(int index) { return m_frames[index].get(); }

		void PushStateLimit(int start_frame, int end_frame);
		bool GetStateLimit(int index, int* start, int* end);

		void SetTimmer(const unsigned int frames_timer) { m_frame_timmer = frames_timer; }
		unsigned int GetTimmer() { return m_frame_timmer; }

	private: 

		std::vector<std::unique_ptr<WireFrame>> m_frames;	/* Total frames */
		std::vector<std::unique_ptr<AnimStateLimit>> m_state_limits;	/* Limits for all states */

		int m_frame_timmer;
};

#endif
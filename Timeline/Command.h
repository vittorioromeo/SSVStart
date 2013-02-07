// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef COMMAND_H_
#define COMMAND_H_

namespace ssvs
{
	class Timeline;

	class Command
	{
		public:
			Timeline* timelinePtr;
			virtual ~Command();
			virtual void update(float mFrameTime);
			virtual void reset();		
	};
} /* namespace ssvs */
#endif /* COMMAND_H_ */

// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef WAIT_H_
#define WAIT_H_

#include "Command.h"

namespace ssvs
{
	class Wait: public Command
	{
		protected:
			float time;
			float currentTime;
			void update(float mFrameTime) override;
			void reset() override;

		public:
			Wait(float);
	};

} /* namespace sses */
#endif /* WAIT_H_ */

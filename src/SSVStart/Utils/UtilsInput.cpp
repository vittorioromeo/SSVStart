// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include <map>
#include "SSVStart/Utils/UtilsInput.h"

using namespace std;
using namespace sf;

namespace ssvs
{
	namespace Utils
	{
		template<typename T, typename U> class Bimap
		{
			private:
				map<T, U> map1;
				map<U, T> map2;

			public:
				Bimap(initializer_list<pair<T, U>> mPairs) { for(const auto& pair : mPairs) insert(pair); }
				void insert(pair<T, U> mPair) { map1[mPair.first] = mPair.second; map2[mPair.second] = mPair.first; }
				T at(U mValue) { return map2.at(mValue); }
				U at(T mValue) { return map1.at(mValue); }
				bool hasValue(T mValue) { return map1.find(mValue) != end(map1); }
				bool hasValue(U mValue) { return map2.find(mValue) != end(map2); }
		};

		const string keyPrefix{"k"};
		const string buttonPrefix{"b"};

		#define SSVS_INSERT_KEY(mName) {keyPrefix + #mName, Keyboard::Key::mName}
		Bimap<string, Keyboard::Key> keys
		{
			SSVS_INSERT_KEY(A),
			SSVS_INSERT_KEY(B),
			SSVS_INSERT_KEY(C),
			SSVS_INSERT_KEY(D),
			SSVS_INSERT_KEY(E),
			SSVS_INSERT_KEY(F),
			SSVS_INSERT_KEY(G),
			SSVS_INSERT_KEY(H),
			SSVS_INSERT_KEY(I),
			SSVS_INSERT_KEY(J),
			SSVS_INSERT_KEY(K),
			SSVS_INSERT_KEY(L),
			SSVS_INSERT_KEY(M),
			SSVS_INSERT_KEY(N),
			SSVS_INSERT_KEY(O),
			SSVS_INSERT_KEY(P),
			SSVS_INSERT_KEY(Q),
			SSVS_INSERT_KEY(R),
			SSVS_INSERT_KEY(S),
			SSVS_INSERT_KEY(T),
			SSVS_INSERT_KEY(U),
			SSVS_INSERT_KEY(W),
			SSVS_INSERT_KEY(X),
			SSVS_INSERT_KEY(Y),
			SSVS_INSERT_KEY(Z),
			SSVS_INSERT_KEY(Num0),
			SSVS_INSERT_KEY(Num1),
			SSVS_INSERT_KEY(Num2),
			SSVS_INSERT_KEY(Num3),
			SSVS_INSERT_KEY(Num4),
			SSVS_INSERT_KEY(Num5),
			SSVS_INSERT_KEY(Num6),
			SSVS_INSERT_KEY(Num7),
			SSVS_INSERT_KEY(Num8),
			SSVS_INSERT_KEY(Num9),
			SSVS_INSERT_KEY(Escape),
			SSVS_INSERT_KEY(LControl),
			SSVS_INSERT_KEY(LShift),
			SSVS_INSERT_KEY(LAlt),
			SSVS_INSERT_KEY(LSystem),
			SSVS_INSERT_KEY(RControl),
			SSVS_INSERT_KEY(RShift),
			SSVS_INSERT_KEY(RAlt),
			SSVS_INSERT_KEY(RSystem),
			SSVS_INSERT_KEY(Menu),
			SSVS_INSERT_KEY(LBracket),
			SSVS_INSERT_KEY(RBracket),
			SSVS_INSERT_KEY(SemiColon),
			SSVS_INSERT_KEY(Comma),
			SSVS_INSERT_KEY(Period),
			SSVS_INSERT_KEY(Quote),
			SSVS_INSERT_KEY(Slash),
			SSVS_INSERT_KEY(BackSlash),
			SSVS_INSERT_KEY(Tilde),
			SSVS_INSERT_KEY(Equal),
			SSVS_INSERT_KEY(Dash),
			SSVS_INSERT_KEY(Space),
			SSVS_INSERT_KEY(Return),
			SSVS_INSERT_KEY(BackSpace),
			SSVS_INSERT_KEY(Tab),
			SSVS_INSERT_KEY(PageUp),
			SSVS_INSERT_KEY(PageDown),
			SSVS_INSERT_KEY(End),
			SSVS_INSERT_KEY(Home),
			SSVS_INSERT_KEY(Insert),
			SSVS_INSERT_KEY(Delete),
			SSVS_INSERT_KEY(Add),
			SSVS_INSERT_KEY(Subtract),
			SSVS_INSERT_KEY(Multiply),
			SSVS_INSERT_KEY(Divide),
			SSVS_INSERT_KEY(Left),
			SSVS_INSERT_KEY(Right),
			SSVS_INSERT_KEY(Up),
			SSVS_INSERT_KEY(Down),
			SSVS_INSERT_KEY(Numpad0),
			SSVS_INSERT_KEY(Numpad1),
			SSVS_INSERT_KEY(Numpad2),
			SSVS_INSERT_KEY(Numpad3),
			SSVS_INSERT_KEY(Numpad4),
			SSVS_INSERT_KEY(Numpad5),
			SSVS_INSERT_KEY(Numpad6),
			SSVS_INSERT_KEY(Numpad7),
			SSVS_INSERT_KEY(Numpad8),
			SSVS_INSERT_KEY(Numpad9),
			SSVS_INSERT_KEY(F1),
			SSVS_INSERT_KEY(F2),
			SSVS_INSERT_KEY(F3),
			SSVS_INSERT_KEY(F4),
			SSVS_INSERT_KEY(F5),
			SSVS_INSERT_KEY(F6),
			SSVS_INSERT_KEY(F7),
			SSVS_INSERT_KEY(F8),
			SSVS_INSERT_KEY(F9),
			SSVS_INSERT_KEY(F10),
			SSVS_INSERT_KEY(F11),
			SSVS_INSERT_KEY(F12),
			SSVS_INSERT_KEY(F13),
			SSVS_INSERT_KEY(F14),
			SSVS_INSERT_KEY(F15),
			SSVS_INSERT_KEY(Pause)
		};
		#undef SSVS_INSERT_KEY

		#define SSVS_INSERT_BUTTON(mName) {buttonPrefix + #mName, Mouse::Button::mName}
		Bimap<string, Mouse::Button> buttons
		{
			SSVS_INSERT_BUTTON(Left),
			SSVS_INSERT_BUTTON(Right),
			SSVS_INSERT_BUTTON(Middle),
			SSVS_INSERT_BUTTON(XButton1),
			SSVS_INSERT_BUTTON(XButton2)
		};
		#undef SSVS_INSERT_BUTTON

		Keyboard::Key getKey(const string& mName)		{ return keys.at(mName); }
		Mouse::Button getButton(const string& mName)	{ return buttons.at(mName); }
		string getKeyName(Keyboard::Key mKey)			{ return keys.at(mKey); }
		string getButtonName(Mouse::Button mButton)		{ return buttons.at(mButton); }
		bool isKeyNameValid(const string& mName)		{ return keys.hasValue(mName); }
		bool isButtonNameValid(const string& mName)		{ return buttons.hasValue(mName); }
	}
}

// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVS_UTILS_INPUT
#define SSVS_UTILS_INPUT

#include "SSVStart/Global/Typedefs.hpp"
#include "SSVStart/Input/Input.hpp"
#include "SSVStart/GameSystem/GameState.hpp"

namespace ssvs
{
	using ITrigger = Input::Trigger;
	using IType = Input::Type;
	using IMode = Input::Mode;

	#define SSVS_KEY_PREFIX "k"
	#define SSVS_BTN_PREFIX "b"

	namespace Internal
	{
		inline const auto* getKKeyStrArray() noexcept
		{
			#define SSVS_INS_KEY(mName) SSVS_KEY_PREFIX #mName
			static std::string keys[]
			{
				SSVS_INS_KEY(A),
				SSVS_INS_KEY(B),
				SSVS_INS_KEY(C),
				SSVS_INS_KEY(D),
				SSVS_INS_KEY(E),
				SSVS_INS_KEY(F),
				SSVS_INS_KEY(G),
				SSVS_INS_KEY(H),
				SSVS_INS_KEY(I),
				SSVS_INS_KEY(J),
				SSVS_INS_KEY(K),
				SSVS_INS_KEY(L),
				SSVS_INS_KEY(M),
				SSVS_INS_KEY(N),
				SSVS_INS_KEY(O),
				SSVS_INS_KEY(P),
				SSVS_INS_KEY(Q),
				SSVS_INS_KEY(R),
				SSVS_INS_KEY(S),
				SSVS_INS_KEY(T),
				SSVS_INS_KEY(U),
				SSVS_INS_KEY(V),
				SSVS_INS_KEY(W),
				SSVS_INS_KEY(X),
				SSVS_INS_KEY(Y),
				SSVS_INS_KEY(Z),
				SSVS_INS_KEY(Num0),
				SSVS_INS_KEY(Num1),
				SSVS_INS_KEY(Num2),
				SSVS_INS_KEY(Num3),
				SSVS_INS_KEY(Num4),
				SSVS_INS_KEY(Num5),
				SSVS_INS_KEY(Num6),
				SSVS_INS_KEY(Num7),
				SSVS_INS_KEY(Num8),
				SSVS_INS_KEY(Num9),
				SSVS_INS_KEY(Escape),
				SSVS_INS_KEY(LControl),
				SSVS_INS_KEY(LShift),
				SSVS_INS_KEY(LAlt),
				SSVS_INS_KEY(LSystem),
				SSVS_INS_KEY(RControl),
				SSVS_INS_KEY(RShift),
				SSVS_INS_KEY(RAlt),
				SSVS_INS_KEY(RSystem),
				SSVS_INS_KEY(Menu),
				SSVS_INS_KEY(LBracket),
				SSVS_INS_KEY(RBracket),
				SSVS_INS_KEY(SemiColon),
				SSVS_INS_KEY(Comma),
				SSVS_INS_KEY(Period),
				SSVS_INS_KEY(Quote),
				SSVS_INS_KEY(Slash),
				SSVS_INS_KEY(BackSlash),
				SSVS_INS_KEY(Tilde),
				SSVS_INS_KEY(Equal),
				SSVS_INS_KEY(Dash),
				SSVS_INS_KEY(Space),
				SSVS_INS_KEY(Return),
				SSVS_INS_KEY(BackSpace),
				SSVS_INS_KEY(Tab),
				SSVS_INS_KEY(PageUp),
				SSVS_INS_KEY(PageDown),
				SSVS_INS_KEY(End),
				SSVS_INS_KEY(Home),
				SSVS_INS_KEY(Insert),
				SSVS_INS_KEY(Delete),
				SSVS_INS_KEY(Add),
				SSVS_INS_KEY(Subtract),
				SSVS_INS_KEY(Multiply),
				SSVS_INS_KEY(Divide),
				SSVS_INS_KEY(Left),
				SSVS_INS_KEY(Right),
				SSVS_INS_KEY(Up),
				SSVS_INS_KEY(Down),
				SSVS_INS_KEY(Numpad0),
				SSVS_INS_KEY(Numpad1),
				SSVS_INS_KEY(Numpad2),
				SSVS_INS_KEY(Numpad3),
				SSVS_INS_KEY(Numpad4),
				SSVS_INS_KEY(Numpad5),
				SSVS_INS_KEY(Numpad6),
				SSVS_INS_KEY(Numpad7),
				SSVS_INS_KEY(Numpad8),
				SSVS_INS_KEY(Numpad9),
				SSVS_INS_KEY(F1),
				SSVS_INS_KEY(F2),
				SSVS_INS_KEY(F3),
				SSVS_INS_KEY(F4),
				SSVS_INS_KEY(F5),
				SSVS_INS_KEY(F6),
				SSVS_INS_KEY(F7),
				SSVS_INS_KEY(F8),
				SSVS_INS_KEY(F9),
				SSVS_INS_KEY(F10),
				SSVS_INS_KEY(F11),
				SSVS_INS_KEY(F12),
				SSVS_INS_KEY(F13),
				SSVS_INS_KEY(F14),
				SSVS_INS_KEY(F15),
				SSVS_INS_KEY(Pause)
			};
			#undef SSVS_INS_KEY

			return keys;
		}

		inline const auto* getMBtnStrArray() noexcept
		{
			#define SSVS_INS_BTN(mName) SSVS_BTN_PREFIX #mName
			static std::string btns[]
			{
				SSVS_INS_BTN(Left),
				SSVS_INS_BTN(Right),
				SSVS_INS_BTN(Middle),
				SSVS_INS_BTN(XButton1),
				SSVS_INS_BTN(XButton2)
			};
			#undef SSVS_INS_BTN

			return btns;
		}

		inline const auto& getStrKKeyMap() noexcept
		{
			#define SSVS_INS_KEY(mName) {SSVS_KEY_PREFIX #mName, KKey::mName}
			static std::map<std::string, KKey> keys
			{
				SSVS_INS_KEY(A),
				SSVS_INS_KEY(B),
				SSVS_INS_KEY(C),
				SSVS_INS_KEY(D),
				SSVS_INS_KEY(E),
				SSVS_INS_KEY(F),
				SSVS_INS_KEY(G),
				SSVS_INS_KEY(H),
				SSVS_INS_KEY(I),
				SSVS_INS_KEY(J),
				SSVS_INS_KEY(K),
				SSVS_INS_KEY(L),
				SSVS_INS_KEY(M),
				SSVS_INS_KEY(N),
				SSVS_INS_KEY(O),
				SSVS_INS_KEY(P),
				SSVS_INS_KEY(Q),
				SSVS_INS_KEY(R),
				SSVS_INS_KEY(S),
				SSVS_INS_KEY(T),
				SSVS_INS_KEY(U),
				SSVS_INS_KEY(V),
				SSVS_INS_KEY(W),
				SSVS_INS_KEY(X),
				SSVS_INS_KEY(Y),
				SSVS_INS_KEY(Z),
				SSVS_INS_KEY(Num0),
				SSVS_INS_KEY(Num1),
				SSVS_INS_KEY(Num2),
				SSVS_INS_KEY(Num3),
				SSVS_INS_KEY(Num4),
				SSVS_INS_KEY(Num5),
				SSVS_INS_KEY(Num6),
				SSVS_INS_KEY(Num7),
				SSVS_INS_KEY(Num8),
				SSVS_INS_KEY(Num9),
				SSVS_INS_KEY(Escape),
				SSVS_INS_KEY(LControl),
				SSVS_INS_KEY(LShift),
				SSVS_INS_KEY(LAlt),
				SSVS_INS_KEY(LSystem),
				SSVS_INS_KEY(RControl),
				SSVS_INS_KEY(RShift),
				SSVS_INS_KEY(RAlt),
				SSVS_INS_KEY(RSystem),
				SSVS_INS_KEY(Menu),
				SSVS_INS_KEY(LBracket),
				SSVS_INS_KEY(RBracket),
				SSVS_INS_KEY(SemiColon),
				SSVS_INS_KEY(Comma),
				SSVS_INS_KEY(Period),
				SSVS_INS_KEY(Quote),
				SSVS_INS_KEY(Slash),
				SSVS_INS_KEY(BackSlash),
				SSVS_INS_KEY(Tilde),
				SSVS_INS_KEY(Equal),
				SSVS_INS_KEY(Dash),
				SSVS_INS_KEY(Space),
				SSVS_INS_KEY(Return),
				SSVS_INS_KEY(BackSpace),
				SSVS_INS_KEY(Tab),
				SSVS_INS_KEY(PageUp),
				SSVS_INS_KEY(PageDown),
				SSVS_INS_KEY(End),
				SSVS_INS_KEY(Home),
				SSVS_INS_KEY(Insert),
				SSVS_INS_KEY(Delete),
				SSVS_INS_KEY(Add),
				SSVS_INS_KEY(Subtract),
				SSVS_INS_KEY(Multiply),
				SSVS_INS_KEY(Divide),
				SSVS_INS_KEY(Left),
				SSVS_INS_KEY(Right),
				SSVS_INS_KEY(Up),
				SSVS_INS_KEY(Down),
				SSVS_INS_KEY(Numpad0),
				SSVS_INS_KEY(Numpad1),
				SSVS_INS_KEY(Numpad2),
				SSVS_INS_KEY(Numpad3),
				SSVS_INS_KEY(Numpad4),
				SSVS_INS_KEY(Numpad5),
				SSVS_INS_KEY(Numpad6),
				SSVS_INS_KEY(Numpad7),
				SSVS_INS_KEY(Numpad8),
				SSVS_INS_KEY(Numpad9),
				SSVS_INS_KEY(F1),
				SSVS_INS_KEY(F2),
				SSVS_INS_KEY(F3),
				SSVS_INS_KEY(F4),
				SSVS_INS_KEY(F5),
				SSVS_INS_KEY(F6),
				SSVS_INS_KEY(F7),
				SSVS_INS_KEY(F8),
				SSVS_INS_KEY(F9),
				SSVS_INS_KEY(F10),
				SSVS_INS_KEY(F11),
				SSVS_INS_KEY(F12),
				SSVS_INS_KEY(F13),
				SSVS_INS_KEY(F14),
				SSVS_INS_KEY(F15),
				SSVS_INS_KEY(Pause)
			};
			#undef SSVS_INS_KEY

			return keys;
		}

		inline const auto& getStrMBtnMap() noexcept
		{
			#define SSVS_INS_BTN(mName) {SSVS_BTN_PREFIX #mName, MBtn::mName}
			static std::map<std::string, MBtn> btns
			{
				SSVS_INS_BTN(Left),
				SSVS_INS_BTN(Right),
				SSVS_INS_BTN(Middle),
				SSVS_INS_BTN(XButton1),
				SSVS_INS_BTN(XButton2)
			};
			#undef SSVS_INS_BTN

			return btns;
		}
	}

	#undef SSVS_KEY_PREFIX
	#undef SSVS_BTN_PREFIX

	/// @brief Returns whether mId is a valid KKey name or not.
	inline bool isKKeyNameValid(const std::string& mId) noexcept
	{
		return Internal::getStrKKeyMap().count(mId) > 0;
	}

	/// @brief Returns whether mId is a valid MBtn name or not.
	inline bool isMBtnNameValid(const std::string& mId)	noexcept
	{
		return Internal::getStrMBtnMap().count(mId) > 0;
	}

	/// @brief Returns a KKey from a valid mId string identifier.
	inline KKey getKKey(const std::string& mId)	noexcept
	{
		SSVU_ASSERT(isKKeyNameValid(mId));
		return Internal::getStrKKeyMap().at(mId);
	}

	/// @brief Returns a MBtn from a valid mId string identifier.
	inline MBtn getMBtn(const std::string& mId)	noexcept
	{
		SSVU_ASSERT(isMBtnNameValid(mId));
		return Internal::getStrMBtnMap().at(mId);
	}

	/// @brief Returns the std::string identifier associated with the mKKey KKey.
	inline const auto& getKKeyName(KKey mKKey) noexcept
	{
		SSVU_ASSERT(mKKey != KKey::Unknown);
		return Internal::getKKeyStrArray()[static_cast<int>(mKKey)];
	}

	/// @brief Returns the std::string identifier associated with the mMBtn MBtn.
	inline const auto& getMBtnName(MBtn mMBtn) noexcept
	{
		return Internal::getMBtnStrArray()[static_cast<int>(mMBtn)];
	}

	/// @brief Shortcut to create a simple 2-state input that operates on a boolean value.
	/// @return Returns a reference to the newly created bind.
	inline auto& add2StateInput(GameState& mGameState, const ITrigger& mOn, bool& mValue, IType mType = IType::Always, IMode mMode = IMode::Overlap)
	{
		return mGameState.addInput(mOn, [&mValue](FT){ mValue = true; }, [&mValue](FT){ mValue = false; }, mType, mMode);
	}

	/// @brief Shortcut to create a simple 3-state input that operates on an int value.
	/// @details The value is set to 0 when no triggers are in use, to -1 when mOff is in use, to 1 when mOn is in use.
	/// @return Returns a pair containing references to the newly created binds.
	inline auto add3StateInput(GameState& mGameState, const ITrigger& mOff, const ITrigger& mOn, int& mValue, IType mType = IType::Always, IMode mMode = IMode::Overlap)
	{
		auto& b1(mGameState.addInput(mOff, [&mValue](FT){ mValue = -1; }, [&mValue](FT){ if(mValue == -1) mValue = 0; }, mType, mMode));
		auto& b2(mGameState.addInput(mOn, [&mValue](FT){ mValue = 1; }, [&mValue](FT){ if(mValue == 1) mValue = 0; }, mType, mMode));

		return std::make_pair<Input::Bind&, Input::Bind&>(b1, b2);
	}
}

#endif

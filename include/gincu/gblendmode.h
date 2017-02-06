#ifndef GBLENDMODE_H
#define GBLENDMODE_H

// code in this file is mostly a rewritten from SFML

namespace gincu {

enum class GameBlendFunc
{
	zero,
	one,
	sourceColor,
	oneMinusSourceColor,
	destColor,
	oneMinusDestColor,
	sourceAlpha,
	oneMinusSourceAlpha,
	destAlpha,
	oneMinusDestAlpha
};

enum class GameBlendEquation
{
	add,
	subtract,
	reverseSubtract
};

struct GameBlendModeChannel
{
	constexpr GameBlendModeChannel()
		: source(), dest(), func()
	{}

	constexpr GameBlendModeChannel(
		const GameBlendFunc source,
		const GameBlendFunc dest,
		const GameBlendEquation func = GameBlendEquation::add
	)
		: source(source), dest(dest), func(func)
	{}

	GameBlendFunc source;
	GameBlendFunc dest;
	GameBlendEquation func;
};

inline bool operator == (const GameBlendModeChannel & a, const GameBlendModeChannel & b)
{
	return a.source == b.source && a.dest == b.dest && a.func == b.func;
}

struct GameBlendMode
{
	constexpr GameBlendMode()
		: colorChannel{ GameBlendFunc::sourceAlpha, GameBlendFunc::oneMinusSourceAlpha },
			alphaChannel{ GameBlendFunc::one, GameBlendFunc::oneMinusSourceAlpha }
	{}

	constexpr GameBlendMode(
		const GameBlendFunc source,
		const GameBlendFunc dest,
		const GameBlendEquation func = GameBlendEquation::add
	)
		: colorChannel(source, dest, func), alphaChannel(source, dest, func)
	{}

	constexpr GameBlendMode(
		const GameBlendModeChannel colorChannel,
		const GameBlendModeChannel alpha
	)
		: colorChannel(colorChannel), alphaChannel(alpha)
	{}

	GameBlendModeChannel colorChannel;
	GameBlendModeChannel alphaChannel;
};

inline bool operator == (const GameBlendMode & a, const GameBlendMode & b)
{
	return a.colorChannel == b.colorChannel && a.alphaChannel == b.alphaChannel;
}

constexpr GameBlendMode blendModeAlpha(
	{ GameBlendFunc::sourceAlpha, GameBlendFunc::oneMinusSourceAlpha },
	{ GameBlendFunc::one, GameBlendFunc::oneMinusSourceAlpha });

constexpr GameBlendMode blendModeAdd(
	{ GameBlendFunc::sourceAlpha, GameBlendFunc::one },
	{ GameBlendFunc::one, GameBlendFunc::one });

constexpr GameBlendMode blendModeMultiply(GameBlendFunc::destColor, GameBlendFunc::zero);

constexpr GameBlendMode blendModeNone(GameBlendFunc::one, GameBlendFunc::zero);


} //namespace gincu



#endif
